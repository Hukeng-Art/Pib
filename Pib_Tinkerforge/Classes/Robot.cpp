#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ServoControl.cpp"
#include "SensorControl.cpp"
#include "NetworkControl.cpp"


class Robot {
	
		public:
		
		ServoControl* servos;
		SensorControl* sensors;
		NetworkControl* network;
	
		
		public:
		
		// constructor - instantiate contained objects via initializer list
		Robot(std::string settings_path) {
			servos = new ServoControl();
			sensors = new SensorControl();
			network = new NetworkControl();	
		}
		
		~Robot() {
			delete servos;
			delete sensors;
			delete network;	
		}
};
