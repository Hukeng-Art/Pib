#include <queue>
#include <vector>
#include <string>
#include <fstream>

#include "../../Structs/animatronicCommand.cpp"


class Animatronic : public Behavior {
	
	std::string script;
	
	double time_since_start;
	double program_duration;
	
	int iterations;
	bool looping;
	
	std::queue<animatronicCommand> commands;
	
	public:
	
		Animatronic(std::string script_file) {
			
			script = script_file;
			
			load_script(script);
			
			time_since_start = 0;
			
				
		}
		
		
		~Animatronic() {
			
			servos->reset_servos();
			
		}
		
		
		void tick(double external_delta) {
			
			time_since_start += external_delta;
			
			if (time_since_start > program_duration) {
				return;
			} 
			
			while (commands.front().start <= time_since_start) {
				
				animatronicCommand command = commands.front();
				
				double time_for_execution = command.end - time_since_start;
				
				int16_t current_servo_pos = servos->get_servo_pos(command.bricklet, command.servo);
				
				uint32_t path_len = std::abs(100 * (command.pos - current_servo_pos));
				
				uint32_t required_vel = (uint32_t)(path_len / time_for_execution);
				
				// UGLY - find better solution
				servos->set_servo_params(command.bricklet,
				                         command.servo,
				                         DEFAULT_DEGREE_MIN,
				                         DEFAULT_DEGREE_MAX,
				                         DEFAULT_PULSE_WIDTH_MIN,
				                         DEFAULT_PULSE_WIDTH_MAX,
				                         DEFAULT_PERIOD,
				                         required_vel,
				                         DEFAULT_ACC,
				                         DEFAULT_DEC);
				
				servos->set_servo_pos(command.bricklet, command.servo, command.pos);
				
				commands.push(command);
				commands.pop();
				
			}
		}
		
		
		void load_script(std::string script_file) {
			
			if (!commands.empty()) {
				commands = std::queue<animatronicCommand>();
			}
			
			std::ifstream f(script_file);
			std::string line;
			std::string token;
			std::vector<std::string> substring_list;
			
			
			while (getline(f,line)) { // LOOP THROUGH ALL LINES
				
				std::vector<std::string> substring_vec;
				
				animatronicCommand new_command;
				
				// SPLIT FUNCTION ADAPTED FOR CSV
				// TURN INTO UTIL LATER
				size_t pos_start = 0;
				size_t pos_end;
				
				while ((pos_end = line.find(",", pos_start)) != std::string::npos) { 
					token = line.substr(pos_start, pos_end - pos_start);
					pos_start = pos_end++;
					substring_vec.push_back(token);
				}
	
				substring_vec.push_back(line.substr(pos_start));
				
				new_command.start = std::stod(substring_list[0]);
				new_command.end = std::stod(substring_list[1]);
				new_command.bricklet = std::stoi(substring_list[2]);
				new_command.servo = std::stoi(substring_list[3]);
				new_command.pos = std::stoi(substring_list[4]);
				
				std::cout << new_command.start << "\n";
				
				commands.push(new_command);
			
			}
			
			program_duration = commands.back().end;
		}
		
		void reset_time() {
			time_since_start = 0;
		}
		
};
