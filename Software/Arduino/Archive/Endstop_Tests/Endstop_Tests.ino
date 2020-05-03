#include <Stepper.h> //Includes the arduino servo library
//#include <Servo.h> //Includes the arduino stepper library

// Communication variable

// Movement variables

//#define CAMERA_AUTOFOCUS 2 // Creates a definition for Autofocus
//#define CAMERA_SHUTTER 3 // Creates a definition for Shutter Release

//#define STEPSVERT 800 //Steps of motor
#define STEPSHORIZ 800 // Steps of motor
//#define STEPSTURN 1 // Steps of motor

//Stepper stepperVert(STEPSVERT, 46, 48); // create stepper class Vertical
//Stepper stepperHoriz(STEPSHORIZ, A0, A1); // create stepper class Horizontal
//Stepper stepperTurn(8400, A6, A7); // create stepper class Turntable 


int endstop_Zmin = 18; // Set endstop for Z min to pin 18
int endstop_Zmax = 19; // Set endstop for Z max to pin 19
int endstop_Xmin = 3;  // Set endstop for X min to pin 3
int endstop_Xmax = 2;  // Set endstop for X max to pin 2
int pin_motor_step_x = A0;
int pin_direction_x = A1;
int pin_enable_motor_x = 38;


void setup() {

  pinMode(endstop_Zmin,INPUT); // Sets endstop as input
  pinMode(endstop_Zmax,INPUT); // Sets endstop as input
  pinMode(endstop_Xmin,INPUT_PULLUP); // Sets endstop as input
  pinMode(endstop_Xmax,INPUT_PULLUP); // Sets endstop as input
  pinMode(pin_enable_motor_x, OUTPUT);
  pinMode(pin_motor_step_x, OUTPUT);
  pinMode(pin_direction_x, OUTPUT);

  digitalWrite(pin_enable_motor_x, LOW);

  for (int i = 0; i < 200000; i++) {
    runMotorSingleStepX(100, false); // runMotorSingleStepX(int delay, boolean direction)
    if (digitalRead(endstop_x) == true) {
      break;
    }
  }
}

Serial.begin(9600);


}


void loop() {

}

void runMotorSingleStepX(int wait, boolean value) { //dir(pino),
  digitalWrite(pin_direction_x, value);
  digitalWrite(pin_motor_step_x, HIGH);
  delayMicroseconds(wait);
  digitalWrite(pin_motor_step_x, LOW);
  delayMicroseconds(wait);
}

  


