#include "PibAnimatronic.cpp"

int main() {

	PibAnimatronic* animatronic_application = new PibAnimatronic();
	
	animatronic_application->run();
	
	delete animatronic_application;
	
	return 0;
	
} 
