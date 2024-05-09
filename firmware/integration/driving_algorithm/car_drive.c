/**
 * @file car_drive.c
 * @brief File containing function definitons for vehicle moving.
*/


/**
 * @name Macros used in program 
 * @{
*/
/** @brief Macro that defines speed of the vehicle (0-255) */ 
#define SPEED 125
/** @brief I2C address of the device */
#define DEVICE_ADDR 0x0E
/** @} */



/**
 * @name I2C Communication
 * Enable Software I2C communication, through the desired pins
 * @{
*/
sbit Soft_I2C_Sda           at RB2_bit;
sbit Soft_I2C_Scl           at RB3_bit;
sbit Soft_I2C_Sda_Direction at TRISB2_bit;
sbit Soft_I2C_Scl_Direction at TRISB3_bit;
/** @} */

/*
 * Function for I2C controller configuration. It start I2C communication, 
 * addresses device, then desired register, and puts some value appropriate value in it.
 * At the end it stops the communication.
*/
void static I2C_Send_Message(unsigned short dev_addr, unsigned short reg_addr, unsigned short data_value){
     Soft_I2C_Start();
     Soft_I2C_Write(dev_addr);
     Soft_I2C_Write(reg_addr);
     Soft_I2C_Write(data_value);
     Soft_I2C_Stop();
}

/*
 * Function that initializes I2C communication. It inits I2C, then sets MODE1 register of
 * PCA9633 device with appropriate bit setting (AIx to 000, SLEEP to 0, SUBx to 000, ALLCALL to 1).
 * After that set LEDOUT register to 0xAA
*/
void initialize_car_drive(){
     Soft_I2C_Init();
     Delay_ms(100);
     I2C_Send_Message(DEVICE_ADDR, 0x00, 0x01);
     I2C_Send_Message(DEVICE_ADDR, 0xE8, 0xAA);
}

/*
 * Function for driving vehicle forward. Setting PWMx registers of PCA9633 to appropriate
 * values for going forward.
*/
void static forward()
{
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, SPEED);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
}

/*
 * Function for driving vehicle left. Setting PWMx registers of PCA9633 to appropriate
 * values for going left.
*/
void static left()
{
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);
}

/*
 * Function for driving vehicle right. Setting PWMx registers of PCA9633 to appropriate
 * values for going right.
*/
void static right()
{
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, SPEED);

}

/*
 * Function for stopping the vehicle. Setting PWMx registers of PCA9633 to appropriate
 * values for braking.
*/
void static brake(){
     I2C_Send_Message(DEVICE_ADDR, 0x02, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x03, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x04, 0);
     I2C_Send_Message(DEVICE_ADDR, 0x05, 0);
}

/*
 * Function for driving vehicle east. This means going left 90 degrees for some time, 
 * and then going forward.
*/
void go_east()
{
    left();
    Delay_ms(1000);
    brake();
    forward();

}


/*
 * Function for driving vehicle north east. This means going left 45 degrees for some time, 
 * and then going forward.
*/
void go_north_east()
{
     // go left 45 degress
    left();
    Delay_ms(750);
    brake();

    // go forward
    forward();

}


/*
 * Function for driving vehicle north. This is just basically going forward.
*/
void go_north()
{
    forward();
}


/*
 * Function for driving vehicle north west. This means going right 45 degrees for some time, 
 * and then going forward.
*/
void go_north_west()
{
    right();
    Delay_ms(750);
    brake();

    // go forward
    forward();
}


/*
 * Function for driving vehicle west. This means going right 90 degrees for some time, 
 * and then going forward.
*/
void go_west()
{

    right();
    Delay_ms(1000);
    brake();

    // go forward
    forward();
}

/*
 * Function for stopping the car. Just calls brake function.
*/
void stop()
{
    brake();
}
