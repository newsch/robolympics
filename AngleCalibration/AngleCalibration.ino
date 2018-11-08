// This code should help you calibrate the angle offset for Rocky.  Here are the steps.
//
// 1.  Start Rocky on a flat surface with the USB cable plugged in (you could also do this with Bluetooth if you know how to set that up)
// 2.  Open up the serial monitor
// 3.  Press the reset button to make sure the code is running starting from this lying down configuration
// 4.  Once the red LED has turned on and then off, raise Rocky up making sure to only rotate it about the axis of its wheels.
// 5.  Balance Rocky as closely as possible to its stable equilibrium.  Make note of the angle that is displayed on the Serial monitor.
// 6.  Take this angle and insert it into your Rocky balancer code in the following location
//
//      // this is based on coarse measurement of what I think the angle would be resting on the flat surface. 
//      // this corresponds to 94.8 degrees
//      angle = [INSERT YOUR ANGLE CALIBRATION HERE];

#include <Balboa32U4.h>
#include "Balance.h"

#define METERS_PER_CLICK 3.141592*80.0*(1/1000.0)/12.0/(162.5)
#define MOTOR_MAX 300
#define MAX_SPEED 0.75  // m/s
#define FORTY_FIVE_DEGREES_IN_RADIANS 0.78

extern int32_t angle_accum;
extern int32_t speedLeft;
extern int32_t driveLeft;
extern int32_t distanceRight;
extern int32_t speedRight;
extern int32_t distanceLeft;
extern int32_t distanceRight;

float vL, vR, totalDistanceLeft, totalDistanceRight;
float leftMotorPWM = 0;
float rightMotorPWM = 0;

void balanceDoDriveTicks();

extern int32_t displacement;
int32_t prev_displacement=0;

LSM6 imu;
Balboa32U4ButtonA buttonA;


uint32_t prev_time;

void setup()
{
  prev_time = 0;
  ledYellow(0);
  ledRed(1);
  balanceSetup();
  ledRed(0);
  ledGreen(0);
  ledYellow(0);
}

extern int16_t angle_prev;
int16_t start_counter = 0;
void lyingDown();
extern bool isBalancingStatus;
extern bool balanceUpdateDelayedStatus;

void newBalanceUpdate()
{
  static uint32_t lastMillis;
  uint32_t ms = millis();

  if ((uint32_t)(ms - lastMillis) < UPDATE_TIME_MS) { return; }
  balanceUpdateDelayedStatus = ms - lastMillis > UPDATE_TIME_MS + 1;
  lastMillis = ms;

  // call functions to integrate encoders and gyros
  balanceUpdateSensors();
}


void loop()
{
  uint32_t cur_time = 0;
  static uint32_t prev_print_time = 0;   // this variable is to control how often we print on the serial monitor
  static float angle_rad;                // this is the angle in radians
  static float error_ = 0;      // this is the accumulated velocity error in m/s

  cur_time = millis();                   // get the current time in miliseconds

  newBalanceUpdate();                    // run the sensor updates. this function checks if it has been 10 ms since the previous 
  
  // Uncomment this and comment the above if doing wireless
  // Serial1.println(angle);
}
