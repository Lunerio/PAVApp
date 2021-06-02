/*
  Plex64.h - Library for plex64 analog input multiplexer
  Copyright (c) 2020 Chris Steenerson.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Plex64_h
#define Plex64_h

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// enumerate pins so we can use channel+input/column+row pin names instead of 0-63
enum : uint8_t { 
  E0,E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,
  F0,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,
  G0,G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,
  H0,H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15
};

// 
class Plex64
{
  public:
    Plex64(uint8_t address, uint8_t pinE, uint8_t pinF, uint8_t pinG, uint8_t pinH);
    void begin(void);
    void setAllChannels(uint8_t input);
    void setChannel(uint8_t pin, bool force);
    uint16_t readAnalog(uint8_t pin, bool force);
    uint16_t getAllChannels(void);
  private:
    //variables to store instance info
    uint8_t _pinE;
    uint8_t _pinF;
    uint8_t _pinG;
    uint8_t _pinH;
    uint8_t _address;
    
    //register structure that allows updating each group of 4 address pins without shifting
    union{
      struct {
        byte _outputRegisterE: 4;
        byte _outputRegisterF: 4;
      };
      uint8_t _outputRegisterLow;
    };
    union {
      struct {
        byte _outputRegisterG: 4;
        byte _outputRegisterH: 4;
      };
      uint8_t _outputRegisterHigh;
    };

    void updateOutputRegisterLow(void);
    void updateOutputRegisterHigh(void);
    void updateOutputRegisterAll(void);
};

#endif