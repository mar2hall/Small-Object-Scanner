#include <Servo.h>  //Includes the arduino servo library
#include <Stepper.h>  // Includes the arduino stepper library
#define CAMERA_AUTOFOCUS 2  // Creates a definition for Autofocus
#define CAMERA_SHUTTER 3  // Creates a definition for Shutter Release 

#define STEPSVERT 800 // change this to the number of steps on your motor
#define STEPSHORIZ 800 // change this to the number of steps on your motor
#define STEPSTURN 1 // change this to the number of steps on your motor

Stepper stepperVert(STEPSVERT, 30, 31, 32, 33); // create stepper class Vertical
Stepper stepperHoriz(STEPSHORIZ, 50, 51, 52, 53); // create stepper class Horizontal
Stepper stepperTurn(8400, 36, 37); // create stepper class Turntable 
Servo myservo; // Name servo myservo
int angle = 180; //Create an interger for servo angle
long turntablestep = 910; //Create a long interger for stepping turntable

void setup()
{
Serial.begin(9600);  //Starts serial connection between arduino and laptop
Serial.println("Scanning!");  //Prints Scanning into serial monitor
stepperVert.setSpeed(60); // set the speed of the motor to 30 RPMs
digitalWrite(30, LOW);    //Tells pins to turn off
digitalWrite(31, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
stepperHoriz.setSpeed(60); // set the speed of the motor to 30 RPMs
digitalWrite(50, LOW);
digitalWrite(51, LOW);
digitalWrite(52, LOW);
digitalWrite(53, LOW);
pinMode(40, OUTPUT); // Sets Shutter Pins as output
pinMode(41, OUTPUT); // Sets Shutter Pins as output
stepperTurn.setSpeed(60); // Set speed of the motor to 30 RPMs
digitalWrite(36, LOW);
digitalWrite(37, LOW);
myservo.attach(9);   // Attatches Servo to digital pin 9
myservo.write(180);  //Writes Servo to 180 degrees
long turntablestep;  // Includes long integer


}

void loop()
{
Serial.println("Scanning in");   // Counts down to scanning
delay(1000);
Serial.println("3");
delay(1000);
Serial.println("2");
delay(1000);
Serial.println("1");
delay(5000);
myservo.read();         //Reads servo angle(starts at 180) writes to confirm its at 180
Serial.println(angle);
myservo.write(angle);
delay(1000);
angle=angle-10;         //takes 10 from angle integer and sets that as the new angle integer.
Serial.println(angle);
myservo.write(angle);   //Writes the new angle to the servo

TurntableSeq();     //Runs turntable sequence. In this case stops every 5 degrees

delay(1000);

Horizback();  // Moves turntable closer to camera

Vertup();     // Moves camera higher

ServAng();  // Angles the camera down towards subject

TurntableSeq();  // Runs turntable rotation

delay(1000);

Horizback();

Vertup();

ServAng();

TurntableSeq();

delay(1000);

Horizback();

Vertup();

ServAng();

TurntableSeq();

delay(1000);

Horizback();

Vertup();

ServAng();

TurntableSeq();


myservo.read();
Serial.println(angle);
myservo.write(angle);
delay(1000);
angle=angle+35;
Serial.println(angle);
myservo.write(angle);

HorizForward();
delay(500);
HorizForward();
delay(500);
HorizForward();
delay(500);
HorizForward();
delay(500);
VertDown();
delay(500);
VertDown();
delay(500);
VertDown();
delay(500);
VertDown();



delay(1000);

Serial.println("Scan Done");

delay(100000);
}

void Takeimage()
{
delay (1000);    //wait 1 seconds
digitalWrite(40, HIGH);  //Adjust Focus
Serial.println("Adjust Focus");
delay(1000);  //wait 5 seconds
digitalWrite(41, HIGH);  //Release Shutter
delay(500);
Serial.println("Release Shutter");
delay(1000);   //wait 5 seconds
digitalWrite(40, LOW); // Sets camera pins back to low
digitalWrite(41, LOW); // Sets camera pins back to low
}

void TurntableSeq()
{

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);

Takeimage();
stepperTurn.step(turntablestep*STEPSTURN);
digitalWrite(36, LOW);
digitalWrite(37, LOW);
delay(1000);



}


void Horizback()
{

Serial.println("Horizontal Backward");
stepperHoriz.step(-STEPSHORIZ);
digitalWrite(50, LOW);
digitalWrite(51, LOW);
digitalWrite(52, LOW);
digitalWrite(53, LOW);
}

void Vertup()
{
Serial.println("Vertical Forward");
stepperVert.step(STEPSVERT);
digitalWrite(30, LOW);
digitalWrite(31, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
}

void ServAng()
{
  myservo.read();
Serial.println(angle);
myservo.write(angle);
delay(1000);
angle=angle-5;
Serial.println(angle);
myservo.write(angle);
}

void HorizForward()
{

Serial.println("Horizontal Backward");
stepperHoriz.step(STEPSHORIZ);
digitalWrite(50, LOW);
digitalWrite(51, LOW);
digitalWrite(52, LOW);
digitalWrite(53, LOW);

}

void VertDown()
{
Serial.println("Vertical Forward");
stepperVert.step(-STEPSVERT);
digitalWrite(30, LOW);
digitalWrite(31, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
  
}

