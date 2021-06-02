/****************************************************************************************************************************
  UDPClientMultiple.ino
  For ESP8266/ESP32-AT-command running shields
  
  ESP_AT_Lib is a wrapper library for the ESP8266/ESP32 AT-command shields
  
  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_Lib
  Licensed under MIT license
  
  @example UDPClientMultiple.ino
  @brief The UDPClientMultiple demo of library WeeESP8266.
  @author Wu Pengfei<pengfei.wu@itead.cc>
  @date 2015.02
  
  @par Copyright:
  Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version. \n\n
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
  Version: 1.2.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      12/02/2020 Initial coding for ESP8266/ESP32-AT shields to support Mega, nRF52, SAMD, DUE, STM32, etc.
  1.1.0   K Hoang      10/05/2021 Add support to BOARD_SIPEED_MAIX_DUINO and RASPBERRY_PI_PICO
  1.2.0   K Hoang      17/05/2021 Add support to RP2040-based boards using Arduino-mbed RP2040 core. Fix compiler warnings
 *****************************************************************************************************************************/

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT     Serial

#define _ESP_AT_LOGLEVEL_       4

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT      true

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ESP_AT_USE_NRF528XX)
    #undef ESP_AT_USE_NRF528XX
  #endif
  #define ESP_AT_USE_NRF528XX      true
#endif

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(ESP_AT_USE_SAMD)
    #undef ESP_AT_USE_SAMD
  #endif
  #define ESP_AT_USE_SAMD           true
#endif

#if ( defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) )
  #if defined(ESP_AT_USE_AVR)
    #undef ESP_AT_USE_AVR
  #endif
  #define ESP_AT_USE_AVR      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ESP_AT_USE_SAM_DUE)
    #undef ESP_AT_USE_SAM_DUE
  #endif
  #define ESP_AT_USE_SAM_DUE        true
#endif

#if ( defined(CORE_TEENSY) && !( defined(__MKL26Z64__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega32U4__) ) )
  #if defined(ESP_AT_USE_TEENSY)
    #undef ESP_AT_USE_TEENSY
  #endif
  #define ESP_AT_USE_TEENSY         true
#endif

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
  #if defined(ESP_AT_USE_STM32)
    #undef ESP_AT_USE_STM32
  #endif
  #define ESP_AT_USE_STM32      true
#endif

#if (ESP_AT_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NORDIC_NRF52840DK"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(MDBT50Q_RX)
    #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

  #define EspSerial Serial1

#elif defined(ESP_AT_USE_SAMD)
  #if defined(ARDUINO_SAMD_ZERO)
    #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

  #define EspSerial Serial1

#elif defined(ESP_AT_USE_SAM_DUE)
  #if ( defined(ARDUINO_SAM_DUE) || (__SAM3X8E__) )
    #define BOARD_TYPE      "SAM DUE"
  #else
    #define BOARD_TYPE      "SAM Unknown"
  #endif

  #define EspSerial Serial1

#elif ( defined(CORE_TEENSY) )
  // For Teensy 4.0
  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif    
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE      "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE      "Teensy 3.5"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE      "Teensy 3.2/3.1"
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE      "Teensy 3.0"
  #elif ( defined(__MKL26Z64__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega32U4__) )
    #error "Teensy LC, 2.0++ and 2.0 not supported"
  #else
    #define BOARD_TYPE      "Teensy Unknown"
  #endif

  #define EspSerial Serial1

#elif ESP_AT_USE_STM32
  
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
    #error Board STM32F0 not supported
  #elif defined(STM32F1)
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif

  // For STM32, you have to declare and enable coreresponding Serial Port somewhere else before using it
  #define EspSerial Serial1

#elif defined(BOARD_SIPEED_MAIX_DUINO)

  #warning SIPEED_MAIX_DUINO board selected
  #define BOARD_TYPE  "BOARD_SIPEED_MAIX_DUINO"

  #define EspSerial       Serial1

#elif ( defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
    
  #warning RASPBERRY_PI_PICO board selected

  #if defined(ARDUINO_ARCH_MBED)

    #if defined(BOARD_NAME)
      #undef BOARD_NAME
    #endif

    #if defined(ARDUINO_RASPBERRY_PI_PICO) 
      #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
    #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
      #define BOARD_TYPE      "MBED DAFRUIT_FEATHER_RP2040"
    #elif defined(ARDUINO_GENERIC_RP2040)
      #define BOARD_TYPE      "MBED GENERIC_RP2040"
    #else
      #define BOARD_TYPE      "MBED Unknown RP2040"
    #endif
  #else  
    #define BOARD_TYPE  "RASPBERRY_PI_PICO"
  #endif
  
  #define EspSerial       Serial1   
  
#elif (ESP_AT_USE_AVR)

  #if defined(ARDUINO_AVR_MEGA2560)
    #define BOARD_TYPE      "AVR Mega2560"
  #elif defined(ARDUINO_AVR_MEGA) 
    #define BOARD_TYPE      "AVR Mega"
  #else
    #define BOARD_TYPE      "AVR ADK"
  #endif

  // For Mega, use Serial1 or Serial3
  #define EspSerial Serial3

#else
  #error Unknown or unsupported Board. Please check your Tools->Board setting.
  
#endif    //ESP_AT_USE_NRF528XX

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include "ESP_AT_Lib.h"

#define SSID        "SSID"
#define PASSWORD    "password"

//#define HOST_NAME   "www.yahoo.com"
#define HOST_NAME   "192.168.2.30"
#define HOST_PORT   (5416)

ESP8266 wifi(&EspSerial);

// Your board <-> ESP_AT baud rate:
#define ESP_AT_BAUD       115200

void setup(void)
{
  Serial.begin(115200);
  while (!Serial);

#if defined(BOARD_NAME)
  Serial.println("\nStart UDPClientMultiple on " + String(BOARD_NAME));
#else
  Serial.println("\nStart UDPClientMultiple");
#endif

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP())
  {
    Serial.print("Set AP/STA Mode OK");
  }
  else
  {
    Serial.print("Set AP/STA Mode failed");
  }

  if (wifi.joinAP(SSID, PASSWORD))
  {
    Serial.println("Connect to WiFi OK");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  }
  else
  {
    Serial.println("Connect to WiFi failed");
  }

  if (wifi.enableMUX())
  {
    Serial.println("enableMUX OK");
  }
  else
  {
    Serial.println("enableMUX failed");
  }

  Serial.println("Done");
}

void loop(void)
{
  uint8_t buffer[128] = {0};
  static uint8_t mux_id = 0;

  Serial.print("Register UDP ");
  Serial.print(mux_id);
  
  if (wifi.registerUDP(mux_id, HOST_NAME, HOST_PORT))
  {
    Serial.println(" OK");
  }
  else
  {
    Serial.println(" failed");
  }

  char hello[] = "Hello, this is client!";

  if (wifi.send(mux_id, (const uint8_t*) hello, strlen(hello)))
  {
    Serial.println("Send OK");
  }
  else
  {
    Serial.println("Send err");
  }

  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);

  if (len > 0)
  {
    Serial.print("Received:\n[");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char)buffer[i]);
    }

    Serial.println("]");
  }

  Serial.print("Unregister UDP ");
  Serial.print(mux_id);

  if (wifi.unregisterUDP(mux_id))
  {
    Serial.println(" OK");
  }
  else
  {
    Serial.println(" failed");
  }

  delay(5000);

  mux_id++;

  if (mux_id >= 5)
  {
    mux_id = 0;
  }
}