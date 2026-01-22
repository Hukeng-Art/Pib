#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <iostream>
#include <vector>

#include "ip_connection.h"
#include "brick_hat.h"
#include "bricklet_servo_v2.h"
#include "bricklet_solid_state_relay_v2.h"

#define HOST "localhost"
#define PORT 4223

#define SOLID_STATE_RELAY_UID "27PE"
#define SERVO_UID_0 "2cPS"
#define SERVO_UID_1 "2cPT"
#define SERVO_UID_2 "SGA"

#define BRICKLET_CONNECTIONS 10

#define DEFAULT_DEGREE_MIN -9000
#define DEFAULT_DEGREE_MAX 9000
#define DEFAULT_PULSE_WIDTH_MIN 700
#define DEFAULT_PULSE_WIDTH_MAX 2500
#define DEFAULT_PERIOD 19500
#define DEFAULT_VEL 100000
#define DEFAULT_ACC 50000
#define DEFAULT_DEC 50000

class ServoControl {
	
	// ATTRIBUTES
	private:
		std::vector<IPConnection> ipcons;
		std::vector<ServoV2> bricklets;
		
		IPConnection ssr_ipcon;
		SolidStateRelayV2 ssr;
		
		std::vector<std::vector<std::int8_t>> inversion;
		std::vector<std::string> servo_uids;
		
	public:
		ServoControl();
		~ServoControl();
		
		
		// set servo position
		void set_servo_pos(uint8_t bricklet, uint8_t servo, int16_t pos);
		
		// get position info on specific servo 
		// position factors in inversion
		int16_t get_servo_pos(uint8_t b, uint8_t s);
		
		// reset all servos to default parameters and zero position
		void reset_servos();
		
		// set parameters for select servo, reset to defaults if no values are passed
		void set_servo_params(uint8_t b,
		                      uint8_t s,
		                      int16_t min_degree = DEFAULT_DEGREE_MIN,
		                      int16_t max_degree = DEFAULT_DEGREE_MAX,
		                      uint32_t min_pulse_width = DEFAULT_PULSE_WIDTH_MIN,
		                      uint32_t max_pulse_width = DEFAULT_PULSE_WIDTH_MAX,
		                      uint32_t period = DEFAULT_PERIOD,
		                      uint32_t vel = DEFAULT_VEL,
		                      uint32_t acceleration = DEFAULT_ACC,
		                      uint32_t deceleration = DEFAULT_DEC);
		
		// save current position to csv file.
		// TO DO: fstream implementation
		void save_pose(std::string save_file);

		void load_pose(std::string save_file);
	
};

#endif
