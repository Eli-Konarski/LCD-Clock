/* Hello, My name is Eli Konarski. Time of uplaod to git hub, 08/2/2021. check out the readme.md for more info*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long event = 940;
unsigned long previousTime = 0;


unsigned long int Delay = 100;
char newLine = ' ';
unsigned long int btn1 = 48;
unsigned long int btn2 = 38;
unsigned long int btn3 = 50;
unsigned long int btn4 = 17;
unsigned long int LED1 = 30;  
unsigned long int buttonStatebtn1; 
unsigned long int buttonStatebtn2;
unsigned long int buttonStatebtn3;
unsigned long  int secondsPassed = 55;
unsigned long  int minutsPassed = 59;
unsigned long  int hourPassed = 15;
unsigned long  int minutsPassedALARM = 0;
unsigned long  int hourPassedALARM = 16;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(LED1, OUTPUT);
  pinMode(btn1, INPUT);    
  pinMode(btn2, INPUT);                                                                                                                                                                                                                                                                                      
  pinMode(btn3, INPUT);                                                                                                                                                                                                                                                                     }


void updateClock() {
  // this is essantally a usless delay, the only thing it does it avoids visual glitches.
    delay(60);
    if (millis() - previousTime >= event){
      secondsPassed+= 1;
      previousTime = millis();
    }
    
    if (secondsPassed == 60) {
     minutsPassed += 1;
     secondsPassed = 0;
    }
    if (minutsPassed == 60) {
      if (buttonStatebtn2 != HIGH) {
        hourPassed += 1;
      }
        
      
      minutsPassed = 0;
    }
    if (hourPassed == 24){
      hourPassed = 0;
      minutsPassed = 0;
      
    } 
  }

  void buttonIsPressed(){

   buttonStatebtn1 = digitalRead(btn1);
   buttonStatebtn2 = digitalRead(btn2);
   buttonStatebtn3 = digitalRead(btn3);
   if (buttonStatebtn3 == HIGH) { 
    if (buttonStatebtn1 == HIGH) {
      if (hourPassed < 10){
        lcd.setCursor(1, 0);
        lcd.print(' ');
           
      }
        hourPassedALARM += 1;
        delay(100);
        event = 830;
        } else {
        event = 940;
        }


if (minutsPassedALARM == 60) {
      minutsPassedALARM = 0;
    }
    if (hourPassedALARM== 24){
      hourPassedALARM = 0;
      minutsPassedALARM = 0;
      
    } 
  
if (buttonStatebtn2 == HIGH) {
   minutsPassedALARM += 1;
   delay(100);
  event = 830;
   } else {
    event = 940;
   }
   
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(":");
  lcd.setCursor(2, 0);
  lcd.print(":");
  lcd.setCursor(0, 0);
  lcd.print(hourPassedALARM);
  if (secondsPassed < 10) {
  lcd.setCursor(7, 0);
  lcd.print(' ');
  lcd.setCursor(2, 0);
  lcd.print(":");
  }
  if (minutsPassedALARM < 10) {
  lcd.setCursor(3, 0);
  lcd.print('0');
  lcd.setCursor(4, 0);
  lcd.print(minutsPassedALARM);
  } else {
    lcd.setCursor(3, 0);
    lcd.print(minutsPassedALARM);
  }
  
} else {
  lcd.clear();
if (buttonStatebtn1 == HIGH) {
   if (hourPassed < 10){
      lcd.setCursor(1, 1);
      lcd.print(' ');
      event = 830;
   } else {
    event = 940;
   }
   delay(100);
   hourPassed += 1;
  }
if (buttonStatebtn2 == HIGH) {
   minutsPassed += 1;
   delay(100);
   event = 830;
   } else {
    event = 940;
   }
                              
  lcd.setCursor(2, 1);
  lcd.print(":");
  lcd.setCursor(6, 1);
  lcd.print(secondsPassed); 
  lcd.setCursor(2, 1);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print(hourPassed);
  if (secondsPassed < 10) {
  lcd.setCursor(7, 1);
  lcd.print(' ');
  lcd.setCursor(2, 1);
  lcd.print(":");
  }
  if (minutsPassed < 10) {
  lcd.setCursor(3, 1);
  lcd.print('0');
  lcd.setCursor(4, 1);
  lcd.print(minutsPassed);
  } else {
    lcd.setCursor(3, 1);
    lcd.print(minutsPassed);
    }
    
  }
}

void alarm() {
   if (hourPassed == hourPassedALARM && minutsPassed == minutsPassedALARM && secondsPassed < 20){
        digitalWrite(LED1, HIGH);
        delay(80);
        digitalWrite(LED1, LOW);
        delay(80);
    }else {
        digitalWrite(LED1, LOW);
    }


  if (LED1 == HIGH){
    event = 900;
  } else {
    event = 940;
  }

}

void loop() {
    updateClock();
    buttonIsPressed();
    alarm();

    
}
