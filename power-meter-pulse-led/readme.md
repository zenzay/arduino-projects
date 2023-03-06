Power Meter Pulse LED
=====================

A simple Arduino sketch to simulate the Pulse-LED, found on some Electricity Power Meters.

It only does fixed wattage, for now. I've thought about doing some kind of simulation of real power consumption patterns, I but don't need or have any use for that. I basically only need a fixed wattage, so I easily can check the accuracy of the device which is tracking usage with a Photodiode.

The default power consumption is set at 1000 Watt, with a pulse rate of 1000 blinks per kWh, but you can change that in the code.

Note: It's a bit inaccurate at specific high levels of simulated power consumption. 2100 Watt, for example. It'll keep the intervals steady but the LED will pulse slightly too fast or slow, and thus not reflect the set level *exactly* - it'll be a few Watts off. It's simply not fast enough to manage a 1ms resolution.

Components
----------

* A White LED (other colours might work).
* A 330Ω resistor (or anything from 220 to 1k).
* An ESP board (I recommend an ESP32, but an ESP8266 might work for you)

Assets
------
Here's a picture of the test-bed I used to test the accuracy of my [ESPHome Power Meter](https://github.com/zenzay/esphome-projects/tree/main/power-meter).

![pulse_led_test_bed](./assets/images/pulse_led_test_bed.jpg)

