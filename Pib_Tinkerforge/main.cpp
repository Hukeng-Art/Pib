#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "Classes/Robot.cpp"


using namespace std;





int main() {
	
	// instantiate robot
	Robot pib("a");
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	pib.set_servo_pos(0,2,9000);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	return 0;
}
