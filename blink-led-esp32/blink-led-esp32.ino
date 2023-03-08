/*
  Blink a LED on an ESP32 using hardware timers and setting GPIO bits directly

  The ESP32 has 4 high resolution hardware timers. This sketch is employing one of them to track time.

  The sketch also sets/clears the pins the same way digitalWrite does it. The following is (folded a bit) from esp32-hal-gpio.c

  extern void IRAM_ATTR __digitalWrite(uint8_t pin, uint8_t val) {
    if(val) {
      if(pin < 32) {
        GPIO.out_w1ts = ((uint32_t)1 << pin);
      } else if(pin < 34) {
        GPIO.out1_w1ts.val = ((uint32_t)1 << (pin - 32));
      }
    } else {
      if(pin < 32) {
        GPIO.out_w1tc = ((uint32_t)1 << pin);
      } else if(pin < 34) {
        GPIO.out1_w1tc.val = ((uint32_t)1 << (pin - 32));
      }
    }
  }

  Created in the spring of 2023
  by Jens Hansen

*/

const uint8_t led_pin = 17;       // GPIO number of LED pin
hw_timer_t * timer = NULL;        // Our hardware timer structure
uint8_t state = LOW;              // Initial LED state
uint32_t interval = 1000000;      // Blink interval in microseconds

// The OnTimer function called by timer interrupts
void IRAM_ATTR onTimer()
{
    state = !state;         // Toogle state
    if (state)
    {
      // Set the bit = Turn LED On
      GPIO.out_w1ts = ((uint32_t)1 << led_pin);
    }
    else
    {
      // Clear the bit = Turn LED Off
      GPIO.out_w1tc = ((uint32_t)1 << led_pin);
    }
}

void setup() {
  // Setting up the gpio
  gpio_config_t io_conf;              // gpio configuration structure
  io_conf.mode = GPIO_MODE_OUTPUT;    // set mode to output
  //Setting the bitmask of gpio pins that are part of this configuration
  //you can use multiple pins like thus: (1 << PIN1) | (1 << PIN2) | (1 << PIN3)
  io_conf.pin_bit_mask = ((uint32_t)1 << led_pin);
  gpio_config(&io_conf);              // apply the configuration

  /* Create the timer
   We're using timer 0, setting the pre-scaler to 80 and telling it count up (true).
   1 tick take 1/(80MHZ/80) = 1us so we set pre-scaler to 80 */
  timer = timerBegin(0, 80, true);
  /* Attach the interrupt to our onTimer function */
  timerAttachInterrupt(timer, &onTimer, true);
  /* Set alarm to call onTimer function every second 1 tick is 1us
   and repeat the alarm */
  timerAlarmWrite(timer, interval, true);
    /* Enable the timer */
  timerAlarmEnable(timer);
}

void loop() {
  /* Move along. Nothing to see here... */
}
