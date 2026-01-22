#ifndef PIB_ANIMATRONIC_APP_H
#define PIB_ANIMATRONIC_APP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <memory>
#include <vector>

#include "../Pib_Tinkerforge/Classes/Robot.cpp"
#include "../Pib_Tinkerforge/Classes/Behaviors/Animatronic.cpp"
#include "../../SDL_Application/SDL_Application.cpp"


class PibAnimatronic : public SDL_Application {

	Robot* robot;
	Animatronic* current_animatronic;
	
	std::vector<SDL_Texture*> pib_eyes;
	
	double eye_counter;
	int8_t eye_index;
	
	
	const char* window_title = "Pib_Animatronic";
	
	
	public:
		PibAnimatronic();
		~PibAnimatronic();
		
	
	private:
	
		void events_ext();
		void update_ext();
		void draw_ext();
	
};

#endif

