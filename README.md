# Digital Pixel Clock
Insipired by Destin's wall clock as seen in the background of almost every [Smarter Every Day](https://www.youtube.com/@smartereveryday) video.

## Creating secret.h
Within your `DigitalPixelClock` directory, create a `secret.h` header file.  

Populate as follows:
```c++
// Network Config
#define WIFI_SSID "" // Your WiFi SSID (2.4GHz)
#define WIFI_PASS "" // Your WiFi Password
```

## B.O.M.  
| **Component** 	| **Description**                               	|
|---------------	|-----------------------------------------------	|
| Wemos D1 Mini 	| Arduino Microcontroller                       	|
| 36x WS2812B 5050 	| Addressable RGB LED Tape. 60 pixels per meter 	|

## Schematic  
![Schematic](/Assets/breadboard-tix-clock.png)

## Additional Information - Pixel Mapping
Pixel Allocation (What pixels apply to each time component).  
Pixels are counted from index 0 and increment sequentially along the LED tape. Ensure you have the correct orientation of the LED tape and wiring follows the schematic above.

```c++
int hourTens[]  = {0, 12, 24};
int hourUnits[] = {2, 3, 4, 14, 15, 16, 26, 27, 28};
int minTens[]   = {6, 7, 18, 19, 30, 31};
int minUnits[]  = {9, 10, 11, 21, 22, 23, 33, 34, 35};
```