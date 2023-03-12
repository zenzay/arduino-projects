/*
  Power Meter Pulse LED

  A simple Sketch that attempts to simulate the pulsing LED on a Power Meter.

  Some Meters have a LED that blinks (pulses) in relation to your power consumption.
  These LEDs usually have a pulse rate of a 1.000 blinks (pulses) for every kWh consumed.
  Some Power Meters really like to 'have the LED blinking' though, and use a pulse rate set to 10.000!

  Created in the spring of 2023
  by Jens Hansen

*/

#define BASE_PULSE_RATE 1000              // the base pulse rate. 1000 blinks with each kWh used.
#define MICROS_PER_HOUR 3600000000        // microseconds in an hour

// set the following constants according to your wishes
const uint8_t led_pin = 17;               // gpio number of led pin
const float power_consumption = 1000;     // power consumption to simulate in watts
const float pulse_rate = 1000;            // pulse rate you wish to simulate
const uint32_t pulse_duration = 50000;    // how many micros to keep the led on
const bool random_power = true;           // randomize (pseudo) power consumption
const int power_min = 100;                // minimum random power consumption
const int power_max = 1000;               // maximum random power consumption

uint32_t now;                             // current milliseconds fetched at start of loop
uint32_t last_pulse;                      // milliseconds at last pulse
uint32_t pulse_interval;                  // milliseconds between each pulse
uint8_t led_state;                        // current led state

void setup()
{
  pinMode(led_pin, OUTPUT);
  // calculate the pulse interval from specified power consumption and pulse rate
  pulse_interval = MICROS_PER_HOUR / power_consumption * (BASE_PULSE_RATE / pulse_rate); 
  
  // If using ESPHome pulse_meter to test this, it turns out that I need to add 1000 micros to pulse_interval...why?
  // Maybe because they do this:
     // We quantize our pulse widths to 1 ms to avoid unnecessary jitter
     // const uint32_t pulse_width_ms = this->pulse_width_us_ / 1000;
     // this->publish_state((60.0f * 1000.0f) / pulse_width_ms);
  // anyway... ESPHome pulse_meter isn't 100% accurate when trying out 'odd' power consumption levels f.eks 2847 W
  
  last_pulse = 0;               // initial microseconds
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
    if (random_power) {
      pulse_interval = MICROS_PER_HOUR /  random(power_min, power_max)  * (BASE_PULSE_RATE / pulse_rate);
    }
  }
  else if ( led_state == HIGH )
  {
    if ( (now - last_pulse) >= pulse_duration )
    {
      led_state = LOW;
      digitalWrite(led_pin, led_state);
    }
  }
}
