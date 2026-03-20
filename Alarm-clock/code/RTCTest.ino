#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  delay(2000);  // allow serial to open

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // ----------------------------
  // ONLY UNCOMMENT THIS ONE TIME
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // ----------------------------

  Serial.println("RTC Ready!");
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day());
  Serial.print("  ");

  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());

  Serial.println();

  delay(1000);  // print every second
}
