// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int TEMPERATUUR_PIN = A1;
const int LAMP = 10;
const int KNOP = 9;

float vorigeCelcius = 0.0;
float temps = 0.0;
int stand = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(KNOP, INPUT);
  pinMode(LAMP, OUTPUT);
  
}

void loop() {
  float temps = temperatuur();
  if(digitalRead(KNOP) == HIGH){
      stand += 1;
      if (stand > 4){
        stand = 0;
      }
    delay(200);
  }
  analogWrite(LAMP, map(stand, 0, 4, 0, 255));
}


float temperatuur(){
  // delay(250);
  // lcd.scrollDisplayLeft();
  int Temp = analogRead(TEMPERATUUR_PIN);  
  float volts = (Temp / 965.0) * 5;  
  float celcius = (volts - 0.5) * 100;  
  float deltaCelcius = abs(vorigeCelcius - celcius);
  if (deltaCelcius > 1.3){
    lcd.home();
    lcd.print(celcius-4);
    lcd.setCursor(0,2);
    lcd.print("graden Celcius");
    vorigeCelcius = celcius;
  }
  return celcius-6;
}
