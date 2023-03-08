/*
  Pulse Meter with a display

  Some Meters have a LED that blinks (pulses) in relation to your power consumption.
  These LEDs usually have a pulse rate of a 1.000 blinks (pulses) for every kWh consumed.

  This sketch tries to measure the pulses and report power consumption on a SSD1306 display

  Created in the spring of 2023
  by Jens Hansen

*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

const uint8_t pulse_pin = 26;            // gpio pin the photodiode D0 pin is attached to
const float pulse_rate = 1000;           // pulse rate you wish to simulate
const uint64_t pulse_filter = 10000;     // a debounce or filter interval
const uint8_t count_method = RISING;     // method to use when counting pin changes

uint64_t pulse_micros = 0;               // microseconds of newest pulse
uint64_t pulse_width = 0;                // microseconds since last pulse
uint64_t last_update = 0;                // microseconds of last pulse
uint64_t total_pulses = 0;               // count total pulses
uint64_t last_count = 0;                 // last count of totals - used to check if we need to take action in loop()

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void ARDUINO_ISR_ATTR isr() {
  pulse_micros = micros();                   // get current micros
  pulse_width = pulse_micros - last_update;  // calculate pulse width
  // implement filter (debounce) function
  if ( (pulse_width) > pulse_filter) {
    last_update = pulse_micros;
    total_pulses++;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pulse_pin, INPUT_PULLDOWN);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();  
  display.setRotation(2);   // 0=0, 1=90, 2=180, 3=270
  display.setTextColor(WHITE); 
  attachInterrupt(pulse_pin, isr, count_method);
}

void loop() {
  if ((total_pulses - last_count) > 0) {
    last_count = total_pulses;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print(floor(3600000000 / pulse_width), 0);
    display.println(" W");
    display.setCursor(0, 24);
    display.setTextSize(1);
    display.print("Total: ");
    display.print(total_pulses * (1 / pulse_rate), 3);
    display.println(" kWh");
    display.display();
  }
}
