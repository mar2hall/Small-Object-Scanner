/*
 * Development of Small Object Scanner 
 * 
 */

#include <EEPROM.h>

//storeFocal = 1
//storeMinFocus = 2
//storeSensorHeight = 3
//storeSensorWidth = 4
//storeQuality = 5




void setup() {
  Serial.begin(9600);

}


void loop() {
  readEeprom();
//  initEeprom();

}


void readEeprom(){
 
  int a;  //creates int a for storing the returned user inputted access option
  int b;  //creates int b for storing the returned user inputted write value
  int eepromValue = 0;
  
  Serial.println("What option to change? ");
  Serial.println("1. Focal Length");
  Serial.println("2. Minimum Focus Distance");
  Serial.println("3. Sensor Height");
  Serial.println("4. Sensor Width");
  Serial.println("5. Default scan Quality");
  Serial.println();
  while (Serial.available() == 0){}
  delay(10);
  a = readSerial(); //stores incoming number
  //Serial.print(" Address to access is, ");
  //Serial.println(a);

  whichOption(a);

  eepromValue = EEPROM.read(a);
  Serial.println(eepromValue);

  Serial.println("What do you want to change the value to?");
  while (Serial.available() == 0){}
  delay(10);
  b = readSerial(); //stores incoming number

  writeEeprom(a,b);    //calls writeEeprom, passing address and value 

  Serial.println("Value saved");
   
}


/*
void initEeprom(){

  int a;  //creates int a for storing the returned user inputted access address
  int b;  //creates int b for storing the returned user inputted write number
  int o;  //creates int b for storing the returned user option
  
  Serial.println("What option to chose? ");
  while (Serial.available() == 0){}
  delay(10);
  a = readSerial(); //stores incoming number
  
  delay(10);
  
  whichOption(a);
  
  //Serial.print(" Address to write to is, ");
  //Serial.println(a);
  Serial.flush();

  delay(10);

  //Serial.println("What value to write? ");
  while (Serial.available() == 0){}
  delay(10);
  b = readSerial(); //stores incoming number
  Serial.print(" Value to write is, ");
  Serial.println(b);  

  writeEeprom(a,b);    //calls writeEeprom, passing i 
  

  
}

*/

void writeEeprom(int address, int value){

  
  EEPROM.write(address,value);
  delay(10);
  
}


int readSerial(){
  int i =Serial.parseInt();
  if(i<1)
  {
    return;
  }
  Serial.println(i);
  delay(10);
  Serial.parseInt();
  Serial.flush();
  delay(10);
  return i;
}

void whichOption(int option){
  
  if(option==1){
    Serial.print("Focal length has a value of ");
    return;
  }
  if(option==2){
    Serial.print("Minimum focus distance between object and camera has a value of ");
    return;
  }
  if(option==3){
    Serial.print("Sensor height has a value of ");
    return;
  }
  if(option==4){
    Serial.print("Sensor width has a value of ");
    return;
  }
  if(option==5){
    Serial.print("Default scan Quality has a value of ");
    return;  
  }
  
}
