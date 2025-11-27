
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

		}
		
		
		void run() { // run a constant refresh loop, 
			start = clock();
			
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
		
		
		void set_running_true() {
			is_running = true;
		}
		
		void set_running_false() {
			is_running = false;
		}
	
	protected:
		
		// run a single refresh cycle, pass delta to determine time elapsed since last update
		// call to execute behaviour refresh cycle as part of external refresh loop	
		virtual void tick(double current_delta) {} // estend in subclass
		
	private:
	
		void update_delta() { // update delta variable (time elapsed since last refresh cycle)
			end = clock();
			delta = (double)(end-start) / CLOCKS_PER_SEC; // calculate duration of previous refresh cycle, set delta
			start = clock();	
		}

};
