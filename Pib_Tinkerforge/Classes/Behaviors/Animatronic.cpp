#include "../Behavior.cpp"
#include "../../Structs/animatronicCommand.cpp"

#include <queue>


class Animatronic : public Behavior {
	
	double time_since_start;
	double program_duration;
	
	int iterations;
	bool looping;
	
	std::queue<animatronicCommand> commands;
	
	public:
	
		Animatronic(std::string script) {
			
		}
		
		
		void tick(double external_delta) {
			
			time_since_start += external_delta;
			
			if (time_since_start > program_duration) {
				break;
			} 
			
			while (commands.front.start <= time_since_start) {
				
				animatronicCommand command = commands.pop();
				
				double time_for_execution = command.end - time_since_start;
				
				int16_t current_servo_pos = servos->get_servo_pos(command.bricklet, command.servo);
				
				uint32_t path_len = std::abs(100 * (command.pos - current_servo_pos));
				
				uint32_t required_vel = (uint32_t)(path_len / time_for_execution);
				
				servos->set_servo_params(command.bricklet, command.servo, velocity=required_vel);
				servos->set_servo_pos(command.bricklet, command.servo, command.pos);
				
				commands.push(command);
				
			}
		}
}
