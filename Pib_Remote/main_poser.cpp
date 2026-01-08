#include "PibPoserApp.cpp"

int main() {

	PibPoserApp* poser = new PibPoserApp();
	
	poser->run();
	
	delete poser;
	
	return 0;
	
} 
