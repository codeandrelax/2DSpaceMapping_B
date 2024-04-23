#define DEVICE_ADDR 0xE0
#define SPEED 125

unsigned pwm_period = 0;
float duty_cycle = 0;
float duty_cycles[] = {2.0, 4.7, 7.5, 10.2, 13.5};

// sensor
unsigned sensor_reading = 0;
unsigned sensor_values[5] = {0};

/*
 * Enable Software I2C communication, through the desired pins
*/
sbit Soft_I2C_Sda           at RB2_bit;
sbit Soft_I2C_Scl           at RB3_bit;
sbit Soft_I2C_Sda_Direction at TRISB2_bit;
sbit Soft_I2C_Scl_Direction at TRISB3_bit;





void initialize_servo_for_sensor(){
    ODCB.F14 = 1;   // set pin RB14 to work in open drain configuration

    // set up PWM
    Unlock_IOLOCK();
    PPS_Mapping_NoLock(14, _OUTPUT, 18);     // set RP14, RB14 (pin 25) for PWM
    Lock_IOLOCK();

    pwm_period = PWM_Init(50, 1, 0, 2);   // set 50Hz period, channel 1, no prescaler, timer 2
    PWM_Start(1);
}

/*
*
*/
void set_servo_sensor_to_starting_pos(){
     duty_cycle = 7.5;
     PWM_Set_Duty(duty_cycle * pwm_period / 100, 1);
}


void initialize_ADC(){
     ADC1_Init_Advanced(_ADC_INTERNAL_REF);       // Init ADC to use 10-bit module, and use Internal voltage reference(AVDD, AVSS)
}


/*    DRIVE        */

/*
*
*/


/*
* Function for I2C controller configuration. It addresses device, then desired register, and puts some value in it
*/
void I2C_Send_Message(unsigned short dev_addr, unsigned short reg_addr, unsigned short data_value){
     Soft_I2C_Start();
     Soft_I2C_Write(dev_addr);
     Soft_I2C_Write(reg_addr);
     Soft_I2C_Write(data_value);
     Soft_I2C_Stop();
}


/*
*
*/
void initialize_I2C(){
     Soft_I2C_Init();
     Delay_ms(100);
     /* Set MODE1 register of PCA9633
      * AIx                   - Auto-Increment disabled
      * SLEEP bit set to 0    - Normal Mode
      * SUBx bit set to 0     - PCA does not respond to subadresses
      * ALLCALL bit set to 1  - PCA9633 responds to ALLCALL address (0xE0)
     */
     I2C_Send_Message(DEVICE_ADDR, 0x00, 0x01);
     /* Set LEDOUT register of PCA9633
      * LEDx output state control - all set to 0x10 which results in 0xAA value put into LEDOUT register
     */
     I2C_Send_Message(DEVICE_ADDR, 0xE8, 0xAA);
}


void drive_forward(){
     /* Set PWMx (x = 0, 1, 2, 3) registers to values according to datasheet in order for vehice to go forward*/
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, SPEED);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
}
/*
*
*/
void brake(){
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, 0);
}

/*
*
*/
void go_east(){
    // go left 90 degress
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
     Delay_ms(1000);
     brake();

     // go forward
     drive_forward();

}



/*
*
*/
void go_north_east(){

     // go left 45 degress
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
     Delay_ms(750);
     brake();

     // go forward
     drive_forward();

}


/*
*
*/
void go_north(){
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, SPEED);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
}


/*
*
*/
void go_north_west(){

     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, SPEED);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, 0);
     Delay_ms(750);
     brake();

     // go forward
     drive_forward();
}


/*
*
*/
void go_west(){

     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, SPEED);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, 0);
     Delay_ms(1000);
     brake();

     // go forward
     drive_forward();
}



/*
*
*/
void scan_space_with_sensor(){
    unsigned i = 0;
    for(i=0; i < 5; i++){
       sensor_values[i] = 0;
    }

    for(i = 0; i<5; i++) {
      duty_cycle = duty_cycles[i];
      PWM_Set_Duty(duty_cycle * pwm_period / 100, 1);
      sensor_values[i] = ADC1_Get_Sample(9);
      Delay_ms(600);

    }

     // always return sensor to face north
     set_servo_sensor_to_starting_pos();
     Delay_ms(600);
}


/*
*
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
           brake();
           break;
     }

}




void main()
{

  unsigned i = 0;

  AD1PCFG = 0xFDFF;        // set all pins to digital except pin AN9(RB15)
  LATB = 0;
  TRISB = 0;
  TRISB.F15 = 1;          // set pin AN9(RB15) as input

  initialize_I2C();
  Delay_ms(100);

  initialize_ADC();
  Delay_ms(100);

  initialize_servo_for_sensor();
  Delay_ms(100);
  set_servo_sensor_to_starting_pos();
  Delay_ms(600);

  // get Sensor value and convert it
  drive_forward();
  sensor_reading = ADC1_Get_Sample(9);
  if(sensor_reading >= 300){
     scan_space_with_sensor();
     where_to_go();
  }



  while(1)
  {
     sensor_reading = ADC1_Get_Sample(9);
     if(sensor_reading >= 300){
       brake();
       scan_space_with_sensor();
       where_to_go();
     }
  }
}
