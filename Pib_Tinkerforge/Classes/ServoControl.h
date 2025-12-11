#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <iostream>
#include <vector>

#include "../Resources/ip_connection.h"
#include "../Resources/brick_hat.h"
#include "../Resources/bricklet_servo_v2.h"
#include "../Resources/bricklet_solid_state_relay_v2.h"

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

#endif
