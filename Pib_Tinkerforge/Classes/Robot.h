#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#include "ServoControl.cpp"
#include "SensorControl.cpp"
#include "NetworkControl.cpp"
#include "AudioVideoControl.cpp"
#include "Behavior.cpp"

class Robot {
	
	public:
		
		ServoControl *servos;
		SensorControl *sensors;
		NetworkControl *network;
		AudioVideoControl *audiovideo;
		Behavior *behavior;
		
		
	public:
		
		Robot(std::string settings_path);
		~Robot();
		
		void assign_behavior(Behavior *new_behavior);
		void run_behavior();
		void reset_defaults();
		
};

#endif
