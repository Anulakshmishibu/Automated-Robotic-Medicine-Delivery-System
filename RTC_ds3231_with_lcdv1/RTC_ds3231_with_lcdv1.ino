
#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display
RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;
int next = 8;
int INC = 9;
int set_mad = 10;

#define buzzer 13
#define sw1 6
int HOUR, MINUT, SECOND;

void setup() {
  
  Serial.begin(9600);
    myservo1.attach(2);  // attaches the servo on pin 9 to the servo object
    myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
    myservo3.attach(4);  // attaches the servo on pin 9 to the servo object
    myservo4.attach(5);  // attaches the servo on pin 9 to the servo object
    myservo1.write(180);
    delay(100);// sets the servo position according to the scaled value
    myservo2.write(180);
        delay(100);// sets the servo position according to the scaled value
// sets the servo position according to the scaled value
    myservo3.write(180);
        delay(100);// sets the servo position according to the scaled value
// sets the servo position according to the scaled value
    myservo4.write(180);
        delay(100);// sets the servo position according to the scaled value
// sets the servo position according to the scaled value

  Wire.begin();
  RTC.begin();
 lcd.init();
  lcd.backlight(); // Turn on the backlight
  pinMode(INC, INPUT_PULLUP);
  pinMode(next, INPUT_PULLUP);
  pinMode(set_mad, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Medicin reminder");
  lcd.setCursor(0, 1);
  lcd.print(" Using Arduino  ");
  delay(2000);
  if (!RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
     // RTC.adjust(DateTime(__DATE__, __TIME__));

}

void loop() {
  int temp = 0, val = 1, temp4;

  if(!digitalRead(sw1))
      myservo4.write(90);
      else
      myservo4.write(170);


  DateTime now = RTC.now();
Serial.print("hour 1 =");
Serial.println(EEPROM.read(11));
 Serial.print("min 1 =");
Serial.println(EEPROM.read(12));

 Serial.print("hour 2 =");
Serial.println(EEPROM.read(13));

Serial.print("min 2 =");
Serial.println(EEPROM.read(14));

Serial.print("hour 3 =");
Serial.println(EEPROM.read(15));

Serial.print("min 3 =");
Serial.println(EEPROM.read(16));

  if (digitalRead(set_mad) == 0)  
  {
    lcd.setCursor(0, 0);
    lcd.print("  Set Medicine  ");
    lcd.setCursor(0, 1);
    lcd.print("  Reminder time ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 1");
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 2");
    defualt();
    delay(1000);
    time(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 3");
    defualt();
    time(3);
    lcd.setCursor(0, 0);
    lcd.print("Medicin reminder");
    lcd.setCursor(0, 1);
    lcd.print("  time has set  ");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  match();
  delay(200);
}

void defualt() {
  lcd.setCursor(0, 1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}
void time(int x) {
  int temp = 1, minuts = 0, hours = 0, seconds = 0;
  while (temp == 1) {
    if (digitalRead(INC) == 0) {
      HOUR++;
      if (HOUR == 24) {
        HOUR = 0;
      }
      while (digitalRead(INC) == 0)
        ;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0) {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);
      temp = 2;
      while (digitalRead(next) == 0)
        ;
    }
  }
  while (temp == 2) {
    if (digitalRead(INC) == 0) {
      MINUT++;
      if (MINUT == 60) { MINUT = 0; }
      while (digitalRead(INC) == 0)
        ;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0) {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
      while (digitalRead(next) == 0)
        ;
    }
  }
  delay(1000);
}
void match() {
  int tem[17];
  for (int i = 11; i < 17; i++) {
    tem[i] = EEPROM.read(i);
  }
  if (HOUR == tem[11] && MINUT == tem[12]) {
        myservo1.write(90);

    beep();
    beep();
    lcd.setCursor(0, 0);
    lcd.print("  Take Group One  ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine     ");
    delay(60000);
                myservo1.write(170);

  }

  if (HOUR == tem[13] && MINUT == tem[14]) {
            myservo2.write(90);

    beep();
    beep();
   
    lcd.setCursor(0, 0);
    lcd.print("  Take Group Two  ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine     ");
        delay(60000);
          myservo2.write(170);

  }


  if (HOUR == tem[15] && MINUT == tem[16]) {
            myservo3.write(90);

    beep();
    beep();
    lcd.setCursor(0, 0);
    lcd.print("Take Group Three ");
    lcd.setCursor(0, 1);
    lcd.print("     Medicine    ");
           delay(60000);
                myservo3.write(170);

  }
}

void beep() {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}
