#ifndef PIB_REMOTE_APP_H
#define PIB_REMOTE_APP_H

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
#include "../../SDL_Application/SDL_Application.cpp"


#define BRICKLET_NUM 3

#define FINGER_SPEED_SCALE 3 // factor by which fingers are faster than other servos
#define SERVO_SPEED 4500     // centi-degrees per second
#define BLINK_DURATION 2
#define BREATHER_DELAY 10    // required to prevent brick hat buffer congestion

#endif
