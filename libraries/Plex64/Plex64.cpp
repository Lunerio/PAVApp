/*
  Plex64.h - Library for Plex64 analog input multiplexer
  Copyright (c) 2020 Chris Steenerson.  All right reserved.
*/

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// include this library's description file
#include "Plex64.h"

// include description files for other libraries used (if any)
#include "Wire.h"

// Constructor /////////////////////////////////////////////////////////////////
// creates instance and sets variables for rest of library to use. The rest of the
// startup was moved to begin() for STM32 compatibility
Plex64::Plex64(uint8_t address, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinH)
{
  // set private variables
  _address = address;
  _pinE = pinE;
  _pinF = pinF;
  _pinG = pinG;
  _pinH = pinH;
}

// begin function
void Plex64::begin(void) {
  // start default i2c bus and set clock to 400kHz
  Wire.begin();
  Wire.setClock(400000);

  // set analog pins to inputs
  pinMode(_pinE, INPUT);
  pinMode(_pinF, INPUT);
  pinMode(_pinG, INPUT);
  pinMode(_pinH, INPUT);

  //initialize output register variables, all channels start at input 0
  _outputRegisterLow = 0;
  _outputRegisterHigh = 0;

  //setup all expander ports as outputs and then update output register to set all outputs to low
  Wire.beginTransmission(_address);  // setup direction registers
  Wire.write(0x06);  // pointer to config register
  Wire.write(0);  // Port0 all output 
  Wire.write(0);  // Port1 all output
  Wire.endTransmission(); 
  updateOutputRegisterAll();
}

//sets all 4 channels to the same input
//@param input: must be integer from 0-15
void Plex64::setAllChannels(uint8_t input)
{
  //update output register variables, all to same input
  _outputRegisterE = input;
  _outputRegisterF = input;
  _outputRegisterG = input;
  _outputRegisterH = input;
  
  //update IO expander to apply
  updateOutputRegisterAll();
}

// sets one channel (E/F/G/H) to the given input (0-15)
// @param pin: integer from 0-63 or pin name E0-15,F0-15,G0-15,H0-15
// @param force: boolean, set true to always update IO expander regardless of current state
void Plex64::setChannel(uint8_t pin, bool force = 0)
{
  uint8_t input = 0;  

  //channel E
  if (pin < 16) {
    input = pin;
    if (force == 0 && _outputRegisterE != input ) {
      _outputRegisterE = input;
      updateOutputRegisterLow();
    }
    else {
      updateOutputRegisterLow();
    }
  }
  
  //channel F
  else if (pin < 32) {
    input = pin - 16;
    if (force == 0 && _outputRegisterF != input ) {
      _outputRegisterF = input;
      updateOutputRegisterLow(); 
    }
    else {
      updateOutputRegisterLow();
    }
  }
  
  //channel G
  else if (pin < 48) {
    input = pin - 32;
    if (force == 0 && _outputRegisterG != input ) {
      _outputRegisterG = input;
      updateOutputRegisterHigh();
    }
    else {
      updateOutputRegisterHigh();
    }
  }
  
  //channel H
  else if (pin < 64) {
    input = pin - 48;
    if (force == 0 && _outputRegisterH != input ) {
      _outputRegisterH = input;
      updateOutputRegisterHigh();
    }
    else {
      updateOutputRegisterHigh();
    }
  }
}

// sets one channel to the given input, reads with analogRead and returns the value. needs a number from 0-63 or pin name, same as setChannel
// @param pin: integer from 0-63 or pin name E0-15,F0-15,G0-15,H0-15
// @param force: boolean, set true to always update IO expander regardless of current state.
uint16_t Plex64::readAnalog(uint8_t pin, bool force = 0)
{
  setChannel(pin, force);
  uint16_t result;

  //channel E
  if (pin < 16) {
    result = analogRead(_pinE);
    return result;
  }
  
  //channel F
  else if (pin < 32) {
    result = analogRead(_pinF);
    return result;
  }
  
  //channel G
  else if (pin < 48) {
    result = analogRead(_pinG);
    return result;
  }
  
  //channel H
  else if (pin < 64) {
    result = analogRead(_pinH);
    return result;
  }
}

//get and returns contents of output registers, useful to confirm that writing to IO expander is working correctly
uint16_t Plex64::getAllChannels(void)
{
  uint16_t data = 0;
  Wire.beginTransmission(_address);
  Wire.write(0x02); // pointer to low output register
  Wire.endTransmission();  
  Wire.requestFrom(_address, 2);
  if(Wire.available()) {
    data = Wire.read();
  }
  if(Wire.available()) {
    data = data + (Wire.read() << 8);
  }
  return data;
}

//private function to write low output register variable to IO expander
void Plex64::updateOutputRegisterLow(void)
{
  Wire.beginTransmission(_address);
  Wire.write(0x02);  // pointer to low output register
  Wire.write(_outputRegisterLow);  // update PORT0
  Wire.endTransmission(); 
}

//private function to write high output register variable to IO expander
void Plex64::updateOutputRegisterHigh(void)
{
  Wire.beginTransmission(_address);
  Wire.write(0x03);  // pointer to high output register
  Wire.write(_outputRegisterHigh);  // update PORT1
  Wire.endTransmission(); 
}

//private function to write full output register variable to IO expander
void Plex64::updateOutputRegisterAll(void)
{
  Wire.beginTransmission(_address);
  Wire.write(0x02);  // pointer to low output register
  Wire.write(_outputRegisterLow);  // update PORT0
  Wire.write(_outputRegisterHigh);  // update PORT1
  Wire.endTransmission(); 
}