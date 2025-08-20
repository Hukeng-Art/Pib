#include <stdio.h>
#include <iostream>
#include <string>

#include "ip_connection.h"
#include "brick_hat.h"
#include "bricklet_servo_v2.h"

#define HOST "localhost"
#define PORT 4223

#define HAT_UID "27PE"
#define BRICKLET_1_UID "2cPS"
#define BRICKLET_2_UID "2cPT"
#define BRICKLET_3_UID "SGA"

#define CHECK_ENABLED false;

int main(void) {
	
	std::string bricklet_code = "";
	std::string servo_code = "";
	std::string requested_position = "";
	
	int b_code;
	int s_code;
	int r_pos;
	
	int16_t* ret_pos;
	
	bool valid_input = false;
	bool command_enabled = true;
	
	bool enable = true;
	bool disable = false;
	bool* ret_enable = &enable;
	
	// Create IP connections to bricklets
	IPConnection ipcon_b1;
	IPConnection ipcon_b2;
	IPConnection ipcon_b3;
	
	ipcon_create(&ipcon_b1);
	ipcon_create(&ipcon_b2);
	ipcon_create(&ipcon_b3);
	
	ServoV2 bricklet_1;
	servo_v2_create(&bricklet_1, BRICKLET_1_UID, &ipcon_b1);
	ServoV2 bricklet_2;
	servo_v2_create(&bricklet_2, BRICKLET_2_UID, &ipcon_b2);
	ServoV2 bricklet_3;
	servo_v2_create(&bricklet_3, BRICKLET_3_UID, &ipcon_b3);
	
	
	if(ipcon_connect(&ipcon_b1, HOST, PORT) < E_OK) {
        fprintf(stderr, "Could not connect - ipcon for b1 failed\n");
        return 1;
    }
    if(ipcon_connect(&ipcon_b2, HOST, PORT) < E_OK) {
        fprintf(stderr, "Could not connect - ipcon for b2 failed\n");
        return 1;
    }
    if(ipcon_connect(&ipcon_b3, HOST, PORT) < E_OK) {
        fprintf(stderr, "Could not connect - ipcon for b3 failed\n");
        return 1;
    }
    
	// set servos to default pib params and pos 0
	for (int i = 0; i < 10; i++) {
		servo_v2_set_degree(&bricklet_1, i, -9000, 9000);
		servo_v2_set_pulse_width(&bricklet_1, i, 700, 2500);
		servo_v2_set_period(&bricklet_1, i, 19500);
		servo_v2_set_motion_configuration(&bricklet_1, i, 100000, 50000, 50000);
		
		servo_v2_set_position(&bricklet_1, i, 0);
		servo_v2_set_enable(&bricklet_1, i, true);   // Pass order to bricklet
	}
	for (int i = 0; i < 10; i++) {
		servo_v2_set_degree(&bricklet_2, i, -9000, 9000);
		servo_v2_set_pulse_width(&bricklet_2, i, 700, 2500);
		servo_v2_set_period(&bricklet_2, i, 19500);
		servo_v2_set_motion_configuration(&bricklet_2, i, 100000, 50000, 50000);
		
		servo_v2_set_position(&bricklet_2, i, 0);
		servo_v2_set_enable(&bricklet_2, i, true);   // Pass order to bricklet
	}
	for (int i = 0; i < 10; i++) {
		servo_v2_set_degree(&bricklet_3, i, -9000, 9000);
		servo_v2_set_pulse_width(&bricklet_3, i, 700, 2500);
		servo_v2_set_period(&bricklet_3, i, 19500);
		servo_v2_set_motion_configuration(&bricklet_3, i, 100000, 50000, 50000);
		
		servo_v2_set_position(&bricklet_3, i, 0);
		servo_v2_set_enable(&bricklet_3, i, true);   // Pass order to bricklet
	}
	
	
	/// SERVO CONTROL TESTS ///
	while (command_enabled) {
		
		while (!valid_input) {
			std::cout << "Please enter a bricklet code (1-3), a servo code (0-9) and a desired position (-9000 to 9000). Type q to quit.\n";
			std::cin >> bricklet_code >> servo_code >> requested_position;
		
			if (bricklet_code == "q" || servo_code == "q" || requested_position == "q") {        // quit interactive mode
				command_enabled = false;
				break;
			} else {
				try {
					b_code = stoi(bricklet_code);
					s_code = stoi(servo_code);
					r_pos = stoi(requested_position); 
					
					if (-1 < s_code < 10 && -9001 < r_pos < 9001) {
						if (b_code == 1) {
							servo_v2_set_position(&bricklet_1, s_code, r_pos);
							servo_v2_set_enable(&bricklet_1, s_code, true);
						} else if (b_code == 2) {
							servo_v2_set_position(&bricklet_2, s_code, r_pos);
							servo_v2_set_enable(&bricklet_2, s_code, true); 
						} else if (b_code == 3) {
							servo_v2_set_position(&bricklet_3, s_code, r_pos);
							servo_v2_set_enable(&bricklet_3, s_code, true);
						} else {
							std::cout << "Invalid input. ";
						}
					
					} else {
						std::cout << "Invalid input. ";
					}
					
					
				} catch (std::invalid_argument) {
					std::cout << "Invalid input. ";
				}
				
			}
		
		}
	
	}
	
	/// SERVO CONTROL TESTS END ///
	
	for (int i = 0; i< 10; i++) {
		servo_v2_get_position(&bricklet_1, i, ret_pos);
		std::cout << "Position of b2 s" << i << ": " << ret_pos;
	}
	
	servo_v2_get_position(&bricklet_1, 2, ret_pos);
	
	std::cout << "Position of b2 s1: " << ret_pos;
	
	// disable servo bricklet connections
	std::cout << "\nDisabling bricklet connections\n\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_1, i, false) < E_OK) {
			std::cout << "ERROR: could not disable bricklet 1 - servo " << i << "\n";
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_2, i, false) < E_OK) {
			std::cout << "ERROR: could not disable bricklet 2 - servo " << i << "\n";
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_3, i, false) < E_OK) {
			std::cout << "ERROR: could not disable bricklet 3 - servo " << i << "\n";
		}
	}
    
	
	servo_v2_destroy(&bricklet_1);
	ipcon_destroy(&ipcon_b1); // calls ipcon_disconnect internally
	servo_v2_destroy(&bricklet_2);
	ipcon_destroy(&ipcon_b2); // calls ipcon_disconnect internally
	servo_v2_destroy(&bricklet_3);
	ipcon_destroy(&ipcon_b3); // calls ipcon_disconnect internally
	
	return 0;
}

