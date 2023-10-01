#include "sketch_mar7a.h"
#include "ReverseCarMain.h"
Motor::Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin)
{
  In1 = In1pin;
  In2 = In2pin;
  PWM = PWMpin;
  Standby = STBYpin;
  Offset = offset;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(Standby, OUTPUT);
}
void Motor::drive(int speed)
{
  digitalWrite(Standby, HIGH);
  speed = speed * Offset;
  if (speed>=0) fwd(speed);
  else rev(-speed);
}
void Motor::drive(int speed, int duration)
{
  drive(speed);
  delay(duration);
}

void Motor::fwd(int speed)
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
   analogWrite(PWM, speed);

}

void Motor::rev(int speed)
{
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);
   analogWrite(PWM, speed);
}

void Motor::brake()
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, HIGH);
   analogWrite(PWM,0);
}

void Motor::standby()
{
   digitalWrite(Standby, LOW);
}

void forward(Motor motor1, int speed)
{
	motor1.drive(speed);
}
void forward(Motor motor1)
{
	motor1.drive(DEFAULTSPEED);
}


void back(Motor motor1, int speed)
{
	int temp = abs(speed);
	motor1.drive(-temp);
}
void back(Motor motor1)
{
	motor1.drive(-DEFAULTSPEED);
}
void left(Motor left,int speed)
{
	int temp = abs(speed)/2;
	left.drive(-temp);
	
}

void right(Motor left, int speed)
{
	int temp = abs(speed)/2;
	left.drive(temp);
	
}
void motor(Motor left, Motor right)
{
   //pass
}

void brake(Motor motor1)
{
	motor1.brake();
}
void spinCircles(Motor left, Motor right, int speed) {
  int duration = 500; // milliseconds
  int num_spins = 3; // number of circles to spin
  for (int i = 0; i < num_spins * 2; i++) {
    if (i % 2 == 0) {
      left.drive(-speed);
      right.drive(speed);
    } else {
      left.drive(speed);
      right.drive(-speed);
    }
    delay(duration);
  }
  left.brake();
  right.brake();
}

void progressiveDrive(Motor Motor1, int speed, int duration, int delta) {
  int currentSpeed = 0;
  int increment = delta;

  if (speed < 0) {
    increment = -increment;
  }

  // Gradually increase/decrease the speed until we reach the desired value
  while (abs(currentSpeed - speed) > abs(increment)) {
    currentSpeed += increment;
    Motor1.drive(currentSpeed);
    delay(duration);
  }

  // Set the final speed
  Motor1.drive(speed);
}

void rotate180(Motor left, Motor right)
{
  int SLOWSPEED = 124;
  int TURNSPEED = 255 / 4;
  int ROTATION_DELAY_MS = 1000;
  // Set motors to go backwards at a slow speed
  back(left, SLOWSPEED);
  back(right, SLOWSPEED);

  // Wait for the car to come to a stop
  delay(ROTATION_DELAY_MS);

  // Turn the car to the right until it's facing the opposite direction

  right(left, TURNSPEED);
  left(right, -TURNSPEED);


  // Stop the motors
  left.brake();
  right.brake();
}
// Pin Set up on Arduino
#define AIN1 12
#define AIN2 11
#define STBY 10
#define PWMA 13

#define B1N1 22
#define B1N2 24
#define STBY 10
#define PWMB 28

const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(B1N1, B1N2, PWMB, offsetB, STBY);

void setup()
{
 //Nothing here
}


void loop()
{
   // Random Tests for Reverse Engineered Car
   motor2.drive(255,1000);
   motor2.drive(-255,1000);
   motor2.brake();
   motor1.drive(255,1000);
   motor1.drive(-255,1000);
   motor1.brake();
   delay(1000);
   
   
   forward(motor2, 150);
   delay(1000);
   
   back(motor2, -150);
   delay(1000);
   
   brake(motor2);
   delay(1000);
   
   left(motor2, 100);
   delay(1000);
   right(motor2,100);
   delay(1000);
   forward(motor1, 150);
   brake(motor2);
   delay(1000);
   progressiveDrive(25, 2000,1);
}
