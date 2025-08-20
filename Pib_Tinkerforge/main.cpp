#include <iostream>
#include <vector>

#include "Classes/Robot.cpp"


using namespace std;





int main() {
	
	// instantiate robot
	Robot pib("a");
	
	pib.set_servo_pos(0,2,9000);
	
	return 0;
}
