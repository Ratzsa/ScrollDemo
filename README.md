# Yrkesakademin Trollhättan
# Software Developer Electrical & Autonomous Vehicles

## SV23TR E. Programmering och utveckling av inbyggda system
## YH00260-2020-3

## Class assignment 2023-08-18
## Scrolling LED matrix display

Small piece of code to scroll text across a set of max7219b LED matrix displays.
The code is currently set up to scroll on a set of 4 segments but can easily be changed around to work on this project:
https://wokwi.com/projects/296234816685212169

Files used:
config.h template taken from a different, ongoing, project of mine.
letters.c and letters.h content from https://www.hackster.io/SAnwandter1/programming-8x8-led-matrix-23475a and adjusted to work for me.
max72xx.c, max72xx.h, uart.c, uart.h, millis.c, millis.h all provided by teacher.

Having a large number of letters globally like that is suboptimal. A better way would be a temp array where each letter is placed and then sent to the relevant functions.

Scrolling can be adjusted for some fancy screen transitions. Might play around with that if time allows for it.