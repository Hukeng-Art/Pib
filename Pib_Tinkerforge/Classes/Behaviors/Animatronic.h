#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include <vector>
#include <queue>
#include <string>
#include <fstream>

#include "animatronicCommand.h"


class Animatronic : public Behavior {
	
	std::queue<animatronicCommand> program;
	std::queue<animatronicCommand> commands;
	
	std::string script_path;
	
	double time_since_start;
	double program_duration;
	
	int iterations;
	
	bool looping;
	
	
	public:
	
		Animatronic(std::string path);
		~Animatronic();
		
		void tick(double external_delta);
		void load_script(std::string script_file);
		void reset();
		
		
		void set_looping(bool b);
		
		void set_iterations(int i);
		
};

#endif
