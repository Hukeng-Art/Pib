#include "faceAudioTest.h"

int main() {
	
	Robot *robot = new Robot("a");
	
	robot->audiovideo->push_audio("front_center", "assets/Front_Center.wav");
	
	robot->audiovideo->push_image("eyes_01", "assets/pibEyes/eyes01.png");
	robot->audiovideo->push_image("eyes_02", "assets/pibEyes/eyes02.png");
	
	std::cout << "Display files loaded. Press any key to continue.\n";
	getchar();
	
	robot->audiovideo->set_image("eyes_01");
	robot->audiovideo->update(1.0);
	
	std::cout << "Eyes_01 set. Press any key to continue.\n";
	getchar();
	
	robot->audiovideo->set_image("eyes_02");
	robot->audiovideo->update(1.0);
	
	std::cout << "Eyes_02 set. Press any key to continue.\n";
	getchar();
	
	robot->audiovideo->play_sfx("front_center");
	
	std::cout << "Sound effect played. Press any key to end program.\n";
	getchar();
	
	
	delete robot;
	return EXIT_SUCCESS;
}
