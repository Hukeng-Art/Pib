#include "PibAnimatronic.h"



class PibAnimatronic : public SDL_Application {

	Robot* robot;
	
	Animatronic* current_animatronic;
	
	Animatronic* hand_test;
	
	std::vector<SDL_Texture*> pib_eyes;
	
	double eye_counter;
	int8_t eye_index;
	
	
	const char* window_title = "Pib_Animatronic";
	
	
	public:
		PibAnimatronic() {
			
			robot = new Robot("a");
			
			hand_test = new Animatronic("Scripts/hand_test.csv");
			
			//current_animatronic = hand_test;
		
			robot->servos->set_servo_pos(0, 8, -4500);
			robot->servos->set_servo_pos(2, 8, -4500);
			
			//robot->assign_behavior(hand_test);
			
		}
		
		~PibAnimatronic() {
			
			//delete hand_test;
			delete robot;
			
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
				//current_animatronic->load_script("Scripts/hand_test.csv");
				//current_animatronic->reset_time();
			}
		}
		
		void update_ext() {
			
			// robot->behavior->tick(delta);
			
		}
		
		void draw_ext() {}
		
	
};
