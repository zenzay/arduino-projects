// pulse_led - simulate the pulse led on a power panel
const float pulse_rate = 1000.0f;        // number of blinks per kWh
const float watt_target = 1000.0f;       // power consumption to simulate - not used if random_power flag is set
const int led_pin = 16;                  // gpio pin number of led
const uint32_t led_on_ms = 100;          // led on duration
uint32_t blink_interval = ( 1000.0f / pulse_rate ) * ( 1000.0f / watt_target ) * 3600.0f;             // blink interval in milliseconds
uint32_t now = 0;                        // current millis
uint32_t last_blink = 0;                 // last blink millis
int led_state = LOW;                     // initial led state

void setup() {
  pinMode(led_pin, OUTPUT);                                 // blink!
  last_blink = millis();                                    // get the base millis for evaluating the time spend since last blink
}

void loop() {
  now = millis();
  if ( (now - last_blink) > blink_interval) {
    // if millis passed since last blink is over the specified interval, turn led on
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
    last_blink = now;                                  // remember when we last turn the led on
  } else if (led_state == HIGH) {
    if ( (now - last_blink) >= led_on_ms) {
      // if led is on and the time is up, turn it off
      led_state = !led_state;
      digitalWrite(led_pin, led_state);
    }
  }
}
