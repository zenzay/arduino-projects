Power Meter Pulse LED
=====================

A simple Arduino sketch to simulate the Pulse-LED, found on some Electricity Power Meters.

It only does fixed wattage, for now. I tried to do some simulation of real power consumption patterns, but that made the whole thing crash after a couple of hours. Not sure why, and not interested in following it up, as I don't need it.

The parameters are set in the code.

Components
----------

* A White LED (other colours might work).
* A 330Ω resistor (or anything from 220 to 1k).
* An ESP board (I recommend an ESP32, but an ESP8266 might work for you)

Assets
------
Here's a picture of the test-bed I used to test the accuracy of my [ESPHome Power Meter](https://github.com/zenzay/esphome-projects/tree/main/power-meter).

![pulse_led_test_bed](./assets/images/pulse_led_test_bed.jpg)

