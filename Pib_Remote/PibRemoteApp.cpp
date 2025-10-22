#include <iostream>

#include "../Pib_Tinkerforge/Classes/Robot.cpp"
#include "../../SDL_Application/SDL_application.cpp"


class PibRemoteApp: public SDL_application {
	
	Robot robot;
	
	public:
	
	PibRemoteApp(int width, int height) : public SDL_application(width, height) {
		
	}
	
	
};

