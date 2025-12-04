#include "ServoControl.h"

// Basic class for controlling servos via Tinkerforge servo bricklet v2 hardware
class ServoControl {
	
	// ATTRIBUTES
	private:
		std::vector<IPConnection> ipcons;
		std::vector<ServoV2> bricklets;
		
		IPConnection ssr_ipcon;
		SolidStateRelayV2 ssr;
		
		std::vector<std::vector<std::int8_t>> inversion;
		std::vector<std::string> servo_uids;
		
		
		
	// METHODS
	public:
	
		// constructor
		ServoControl() {
			
			///////////////////////////////////////////////////
			// TO DO: import robot info from settings struct //
			///////////////////////////////////////////////////
			
			std::vector<std::string> servo_uids = {SERVO_UID_0, SERVO_UID_1, SERVO_UID_2};
			
			// create ipcon for solid state relay
			ipcon_create(&ssr_ipcon);
			solid_state_relay_v2_create(&ssr, SOLID_STATE_RELAY_UID, &ssr_ipcon);
			
			// Connect to brickd, interrupt execution in case of failure
			if(ipcon_connect(&ssr_ipcon, HOST, PORT) < 0) {
				fprintf(stderr, "Could not connect - ipcon for solid state bricklet failed\n");
				throw("Solid state relay ipcon connection failed\n");
			}
			
			// initialize IP connections and bricklets
			for (int i = 0; i < servo_uids.size(); i++) {
				IPConnection new_ipcon;
				ipcons.push_back(new_ipcon);
				ipcon_create(&ipcons[i]);
				
				// convert string to const char* for use as arg in servo_v2_create()
				const char* current_uid = servo_uids[i].c_str();
				
				ServoV2 new_bricklet;
				bricklets.push_back(new_bricklet);
				servo_v2_create(&bricklets[i], current_uid, &ipcons[i]);
				
				// connect ipcons to brickd, interrupt execution in case of failure
				if(ipcon_connect(&ipcons[i], HOST, PORT) < E_OK) {
					std::cerr << "Could not connect - ipcon for bricklet " << i << " with servo uid " << servo_uids[i] << "failed\n";
					throw("Ipcon connection failed\n");
				}
				
				// activate ssr
				solid_state_relay_v2_set_state(&ssr, true);
				
				// activate servos, set default values (pib standard, zero position)
				for (int j = 0; j < BRICKLET_CONNECTIONS; j++) {
					servo_v2_set_degree(&bricklets[i], j, -9000, 9000);
					servo_v2_set_pulse_width(&bricklets[i], j, 700, 2500);
					servo_v2_set_period(&bricklets[i], j, 19500);
					servo_v2_set_motion_configuration(&bricklets[i], j, 100000, 50000, 50000);
					
					servo_v2_set_position(&bricklets[i], j, 0);
					servo_v2_set_enable(&bricklets[i], j, true);   // Pass order to bricklet
					
					//std::cout << "Bricklet " << i << ", Servo " << j << " activated.\n";
				}
				
			}
			
			// initialize inversion vector
			// TO DO: import info from info.txt
			
			for (int i = 0; i < servo_uids.size(); i++) {
				
				std::vector<std::int8_t> new_vec;
				for (int j = 0; j < BRICKLET_CONNECTIONS; j++) {
					new_vec.push_back(1);
				}
				
				inversion.push_back(new_vec);
			}
			
			// magic number(s) - inversion data for current build
			inversion[0][3] = -1; 
			
		}
		
		// destructor
		~ServoControl() {
			
			std::cout << "\nDisabling bricklet connections\n";
			
			for (int i = 0; i < bricklets.size(); i++) {
				for (int j = 0; j < BRICKLET_CONNECTIONS; j++) {
						if (servo_v2_set_enable(&bricklets[i], j, false) < E_OK) {
						std::cout << "ERROR: could not disable bricklet " << i << " - servo " << j << "\n";
					}
				}
				
				servo_v2_destroy(&bricklets[i]);
				ipcon_destroy(&ipcons[i]); // calls ipcon_disconnect internally
			}
			
			// turn off ssd
			solid_state_relay_v2_set_state(&ssr, false);
			
			std::cout << "\nDisabling solid state relay connection.\n";
			solid_state_relay_v2_destroy(&ssr);
			ipcon_destroy(&ssr_ipcon); // Calls ipcon_disconnect internally	
			
		}
		
		// set servo positions
		
		int set_servo_pos(int bricklet, int servo, int pos) {
			servo_v2_set_position(&bricklets[bricklet], servo, pos * inversion[bricklet][servo]);
			servo_v2_set_enable(&bricklets[bricklet], servo, true);
			return 0;
		}
		
		// get all relevant information on a specific servo
		// TO DO: CHANGE OUTPUT TO SOMETHING MANAGEABLE (e.g. DIAGNOSTIC INFO STRUCT)
		int get_servo_pos(int b, int s) {
			int16_t ret;
			int16_t* ret_pos = &ret;
			ServoV2* bricklet_pos = &bricklets[b];
			
			servo_v2_get_position(bricklet_pos, s, ret_pos);
			
			return ret;
		}
		
		// return servo bricklet vector
		// ONLY FOR TESTING - BRICKLET POINTERS SHOULD BE PRIVATE
		/*
		std::vector<ServoV2> get_bricklets() {
			return bricklets;
		}
		*/
		
		// return ipcon vector
		// ONLY FOR TESTING - IPCON POINTERS SHOULD BE PRIVATE
		/*
		std::vector<IPConnection> get_ipcons() {
			return ipcons;
		}
		*/
		
		// save current position to csv file.
		// TO DO: fstream implementation
		int save_pose(std::string save_file) {
			std::string save_str = "";
			
			for (int i = 0; i < bricklets.size(); i++) {
				for (int j = 0; j < BRICKLET_CONNECTIONS; j++) {
					save_str += std::to_string(get_servo_pos(i,j));
				}
				
				save_str += "\n";
			}
			
			return 0;
		}
	
		int load_pose(std::string save_file) {
			return 0;
		}
	
};
