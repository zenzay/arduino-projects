/*
  Pulse LED

  A simple Sketch that pulses a LED, with microsecond precision.

  Created in the spring of 2023
  by Jens Hansen

*/

const uint8_t led_pin = 17;                // gpio number of led pin
const uint64_t pulse_interval = 1000000;   // micros between each pulse
const uint64_t pulse_duration = 10000;     // micros to keep the led on

uint64_t now;                         // current micros
uint64_t last_pulse = 0;              // micros at last pulse
uint8_t led_state = LOW;              // current led state

void setup()
{
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  now = micros();
  if ( (now - last_pulse) > pulse_interval )
  {
    led_state = HIGH;
    last_pulse = now;
    digitalWrite(led_pin, led_state);
  }
  else if ( led_state == HIGH )
  {
    if ( (now - last_pulse) > pulse_duration )
    {
      led_state = LOW;
      digitalWrite(led_pin, led_state);
    }
  }
}
