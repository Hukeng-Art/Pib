#include "../../SDL_application/SDL_application.cpp"
#include "PibRemoteApp.cpp"




int main() {

	PibRemoteApp* remote = new PibRemoteApp(800,500);
	
	remote->run();
	
	delete remote;
	
	return 0;
	
} 
