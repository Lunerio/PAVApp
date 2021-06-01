/*
  This file is part of the Arduino_MKRENV library.
  Copyright (c) 2019 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _MKRENV_H_
#define _MKRENV_H_

#include <Arduino.h>
#include <Wire.h>

enum {
  FAHRENHEIT,
  CELSIUS,
  PSI,
  MILLIBAR,
  KILOPASCAL,
  FOOTCANDLE,
  METERCANDLE,
  LUX = METERCANDLE
};

class ENVClass {
public:
  ENVClass(TwoWire& wire, int lightSensorPin);

  int begin();
  void end();

  float readTemperature(int units = CELSIUS);
  float readHumidity();
  float readPressure(int units = KILOPASCAL);
  float readIlluminance(int units = LUX);
  float readUVA();
  float readUVB();
  float readUVIndex();

  // deprecated, use readIlluminance() instead
  float readLux() { return readIlluminance(LUX); }

private:
  int i2cRead(uint8_t address, uint8_t reg);
  int i2cRead16(uint8_t address, uint8_t reg) { 
    return (i2cRead(address, reg) | (i2cRead(address, reg + 1) << 8));
  }
  int i2cWrite(uint8_t address, uint8_t reg, uint8_t val);

  int i2cReadWord(uint8_t address, uint8_t reg);
  int i2cWriteWord(uint8_t address, uint8_t reg, uint16_t val);

  void readHTS221Calibration();

private:
  TwoWire* _wire;
  int _lightSensorPin;

  float _hts221HumiditySlope;
  float _hts221HumidityZero;
  float _hts221TemperatureSlope;
  float _hts221TemperatureZero;
};

extern ENVClass ENV;

#endif
