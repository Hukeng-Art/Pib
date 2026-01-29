#include "PibAnimatronic.h"


PibAnimatronic::PibAnimatronic() {
	
	robot = new Robot("a");
	
	current_animatronic = new Animatronic("Scripts/hand_test.txt");
	
	robot->servos->set_servo_pos(0, 8, -4500);
	robot->servos->set_servo_pos(2, 8, -4500);
	
	robot->assign_behavior(current_animatronic);
	
}


PibAnimatronic::~PibAnimatronic() {
	
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


void PibAnimatronic::events_ext() {
	
	if (key_states[SDL_SCANCODE_R]) { // reset behaviour
		current_animatronic->reset();
	}
	
}


void PibAnimatronic::update_ext() {
	
	robot->behavior->tick(delta);
	
}


void PibAnimatronic::draw_ext() {}

