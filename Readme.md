MSGEQ7 Library 1.2 + Board v1.0
===============================
![Header](header.png)

The MSGEQ7 is an IC designed to analyze music on different frequencies.
This library reads the MSGEQ7 with 7 different frequencies from range 0-255, stereo or mono.
It can be used to visualize audio through Leds for example.
This repository also includes the source of an [Breakout Board](https://github.com/NicoHood/MSGEQ7/tree/dev#breakout-board).

The frequencies are:
63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25KHz, 16kHz

####Features
* IDE 1.6.x with every Arduino compatibly
* [Sparkfun Spectrum Shield](https://www.sparkfun.com/products/13116) compatible
* Reads 1-n MSGEQ7 sensors
* Compact and fast implementation
* More compact and flexible 8 bit resolution
* Optional 10 bit resolution
* Value smoothing
* Tools to reduce noise
* A [Breakout Board](https://github.com/NicoHood/MSGEQ7/tree/dev#breakout-board).

####Examples included:
* Led: blinks led, shows basic usage
* Serial: shows spectrum via serial and how to use more channels
* FastLED: blinks led strip with different frequencies. Shows how to use different syntax.
Uses [FastLED library](https://github.com/FastLED/FastLED)

More projects/contact:
http://www.NicoHood.de


Hardware Setup
==============
To use the MSGEQ7 you first need a few other parts and connect them properly.
Make sure the 33pF capacitor and the 200k Ohm resistor are precise.
Otherwise the frequencies may be off.
See the [data sheet](https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf) for more information.

#####Required parts (stereo):
* 2x [MSGEQ7 IC](https://www.sparkfun.com/products/10468)
* 1x [Audio Jack 3.5mm](https://www.sparkfun.com/products/8032) (or any other audio input)
* 2x 10nF Capacitor
* 4x 100nF Capacitor
* 2x 33pF Capacitor
* 2x 200k Ohm Resistor
* Led or Led strips
* 1x 220 Ohm Resistor (for Led)

###Breadboard Setup
This would be an example breadboard setup for the Led example.

![Schematic](extras/breadboard/MSGEQ7_Schematic.png)

![Breadboard Setup](extras/breadboard/MSGEQ7_Breadboard.png)


Software installation
=====================
Install the library as you are used to.
More information can be found [here](http://arduino.cc/en/guide/libraries).


API Documentation
=================

#####`template <bool smooth, uint8_t resetPin, uint8_t strobePin, uint8_t firstAnalogPin, uint8_t ...analogPins> class CMSGEQ7`
Every CMSGEQ7 instance needs some pins passed via template to optimize the code.
If you want to smooth the readings with the last reading pass true as first argument.
The reset and strobe pin can be anyone on the board.
You can input as many analog pins as needed.
For example as mono mode only a single IC, stereo 2 or surround as many channels as you want.

#####`void begin(void);`
Do whatever is required to initialize the IC and resets it.

#####`void end(void);`
Sets pins to input again to safely remove connections if needed

#####`void reset(void);`
Resets IC, so it starts reading at 0 again.
Normally this is not needed since its done in the `begin()` function.

#####`bool read(void);`
Basic read function. Reads all channels and saves value inside the buffer.
You can access the buffer with the `get()` function.
Up to 400FPS are possible with 2 channels I've measured.

#####`bool read(const uint32_t currentMicros, const uint32_t interval);`
To automatically read every X seconds you may also use this function.
Use the `ReadsPerSecond(f)` Makro with the interval and you can easily choose a good speed interval.
You can also leave out the first argument, this will be automatically replaced with a `micros()`.

#####`MSGEQ7_data_t get(const uint8_t frequency, const uint8_t channel);`
Returns the data of the selected frequency and channel.
By default this returns an `uint8_t` value, for 10bit resolution `uint16_t`.
Frequency should be 0-6 where 0 is the lowest frequency (Bass) and 6 the highest.
Depending on how many analog pins you have attached you can select the channel here (0-n).
You can also leave out the channel variable to get an average value of all channels.

#####`MSGEQ7_data_t getVolume(uint8_t channel);`
Returns the overall volume of all frequencies of a channel.
By default this returns an `uint8_t` value, for 10bit resolution `uint16_t`.
Depending on how many analog pins you have attached you can select the channel here (0-n).
You can also leave out the channel variable to get an average volume of all channels.

#####`MSGEQ7_data_t map(MSGEQ7_data_t x, MSGEQ7_data_t in_min = MSGEQ7_IN_MIN, MSGEQ7_data_t in_max = MSGEQ7_IN_MAX, MSGEQ7_data_t out_min = MSGEQ7_OUT_MIN, MSGEQ7_data_t out_max = MSGEQ7_OUT_MAX);`
Maps the input from a given input range to an output range.
This is useful to reduce noise. All MSGEQ7 produce a noise of about 15-19 if no music is played.
This macro can be used to remap the input. You can leave out the last 4 arguments, they will be replaced with default values.
For 10 bit resolution the function uses `uint16_t` and 1023 as default maximum value.

#####`Definitions`
```cpp
//#define MSGEQ7_10BIT
#define ReadsPerSecond(f) (1000000UL / (f))

// basic frequencys definitions (0-6 valid, 7 channels)
#define MSGEQ7_0 0
#define MSGEQ7_1 1
#define MSGEQ7_2 2
#define MSGEQ7_3 3
#define MSGEQ7_4 4
#define MSGEQ7_5 5
#define MSGEQ7_6 6
#define MSGEQ7_BASS 0
#define MSGEQ7_LOW 0
#define MSGEQ7_MID 3
#define MSGEQ7_HIGH 5
```


Breakout Board
==============
The MSGEQ7 Breakout Board lets you easily hook up an audio source or microphone to your microcontroller.
You may also use a 2nd audio output to pass the audio signal to music boxes again.
You can solder a 6 or 8 pin header to the board and connect it to a breadboard for example.
It is fully open source so you can create a copy for yourself or modify it.

#####Features:
* Stereo music analyze
* Audio input via 3.5mm Jack
* Additional audio output
* Additional audio in/output via pin header
* Mounting holes
* Breadboard compatible
* Easy to solder (DIP parts)
* [Open Source Hardware](http://www.oshwa.org/definition/)

#####Required parts:
* 2x [MSGEQ7 IC](https://www.sparkfun.com/products/10468)
* 2x [Audio Jack 3.5mm](https://www.sparkfun.com/products/8032)
* 8 pin header male
* 2x IC socket 8 pins (optional)
* 2x 10nF Capacitor
* 4x 100nF Capacitor
* 2x 33pF Capacitor
* 2x 200k Ohm Resistor


#####Files:
You can find all needed files in the [board](extras/board/) folder.
Click view raw to download the PDF files.

#####Schematic
![Schematic](extras/board/MSGEQ7_Schematic.png)

#####PCB
![PCB](extras/board/MSGEQ7_PCB.png)


Additional Information
======================
This library started as my very first one and become better and better over the time.
To be honest it is now very complex, due to the optimization and API flexibility.

The read function itself is simple though.
Have a look at the library itself, its not so complicated.
But keep attention to the LOW and HIGH setting of strobe and reset

Keep in mind that the smoothed value is created from the last read + current read divided by 2.
I found out that reading with 50 FPS is a good value to use.

You can reset the IC with myMSGEQ7.reset() but you don't need that normally.

If you only want to use mono mode or one IC just connect the two inputs together to the MSGEQ7
and only use one analog input. But you can also use multiply ICs and connect them to an analog input each.
The reset and strobe line is connected to every IC, so you don't need to multiply them.

The output only ranges from 0-255 to save memory use it easier. You don't lose much information.
If you still want to read up to 1023 define MSGEQ7_10BIT before including the library.

The IC has a standard value at about 10-19. You should keep that in mind.
In this case the Led always glims a bit. Have a look at the map() function to improve this.


Version History
===============
```
1.2.1 Release (xx.xx.2015)
* Added 1.6.x library schema

1.2 Release (23.04.2015)
* Added breakout board files v1.0
* Optimized performance
* Variable number of ICs readable
* Added optional 10bit resolution
* Added more functions/tools
* Improved examples
* Added MSGEQ7_VERSION definition
* Added library.properties

1.1 Release (10.07.2014)
* Changed syntax
* Optimized performance
* Added more examples

1.0 Release (13.04.2014)
* Added general functionality
```


License and Copyright
=====================
If you use this library for any cool project let me know!

```
Copyright (c) 2014-2015 NicoHood

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
