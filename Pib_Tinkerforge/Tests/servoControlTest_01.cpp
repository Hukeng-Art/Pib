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
	
	std::string usr_input = "";
	
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
	
	
	if(ipcon_connect(&ipcon_b1, HOST, PORT) < 0) {
        fprintf(stderr, "Could not connect - ipcon for b1 failed\n");
        return 1;
    }
    if(ipcon_connect(&ipcon_b2, HOST, PORT) < 0) {
        fprintf(stderr, "Could not connect - ipcon for b2 failed\n");
        return 1;
    }
    if(ipcon_connect(&ipcon_b3, HOST, PORT) < 0) {
        fprintf(stderr, "Could not connect - ipcon for b3 failed\n");
        return 1;
    }
    
    
    // check if servo channels are enabled
    if (false) {
		std::cout << "\nChecking servo channels - this might take a while\n\n";
		for (int i = 0; i < 10; i++) {
			std::cout << "Bricklet 1 - servo " << i << " ";
			
			if (!servo_v2_get_enabled(&bricklet_1, i, ret_enable)) {
				
				std::cout << "not ";
			}
			
			std:: cout << "enabled\n";
			
		}
		std::cout << "\n";
		for (int i = 0; i < 10; i++) {
			std::cout << "Bricklet 2 - servo " << i << " ";
			
			if (!servo_v2_get_enabled(&bricklet_1, i, ret_enable)) {
				
				std::cout << "not ";
			}
			
			std:: cout << "enabled\n";
		}
		std::cout << "\n";
		for (int i = 0; i < 10; i++) {
			std::cout << "Bricklet 3 - servo " << i << " ";
			
			if (!servo_v2_get_enabled(&bricklet_1, i, ret_enable)) {
				
				std::cout << "not ";
			}
			
			std:: cout << "enabled\n";
		}
		
		std::cout << "\n";
	}
	
	
	/// SERVO CONTROL TESTS ///
	
	// set servo params (pib default)
	servo_v2_set_degree(&bricklet_1, 2, -9000, 9000);
    servo_v2_set_pulse_width(&bricklet_1, 2, 700, 2500);
    servo_v2_set_period(&bricklet_1, 2, 19500);
    servo_v2_set_motion_configuration(&bricklet_1, 2, 100000, 50000, 50000); // 0.2 max velocity with max ac-/deceleration
    
    servo_v2_set_position(&bricklet_1, 2, 9000); // Set to most right position
    servo_v2_set_enable(&bricklet_1, 2, true);   // Pass order to bricklet
	
	/// SERVO CONTROL TESTS END ///
	
	
    // quit program on input
    while (true) {
		std::cout << "Press q to exit\n";
		std::cin >> usr_input;
		
		if (usr_input == "q") {
				break;
		}
	}
	
	// disable servo bricklet connections
	std::cout << "\nDisabling bricklet connections - this might take a while\n\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_1, i, false)) {
			std::cout << "Disabled bricklet 1 - servo " << i << "\n";
		} else {
			std::cout << "ERROR: could not disable bricklet 1 - servo " << i << "\n";
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_2, i, false)) {
			std::cout << "Disabled bricklet 2 - servo " << i << "\n";
		} else {
			std::cout << "ERROR: could not disable bricklet 2 - servo " << i << "\n";
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 10; i++) {
		if (servo_v2_set_enable(&bricklet_3, i, false)) {
			std::cout << "Disabled bricklet 3 - servo " << i << "\n";
		} else {
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

