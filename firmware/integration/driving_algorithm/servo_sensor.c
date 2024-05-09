/**
 * @file servo_sensor.c
 * @brief File containing function definitions for servo_sensor module.
*/


#include "servo_sensor.h"

/** Number of servo-sensor positions, that is how many different PWMs are */
#define SENSOR_POSITIONS = 5

/**
 * @name PWM variables
 * Variables for setting PWM to different values, and thus controll servo-sensor
 * @{
*/
unsigned pwm_period = 0;
float duty_cycle = 0;
float duty_cycles[] = {2.0, 4.7, 7.5, 10.2, 13.5};
/** @} */

/** Array that store sensor values in each position */
unsigned sensor_values[SENSOR_POSITIONS] = {0};



/*
 * Function for initializing servo-sensor. First it initialies ADC 10-bit module, then sets pin
 * RB14 to work in open drain configuration, remapping pin RP14 to OUTPUT_COMPARE module.
 * Setting PWM to 50 Hz, channel 1, no prescaler, timer2, and then starting the PWM.
*/
void initialize_servo_sensor()
{
	/* Init ADC to use 10-bit module, and use Internal voltage reference(AVDD, AVSS) */
	ADC1_Init_Advanced(_ADC_INTERNAL_REF); 
	/* Set pin RB14 to work in open drain configuration */
    ODCB.F14 = 1;   							
	/* Remapping pin RP14 to OUTPUT_COMPARE module */
    RPOR7 = 0x1200;
	/* Set 50Hz period, channel 1, no prescaler, timer 2 */
    pwm_period = PWM_Init(50, 1, 0, 2);   
    PWM_Start(1);
}


/*
 * Function for setting servo-sensor to starting position
*/
void set_servo_sensor_to_starting_pos()
{
 	 /* starting position is for duty_cycle 7.5 */
     duty_cycle = 7.5;
     PWM_Set_Duty(duty_cycle * pwm_period / 100, 1);
}


/*
 * Function for scaning the space with servo-sensor
*/
void scan_space_with_sensor()
{
    unsigned i = 0;
    
    /* clear the previous sensor values */
    for(i=0; i < 5; i++){
       sensor_values[i] = 0;
    }

	/* go through all possible positions of servo-sensor */
    for(i = 0; i<5; i++) {
      duty_cycle = duty_cycles[i];
      PWM_Set_Duty(duty_cycle * pwm_period / 100, 1);
      sensor_values[i] = ADC1_Get_Sample(9);
      Delay_ms(600);

    }

     /* always return sensor to face north */
     set_servo_sensor_to_starting_pos();
     Delay_ms(600);
}
