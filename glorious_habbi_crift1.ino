#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int s = 0, m = 0, h = 12, d = 1, mo = 1;

char months[13] = {' ', 'j', 'f', 'm', 'a', 'm', 'j', 'j', 'a', 's', 'o', 'n', 'd'};
int l[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int buttonHour = A0;
const int buttonMinute = A1;
const int buttonSet = A2;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  lcd.begin(16, 2);

  pinMode(buttonHour, INPUT_PULLUP);
  pinMode(buttonMinute, INPUT_PULLUP);
  pinMode(buttonSet, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Digital Clock");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    s++;

    if (s >= 60) {
      s = 0;
      m++;
      if (m >= 60) {
        m = 0;
        h++;
        if (h > 12) {
          h = 1;
          d++;
          if (d > l[mo]) {
            d = 1;
            mo++;
            if (mo > 12) {
              mo = 1;
            }
          }
        }
      }
    }
  }

  if (digitalRead(buttonHour) == LOW) {
    h++;
    if (h > 12) h = 1;
    delay(200);
  }

  if (digitalRead(buttonMinute) == LOW) {
    m++;
    if (m >= 60) m = 0;
    delay(200);
  }

  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  if (h < 10) lcd.print("0");
  lcd.print(h);
  lcd.print(":");
  if (m < 10) lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if (s < 10) lcd.print("0");
  lcd.print(s);

  lcd.setCursor(0, 1);
  lcd.print("DATE: ");
  if (d < 10) lcd.print("0");
  lcd.print(d);
  lcd.print("/");
  if (mo < 10) lcd.print("0");
  lcd.print(mo);
  lcd.print(" M:");
  lcd.print(months[mo]);
}