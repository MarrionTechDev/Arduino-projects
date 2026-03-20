#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

// MD_Parola object for time display
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// MD_MAX72XX object for AM/PM display
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Custom AM letters (5x8)
byte A[8] = { B01000, B10100, B11100, B10100, B00000, B00000, B00000, B00000 };
byte M[8] = { B10100, B10100, B11100, B10100, B00000, B00000, B00000, B00000 };

// Custom PM letters (5x8)
byte P_letter[8] = { B11110, B10001, B10001, B11110, B10000, B10000, B00000, B00000 };
byte M_letter[8] = { B10100, B10100, B11100, B10100, B00000, B00000, B00000, B00000 };

void setup() {
  // Initialize Parola for devices 0-2 (time display)
  P.begin();
  P.setZone(0, 0, 2);         // Zone 0: devices 0,1,2
  P.setIntensity(4);
  P.displayClear();
  P.setTextAlignment(PA_RIGHT);
  P.displayText("12:34", PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);

  // Initialize MX for custom AM/PM on device 3
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 8);
  mx.clear();

  // Draw AM or PM on rightmost device
  drawTwoLetters(A, M, 3, 0, 5);  // Change to drawTwoLetters(P_letter, M_letter, 3, 0, 5) for PM
}

void loop() {
  P.displayAnimate();  // Animates the time on devices 0-2
}

// Function to draw two letters on a single device
void drawTwoLetters(byte letter1[8], byte letter2[8], int device, int offset1, int offset2) {
  for (int row = 0; row < 8; row++) {
    uint8_t mergedRow = (letter1[row] << (8 - 5 - offset1)) | (letter2[row] << (8 - 5 - offset2));
    mx.setRow(device, row, mergedRow);
  }
}
