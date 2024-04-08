unsigned pwm_period;
unsigned duty_cycle1;
unsigned duty_cycle2;

void main() {

    AD1PCFG= 0xFFFF;  // set all analog pins as digital
    // set pins as output pins, and set them to 0
    TRISB = 0;
    PORTB = 0;
    
    ODCB.F11 = 1;   // set pin RB11 to work in open drain configuration
    
    // set up PWM
    Unlock_IOLOCK();
    PPS_Mapping_NoLock(11, _OUTPUT, 18);     // set RP11, RB11 (pin 22) for PWM
    Lock_IOLOCK();

    pwm_period = PWM_Init(50, 1, 0, 2);   // set 50Hz period, channel 1, no prescaler, timer 2
    PWM_Start(1);

    duty_cycle1 = 2.5 * pwm_period / 100;    // set duty cycle to turn on one side
    duty_cycle2 = 12.5 * pwm_period / 100;  // set duty cycle to turn to other side

     while(1){
        PWM_Set_Duty(duty_cycle1, 1);
        Delay_ms(2000);
        PWM_Set_Duty(duty_cycle2, 1);
        Delay_ms(2000);
     }

}
