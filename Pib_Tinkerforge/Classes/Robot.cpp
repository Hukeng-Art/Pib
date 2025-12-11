#include "Robot.h"

#include "ServoControl.cpp"
#include "SensorControl.cpp"
#include "NetworkControl.cpp"
#include "Behavior.cpp"


class Robot {
	
	public:
		
		ServoControl* servos;
		SensorControl* sensors;
		NetworkControl* network;
		Behavior* behavior;
		
		
	public:
		
		// constructor - instantiate contained objects via initializer list
		Robot(std::string settings_path) {
			servos = new ServoControl();
			sensors = new SensorControl();
			network = new NetworkControl();
			
			behavior = NULL;
		}
		
		
		~Robot() {
			delete servos;
			delete sensors;
			delete network;
			
		}
		
		
		void assign_behavior(Behavior* new_behavior) { // pass specific behaviour object
			
			behavior = new_behavior;
			
			behavior->assign_servos(servos);
			behavior->assign_sensors(sensors);
			behavior->assign_network(network);
		}
		
		
		void run_behavior() {
			if (!behavior) {
				std::cout << "Can't run behavior - no behavior assigned!\n";
			} else {
				behavior->set_running(true);
				behavior->run();
			}
		}
		
};
