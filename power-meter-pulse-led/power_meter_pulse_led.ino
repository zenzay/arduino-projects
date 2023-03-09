/*
  Power Meter Pulse LED

  A simple Sketch that attempts to simulate the pulsing LED on a Power Meter.

  Some Meters have a LED that blinks (pulses) in relation to your power consumption.
  These LEDs usually have a pulse rate of a 1.000 blinks (pulses) for every kWh consumed.
  Some Power Meters really like to 'have the LED blinking' though, and use a pulse rate set to 10.000!

  Created in the spring of 2023
  by Jens Hansen

*/

#define BASE_PULSE_RATE 1000          // the base pulse rate. 1000 blinks with each kWh used.
#define MICROS_PER_HOUR 3600000000    // microseconds in an hour

// set the following constants according to your wishes
const uint8_t led_pin = 17;           // gpio number of led pin
const float power_consumption = 1000; // power consumption to simulate in watts
const float pulse_rate = 1000;        // pulse rate you wish to simulate
const uint32_t pulse_duration = 50000;   // how many micros to keep the led on

uint32_t now;                         // current milliseconds fetched at start of loop
uint32_t last_pulse;                  // milliseconds at last pulse
uint32_t pulse_interval;              // milliseconds between each pulse
uint8_t led_state;                    // current led state

void setup()
{
  pinMode(led_pin, OUTPUT);
  // calculate the pulse interval from specified power consumption and pulse rate
  pulse_interval = MICROS_PER_HOUR / power_consumption * (BASE_PULSE_RATE / pulse_rate); 
  last_pulse = micros();        // initial microseconds
  led_state = LOW;              // initial led state
}

void loop()
{
  now = micros();
  if ( (now - last_pulse) > pulse_interval )
  {
    led_state = HIGH;
    digitalWrite(led_pin, led_state);
    last_pulse = now;
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
