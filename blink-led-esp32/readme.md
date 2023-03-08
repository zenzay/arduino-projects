# Blink LED ESP32 #

## Blink a LED on an ESP32 using hardware timers and setting GPIO bits directly ##

The ESP32 has 4 high resolution hardware timers. This sketch is employing one of them to track time.

The sketch also speed things up a bit by bypassing digitalWrite().

Note: This sketch was developed as a stepping-stone to improving my Power-Meter project.
