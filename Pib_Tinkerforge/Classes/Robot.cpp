#include "Robot.h"


Robot::Robot(std::string settings_path) {
	servos = new ServoControl();
	sensors = new SensorControl();
	network = new NetworkControl();
	
	behavior = NULL;
}


Robot::~Robot() {
	
	if (behavior) {
		delete behavior;
	}
	
	delete servos;
	delete sensors;
	delete network;
	
}

// pass specific behaviour object
void Robot::assign_behavior(Behavior* new_behavior) { 
	
	behavior = new_behavior;
	
	behavior->assign_servos(servos);
	behavior->assign_sensors(sensors);
	behavior->assign_network(network);
}


void Robot::run_behavior() {
	if (!behavior) {
		std::cout << "Can't run behavior - no behavior assigned!\n";
	} else {
		behavior->set_running(true);
		behavior->run();
	}
}

