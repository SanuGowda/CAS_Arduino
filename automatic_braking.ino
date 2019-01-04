#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define echo1 A0
#define trig1 A1
#define echo2 A2
#define trig2 A3
#define echo3 A4
#define trig3 A5
#define echo4 A6
#define trig4 A7
#define buzz 26
#define rely1 27
#define rely2 28
#define gsm 30
#define acc 31

int distance = 10, frt = 0, bck = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WELCOME");
  Serial.println("AUTOMATIC BRAKING SYSTEM");
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("AUTOMATIC");
  lcd.setCursor(1, 1);
  lcd.println("BRAKING SYSTEM");
  delay(2000);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(echo4, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(trig4, OUTPUT);
  pinMode(rely1, OUTPUT);
  pinMode(rely2, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(gsm, INPUT);
  pinMode(acc, INPUT);
  noTone(buzz);
}

void loop() {
  // put your main code here, to run repeatedly:
  int gs = digitalRead(gsm);
  int ac = digitalRead(acc);
  radar();
  if (frt == 1)
  {
    digitalWrite(rely1, LOW);
  }
  else if (bck == 1)
  {
    digitalWrite(rely2, LOW);
  }
  else if ((gs > 0) || (ac > 0))
  {
    Serial.println("gs or ac");
    digitalWrite(rely1, LOW);
    digitalWrite(rely2, LOW);
  }
  else
  {
    digitalWrite(rely1, HIGH);
    digitalWrite(rely2, HIGH);
  }
}

void radar()
{
  if ((radar1() <= distance) || (radar2() <= distance))
  {
    frt = 1;
    // To disconnect motor supply
    tone(buzz, 500);
    lcd.clear();
    Serial.println("OBSTRUCTION IN FRONT");
    lcd.print("   OBSTRUCTION");
    lcd.setCursor(4, 1);
    lcd.print("IN FRONT");
  }
  else if ((radar3() <= distance) || (radar4() <= distance))
  {
    bck = 1;
    // To disconnect motor supply
    tone(buzz, 300);
    lcd.clear();
    lcd.print("   OBSTRUCTION");
    lcd.setCursor(4, 1);
    lcd.print("IN BACK");
    Serial.println("OBSTRUCTION IN BACK");
  }
  else
  {
    frt = 0;
    bck = 0;
    // To reconnect motor supply
    digitalWrite(buzz, LOW);
    lcd.clear();
    lcd.print("Safe Distance :)");
    Serial.println("SAFE DISTANCE");
  }
}

long radar1(void)
{
  digitalWrite(trig1, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig1, LOW);
  long  dur = pulseIn(echo1, HIGH);
  dur = dur / 58;
  return dur;
}
long radar2(void)
{
  digitalWrite(trig2, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig2, LOW);
  long  dur = pulseIn(echo2, HIGH);
  dur = dur / 58;
  return dur;
}
long radar3(void)
{
  digitalWrite(trig3, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig3, LOW);
  long  dur = pulseIn(echo3, HIGH);
  dur = dur / 58;
  return dur;
}
long radar4(void)
{
  digitalWrite(trig4, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig4, LOW);
  long  dur = pulseIn(echo4, HIGH);
  dur = dur / 58;
  return dur;
}
