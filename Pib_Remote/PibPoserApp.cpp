#include "PibPoserApp.h"


PibPoserApp::PibPoserApp() {
	robot = new Robot("a");
	
	servo_positions[0][8] = -4500;
	servo_positions[2][8] = -4500;
		
	robot->servos->set_servo_pos(0, 8, -4500);
	robot->servos->set_servo_pos(2, 8, -4500);
	
	next_bricklet = 0;
	selected_bricklet = 0;
	
	// prepare font
	font_ptr = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	
	if (!font_ptr) {
		throw std::runtime_error("Error creating Font.");
	}
	
	// populate position info surfaces
	for (int i = 0; i < BRICKLET_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			
			update_info_surface(i,j);
		}
	}
		
}


PibPoserApp::~PibPoserApp() {
	
	delete robot;
	
	TTF_CloseFont(font_ptr);
	font_ptr = NULL;
	
	// free position info surfaces
	for (int i = 0; i < BRICKLET_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			if (pos_info_surfaces[i][j]) {
				SDL_DestroySurface(pos_info_surfaces[i][j]);
			}
		}
	}
	
}


void PibPoserApp::events_ext() {
	
	if (key_states[SDL_SCANCODE_SPACE]) {
		next_bricklet = (next_bricklet + 1) % BRICKLET_NUM;
	}
	
	if (key_states[SDL_SCANCODE_0]) {
		moving_servos [selected_bricklet][0] = 1;
	}
	if (key_states[SDL_SCANCODE_P]) {
		moving_servos [selected_bricklet][0] = -1;
	}
	
	if (key_states[SDL_SCANCODE_1]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_Q]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_2]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_W]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_3]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_E]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_4]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_R]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_5]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_T]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_6]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_Z]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_7]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_U]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_8]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_I]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
	if (key_states[SDL_SCANCODE_9]) {
		moving_servos[selected_bricklet][1] = -1;
	}
	if (key_states[SDL_SCANCODE_O]) {
		moving_servos[selected_bricklet][1] = 1;
	}
	
}

		
void PibPoserApp::update_ext() {
	
	selected_bricklet = next_bricklet;
	
	for (int i = 0; i < BRICKLET_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			if (moving_servos[i][j] != 0) {
				
				servo_positions[i][j] += SERVO_SPEED * moving_servos[i][j] * delta;
				
				// putting everything in one statement causes unexpected behavior
				if (servo_positions[i][j] > 9000) {
					servo_positions[i][j] = 9000;
				} else if (servo_positions[i][j] < -9000) {
					servo_positions[i][j] = -9000;
				}
				
				robot->servos->set_servo_pos(i, j, (int)(servo_positions[i][j]));
				moving_servos[i][j] = 0;
				
				// update position info surface texture for display
				update_info_surface(i,j);
				
				if (!pos_info_surfaces[i][j]) {
					throw std::runtime_error("Error updating info text.");
				}
				
				SDL_Delay(BREATHER_DELAY);
		
			}
			
		}
		
	}

}


void PibPoserApp::draw_ext() {
	
	draw_pos_info_surfaces();

}


void PibPoserApp::draw_pos_info_surfaces() {
	
	for (int i = 0; i < BRICKLET_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			
			SDL_FRect target_rect = (SDL_FRect){
				(float)(i * CELL_WIDTH + i * VERTICAL_SPACING),
				(float)(j * FONT_SIZE + j * VERTICAL_SPACING), 
				(float)CELL_WIDTH,
				(float)FONT_SIZE
			};
			
			SDL_RenderTexture(renderer, SDL_CreateTextureFromSurface(renderer, pos_info_surfaces[i][j]), NULL, &target_rect);

		}
	}	
}


void PibPoserApp::update_info_surface(uint8_t b, uint8_t s) {
	
	std::string value_string = std::to_string(servo_positions[b][s]);
	const char *value_chars = value_string.c_str();
			
	pos_info_surfaces[b][s] = TTF_RenderText_Blended(font_ptr, value_chars, 0, FONT_COLOR);
}
