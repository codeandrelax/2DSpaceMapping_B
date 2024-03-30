void main() {


     AD1PCFG = 0xFFFF; // Set All pins as digital
     TRISB.F15 = 0;   // Initialize pin RB15 as output
     LATB.F15 = 0;   // Set pin RB15 to zero

     while(1) {
        LATB.F15 = ~LATB.F15; // Invert RB15 value
        Delay_ms(1000);
     }

}