# Arduino, ESP8266 and STM32 multiplexed outputs library - uMuxOutputLib #

Master status:   [![Build Status](https://travis-ci.org/Naguissa/uMuxOutputLib.svg?branch=master)](https://travis-ci.org/Naguissa/uMuxOutputLib)

## What is this repository for? ##

Really tiny library to control multiplexed outputs.

It cycles among multiplexed outputs using a timer to control all pins.

## Important: Dependencies ##

This library requires uTimerLib libary; it's available on IDE Library Manager and also here:

https://github.com/Naguissa/uTimerLib
https://github.com/Naguissa/uTimerLib/releases



## How do I get set up? ##

You can get it from Arduino libraries directly, searching by uMuxOutputLib.

For manual installation:

 * Get the ZIP from releases link: https://github.com/Naguissa/uMuxOutputLib/releases
 * Rename to uMuxOutputLib.zip
 * Install library on Arduino


## Documentation and extras ##

You can find all documentation and extras in this repository: https://github.com/Naguissa/uMuxOutputLib_doc_and_extras

Due GitHub limitations HTML documentation is not avaliable online, you need to download the zip.


## Usage ##

### Constructor: ###

uMuxOutputLib::uMuxOutputLib(uint8_t npins, uint8_t nmuxes, int *pins, int *muxes, unsigned int freq);

Parameters:
 - npins: number of real pins, excluding muxes
 - nmuxes: number of muxes pins
 - pins: Array of all real pins, excluding muxes.
 - muxes: Array of pins used to multiplex real pins.
 - freq: Optional. Desired refresh frequency. Default is 70 (Hz). This frequency will be multiplied by number of muxes.

### Set a value: ###


void uMuxOutputLib::setPinAbsolute(uint position, bool value);

Parameters:
  - position: Position of the bit on linear fashion
  - value: Value to be set


void uMuxOutputLib::setPinMuxPin(uint8_t pin, uint8_t mux, bool value);

Parameters:
  - pin: Pin position on passed pins array (starting at 0)
  - mux: Mux position on passed muxes array (starting at 0)
  - value: Value to be set


### Start library ###

void uMuxOutputLib::attachInterrupt();

Attaches internal timer interrupts to run multiplexed pins.


### Extra: Mux logic level ###

bool uSevenSegmentLib::activeMuxValue = false;

This variable is used to indicate the level of an active mux. All muxes will be set to inverse of this value when they are not active.


## Typical usage: ##

 - You instantiate an object (usually a global scope object): uMuxOutputLib muxed(nPins, nMuxes, pinsArray, muxesArray);
 - Then set any initial value on it on setup(): muxed.set(position, bool_value); or muxed.set(pin, mux, bool_value);
 - And attach interrupts to start working (still on setup()): muxed.attachInterrupt();
 - Then, wherever you want, you can change displayed values at your will using same methods as 2nd step.



## Examples ##

Included on example folder, available on Arduino IDE.

 - 6 leds cycling, connected using 3 real pins and 2 muxed pins

## Who do I talk to? ##

 * [Naguissa](https://github.com/Naguissa)
 * https://www.foroelectro.net/librerias-arduino-ide-f29/umuxoutputlib-libreria-arduino-para-controlar-mult-t293.html
 * https://www.naguissa.com


## Contribute ##

Any code contribution, report or comment are always welcome. Don't hesitate to use GitHub for that.


You can make a donation via PayPal: https://paypal.me/foroelectro


Thanks for your support.


Contributors hall of fame: https://www.foroelectro.net/hall-of-fame-f32/contributors-contribuyentes-t271.html
