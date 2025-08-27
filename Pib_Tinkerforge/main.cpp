#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "Classes/ServoControl.cpp"


using namespace std;





int main() {
	
	// instantiate robot
	ServoControl pib("a");
	
	// Vars for command input
	std::string bricklet_code = "";
	std::string servo_code = "";
	std::string requested_position = "";
	
	int b_code;
	int s_code;
	int r_pos;
	
	bool valid_input = false;
	bool command_enabled = true;
	
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	
	// set servo positions via direct input
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
					
					if (-1 < b_code < 2 && -1 < s_code < 10 && -9001 < r_pos < 9001) {
						pib.set_servo_pos(b_code, s_code, r_pos);
					} else {
						std::cout << "Invalid input. ";
					}	
					
				} catch (std::invalid_argument) {
					std::cout << "Invalid input. ";
				}
				
			}
		
		}
	
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	return 0;
}
