/**
 * @file car_drive.h
 * @brief File containing function declarations for vehicle moving.
*/

#ifndef CAR_DRIVE
#define CAR_DRIVE


/**
 * @brief Function for initializing necessary things for driving.
 *
 * This function initializes I2C interface that is needed for configuring
 * the I2C driver on the vehicles driver board. It also then configures
 * I2C driver in way that driving of the vehicle is enabled.
*/
void initialize_car_drive();


/**
 * @brief Function for driving the car north.
 *
 * This function is used when the desired direction of the car is north,
 * by north it is meant to go straight forward. 
 * The sides of world notation is used because the car can go in more directions
 * than just forward,left, right.
*/
void go_north();


/**
 * @brief Function for driving the car north east.
 *
 * This function is used when the desired direction of the car is east,
 * by north east it is meant a direction that is just between forward and right.
 * The sides of world notation is used because the car can go in more directions
 * than just forward,left, right.
*/
void go_north_east();


/**
 * @brief Function for driving the car east.
 *
 * This function is used when the desired direction of the car is east,
 * by east it is meant a direction that is on the right from its
 * current position.
 * The sides of world notation is used because the car can go in more directions
 * than just forward,left, right.
*/
void go_east();

/**
 * @brief Function for driving the car north west.
 *
 * This function is used when the desired direction of the car is north west,
 * by north west it is meant a direction that is just between forward and left.
 * The sides of world notation is used because the car can go in more directions
 * than just forward,left, right.
*/
void go_north_west();


/**
 * @brief Function for driving the car west.
 *
 * This function is used when the desired direction of the car is west,
 * by north west it is meant a direction that is is on the right from its
 * current position.
 * The sides of world notation is used because the car can go in more directions
 * than just forward,left, right.
*/
void go_west();


/**
 * @brief Function for stopping the car
 *
 * This function is used when the car needs to stop.
*/
void stop();

#endif  /* CAR_DRIVE */
