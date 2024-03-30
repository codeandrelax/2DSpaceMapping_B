unsigned value;
float real_value;

float Vref = 3.3;
float delta_V;
unsigned no_of_quantums;


void main() {

   AD1PCFG = 0xFDFF;        // set all pins to digital except pin AN9(RB15)
   TRISB.F15 = 1;          // set pin AN9(RB15) as input
   
   /* Set pin RB14 as output for LED */
   TRISB.F14 = 0;   	  // Initialize RB14 as output
   LATB.F14 = 0;  	  // Set RB14 to zero


   //ADC1_Init();
   ADC1_Init_Advanced(_ADC_INTERNAL_REF);       // Init ADC to use 10-bit module, and use Internal voltage reference(AVDD, AVSS)

   no_of_quantums = 1023;                          // since we use 10-bit module, number of possible values is 2^10 = 1023
   delta_V = Vref / no_of_quantums;                // delta_V is quantuom of input voltage


   while(1){
      value = ADC1_Get_Sample(9);                        // get the value from analog input, channel 9 (AN9)
      real_value =  value * Vref / no_of_quantums;       // calculate the value of the input voltage
                        
      /* setting threshold */	    
      if(real_value > 1.5){
         LATB.F14 = 1;        // LED turn on
      } else {
        LATB.F14 = 0;        // LED turn off
      }
      
      Delay_ms(100);
   }
}
