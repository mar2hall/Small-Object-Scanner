// Servo: 0 - 180 
// Rotary platforms: 1 turn -> 10 stepper revs -> 32000 microsteps
// Linear guides steppers 8mm - 3200 microsteps

#include <Servo.h>
#include <AccelStepper.h>

#define X_STEP_PIN 8
#define X_DIR_PIN 9
#define X_ENABLE_PIN 10
#define X_MIN_PIN 3
#define X_MAX_PIN 22

#define Y_STEP_PIN 36
#define Y_DIR_PIN 34
#define Y_ENABLE_PIN 38
#define Y_MIN_PIN 2
#define Y_MAX_PIN 23

#define Z_STEP_PIN 7
#define Z_DIR_PIN 6
#define Z_ENABLE_PIN 5

#define SHUTTER_PIN 52
#define FOCUS_PIN 50

//Stepper Init

AccelStepper stepperX(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperZ(1, Z_STEP_PIN, Z_DIR_PIN);

//Servo Init

Servo myservo;

long CamAng;
// Stepper Travel Variables
long TravelX;  // Used to store the X value entered in the Serial Monitor
long TravelY;  // Used to store the X value entered in the Serial Monitor
long TravelZ;  // Used to store the X value entered in the Serial Monitor

int move_X_finished=1;  // Used to check if X move is completed
int move_Y_finished=1;  // Used to check if Y move is completed
int move_Z_finished=1;  // Used to check if Y move is completed
long initial_X_homing=-1;  // Used to Home X Stepper at startup
long initial_Y_homing=-1;  // Used to Home Y Stepper at startup
long initial_Z_homing=-1;  // Used to Home Y Stepper at startup

int startProcessMillis = 0; 
int processMillis = 2000;
boolean processing = false;

// Communication variable

int IDLE_READ_STATE = 0;
int STEPPER_1_READ_STATE = 1;
int STEPPER_2_READ_STATE = 2;
int STEPPER_3_READ_STATE = 3;
int SERVO_READ_STATE = 4;

int readState = IDLE_READ_STATE;

String stepper_1_string = "";
String stepper_2_string = "";
String stepper_3_string = "";
String servo_string = "";
String inputString = "";
boolean stringComplete = false;  // whether the string is complete

bool cameraCalibrated = false;

void setup()
{  

  // COMMS
  Serial.begin(9600);
  inputString.reserve(200); // reserve 200 bytes for the inputString:

  //Servo

  myservo.attach(11);
  myservo.write(135);

  //Shutter
  
  pinMode(SHUTTER_PIN, OUTPUT);
  pinMode(FOCUS_PIN, OUTPUT);

  digitalWrite(SHUTTER_PIN, HIGH); // Relay board uses inverse logic: HIGH means open contact
  digitalWrite(FOCUS_PIN, HIGH);

  //PinsIn/Outs

  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);

  delay(5);  // Wait for drivers to wake up

 
  setupSteppers();
}

void loop()
{ 
  serialEvent();

  if (stringComplete) {

    // clear serial input string:
    inputString = "";
    stringComplete = false;

// Conversion from Grassoper units to stepper unit
    int stepper_1_value = (int) stepper_1_string.toFloat();
    int stepper_2_value = (int) stepper_2_string.toFloat();
    int stepper_3_value = (int) stepper_3_string.toFloat();
    int servo_value = (int) servo_string.toFloat();

    //Serial.print(" New Sequence step: ");
    rotate(stepper_1_value);
    moveX(stepper_2_value);
    moveY(stepper_3_value);
    tilt(servo_value);

    takePhoto();
    //Serial.println();Serial.println();

    // Init movement variables and starting process
    processing = true;
    startProcessMillis = millis();

    delay(3000);
    //Serial.println('E');
    Serial.println("End of process: " + stepper_1_string + " "+ stepper_2_string + " " + stepper_3_string + " " + servo_string);
    processing = false;
  }
  

    
 
}

void takePhoto() {

    digitalWrite(FOCUS_PIN, LOW);
    delay(1500);
    digitalWrite(SHUTTER_PIN, LOW);
    delay(1000);
    digitalWrite(FOCUS_PIN, HIGH);
    digitalWrite(SHUTTER_PIN, HIGH);
    
}


void setupSteppers() {

  // HOME X

  //Steppers
  stepperX.setEnablePin(X_ENABLE_PIN); 
  //stepperX.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperX.enableOutputs();
  stepperX.setCurrentPosition(0);
  stepperX.setMaxSpeed(16000.0); 
  stepperX.setAcceleration(10000.0);
  stepperX.moveTo(10000000);

  //Serial.print("X Stepper is Homing . . . . . . . . . . . ");

  while (!digitalRead(X_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    stepperX.run();  // Start moving the stepper
  }
  stepperX.setCurrentPosition(0);
  initial_X_homing=1;
  stepperX.setCurrentPosition(0);
  initial_X_homing = 1;
  //Serial.println("Homing X Completed");
  stepperX.moveTo(-1600);
  
  while ( stepperX.currentPosition() > -1600 ) {
    stepperX.run();  // Start moving the stepper
  }
  stepperX.setCurrentPosition(0);

  // HOME Y
  stepperY.setEnablePin(Y_ENABLE_PIN); 
 // stepperY.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperY.enableOutputs();
  stepperY.setCurrentPosition(0);
  stepperY.setMaxSpeed(16000.0); 
  stepperY.setAcceleration(10000.0);
  stepperY.moveTo(10000000);
  //Serial.print("Stepper Y is Homing . . . . . . . . . . . ");

  while (!digitalRead(Y_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    stepperY.run();  // Start moving the stepper
  }
  stepperY.setCurrentPosition(0);
  initial_Y_homing=1;
  stepperY.setCurrentPosition(0);
  initial_Y_homing = 1;
  //Serial.println("Homing Y Completed");
  stepperY.moveTo(-1600);
  
  while ( stepperY.currentPosition() > -1600 ) {
    stepperY.run();  // Start moving the stepper
  }
  stepperY.setCurrentPosition(0);

//Setup Z
  
   stepperZ.setEnablePin(Z_ENABLE_PIN); 
//   stepperZ.setPinsInverted(false, false, true); //invert logic of enable pin
   stepperZ.enableOutputs();
   
   stepperZ.setCurrentPosition(0);
   //Serial.println("Homing Z Completed");
   //Serial.println("");
   stepperZ.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
   stepperZ.setAcceleration(10000.0);  // Set Acceleration of Stepper  

   Serial.println("Waiting for start recording message");
   stepperY.moveTo(-50000);
  
    while ( stepperY.currentPosition() > -50000 ) {
    stepperY.run();  // Start moving the stepper
  }
      
}

/*
void recording() {

 for(int i = 0; i < numOfPositions; i++){
    //Serial.print("Sequence step: ");
    //Serial.println(i);
    rotate(positions[i][0]);
    moveX(positions[i][1]);
    moveY(positions[i][2]);
    tilt(positions[i][3]);
    //Serial.println();Serial.println();
    takePhoto();
    delay(500);
 }

}
*/

void moveX(float targetX){
  stepperX.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepperX.setAcceleration(10000.0);  // Set Acceleration of Stepper
  //Serial.print("Moving stepper X into position: ");
  //Serial.println(targetX);
  if (targetX < -184000 || targetX > 0) {  // Make sure the position entered is not beyond the HOME or MAX position
    //Serial.println("");
    //Serial.println("Please enter a value greater than zero and smaller or equal to 1500.....");
    //Serial.println("");
  } else {
    //Serial.println(targetX);
    long stepsX = (long) targetX; //
    stepperX.moveTo(stepsX);
    boolean endOfX = false;
    while((endOfX == false) && (stepperX.distanceToGo() != 0)){
      stepperX.run();  // Move Stepper into position
      endOfX = digitalRead(X_MIN_PIN); //|| digitalRead(X_MAX_PIN);
      //delay(2);
    }
    if(endOfX){
      //Serial.println("Limit switch X activated");
    } else {
      //Serial.println("Target position X reached");
    }
    
    //stepperX.moveTo(targetX);  // Set new moveto position of Stepper
    //delay(1000);  // Wait 1 seconds before moving the Stepper
  }
    
}

void moveY(float targetY){
    stepperY.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
    stepperY.setAcceleration(10000.0);  // Set Acceleration of Stepper
    //Serial.print("Moving stepper Y into position: ");
    //Serial.println(targetY);
    if (targetY < -184000 || targetY > 0) {  // Make sure the position entered is not beyond the HOME or MAX position
      //Serial.println("");
      //Serial.println("Please enter a value greater than zero and smaller or equal to 1500.....");
      //Serial.println("");
    } else {
      //Serial.println(targetY);
      long stepsY = (long) targetY; //
      stepperY.moveTo(stepsY);
      boolean endOfY = false;
      while((endOfY == false) && (stepperY.distanceToGo() != 0)){
        stepperY.run();  // Move Stepper into position
        endOfY = digitalRead(Y_MIN_PIN); //|| digitalRead(Y_MAX_PIN);
      }
      if(endOfY){
        //Serial.println("Limit switch Y activated");
      } else {
        //Serial.println("Target position Y reached");
      }  
      //stepperX.moveTo(targetX);  // Set new moveto position of Stepper
      //delay(1000);  // Wait 1 seconds before moving the Stepper
    }
}

void rotate(float targetAngle){
    stepperZ.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
    stepperZ.setAcceleration(10000.0);  // Set Acceleration of Stepper
    //Serial.print("Rotating Platform into angle: ");
    //Serial.println(targetAngle);
    if (targetAngle < 0 || targetAngle > 32000) {  // Make sure the position entered is not beyond the HOME or MAX position
      //Serial.println("");
      //Serial.println("Please enter a value greater than zero and smaller or equal to 32000.....");
      //Serial.println("");
    } else {
      //Serial.println(targetAngle);
      long stepsAngle = (long) targetAngle; //
      stepperZ.moveTo(stepsAngle);
      while((stepperZ.distanceToGo() != 0)){
        stepperZ.run();  // Move Stepper into position
      }  
    }
    
}

void tilt(float targetCamAngle){

    //Serial.print("Rotating Camera into angle: ");
    //Serial.println(targetCamAngle);
  if (targetCamAngle < 0 || targetCamAngle > 180){
      //Serial.println("");
      //Serial.println("Please enter a value greater than zero and smaller or equal to 180.....");
      //Serial.println("");
    
  } else {
    myservo.write(targetCamAngle);
    delay(300);
    //Serial.println("Target tilt reached, now shoot camera");
    delay(500);
  }
}


//void cameraMount() {   

//stepperX.moveTo(-50000);
//myservo.write(0);
//delay(300);
//Serial.println("Please mount the camera, input character to confirm camera is mounted");
//delay(300);
//int inChar = Serial.read();
//myservo.write(135);
//delay(300);
//Serial.println("Please calibrate the camera, input character to confirm camera is calibrated");

//}

// Getting new steps via USB
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(inChar == 'C' ){
    //
      myservo.write(0);
      delay(300);
      Serial.println("C");
    } else  if(inChar == 'V' ){
      myservo.write(135);
      delay(300);
      Serial.println("V");
    } else  if(inChar == 'B' ){
      cameraCalibrated = true;
      Serial.println("B");
    }
    else if (inChar == '{' ) {
       readState = STEPPER_1_READ_STATE;
       inputString = "";
    } else if (inChar == ',' ){
       if(readState == STEPPER_1_READ_STATE){
        stepper_1_string = inputString;
       } else if (readState == STEPPER_2_READ_STATE) {
        stepper_2_string = inputString;
       } else if (readState == STEPPER_3_READ_STATE) {
        stepper_3_string = inputString;
       } 
       if(readState != IDLE_READ_STATE){
        readState += 1;
        inputString = "";
       }
    } else if (inChar == '}' ){    
      if(readState == SERVO_READ_STATE){
        servo_string = inputString;
      } 
      stringComplete = true;
      readState = IDLE_READ_STATE;
    } else {
        // add it to the inputString:
        inputString += inChar;
    }
  }
}



