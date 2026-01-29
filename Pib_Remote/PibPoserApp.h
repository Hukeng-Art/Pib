#ifndef PIB_POSER_APP_H
#define PIB_POSER_APP_H

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
#include <fstream>
#include <memory>
#include <vector>

#include "../Pib_Tinkerforge/Classes/Robot.cpp"
#include "../../SDL_Application/SDL_Application.cpp"

#define BRICKLET_NUM 3
#define SERVO_SPEED 4500     // centi-degrees per second
#define BREATHER_DELAY 10    // required to prevent brick hat buffer congestion
#define SELECTION_DELAY 100

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
#define FONT_SIZE 20
#define FONT_COLOR (SDL_Color){255,255,255,255}
#define SELECTED_COLOR (SDL_Color){0,255,0,255}
#define VERTICAL_SPACING 10
#define CELL_WIDTH 100


class PibPoserApp : public SDL_Application {
	
	Robot* robot;
	
	int8_t moving_servos[BRICKLET_NUM][10];
	double servo_positions[BRICKLET_NUM][10];
	
	uint8_t selected_bricklet;
	uint8_t next_bricklet;
	
	bool snapshot_requested;
	
	// text and font attributes
	TTF_Font *font_ptr; 
	SDL_Surface* pos_info_surfaces[BRICKLET_NUM][10];
	
	// Default values - overriden from superclass
	const char* window_title = "Pib_Poser";
	
	public:

		PibPoserApp();
		~PibPoserApp();
		
	private:
		
		void events_ext();
		void update_ext();
		void draw_ext();
		
		void draw_pos_info_surfaces();
		void draw_selection_rect();
		
		void update_info_surface(uint8_t b, uint8_t s);
		
		void pose_snapshot();

};

#endif
