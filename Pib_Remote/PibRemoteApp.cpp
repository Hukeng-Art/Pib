#include "PibRemoteApp.h"

#define BRICKLET_NUM 3
#define SERVO_DELAY 10
#define FINGER_SPEED_SCALE 3

#define SERVO_SPEED 200
#define BLINK_DURATION 10000
#define INVERSION {{1,1,1,-1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1}}


class PibRemoteApp : public SDL_Application {
	
	const bool* key_states;
	
	Robot* robot;
	int moving_servos[3][10];
	int servo_positions[3][10];
	int inversion[3][10] = INVERSION;
	
	std::vector<SDL_Texture*> pib_eyes;
	
	int eye_counter;
	int eye_index;
	
	
	// Default values - overriden from superclass
	const char* window_title = "Pib_Remote";
	
	
public:

	PibRemoteApp() { // Constructor
		
		key_states = SDL_GetKeyboardState(NULL);
		
		robot = new Robot("a");
		
		robot->servos->set_servo_pos(0, 8, -4500);
		robot->servos->set_servo_pos(2, 8, -4500);
		
		pib_eyes.push_back(IMG_LoadTexture(renderer,"assets/pibEyes/eyes01.png"));
		pib_eyes.push_back(IMG_LoadTexture(renderer,"assets/pibEyes/eyes02.png"));
		pib_eyes.push_back(IMG_LoadTexture(renderer,"assets/pibEyes/eyes03.png"));
		pib_eyes.push_back(IMG_LoadTexture(renderer,"assets/pibEyes/eyes04.png"));
		
		eye_counter = 0;
		eye_index = 0;
			
	}
	
	
	~PibRemoteApp(){ // DESTRUCTOR - CLEAN UP MEMORY
		
		delete robot;
		
		for (SDL_Texture* texture : pib_eyes) {
			
			if (texture) {
				SDL_DestroyTexture(texture);
				texture = NULL;
			}
		}
		
		
	}
	
	void run() {
		
		start = clock();
		
		while(is_running) {
			events();
			update();
			draw();
		}	
	}
	
private:

	void events() {
		while (SDL_PollEvent(&event)) { // poll until all events are handled
		
		// check struct type of event
		// adapt action based on type
		switch (event.type) { 
			
			case SDL_EVENT_QUIT: // close game
				is_running = false;
				break;
			
			default:
				break;
		}
		
		events_ext(event);
		
		}	
		
	}
	
	void update() {
		
		SDL_PumpEvents;
				
		update_ext();
		
	}
	
	void draw() {
		SDL_RenderClear(renderer); // clear renderer buffer
		
		draw_ext(); // extended draw function for actual application
		
		SDL_RenderPresent(renderer);
		
	}
	
	
	void events_ext(SDL_Event event) {
		
		// upper arm
		if (key_states[SDL_SCANCODE_E]) {
			moving_servos [1][0] = 1;
		}
		if (key_states[SDL_SCANCODE_Q]) {
			moving_servos [1][0] = -1;
		}
		// shoulder vertical
		if (key_states[SDL_SCANCODE_W]) {
			moving_servos[1][1] = -1;
		}
		if (key_states[SDL_SCANCODE_S]) {
			moving_servos[1][1] = 1;
		}
		// shoulder horizontal
		if (key_states[SDL_SCANCODE_D]) {
			moving_servos[0][9] = -1;
		}
		if (key_states[SDL_SCANCODE_A]) {
			moving_servos [0][9] = 1;
		}
		if (key_states[SDL_SCANCODE_I]) {
			moving_servos [0][8] = 1;
		}
		// elbow
		if (key_states[SDL_SCANCODE_K]) {
			moving_servos [0][8] = -1;
		}
		if (key_states[SDL_SCANCODE_K]) {
			moving_servos [0][8] = -1;
		}
		// wrist rotation
		if (key_states[SDL_SCANCODE_L]) {
			moving_servos [0][7] = 1;
		}
		if (key_states[SDL_SCANCODE_J]) {
			moving_servos [0][7] = -1;
		}
		//fingers
		if (key_states[SDL_SCANCODE_P]) {
			moving_servos[0][2] = FINGER_SPEED_SCALE;
			moving_servos[0][3] = FINGER_SPEED_SCALE;
			moving_servos[0][4] = FINGER_SPEED_SCALE;
			moving_servos[0][5] = FINGER_SPEED_SCALE;
		}
		if (key_states[SDL_SCANCODE_O]) {
			moving_servos[0][2] = -1 * FINGER_SPEED_SCALE;
			moving_servos[0][3] = -1 * FINGER_SPEED_SCALE;
			moving_servos[0][4] = -1 * FINGER_SPEED_SCALE;
			moving_servos[0][5] = -1 * FINGER_SPEED_SCALE;
		}
		// thumb
		if (key_states[SDL_SCANCODE_H]) {
			moving_servos[0][0] = FINGER_SPEED_SCALE;
			moving_servos[0][1] = FINGER_SPEED_SCALE;
		}
		if (key_states[SDL_SCANCODE_U]) {
			moving_servos[0][0] = -1 * FINGER_SPEED_SCALE;
			moving_servos[0][1] = -1 * FINGER_SPEED_SCALE;
		}
		
	}
	
	void update_ext() {
		
		for (int i = 0; i < BRICKLET_NUM; i++) {
			for (int j = 0; j < 10; j++) {
				if (moving_servos[i][j] != 0) {
					
					servo_positions[i][j] += SERVO_SPEED * inversion[i][j] * moving_servos[i][j];
					
					// putting everything in one statement causes unexpected behavior
					if (servo_positions[i][j] > 9000) {
						servo_positions[i][j] = 9000;
					} else if (servo_positions[i][j] < -9000) {
						servo_positions[i][j] = -9000;
					}
					
					robot->servos->set_servo_pos(i, j, servo_positions[i][j]);
					moving_servos[i][j] = 0;
					//SDL_Delay(SERVO_DELAY);
			
				}
				
			}
			
		}
			
		if (eye_counter == BLINK_DURATION) {
			eye_counter = 0;
			eye_index = (eye_index + 1) % pib_eyes.size();
		} else {
			eye_counter++;
		}
	}
	
	void draw_ext() {
	
		// last two params: pointers to source frect and target frect, null for full image & full screen
		SDL_RenderTexture(renderer, pib_eyes[eye_index], NULL, NULL);
	
	}
	

};


