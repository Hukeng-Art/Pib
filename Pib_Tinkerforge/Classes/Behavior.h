#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class Behavior {
	
	protected:
		ServoControl *servos;
		SensorControl *sensors;
		NetworkControl *network;
		AudioVideoControl *audiovideo;
		
		clock_t start;
		clock_t end;
		double delta;
		
		bool is_running  = false;
	
	public:
	
		Behavior();
		
		void set_running(bool value);
		void run();

		void assign_servos(ServoControl *robot_servos);
		void assign_sensors(SensorControl *robot_sensors);
		void assign_network(NetworkControl *robot_network);
		void assing_audiovideo(AudioVideoControl *robot_audiovideo);
		
		// run a single refresh cycle
		// pass delta to determine time elapsed since last update
		// call to include Behavior refresh as part of external refresh cycle
		// (e.g. in update() function in run() loop of SDL_Application object)
		virtual void tick(double ext_delta) {} // extend in subclass
		
	private:
	
		void update_delta();

};

#endif
