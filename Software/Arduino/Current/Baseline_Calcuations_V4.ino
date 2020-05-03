/*
 * Small object scanner development
 * 
 * Baseline Calculator
 * 
 */
#include <math.h>

float turntableRadius = 150.0;
float sensorHeight = 24.0;
float sensorWidth = 35.9;
float focalLength = 35.0;
float minFocus = 350.0;
float imageOverlay = 70.0;

float baselineHoriz = 0;
float baselineVert = 0;


void setup() {
  Serial.begin(9600);

}

void loop() {

  baselineCalc();
  delay(100);
  rotationCalc();
  delay(100000);

}

void baselineCalc(){
  baselineVert =(((minFocus/focalLength)*sensorHeight)*(1-(imageOverlay/100L)));
  baselineHoriz =(((minFocus/focalLength)*sensorWidth)*(1-(imageOverlay/100L)));

  Serial.print("Vertical Baseline is ");
  Serial.println(baselineVert);

  Serial.print("Horizontal Baseline is ");
  Serial.println(baselineHoriz);
  
}

void rotationCalc(){

  long cameraRadius =(minFocus+turntableRadius);
  long baselineConversion = baselineHoriz;

  Serial.print("baselineConversion is ");
  Serial.println(baselineConversion); 

  Serial.print("baselineHoriz is ");
  Serial.println(baselineHoriz);

  Serial.print("Camera radius is ");
  Serial.println(cameraRadius);
  
  float internalAngle = acos(( (square(cameraRadius)) + (square(cameraRadius)) - (square(baselineHoriz)))/(2*(cameraRadius * cameraRadius)));
  float degreesAngle = internalAngle*57.3;

  Serial.print("Rotation Angle in Radians is ");
  Serial.println(internalAngle);

  Serial.print("Rotation Angle in Degrees is ");
  Serial.println(degreesAngle);

  float rotationSteps = floor(360/degreesAngle) + 1;

  Serial.print("Rotation Steps is ");
  Serial.println(rotationSteps);

  
}
