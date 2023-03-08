

#ifndef sketch_mar7a_h
#define sketch_mar7a_h
#include <Arduino.h>
#define DEFAULTSPEED 255  
#define ROTATION 180



class Motor
{
  public:
    Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin);      

    void drive(int speed);  
	
    void drive(int speed, int duration);  
    void brake(); 
    
	
	void standby();	
	
  private:
	int In1, In2, PWM, Offset,Standby;
	
	void fwd(int speed);
	void rev(int speed);


};

void forward(Motor motor1, int speed);
void forward(Motor motor1);

void back(Motor motor1, int speed);
void back(Motor motor1);
void left(Motor left, int speed);
void right(Motor left, int speed);
void progressiveDrive(int speed, int duration, int delta);
void motor(Motor left, Motor right);

void brake(Motor motor1);



#endif