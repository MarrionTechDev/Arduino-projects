#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4   // 32x8 display = 4 modules
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

MD_Parola matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Time variables
int hours = 12;
int minutes = 0;
int seconds = 0;

char timeBuffer[6]; //HH:MM
bool colonOn = true; //for blinking

void setup() {
  matrix.begin();
  matrix.setIntensity(5); // brightness (0-15)
  matrix.displayClear();
}

void loop() {
  colonOn = !colonOn; // Toggle colon every 500ms

  if (colonOn){ // Format time with or without colon
    sprintf(timeBuffer, "%02d:%02d", hours, minutes);
  }
  else{
    sprintf(timeBuffer, "%02d %02d", hours, minutes);
  }
  
matrix.displayText(timeBuffer, PA_CENTER,0,0,PA_PRINT,PA_NO_EFFECT);
matrix.displayAnimate();

delay(500); //500ms for blinging colon

static int halfSeconds = 0; //increment seconds every 500ms cycle
halfSeconds ++; 

  if (halfSeconds >= 2) { // 2*500ms = 1 secs
    halfSeconds = 0;
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }

    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }

    if (hours >= 24) {
      hours = 0;

    }
  }
}