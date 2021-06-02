
This is a C++ library for Arduino, built and tested on version 1.8.10, and based on Arduino's public Test library and 9555 expander examples.

Installation
------

To install this library, download the .zip file and with Arduino open, go 'Sketch->Include Library->Add .ZIP Library...' and open the downloaded file. Or, just place the extracted library as a subfolder in your Arduino/libraries folder.

When installed, this library should look like:

|File/Folder|Description|
|---|---|
|Arduino/libraries/Plex64|This library's folder|
|Arduino/libraries/Plex64/Plex64.cpp|Library implementation file|
|Arduino/libraries/Plex64/Plex64.h|Library description file|
|Arduino/libraries/Plex64/keywords.txt|Syntax coloring file|
|Arduino/libraries/Plex64/examples|Examples in the 'open' menu)|
|Arduino/libraries/Plex64/readme.txt|This file|

Requirements
--------
The Wire library is required, and is included by the library. Wire is a board-specific library and is installed with most boards. You may need to include Wire.h in your sketch to change certain options such as the I2C clock speed.

Adding to Sketch
--------
To use this library in a sketch, go to the Sketch -> Import Library menu and select Plex64.  This will add a corresponding line to the top of your sketch:
`#include <Plex64.h>`

To stop using this library, delete that line from your sketch.

Features
--------

- Supports multiplexing up to 64 inputs into 4 analog pins using 4x CD4067B analog multiplexers/MUXes.
- Configurable 1:1/2:1/4:1/8:1 voltage dividers and OP amp buffering allow high impedance input up to 18V with low settling time. Shield must be configured with VIN larger than the input voltage to support inputs greater than Arduino VBUS (3.3V/5V).
- I2C IO expander minimizes pin requirement footprint and 8 possible addresses support up to 512 analog inputs per I2C bus.

Usage
--------

Plex64(uint8_t address, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinH)

- Class constructor, place before setup().
- Parameter 'address': the I2C address of the 9555 IO expander. Board defaults to 0x20 but can be changed to 0x20-0x27 with solder jumpers A0/A1/A2.
- Parameters 'pinE, pinF, pinG, pinH': the Arduino analog pin numbers that are connected to the shield E/F/G/H channels. Default are A0, A1, A2 and A3 respectively when shield is plugged directly into a standard Arduino.

void begin(void);

- No parameters or return. This must be run inside setup(). Performs startup tasks for I2C interface, analog inputs and IO expander.

void setAllChannels(uint8_t input);

- Sets all 4 channels to the same input number. Does not check how they are set beforehand.

- Parameter 'input': the input number (0-15) that will be used to set all 4 channels.

void setChannel(uint8_t pin, bool force);

   - Sets one single channel to a given input. First it checks the \_outputRegister private variable and only updates the IO expander if it isn't already set, unless 'force' flag is used.
- Parameter 'pin': must be either an integer from 0-63, or a pin name E0-15, F0-15, G0-15, H0-15 which will be translated to 0-63 int using enum table.
- Parameter 'force': boolean, set to 'true' to skip current status check and always update the IO expander. Can be omitted, which is equivalent to false.

uint16_t readAnalog(uint8_t pin, bool force);

   -    Sets one single channel to a given input (if not set already), and then performs and returns analogRead from the same input. analogRead will be affected by standard Arduino functions such as analogReadResolution().
- Parameter pin: must be either an integer from 0-63, or a pin name E0-15, F0-15, G0-15, H0-15 which will be translated to 0-63 int using enum table.
- Parameter 'force': boolean, set to 'true' to skip current status check and always update the IO expander. Can be omitted, which is equivalent to false.

uint16_t getAllChannels(void);

- Gets and returns full 16-bit contents of IO expander output register, can be used to confirm that the expander is being updated correctly.

License
---------
This library is licensed under [MIT license](https://opensource.org/licenses/MIT).