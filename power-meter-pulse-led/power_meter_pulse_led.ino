// power_meter_pulse_led - simulate the pulse led on a power panel
const int led_pin = 16;                 // gpio number of led pin
const float pulse_rate = 1000.0;        // number of pulses per kWh
const float power_use = 1000.0;         // watt. power consumption to simulate
const int pulse_duration = 100;         // how many ms before we turn off LED again

uint32_t now;
uint32_t last_pulse;
uint32_t pulse_interval; 
int led_state = LOW;

void setup() {
  pinMode(led_pin, OUTPUT);
  pulse_interval = ( 60 * 60 * 1000 / power_use ) * (pulse_rate / 1000); 
  last_pulse = millis();
}

void loop() {
  now = millis();
  if ( (now - last_pulse) >= pulse_interval) {
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
    last_pulse = now;
  } else if (led_state == HIGH) {
    if ( (now - last_pulse) >= pulse_duration) {
      led_state = !led_state;
      digitalWrite(led_pin, led_state);
    }
  }
}
