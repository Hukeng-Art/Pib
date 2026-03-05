#include "Robot.h"


std::vector<std::string> split_line(std::string line, std::string del);


Robot::Robot(std::string settings_path) {
	
	robotSettingsStruct settings = read_settings(settings_path);
	
	servos = new ServoControl(settings);
	sensors = new SensorControl();
	network = new NetworkControl();
	audiovideo = new AudioVideoControl(settings);
	
	behavior = NULL;
}


Robot::~Robot() {
	
	if (behavior) {
		delete behavior;
	}
	
	delete servos;
	delete sensors;
	delete network;
	delete audiovideo;
	
}

// pass specific behaviour object
void Robot::assign_behavior(Behavior* new_behavior) {
	
	behavior = new_behavior;
	
	behavior->assign_servos(servos);
	behavior->assign_sensors(sensors);
	behavior->assign_network(network);
	behavior->assign_audiovideo(audiovideo);
}


void Robot::run_behavior() {
	if (!behavior) {
		std::cout << "Can't run behavior - no behavior assigned!\n";
	} else {
		behavior->set_running(true);
		behavior->run();
	}
}

void Robot::reset_defaults() {
	servos->reset_servos();
	audiovideo->free_audios();
	audiovideo->free_images();
}

// create a robot settings struct based on contents of settings file
robotSettingsStruct Robot::read_settings(std::string settings_path) {
	robotSettingsStruct settings;
	
	std::ifstream f(settings_path);
	std::string line;
	
	while (getline(f,line)) { // LOOP THROUGH ALL LINES
		std::vector<std::string> current_line = split_line(line," ");
		
		if (current_line[0] == "#HOST") {
			settings.host = current_line[1].c_str();
		}
		
		if (current_line[0] == "#PORT") {
			settings.port = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#SOLID_STATE_RELAY_UIDS") {
			for (uint8_t i = 0; i < current_line.size(); i++) {
				settings.solid_state_relay_uids.push_back(current_line[i].c_str());
			}
		}
		
		if (current_line[0] == "#SERVO_BRICKLET_UIDS") {
			for (uint8_t i = 0; i < current_line.size(); i++) {
				settings.servo_bricklet_uids.push_back(current_line[i].c_str());
			}
		}
		
		
		if (current_line[0] == "#DEFAULT_DEGREE_MIN") {
			settings.default_servo_degree_min = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_DEGREE_MAX") {
			settings.default_servo_degree_max = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_PULSE_WIDTH_MIN") {
			settings.default_servo_pulse_width_min = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_PULSE_WIDTH_MAX") {
			settings.default_servo_pulse_width_max = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_PERIOD") {
			settings.default_servo_period = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_VEL") {
			settings.default_servo_vel = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_ACC") {
			settings.default_servo_acc = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#DEFAULT_DEC") {
			settings.default_servo_dec = std::stoi(current_line[1]);
		}
		
		if (current_line[0] == "#SERVO_INVERSION") {
			
			getline(f,line);
			
			while (line != "#END_SERVO_INVERSION") {
				
				std::vector<int8_t> new_inversion_vec;
				
				std::vector<std::string> inversion_info = split_line(line, ",");
				
				for (std::string value : inversion_info) {
					new_inversion_vec.push_back(stoi(value));
				}
				
				settings.servo_inversion.push_back(new_inversion_vec);
				
				getline(f,line);
			}
		}
	}
	
	return settings;
	
	
}



// UTILITY FUNCS

std::vector<std::string> split_line(std::string line, std::string del) {
	
	std::vector<std::string> substring_vec;
	size_t pos_start = 0;
	size_t pos_end;
	std::string token;
		
	while ((pos_end = line.find(del, pos_start)) != std::string::npos) { 
		token = line.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + del.size();
		substring_vec.push_back(token);
	}
	
	substring_vec.push_back(line.substr(pos_start));

	return substring_vec;
}
