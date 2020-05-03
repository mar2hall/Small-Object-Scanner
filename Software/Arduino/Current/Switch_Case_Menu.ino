#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int upButton = 7;
int downButton = 8;
int selectButton = 6;
int menu = 1;

void setup() {
  lcd.begin(16,2);
//  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();

}

void loop() {
  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while(!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
    }
}

void updateMenu(){
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">CYLINDRICAL");
      lcd.setCursor(0,1);
      lcd.print(" 2-POINT KEYFRAME");
      break;
     case 2:
      lcd.clear();
      lcd.print(" CYLINDRICAL");
      lcd.setCursor(0,1);
      lcd.print(">2-POINT KEYFRAME");
      break;
     case 3:
      lcd.clear();
      lcd.print(">COMPLEX SPLINE");
      lcd.setCursor(0,1);
      lcd.print(" OPTION4");
      break;
     case 4:
      lcd.clear();
      lcd.print(" COMPLEX SPLINE");
      lcd.setCursor(0,1);
      lcd.print(">OPTION4");
      break;
     case 5:
      menu = 4;
      break;
    }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
  }
}

void action1() {
  lcd.clear();
  lcd.print(">Executing #CYLINDRICAL");
  delay(1500);
}
void action2() {
  lcd.clear();
  lcd.print(">Executing #2-POINT KEYFRAME");
  delay(1500);
}
void action3() {
  lcd.clear();
  lcd.print(">Executing #COMPLEX SPLINE");
  delay(1500);
}
void action4() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);
}
