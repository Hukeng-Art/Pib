#include <vector>

struct robotSettingsStruct {
	const char* host;
	uint16_t port;
	
	std::vector<const char*> solid_state_relay_uids;
	std::vector<const char*> servo_bricklet_uids;
	
	int16_t default_servo_degree_min;
	int16_t default_servo_degree_max;
	uint32_t default_servo_pulse_width_min;
	uint32_t default_servo_pulse_width_max;
	uint32_t default_servo_period;
	uint32_t default_servo_vel;
	uint32_t default_servo_acc;
	uint32_t default_servo_dec;
	
	std::vector<std::vector<int8_t>> servo_inversion; 
};
