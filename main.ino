/*
https://www.projectsofdan.com/?p=385#comments
 
 
(VS_SEG_T_MES (must be >3) * 3600 / VS_FAC) as follows

-VS_SEG_T_MES is the amount of pulses during a given interval measured by the sensor
-*3600 the above is measured in pulses per second this is a conversion from seconds to hours (miles per hour)
-VS_FAC is the factor (based on the amount of pulses) that I need to change in order to fix this issue

205 60 -> 627mm

 7784 pulses per mille
 
 */

// In the e36 there are 9 pulses per rev in the rear differential
#define DIFF_PULSES_PER_REV 9 


// Vars
int actual_speed = 0;
unsigned long time_per_pulse_micro = 0; //microseconds
double time_per_pulse_ms = 0; //miliseconds

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
