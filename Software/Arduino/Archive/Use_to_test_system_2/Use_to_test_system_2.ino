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
#define Z_MIN_PIN 18
#define Z_MAX_PIN 19

#define SHUTTER_PIN 48
#define FOCUS_PIN 46

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

int move_X_finished = 1; // Used to check if X move is completed
int move_Y_finished = 1; // Used to check if Y move is completed
int move_Z_finished = 1; // Used to check if Y move is completed
long initial_X_homing = -1; // Used to Home X Stepper at startup
long initial_Y_homing = -1; // Used to Home Y Stepper at startup
long initial_Z_homing = -1; // Used to Home Y Stepper at startup

int numOfPositions = 172;
float positions[172][4] = {
{24000,-89638,-8800,148},
{22873,-89638,-8800,148},
{21746,-89638,-8800,148},
{20618,-89638,-8800,148},
{19491,-89638,-8800,148},
{18364,-89638,-8800,148},
{17237,-89638,-8800,148},
{16109,-89638,-8800,148},
{14982,-89638,-8800,148},
{13855,-89638,-8800,148},
{12728,-89638,-8800,148},
{11600,-89638,-8800,148},
{10473,-89638,-8800,148},
{9346,-89638,-8800,148},
{8219,-89638,-8800,148},
{7091,-89638,-8800,148},
{5964,-89638,-8800,148},
{4837,-89638,-8800,148},
{3710,-89638,-8800,148},
{2582,-89638,-8800,148},
{1455,-89638,-8800,148},
{328,-89638,-8800,148},
{31201,-89638,-8800,148},
{30073,-89638,-8800,148},
{28946,-89638,-8800,148},
{27819,-89638,-8800,148},
{26692,-89638,-8800,148},
{25564,-89638,-8800,148},
{24437,-89638,-8800,148},
{24000,-94259,-37600,140},
{22899,-94259,-37600,140},
{21798,-94259,-37600,140},
{20697,-94259,-37600,140},
{19596,-94259,-37600,140},
{18494,-94259,-37600,140},
{17393,-94259,-37600,140},
{16292,-94259,-37600,140},
{15191,-94259,-37600,140},
{14090,-94259,-37600,140},
{12989,-94259,-37600,140},
{11888,-94259,-37600,140},
{10787,-94259,-37600,140},
{9686,-94259,-37600,140},
{8585,-94259,-37600,140},
{7483,-94259,-37600,140},
{6382,-94259,-37600,140},
{5281,-94259,-37600,140},
{4180,-94259,-37600,140},
{3079,-94259,-37600,140},
{1978,-94259,-37600,140},
{877,-94259,-37600,140},
{31776,-94259,-37600,140},
{30675,-94259,-37600,140},
{29574,-94259,-37600,140},
{28472,-94259,-37600,140},
{27371,-94259,-37600,140},
{26270,-94259,-37600,140},
{25169,-94259,-37600,140},
{24068,-94259,-37600,140},
{24000,-94663,-66400,132},
{22901,-94663,-66400,132},
{21802,-94663,-66400,132},
{20703,-94663,-66400,132},
{19605,-94663,-66400,132},
{18506,-94663,-66400,132},
{17407,-94663,-66400,132},
{16308,-94663,-66400,132},
{15209,-94663,-66400,132},
{14110,-94663,-66400,132},
{13011,-94663,-66400,132},
{11912,-94663,-66400,132},
{10814,-94663,-66400,132},
{9715,-94663,-66400,132},
{8616,-94663,-66400,132},
{7517,-94663,-66400,132},
{6418,-94663,-66400,132},
{5319,-94663,-66400,132},
{4220,-94663,-66400,132},
{3121,-94663,-66400,132},
{2023,-94663,-66400,132},
{924,-94663,-66400,132},
{31825,-94663,-66400,132},
{30726,-94663,-66400,132},
{29627,-94663,-66400,132},
{28528,-94663,-66400,132},
{27429,-94663,-66400,132},
{26330,-94663,-66400,132},
{25232,-94663,-66400,132},
{24133,-94663,-66400,132},
{24000,-90877,-95200,123},
{22880,-90877,-95200,123},
{21760,-90877,-95200,123},
{20640,-90877,-95200,123},
{19520,-90877,-95200,123},
{18399,-90877,-95200,123},
{17279,-90877,-95200,123},
{16159,-90877,-95200,123},
{15039,-90877,-95200,123},
{13919,-90877,-95200,123},
{12799,-90877,-95200,123},
{11679,-90877,-95200,123},
{10559,-90877,-95200,123},
{9439,-90877,-95200,123},
{8318,-90877,-95200,123},
{7198,-90877,-95200,123},
{6078,-90877,-95200,123},
{4958,-90877,-95200,123},
{3838,-90877,-95200,123},
{2718,-90877,-95200,123},
{1598,-90877,-95200,123},
{478,-90877,-95200,123},
{31357,-90877,-95200,123},
{30237,-90877,-95200,123},
{29117,-90877,-95200,123},
{27997,-90877,-95200,123},
{26877,-90877,-95200,123},
{25757,-90877,-95200,123},
{24637,-90877,-95200,123},
{24000,-82647,-124000,115},
{22831,-82647,-124000,115},
{21662,-82647,-124000,115},
{20492,-82647,-124000,115},
{19323,-82647,-124000,115},
{18154,-82647,-124000,115},
{16985,-82647,-124000,115},
{15815,-82647,-124000,115},
{14646,-82647,-124000,115},
{13477,-82647,-124000,115},
{12308,-82647,-124000,115},
{11138,-82647,-124000,115},
{9969,-82647,-124000,115},
{8800,-82647,-124000,115},
{7631,-82647,-124000,115},
{6461,-82647,-124000,115},
{5292,-82647,-124000,115},
{4123,-82647,-124000,115},
{2954,-82647,-124000,115},
{1784,-82647,-124000,115},
{615,-82647,-124000,115},
{31446,-82647,-124000,115},
{30277,-82647,-124000,115},
{29107,-82647,-124000,115},
{27938,-82647,-124000,115},
{26769,-82647,-124000,115},
{25600,-82647,-124000,115},
{24430,-82647,-124000,115},
{24000,-69344,-152800,106},
{22742,-69344,-152800,106},
{21483,-69344,-152800,106},
{20225,-69344,-152800,106},
{18966,-69344,-152800,106},
{17708,-69344,-152800,106},
{16449,-69344,-152800,106},
{15191,-69344,-152800,106},
{13932,-69344,-152800,106},
{12674,-69344,-152800,106},
{11415,-69344,-152800,106},
{10157,-69344,-152800,106},
{8899,-69344,-152800,106},
{7640,-69344,-152800,106},
{6382,-69344,-152800,106},
{5123,-69344,-152800,106},
{3865,-69344,-152800,106},
{2606,-69344,-152800,106},
{1348,-69344,-152800,106},
{89,-69344,-152800,106},
{30831,-69344,-152800,106},
{29572,-69344,-152800,106},
{28314,-69344,-152800,106},
{27056,-69344,-152800,106},
{25797,-69344,-152800,106},
{24539,-69344,-152800,106},

};


int startProcessMillis = 0;
int processMillis = 2000;
boolean processing = false;


void setup()
{
  Serial.begin(9600);

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
  pinMode(Z_MIN_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

  delay(5);  // Wait for drivers to wake up


  setupSteppers();
}

void loop()
{

  while (Serial.available() > 0)
  {
    //    cameraMount();
    //Serial.println("Please state which lens you are using 35, 55 or 90");
    //if 90 make delay longer in takePhoto as 90mm hunts for focus
   //Serial.println("Place object on the turntable, input character to initiate scan");
    int inChar = Serial.read();
    recording();
  }

}

void takePhoto() {

  digitalWrite(FOCUS_PIN, LOW);
  delay(1000);
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

  Serial.print("X Stepper is Homing . . . . . . . . . . . ");

  while (!digitalRead(X_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    stepperX.run();  // Start moving the stepper
  }
  stepperX.setCurrentPosition(0);
  initial_X_homing = 1;
  Serial.println("Homing X Completed");
  stepperX.moveTo(-1600);
  
  while ( stepperX.currentPosition() > -1600 ) {
    stepperX.run();  // Start moving the stepper
  }
/*
  for( int i=0; i<10000; i++)
  {
     stepperX.run(); 
  }
*/
  //while(digitalRead(X_MIN_PIN)){
  //stepperX.moveTo(-10000);
  //stepperX.run();  // Start moving the stepper
  // }


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
  Serial.println("Homing Y Completed");
  stepperY.moveTo(-1600);
  
  while ( stepperY.currentPosition() > -1600 ) {
    stepperY.run();  // Start moving the stepper
  }
  stepperY.setCurrentPosition(0);
  Serial.println("Homing Y Completed");

  // HOME Z
  Serial.print("Stepper Z is Homing . . . . . . . . . . . ");

  stepperZ.setEnablePin(Z_ENABLE_PIN);
  //  stepperZ.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperZ.enableOutputs();

  stepperZ.setCurrentPosition(0);
  Serial.println("Homing Z Completed");
  Serial.println("");
  stepperZ.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepperZ.setAcceleration(10000.0);  // Set Acceleration of Stepper

  Serial.println("Waiting for start recording message");

}


void recording() {

  for (int i = 0; i < numOfPositions; i++) {
    Serial.print("Sequence step: ");
    Serial.println(i);
    rotate(positions[i][0]);
    moveX(positions[i][1]);
    moveY(positions[i][2]);
    tilt(positions[i][3]);
    Serial.println(); Serial.println();
    delay(100);
    takePhoto();
    delay(500);
  }



}


void moveX(float targetX) {
  stepperX.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepperX.setAcceleration(10000.0);  // Set Acceleration of Stepper
  Serial.print("Moving stepper X into position: ");
  Serial.println(targetX);
  if (targetX < -184000 || targetX > 0) {  // Make sure the position entered is not beyond the HOME or MAX position
    Serial.println("");
    Serial.println("Please enter a value greater than zero and smaller or equal to 1500.....");
    Serial.println("");
  } else {
    Serial.println(targetX);
    long stepsX = (long) targetX; //
    stepperX.moveTo(stepsX);
    boolean endOfX = false;
    while ((endOfX == false) && (stepperX.distanceToGo() != 0)) {
      stepperX.run();  // Move Stepper into position
      endOfX = digitalRead(X_MIN_PIN); //|| digitalRead(X_MAX_PIN);
      //delay(2);
    }
    if (endOfX) {
      Serial.println("Limit switch X activated");
    } else {
      Serial.println("Target position X reached");
    }

    //stepperX.moveTo(targetX);  // Set new moveto position of Stepper
    //delay(1000);  // Wait 1 seconds before moving the Stepper
  }

}

void moveY(float targetY) {
  stepperY.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepperY.setAcceleration(10000.0);  // Set Acceleration of Stepper
  Serial.print("Moving stepper Y into position: ");
  Serial.println(targetY);
  if (targetY < -184000 || targetY > 0) {  // Make sure the position entered is not beyond the HOME or MAX position
    Serial.println("");
    Serial.println("Please enter a value greater than zero and smaller or equal to 1500.....");
    Serial.println("");
  } else {
    Serial.println(targetY);
    long stepsY = (long) targetY; //
    stepperY.moveTo(stepsY);
    boolean endOfY = false;
    while ((endOfY == false) && (stepperY.distanceToGo() != 0)) {
      stepperY.run();  // Move Stepper into position
      endOfY = digitalRead(Y_MIN_PIN); //|| digitalRead(Y_MAX_PIN);
    }
    if (endOfY) {
      Serial.println("Limit switch Y activated");
    } else {
      Serial.println("Target position Y reached");
    }
    //stepperX.moveTo(targetX);  // Set new moveto position of Stepper
    //delay(1000);  // Wait 1 seconds before moving the Stepper
  }
}

void rotate(float targetAngle) {
  stepperZ.setMaxSpeed(16000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepperZ.setAcceleration(10000.0);  // Set Acceleration of Stepper
  Serial.print("Rotating Platform into angle: ");
  Serial.println(targetAngle);
  if (targetAngle < 0 || targetAngle > 32000) {  // Make sure the position entered is not beyond the HOME or MAX position
    Serial.println("");
    Serial.println("Please enter a value greater than zero and smaller or equal to 32000.....");
    Serial.println("");
  } else {
    Serial.println(targetAngle);
    long stepsAngle = (long) targetAngle; //
    stepperZ.moveTo(stepsAngle);
    while ((stepperZ.distanceToGo() != 0)) {
      stepperZ.run();  // Move Stepper into position
    }
  }

}

void tilt(float targetCamAngle) {

  Serial.print("Rotating Camera into angle: ");
  Serial.println(targetCamAngle);
  if (targetCamAngle < 0 || targetCamAngle > 180) {
    Serial.println("");
    Serial.println("Please enter a value greater than zero and smaller or equal to 180.....");
    Serial.println("");

  } else {
    myservo.write(targetCamAngle);
    delay(300);
    Serial.println("Target tilt reached, now shoot camera");
    delay(500);
  }
}
  //void cameraMount() {

  //moveto -50000
 // myservo.write(0);
  //delay(300);
  //Serial.println("Please mount the camera, input character to confirm camera is mounted");
  //delay(300);
  //int inChar = Serial.read();
  //myservo.write(135);
  //delay(300);
  //Serial.println("Please calibrate the camera, input character to confirm camera is calibrated");



