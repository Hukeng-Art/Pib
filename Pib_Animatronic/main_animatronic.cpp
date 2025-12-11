#include "PibAnimatronic.cpp"

int main() {

	PibAnimatronic* animatronic = new PibAnimatronic();
	
	animatronic->run();
	
	delete animatronic;
	
	return 0;
	
} 
