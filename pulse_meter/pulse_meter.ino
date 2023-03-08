/*
  Pulse Meter

  Some Meters have a LED that pulses in relation to your power consumption.
  These LEDs usually have a pulse rate of a 1.000 pulses for every kWh consumed.

  This sketch tries to measure the pulses and report power consumption

  Created in the spring of 2023
  by Jens Hansen

*/

const uint8_t pulse_pin = 18;            // gpio pin the photodiode D0 pin is attached to
const float pulse_rate = 1000;           // pulse rate you wish to simulate
const uint64_t pulse_filter = 10000;     // a debounce or filter interval
const uint8_t count_method = RISING;     // method to use when counting pin changes

uint64_t pulse_micros = 0;               // microseconds of newest pulse
uint64_t pulse_width = 0;                // microseconds since last pulse
uint64_t last_update = 0;                // microseconds of last pulse
uint64_t total_pulses = 0;               // count total pulses
uint64_t last_count = 0;                 // last count of totals - used to check if we need to take action in loop()



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
  attachInterrupt(pulse_pin, isr, count_method);
}

void loop() {
  if ((total_pulses - last_count) > 0) {
    last_count = total_pulses;
    Serial.printf("Total Pulses: %d\n", total_pulses);
    Serial.printf("Pulse Width: %d\n", pulse_width);
    Serial.printf("Power Use: %.3f Watt\n", floor(3600000000 / pulse_width));
    Serial.printf("Total Use: %.3f kWh\n\n", total_pulses * (1 / pulse_rate));
  }
}
