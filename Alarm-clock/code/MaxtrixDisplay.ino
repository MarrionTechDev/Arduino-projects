#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

MD_Parola matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

String message = "This is a message!";

void setup() {
  matrix.begin();
  matrix.setIntensity(1);
  matrix.displayText(message.c_str(), PA_CENTER, 60, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (matrix.displayAnimate()) {
    matrix.displayReset();
  }
}
