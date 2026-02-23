#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <RTClib.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;

char timeBuffer[6]; // HH:MM
bool colonOn = true; // for blinking colon

// Custom AM letters (5x8)
byte A[8] = { B01000, B10100, B11100, B10100, B00000, B00000, B00000, B00000 };
byte M[8] = { B10100, B11100, B10100, B10100, B00000, B00000, B00000, B00000 };

// Custom PM letters (5x8)
byte P_letter[8] = { B11110, B10100, B11100, B10000, B00000, B00000, B00000, B00000 };
byte M_letter[8] = { B10100, B11100, B10100, B10100, B00000, B00000, B00000, B00000 };

void setup() {
  Serial.begin(9600);

  // Setup Parola for time display
  matrix.begin();
  matrix.setZone(0, 0, 2); // Devices 0-2 for time
  matrix.setIntensity(8);
  matrix.displayClear();

  // Setup MX for AM/PM display on rightmost device
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 6);
  mx.clear();

  // Setup RTC
  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1); // Stop if no RTC
  }

  // Uncomment ONE TIME to set RTC to current computer time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();

  // Toggle colon for blinking every 500ms
  colonOn = !colonOn;

  // Convert hour to 12-hour format without leading zero
  int hour12 = now.hour() % 12;
  if (hour12 == 0) hour12 = 12; // 0 -> 12

  // Build time string
  if (colonOn) {
    sprintf(timeBuffer, "%d:%02d", hour12, now.minute()); // e.g., 2:05
  } else {
    sprintf(timeBuffer, "%d %02d", hour12, now.minute()); // e.g., 2 05 (for colon blink)
  }

  // Display time on devices 0-2
  matrix.displayText(timeBuffer, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
  matrix.displayAnimate();

  // Display AM/PM on device 3
  if (now.hour() < 12) {
    drawTwoLetters(A, M, 3, 0, 5); // AM
  } else {
    drawTwoLetters(P_letter, M_letter, 3, 0, 5); // PM
  }

  delay(500); // 500ms for blinking colon
}

// Draw two letters on a single 8x8 device
void drawTwoLetters(byte letter1[8], byte letter2[8], int device, int offset1, int offset2) {
  for (int row = 0; row < 8; row++) {
    uint8_t mergedRow = (letter1[row] << (8 - 5 - offset1)) | (letter2[row] << (8 - 5 - offset2));
    mx.setRow(device, row, mergedRow);
  }
}
