#include "PibAnimatronic.h"



class PibAnimatronic : public SDL_Application {

	Robot* robot;
	Animatronic* current_animatronic;
	
	std::vector<SDL_Texture*> pib_eyes;
	
	double eye_counter;
	int8_t eye_index;
	
	
	const char* window_title = "Pib_Animatronic";
	
	
	public:
		PibAnimatronic() {
			
			robot = new Robot("a");
			
			current_animatronic = new Animatronic("Scripts/hand_test.csv");
			
		
			robot->servos->set_servo_pos(0, 8, -4500);
			robot->servos->set_servo_pos(2, 8, -4500);
			
			robot->assign_behavior(current_animatronic);
			
		}
		
		~PibAnimatronic() {
			
			// TO DO: Why does reset not work?
			robot->servos->reset_servos();
			robot->servos->set_servo_pos(0, 8, -4500);
			robot->servos->set_servo_pos(2, 8, -4500);
			
			delete robot;
			delete current_animatronic;
			
			for (SDL_Texture* texture : pib_eyes) {
			
				if (texture) {
					SDL_DestroyTexture(texture);
					texture = NULL;
				}
			}	
		}
		
	
	private:
	
		void events_ext() {
			
			if (key_states[SDL_SCANCODE_R]) { // reset behaviour
				current_animatronic->reset();
			}
			
		}
		
		
		void update_ext() {
			
			robot->behavior->tick(delta);
			
		}
		
		
		void draw_ext() {}
	
};
