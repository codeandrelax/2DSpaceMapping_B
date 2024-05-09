/**
 * @file main_program.c
 * @brief Main file of the program.
*/

#include "car_drive.h"
#include "servo_sensor.h"


/**
 * @brief Variable to store sensor value.
 *
 * Varible that saves the value of the sensor when the vehicle is going straight.
 */
unsigned sensor_reading = 0;

/**
 * @brief Array in which sensor values are store.
 *
 * Array that saves the values of the sensor when the vehicle is stopped and is
 * scanning  space for further moving
 * 
 */
unsigned extern sensor_values[];


/**
 * @brief Function that determines direction of the car after scaning the space.
 *
 * This function is called after vehicle encounters an obstacle, stops its
 * moving, and scans the space. Based on the values in sensor_values[] array
 * the vehicle determines which of the five directions possible it is going
 * to take.
 * @param None
 * @return void
*/
void where_to_go(){
     int i = 0;
     int lowest_reading = sensor_values[0];
     int index = 0;
     for(i = 0; i < 5; i++){
         if(sensor_values[i] < lowest_reading){
             lowest_reading = sensor_values[i];
             index = i;
         }
     }
     switch(index){
         case 0:
           go_east();
           break;
         case 1:
           go_north_east();
           break;
         case 2:
           go_north();
           break;
         case 3:
           go_north_west();
           break;
         case 4:
           go_west();
           break;
         default:
           stop();
           break;
     }

}

/**
 * @brief Main function of the program, entry point.
 *
 * This function is an entry point of the program. It does all neccesary configuration of all
 * the modules of the program (MCU, servo_sensor, car_drive etc.)
 * In the infinite while loop program is continously driving the vehicle, stops at obstacles
 * scans the space when needed etc.
*/
void main()
{

  AD1PCFG = 0xFDFF;        // set all pins to digital except pin AN9(RB15)
  LATB = 0;
  TRISB = 0;               // set all pins as output
  TRISB.F15 = 1;           // set pin AN9(RB15) as input

  initialize_car_drive();
  Delay_ms(100);
  initialize_servo_for_sensor();
  Delay_ms(100);
  set_servo_sensor_to_starting_pos();
  Delay_ms(600);

  /* Get sensor value and based on it, decide direction */
  go_north();
  sensor_reading = ADC1_Get_Sample(9);
  if(sensor_reading >= 300){
     scan_space_with_sensor();
     where_to_go();
  }

  while(1)
  {
     sensor_reading = ADC1_Get_Sample(9);
     if(sensor_reading >= 300){
       stop();
       scan_space_with_sensor();
       where_to_go();
     }
  }
}
