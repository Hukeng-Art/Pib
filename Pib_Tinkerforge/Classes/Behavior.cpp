
class Behavior {
	
	ServoControl* servos;
	SensorControl* sensors;
	NetworkControl* network;
	
	clock_t start;
	clock_t end;
	double delta;
	
	bool is_running  = false;
	
	
	public:
	
		Behavior() {
			
			delta = 0;

		}
		
		
		void run() { // run a constant refresh loop, 
			
			while (is_running) {
				update_delta();
				tick(delta);
			}
			
		}


		void assign_servos(ServoControl* robot_servos) {
			servos = robot_servos;
		}
		
		
		void assign_sensors(SensorControl* robot_sensors) {
			sensors = robot_sensors;
		}
		
		
		void assign_network(NetworkControl* robot_network) {
			network = robot_network;
		}
		
		
		void set_running(bool value) {
			is_running = value;
		}

		
		// run a single refresh cycle
		// pass delta to determine time elapsed since last update
		// call to include Behavior refresh as part of external refresh cycle
		// (e.g. in update() function in run() loop of SDL_Application object)
		virtual void tick(double external_delta) {} // extend in subclass
		
	private:
	
		void update_delta() { // update delta variable (time elapsed since last refresh cycle)
			
		}

};
