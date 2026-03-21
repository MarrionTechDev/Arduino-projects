# Arduino Alarm Clock Project

This project walks through building a simple alarm clock using an Arduino UNO, a MAX7219 Dot Matrix display, and a DS3231 RTC module.

---

## 🔧 Component Assembly

First, connect your Arduino to your computer using a USB power cable.  
Make sure the power indicator light turns on.

---

##  Dot Matrix Display (MAX7219)

Connect the dot matrix display to the Arduino using **male-to-female jumper wires**.

> **Note:**  
> The "D" pins refer to the **digital pins (0–13)** on the Arduino UNO.

### Wiring (SPI Connection)

VCC -> 5V
GND -> GND
DIN -> D11
CS  -> D10
CLK -> D13

> **Troubleshooting Tip:**  
> If your Arduino is not detected by the IDE after connecting the matrix:
> 1. Disconnect the matrix display  
> 2. Restart the Arduino IDE  
> 3. Connect the Arduino alone first  
> 4. Then reconnect the jumper wires to the Matrix Display

Great, now you have a bright nightlight to illuminate your room in the dark.
---

### Test Display

Upload this test code to test the display and wiring:

- [View Code](code/MaxtrixDisplay.ino)

---

### Example Display Programs

- Simple clock display:  
  [View Code](code/SimpleTimeDisplayMatrix.ino)

- Custom images using bit patterns:  
  [View Code](pmAmSingleDisplayLEDCont.ino)

- Number/clock formatting:  
  [View Code](code/amNumberDisplay.ino)

---

## 🕒 Connecting the DS3231 RTC Module

RTC = **Real-Time Clock**

This module component keeps accurate time and continues running even when the Arduino is powered off (thanks to its battery).

---

### 🔌 Wiring

VCC -> 5V
GND -> GND
SCL -> A5
SDA -> A4
SQW -> Not used

> **Important:**  
> If you're powering both the RTC and the matrix:
> - Use a **breadboard**
> - Use **male-to-male jumper wires**
> - Share the 5V and GND lines properly between the two

---

## Testing the RTC

Upload this code to test RTC:

- [View Code](code/RTCTest.ino)

### Steps:

1. Upload the code to the Arduino  
2. Uncomment this line:
   ```cpp
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
3. Upload again to set the time
4. Open Tools → Serial Monitor
5. Set baud rate to 9600

You should now see the current date and time updating every second.

## 🧪 Testing the RTC Battery

1. After setting the time, comment the line again:
   ```cpp
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
2. Disconnect power from the Arduino
3. Wait 3–5 minutes
4. Reconnect and upload again 

If the time is still correct, the battery works
If not, replace the CR2032 battery

---

### Final Clock Code 

Code for working AM to PM 12-hour format: 
[View Code](code/TimeDisplayAmPm.ino)

###Final Look

Final look at the build after assembly of components
[View Image](Images/2026-03-201.jpeg)

