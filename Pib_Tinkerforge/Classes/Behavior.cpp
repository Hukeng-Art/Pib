#include "Behavior.h"


Behavior::Behavior() {
	
	delta = 0;

}


void Behavior::run() { // run a constant refresh loop, 
	
	while (is_running) {
		update_delta();
		tick(delta);
	}
	
}


void Behavior::assign_servos(ServoControl *robot_servos) {
	servos = robot_servos;
}


void Behavior::assign_sensors(SensorControl *robot_sensors) {
	sensors = robot_sensors;
}


void Behavior::assign_network(NetworkControl *robot_network) {
	network = robot_network;
}

void Behavior::assing_audiovideo(AudioVideoControl *robot_audiovideo) {
	audiovideo = robot_audiovideo;
}


void Behavior::set_running(bool value) {
	is_running = value;
}

// TO DO: CLOCK IMPLEMENTATION 
void Behavior::update_delta() { // update delta variable (time elapsed since last refresh cycle)
	
}
