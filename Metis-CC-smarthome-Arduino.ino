//include downloads in het .vscode folder gaan niet kloppen op andere pc's
#include <Servo.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int TEMPERATUUR_PIN = A1;
const int LAMP = 6;
const int KNOP = 13;
const int SERVO_1_PIN = 10;
const int SERVO_2_PIN = 9;
Servo servo_1;
Servo servo_2;


float temps = 0.0;
int stand = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(KNOP, INPUT);
  pinMode(LAMP, OUTPUT);
  servo_1.attach(SERVO_1_PIN);
  servo_2.attach(SERVO_2_PIN);
}

void loop() {
  //altijd lamp input checken en de lamp aan/uitzetten
  stand = lampje();
  if (stand == 3 || stand == 4){
    servo_1.write(180);
    servo_2.write(0);
  } else {
    servo_1.write(0);
    servo_2.write(180);
  }
    analogWrite(LAMP, map(stand, 0, 4, 0, 255));

  
  unsigned long printtijd = millis();
  temperatuur(printtijd);
}

int lampje(){
  if(digitalRead(KNOP) == HIGH){
      stand += 1;
      if (stand > 4){
        stand = 0;
      }
    analogWrite(LAMP, map(stand, 0, 4, 0, 255));
    delay(250);
  }
  analogWrite(LAMP, map(stand, 0, 4, 0, 255));
  return stand;
}

long temperatuur(unsigned long afgelopen_printtijd){
  //check zonder delay() of er genoeg tijd voorbij is zodat het scherm niet spastisch doet
  // al zouden we delay() doen moest je knopje ingedrukt houden...
  // ik heb geen idee hoe delay van 0l werkt maar oke
  if ((millis()- afgelopen_printtijd) > 0l ){
    int Temp = analogRead(TEMPERATUUR_PIN);  
    float volts = (Temp / 965.0) * 5;  
    float celcius = (volts - 0.5) * 100;  
    
    lcd.home();
    lcd.print(celcius-4.8);
    lcd.setCursor(0,2);
    lcd.print("graden Celcius");
    unsigned long printtijd = millis();
    return printtijd;
  }
}
