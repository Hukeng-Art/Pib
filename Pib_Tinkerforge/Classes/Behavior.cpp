
class Behavior {
	
	ServoControl* servos;
	SensorControl* sensors;
	NetworkControl* network;
	
	public:
	
		Behavior(ServoControl* robot_servos, SensorControl* robot_sensors, NetworkControl* robot_network) {
			servos = robot_servos;
			sensors = robot_sensors;
			network = robot_network;
		}

};
