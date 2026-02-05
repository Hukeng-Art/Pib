#include "Animatronic.h"

// UTILITY FUNCS - TO DO: MOVE TO EXTERNAL PACKAGE
std::vector<std::string> split_line(std::string line, std::string del);
	
Animatronic::Animatronic(std::string path) {
	
	script_path = path;
	
	load_script(script_path);
	
	reset();
	
	looping = true;
	iterations = 0;
		
}


Animatronic::~Animatronic() {
	
}


void Animatronic::tick(double external_delta) {
	
	time_since_start += external_delta;
	
	// loop through commands queue
	// remove after passing to servo control
	while (commands.front().start <= time_since_start && !commands.empty()) {
		
		animatronicCommand command = commands.front();
		
		if (command.type == "p") { // execute position command
		
			double time_for_execution = command.end - time_since_start;
			int16_t current_servo_pos = servos->get_servo_pos(command.bricklet, command.servo);
			uint32_t path_len = std::abs((command.pos - current_servo_pos));
			uint32_t required_vel = (uint32_t)(path_len / time_for_execution);
			
			
			// UGLY - find better solution
			servos->set_servo_params(command.bricklet,
									 command.servo,
									 DEFAULT_DEGREE_MIN,
									 DEFAULT_DEGREE_MAX,
									 DEFAULT_PULSE_WIDTH_MIN,
									 DEFAULT_PULSE_WIDTH_MAX,
									 DEFAULT_PERIOD,
									 required_vel,
									 DEFAULT_ACC,
									 DEFAULT_DEC);
			
			servos->set_servo_pos(command.bricklet, command.servo, command.pos);
			
		} else if (command.type == "s") { // play sound effect
			
			audiovideo -> play_sfx(command.id);
			
		} else if (command.type == "i") { // set face image
			
			audiovideo -> set_image(command.id);
			
		} else if (command.type == "m") { // play music
			
			audiovideo -> play_music(command.id);
			
		}
		
		commands.pop();
		
	}
	
	
	// reset after program is done
	if (time_since_start > program_duration) {
		if (looping) { // forever if looping
			reset();
		} else if (iterations > 0) { // count down remaining iterations
			reset();
			iterations--;
		}
	}
	
	audiovideo->update(external_delta);
}


void Animatronic::load_script(std::string script_file) {
	
	program_duration = 0;
	
	if (!program.empty()) {
		program = std::queue<animatronicCommand>();
		std::cout << "cleared script\n";
		
		audiovideo -> free_audios();
		audiovideo -> free_images();
	}
	
	std::ifstream f(script_file);
	std::string line;
	
	
	while (getline(f,line)) { // LOOP THROUGH ALL LINES
		
		if (line == "#AUDIOS") { // preload audios into AudioVideoControl
			getline(f,line);
			
			while (line != "#END_AUDIOS") {
				std::vector<std::string> import_info = split_line(line, ",");
				audiovideo -> push_audio(import_info[0], import_info[1]);
				getline(f,line);
			}
			
			getline(f,line);
		}
		
		if (line == "#IMAGES") { // preload images into AudioVideocontrol
			getline(f,line);
			
			while (line != "#END_IMAGES") {
				std::vector<std::string> import_info = split_line(line, ",");
				audiovideo -> push_image(import_info[0], import_info[1]);
				getline(f,line);
			}
			
			getline(f,line);
		}
		
		
		std::vector<std::string> command_vec = split_line(line, ",");
		
		animatronicCommand new_command;
		
		if (command_vec[0] == "p") { // load position commmand
			
			new_command.type = command_vec[0];
			new_command.start = std::stod(command_vec[1]);
			new_command.end = std::stod(command_vec[2]);
			new_command.bricklet = std::stoi(command_vec[3]);
			new_command.servo = std::stoi(command_vec[4]);
			new_command.pos = std::stoi(command_vec[5]);
			
			if (new_command.end > program_duration) {
				program_duration = new_command.end;
			}
			
			
		} else if (command_vec[0] == "s" || command_vec[0] == "m" || command_vec[0] == "i") {
			
			new_command.type = command_vec[0];
			new_command.start = std::stod(command_vec[1]);
			new_command.id = command_vec[2];
		}
		
		program.push(new_command);
	
	}
	
}


void Animatronic::reset() {
	time_since_start = 0;
	commands = program;
}


void Animatronic::set_looping(bool b) {
	looping = b;
}


void Animatronic::set_iterations(int i) {
	iterations = i;
}

// UTILITY FUNCS

std::vector<std::string> split_line(std::string line, std::string del) {
	
	std::vector<std::string> substring_vec;
	size_t pos_start = 0;
	size_t pos_end;
	std::string token;
		
	while ((pos_end = line.find(del, pos_start)) != std::string::npos) { 
		token = line.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + del.size();
		substring_vec.push_back(token);
	}
	
	substring_vec.push_back(line.substr(pos_start));

	return substring_vec;
}
