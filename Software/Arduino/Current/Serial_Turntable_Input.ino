/*
 * Rotational movement Standard code
 * 
 * Small Object Scanner 
 * 
 */


void setup() {
  Serial.begin(9600);
  Serial.println("--- Serial Monitor Connection Started ---");
}

void loop() {

  recieveAngle();
  
}

void recieveAngle(){

  int angleDegree;  //creates int for storing the returned user inputted number via serial

  Serial.println(" State turntable angle, ... ");
  while (Serial.available() == 0){}
  delay(10);
  angleDegree = readSerial(); //stores incoming number
  Serial.print(" Selected Turntable Angle is, ");
  Serial.println(angleDegree);

  turntableExecute(angleDegree);    //calls turntableExecute, passing angleDegree 
  
  
}

void turntableExecute(int angleDegree){

 float rotationStep = 360/angleDegree;
 float rotationCurrent = 0;

 Serial.print("angleDegree is ");
 Serial.println(angleDegree);

 Serial.print("Executing turntable motion, ");
 //Serial.println(rotationStep);

  for (float i = 0; i <= rotationStep; i++) 
    {
    Serial.print("Current step is, ");
    Serial.println(rotationCurrent);
    delay(10);
    rotationCurrent = rotationCurrent + angleDegree;
    delay(10);
    takePhoto();
    delay(10);
    motion();
    delay(10);
  } 
}

int readSerial(){
  int i =Serial.parseInt();
  if(i<1)
  {
    return;
  }
  Serial.println(i);
  Serial.parseInt();
  return i;
}

void motion()
{
  delay(100);
  Serial.println("Moving!");
}

void takePhoto() {

    Serial.println("Photo Taken!");
//    digitalWrite(FOCUS_PIN, LOW);
//    delay(1500);
//    digitalWrite(SHUTTER_PIN, LOW);
    delay(100);
//    digitalWrite(FOCUS_PIN, HIGH);
//    digitalWrite(SHUTTER_PIN, HIGH);

}
