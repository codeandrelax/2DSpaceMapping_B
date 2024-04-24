
/* declaring duty cycles which will be used for servo_sensor scanning */
unsigned pwm_period = 0;
float duty_cycle = 0;
float duty_cycles[] = {2.0, 4.7, 7.5, 10.2, 13.0};

/* sensor reading value */
unsigned sensor_reading = 0;
const unsigned STOP_RANGE = 300;


/* 
 * Function that initializes servo_sensor 
*/
void initialize_servo_for_sensor(){
    ODCB.F14 = 1;   // set pin RB14 to work in open drain configuration

    // set up PWM
    Unlock_IOLOCK();
    PPS_Mapping_NoLock(14, _OUTPUT, 18);     // set RP14, RB14 (pin 25) for PWM
    Lock_IOLOCK();

    // get PWM period for duty cycle count
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

/*
 * Function that moves servo_sensor 180 degrees and stores sensor reading from different positions */ 
*/
void scan_space_with_sensor(){
    unsigned i = 0;
    for(; i<5; i++)
    {
      duty_cycle = duty_cycles[i];
      PWM_Set_Duty(duty_cycle * pwm_period / 100, 1);
      Delay_ms(600);

    }

     // always return sensor to face north
     set_servo_sensor_to_starting_pos();
     Delay_ms(600);
}


/*
 * Function that initializes ADC needed for sensor reading 
*/
void initialize_ADC(){
     ADC1_Init_Advanced(_ADC_INTERNAL_REF);       // Init ADC to use 10-bit module, and use Internal voltage reference(AVDD, AVSS)
}



void main()
{

  unsigned i = 0;
  
  AD1PCFG = 0xFDFF;        // set all pins to digital except pin AN9(RB15)
  LATB = 0;
  TRISB = 0;
  TRISB.F15 = 1;          // set pin AN9(RB15) as input
  
  initialize_ADC();
  Delay_ms(100);

  initialize_servo_for_sensor();
  Delay_ms(100);
  
  set_servo_sensor_to_starting_pos();
  Delay_ms(600);
  
  
  while(1)
  {
     /* servo_sensor stays in its initial position until obtacle within predefined STOP_RANGE is observed 
     , after that servo_sensor scans the space around it*/
     sensor_reading = ADC1_Get_Sample(9);
     if(sensor_reading >= STOP_RANGE){
       scan_space_with_sensor();
     }
  }
}
