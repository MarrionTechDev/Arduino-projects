#include <LedControl.h>

LedControl lc = LedControl(11, 13, 10, 4); //Using the LedControl library to test bitmap

// Custom letters (5x8)
byte A[8] = { B01000, B10100, B11100, B10100, B00000, B00000, B00000, B00000 };
byte M[8] = { B10100, B11100, B10100, B10100, B00000, B00000, B00000, B00000 };
byte P[8] = { B11100, B10100, B11100, B10000, B00000, B00000, B00000, B00000 };

void setup() {
  for (int i = 0; i < 4; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  // Draw "AM" on device 0 (rightmost module, physical wiring may vary)
  drawTwoLetters(A, M, 0, 0, 5);

  // Draw "PM" on device 1 (next module to the left)
  drawTwoLetters(P, M, 1, 0, 5);
}

void loop() {}

void drawTwoLetters(byte letter1[8], byte letter2[8], int device, int offset1, int offset2) {
  for (int row = 0; row < 8; row++) {
    byte mergedRow = (letter1[row] << (8 - 5 - offset1)) | (letter2[row] << (8 - 5 - offset2));
    lc.setRow(device, row, mergedRow);
  }
}
