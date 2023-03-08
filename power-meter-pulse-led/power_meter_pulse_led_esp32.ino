/*
  Blink a LED on ESP32 using hardware timers and GPIO directly

  A simple Sketch that attempts to simulate the pulsing LED on a Power Meter.

  Some Meters have a LED that blinks (pulses) in relation to your power consumption.
  These LEDs usually have a pulse rate of a 1.000 blinks (pulses) for every kWh consumed.
  Some Power Meters really like to 'have the LED blinking' though, and use a pulse rate set to 10.000!
  
  This ESP32 version tries to improve accuracy by using hardware timers, interrupts and using the GPIO registers 'directly', instead of using digitalWrite()

  Created in the spring of 2023
  by Jens Hansen

*/

#define BASE_PULSE_RATE 1000          // the base pulse rate. 1000 blinks with each kWh used.
#define MICROS_HOUR 3600000000        // micros per hour 
#define DEF_PULSE_DUR 50000           // default pulse duration in micros
#define DEF_INTERVAL 10              // default interval in micros

// set the following constants according to your wishes
const uint8_t led_pin = 17;              // gpio number of led pin
const float power_consumption = 1000;    // power consumption to simulate in watts
const float pulse_rate = 1000;           // pulse rate you wish to simulate

const uint64_t int_micros = DEF_INTERVAL;
const uint64_t int_per_hour = MICROS_HOUR / int_micros;
const uint64_t int_pulse_dur = DEF_PULSE_DUR / int_micros;

uint8_t led_state;                       // current state of led
uint32_t pulse_interval;                 // pulse interval
uint32_t bitmask_gpio;                   // bitmask specifying which gpio we wanna mess with
uint64_t int_counter;                    // interrupt counter
hw_timer_t *on_timer = NULL;             // hardware timer structure

void IRAM_ATTR onTimer()
{
  int_counter += 1;
  if ( int_counter > pulse_interval )
  {
    GPIO.out_w1ts = bitmask_gpio;
    led_state = HIGH;
    int_counter = 0;
  }
  else if ( led_state == HIGH ) {
    if ( int_counter > int_pulse_dur )
    {
      led_state = LOW;
      GPIO.out_w1tc = bitmask_gpio;
    }    
  }  
}

void setup() {
  
  gpio_config_t io_conf;              // gpio configuration structure
  io_conf.mode = GPIO_MODE_OUTPUT;    // set mode to output

  //bitmask of gpio numbers that are part of this configuration
  //you can use multiple pins like thus: (1 << PIN1) | (1 << PIN2) | (1 << PIN3)
  bitmask_gpio = (1 << led_pin);
  io_conf.pin_bit_mask = bitmask_gpio;
  gpio_config(&io_conf);              // apply the configuration

  led_state = LOW;
  int_counter = 0;
  // calculate the pulse interval from specified power consumption and pulse rate
  pulse_interval = int_per_hour / power_consumption * (BASE_PULSE_RATE / pulse_rate); 

  on_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(on_timer, &onTimer, true);
  timerAlarmWrite(on_timer, int_micros, true);    
  timerAlarmEnable(on_timer);
}

void loop() {}
