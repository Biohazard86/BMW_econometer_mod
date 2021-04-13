/*
https://www.projectsofdan.com/?p=385#comments
 
 
(VS_SEG_T_MES (must be >3) * 3600 / VS_FAC) as follows

-VS_SEG_T_MES is the amount of pulses during a given interval measured by the sensor
-*3600 the above is measured in pulses per second this is a conversion from seconds to hours (miles per hour)
-VS_FAC is the factor (based on the amount of pulses) that I need to change in order to fix this issue

205 60 -> 627mm

 7784 pulses per mille
 
 */


//Perimeter of the wheel
#define PERIMETER_WHEEL 1985 //mm 205 55 R16
// In the e36 there are 9 pulses per rev in the rear differential
#define DIFF_PULSES_PER_REV 9 

// Define the pins
const int input_pin_speed = 2;

// Vars
int actual_speed = 0;
unsigned long time_per_pulse_micro = 0; //microseconds
double time_per_pulse_ms = 0; //miliseconds
int counter = 0;
volatile bool flag = false;
unsigned int time_1 = 0;
unsigned int time_2 = 0;
double frek = 0;




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup() {
  Serial.begin(9600);   //Serial port
  pinMode(input_pin_speed, INPUT);  //We define the pin 2 called input_pin_speed as an input

  // Serial output
  Serial.print("\n\n\n---------------------------------------------\n");
  Serial.print("    ECONOMETER MOD FOR BMW\n");
  Serial.print("       Biohazard86\n");
  Serial.print("--------------------------------------------\n");
  counter = 0;  
}

//========================================================================================
//this function calculates the actual speed when the interrups ocurrs
void speed_fun() {
  if(counter == 0){ //if is the first time we call this function
    time_1=micros();  // save the time in microseconds
    counter++;        // add 1 to the counter to dont enter in the if in the next time we call speed_fun
    flag=false;       // flag to doesnt show the rpm yet
  }
  else{               //2nd time we call speed_fun
    counter = 0;      // set 0 to counter to the next time we call speed_fun to enter in the if
    time_2=micros();  // save the time 
    flag=true;        // turn on the flag to can show the rpm
    } 
  }
//========================================================================================

void loop() {
  attachInterrupt(0, speed_fun, RISING);  // 0 is pin 2 (only 2 and 3 pins can handle interrupts); calls rpm_fun; RISING to trigger when the pin goes from low to high; 
  
  if(flag){
    detachInterrupt(0); // turn off interrupts
    time_per_pulse_micro = (time_2 - time_1); //  calculate the time per pulse in micro seconds
    time_per_pulse_ms = time_per_pulse_micro / 1000.00;   // calculate the time per pulse in micro seconds   
    // frek is the frecuency of each pulse in the diff. We have 9 pulses per rev in the rear diff
    frek = pow((time_per_pulse_ms / 1000), -1); // calculates the frecuency 
    // if we *9 the frek we have the frek of the wheel 
    frek = frek * 9;
    //Frek (hz) * 60 * 60 = rounds per hour. Every turn is PERIMETER_WHEEL in mm then divide by 1000000 to show in km
    actual_speed =  (frek * 60 * 60 * PERIMETER_WHEEL) / 1000000; // calculates the actual speed in km/h
    
      

    flag=false;
    }

}
