// power_meter_pulse_led - simulate the pulse led on a power panel

const int led_pin = 16;
const int pulse_duration = 100;
const float power_consumption = 1000;
const float pulse_rate = 1000;
const unsigned long hour_ms = 3600000;

unsigned long now;
unsigned long last_pulse;
unsigned long pulse_interval; 
int led_state = LOW;

unsigned long get_pulse_interval(float watt, float rate)
{
  return ( hour_ms / watt ) * (rate / 1000.0); 
}

void setup() {
  pinMode(led_pin, OUTPUT);
  pulse_interval = get_pulse_interval(power_consumption, pulse_rate);
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
