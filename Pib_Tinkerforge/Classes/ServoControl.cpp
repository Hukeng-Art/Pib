#include "ServoControl.h"

ServoControl::ServoControl(robotSettingsStruct settings) {
	
	// set default servo settings
	default_servo_degree_min = settings.default_servo_degree_min;
	default_servo_degree_max = settings.default_servo_degree_max;
	default_servo_pulse_width_min = settings.default_servo_pulse_width_min;
	default_servo_pulse_width_max = settings.default_servo_pulse_width_max;
	default_servo_period = settings.default_servo_period;
	default_servo_vel = settings.default_servo_vel;
	default_servo_acc = settings.default_servo_acc;
	default_servo_dec = settings.default_servo_dec;
	
	
	// set up ssr IP connections and ssrs
	for (std::string uid : settings.solid_state_relay_uids) {
		IPConnection new_ipcon;
		SolidStateRelayV2 new_ssr;
		
		ipcon_create(&new_ipcon);
		solid_state_relay_v2_create(&new_ssr, uid.c_str(), &new_ipcon);
		
		if( ipcon_connect(&new_ipcon, settings.host.c_str(), settings.port) < 0) {
			fprintf(stderr, "Could not connect - ipcon for solid state relay failed.\n");
			throw("Solid state relay ipcon connection failed\n");
		}
		
		ssr_ipcons.push_back(new_ipcon);
		ssrs.push_back(new_ssr);
	}
	
	// set up servo bricklet IP connections and servo bricklets
	for (std::string uid : settings.servo_bricklet_uids) {
		IPConnection new_ipcon;
		ServoV2 new_bricklet;
		
		ipcon_create(&new_ipcon);
		servo_v2_create(&new_bricklet, uid.c_str(), &new_ipcon);
		
		if(ipcon_connect(&new_ipcon, settings.host.c_str(), settings.port) < 0) {
			fprintf(stderr, "Could not connect - ipcon for bricklet failed\n");
			throw("Solid state relay ipcon connection failed\n");
		}
		
		bricklet_ipcons.push_back(new_ipcon);
		bricklets.push_back(new_bricklet);
		
	}
	
	// activate ssrs
	for (SolidStateRelayV2 ssr : ssrs) {
		solid_state_relay_v2_set_state(&ssr, true);
	}
	
	// activate servos, set default values (pib standard, zero position)
	reset_servos();
	
	// initialize inversion vector
	for (uint8_t i = 0; i < bricklets.size(); i++) {
		
		std::vector<std::int8_t> new_vec;
		for (uint8_t j = 0; j < BRICKLET_CONNECTIONS; j++) {
			new_vec.push_back(settings.servo_inversion[i][j]);
		}
		
		inversion.push_back(new_vec);
	}
	
	std::cout << "Servo Control online.\n";
	
}


ServoControl::~ServoControl() {
	
	// disable bricklet connections and free bricklets
	std::cout << "Disabling bricklet connections\n";
	for (uint8_t i = 0; i < bricklets.size(); i++) {
		for (uint8_t j = 0; j < BRICKLET_CONNECTIONS; j++) {
				if (servo_v2_set_enable(&bricklets[i], j, false) < E_OK) {
				std::cout << "ERROR: could not disable bricklet " << i << " - servo " << j << "\n";
			}
		}
		
		servo_v2_destroy(&bricklets[i]);
		ipcon_destroy(&bricklet_ipcons[i]); // call ipcon_disconnect internally
	}
	
	// disable ssr connections and free ssrs
	std::cout << "Disabling ssd connections\n";
	for (uint8_t i = 0; i < ssrs.size(); i++) {
		solid_state_relay_v2_set_state(&ssrs[i], false);
		solid_state_relay_v2_destroy(&ssrs[i]);
		ipcon_destroy(&ssr_ipcons[i]); // call ipcon_disconnect internally	
	}
	
	std::cout << "Servo Control offline.\n";
	
}


// set servo positions
void ServoControl::set_servo_pos(uint8_t b, uint8_t s, int16_t pos) {
	servo_v2_set_position(&bricklets[b], s, pos * inversion[b][s]);
	servo_v2_set_enable(&bricklets[b], s, true);
}


// get position info on specific servo 
// position factors in inversion
int16_t ServoControl::get_servo_pos(uint8_t b, uint8_t s) {
	int16_t ret;
	int16_t* ret_ptr = &ret;
	ServoV2* bricklet_ptr = &bricklets[b];
	
	servo_v2_get_position(bricklet_ptr, s, ret_ptr);
	
	return ret * inversion[b][s];
}


// reset all servos to default parameters and zero position
void ServoControl::reset_servos() {
	for (uint8_t i; i < bricklets.size(); i++) {
		for (uint8_t j; j < BRICKLET_CONNECTIONS; j++) {
			
			set_servo_params(i,j);
			
			servo_v2_set_position(&bricklets[i], j, 0);
			servo_v2_set_enable(&bricklets[i], j, true); 
			
		}
	}
}


// set parameters for select servo, reset to defaults if no values are passed
void ServoControl::set_servo_params(uint8_t b,
					  uint8_t s,
					  int16_t min_degree,
					  int16_t max_degree,
					  uint32_t min_pulse_width,
					  uint32_t max_pulse_width,
					  uint32_t period,
					  uint32_t vel,
					  uint32_t acceleration,
					  uint32_t deceleration) {
						  
	ServoV2 *bricklet_ptr = &bricklets[b];
	
	servo_v2_set_degree(bricklet_ptr, s, min_degree, max_degree);
	servo_v2_set_pulse_width(bricklet_ptr, s, min_pulse_width, max_pulse_width);
	servo_v2_set_period(bricklet_ptr, s, period);
	servo_v2_set_motion_configuration(bricklet_ptr, s, vel, acceleration, deceleration);
				
}


// save current position to csv file.
// TO DO: fstream implementation
void ServoControl::save_pose(std::string save_file) {
	std::string save_str = "";
	
	for (uint8_t i = 0; i < bricklets.size(); i++) {
		for (uint8_t j = 0; j < BRICKLET_CONNECTIONS; j++) {
			save_str += std::to_string(get_servo_pos(i,j));
		}
		
		save_str += "\n";
	}
	
}


void ServoControl::load_pose(std::string save_file) {
	
}

