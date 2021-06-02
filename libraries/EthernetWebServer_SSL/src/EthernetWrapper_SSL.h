/****************************************************************************************************************************
  EthernetWrapper.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license
       
  Version: 1.5.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.3.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
  1.3.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
  1.4.0   K Hoang      13/05/2021 Add support to RP2040-based boards using Arduino mbed_rp2040 core
  1.5.0   K Hoang      15/05/2021 Add support to RP2040-based boards using Arduino-pico rp2040 core
 *****************************************************************************************************************************/
#pragma once

#include "detail/Debug.h"

#ifndef USE_UIP_ETHERNET
  // Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
  // Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)
  #define USE_UIP_ETHERNET   false
#endif  
  
#if ( defined(USE_ETHERNET_WRAPPER) && USE_ETHERNET_WRAPPER )
  #warning Use EthernetWrapper from EthernetWebServer

  // Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
  #if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

    // Only one if the following to be true. Default to USE_ETHERNET 
    #ifndef USE_ETHERNET2
      #define USE_ETHERNET2         false
    #endif
    
    #ifndef USE_ETHERNET3
      #define USE_ETHERNET3         false
    #endif
    
    #ifndef USE_ETHERNET_LARGE
      #define USE_ETHERNET_LARGE    false
    #endif
    
    #ifndef USE_ETHERNET_ESP8266
      #define USE_ETHERNET_ESP8266  false
    #endif
    
    #ifndef USE_ETHERNET_ENC
      #define USE_ETHERNET_ENC      false
    #endif
    
    #ifndef USE_NATIVE_ETHERNET
      #define USE_NATIVE_ETHERNET      false
    #endif

    #if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET)
      #ifdef USE_CUSTOM_ETHERNET
        #undef USE_CUSTOM_ETHERNET
      #endif
      #define USE_CUSTOM_ETHERNET   false //true
    #endif
    
    #if USE_NATIVE_ETHERNET
      #include "NativeEthernet.h"
      #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
      #define SHIELD_TYPE           "Custom Ethernet using Teensy 4.1 NativeEthernet Library"
    #elif USE_ETHERNET3
      #include "Ethernet3.h"
      #warning Using Ethernet3 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet3 Library"
    #elif USE_ETHERNET2
      #include "Ethernet2.h"
      #warning Using Ethernet2 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
    #elif USE_ETHERNET_LARGE
      #include "EthernetLarge.h"
      #warning Using EthernetLarge lib
      #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
    #elif USE_ETHERNET_ESP8266
      #include "Ethernet_ESP8266.h"
      #warning Using Ethernet_ESP8266 lib 
      #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library" 
    #elif USE_ETHERNET_ENC
      #include "EthernetENC.h"
      #warning Using EthernetENC lib
      #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
    #elif USE_CUSTOM_ETHERNET
      #include "Ethernet_XYZ.h"
      #warning Using Custom Ethernet library from EthernetWrapper. You must include a library here or error.
      #define SHIELD_TYPE           "Custom Ethernet using Ethernet_XYZ Library"
    #else
      #ifdef USE_ETHERNET
        #undef USE_ETHERNET
      #endif
      #define USE_ETHERNET            true
      #include "Ethernet.h"
      #warning Using Ethernet lib
      #define SHIELD_TYPE           "W5x00 using Ethernet Library"
    #endif    //USE_ETHERNET3

    // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
    // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
    // Otherwise, standard Ethernet library will be used for W5x00
    
  #elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Using UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"  
  #endif    //( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )


  void EthernetInit()
  {
#if !USE_UIP_ETHERNET
    // Just info to know how to connect correctly

    #if USE_NATIVE_ETHERNET
      ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
    #elif USE_ETHERNET
      ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
    #elif USE_ETHERNET2
      ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
    #elif USE_ETHERNET3
      ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
    #elif USE_ETHERNET_LARGE
      ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
    #elif USE_ETHERNET_ESP8266
      ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
    #elif USE_ETHERNET_ENC
      ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));
    #else
      ET_LOGWARN(F("========================="));
    #endif

      ET_LOGWARN(F("Default SPI pinout:"));
      ET_LOGWARN1(F("MOSI:"), MOSI);
      ET_LOGWARN1(F("MISO:"), MISO);
      ET_LOGWARN1(F("SCK:"),  SCK);
      ET_LOGWARN1(F("SS:"),   SS);
      ET_LOGWARN(F("========================="));
       
    #if defined(ESP8266)
      // For ESP8266, change for other boards if necessary
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   D2    // For ESP8266
      #endif
      
      ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);
      
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        // For ESP8266
        // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
        // Ethernet           0                 X            X            X            X        0
        // Ethernet2          X                 X            X            X            X        0
        // Ethernet3          X                 X            X            X            X        0
        // EthernetLarge      X                 X            X            X            X        0
        // Ethernet_ESP8266   0                 0            0            0            0        0
        // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
        // Must use library patch for Ethernet, EthernetLarge libraries
        //Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  

      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        
    #elif defined(ESP32)

      // You can use Ethernet.init(pin) to configure the CS pin
      //Ethernet.init(10);  // Most Arduino shields
      //Ethernet.init(5);   // MKR ETH shield
      //Ethernet.init(0);   // Teensy 2.0
      //Ethernet.init(20);  // Teensy++ 2.0
      //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
      //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
      
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   22    // For ESP32
      #endif
      
      ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);
      
      // For other boards, to change if necessary
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        // Must use library patch for Ethernet, EthernetLarge libraries
        // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
        // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
           
        //Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  
              
      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )

    #elif ETHERNET_USE_RPIPICO

        pinMode(USE_THIS_SS_PIN, OUTPUT);
        digitalWrite(USE_THIS_SS_PIN, HIGH);
        
        // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
        #ifndef USE_THIS_SS_PIN
          #if defined(ARDUINO_ARCH_MBED)
            #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
          #else  
            #define USE_THIS_SS_PIN   17    // For E.Philhower core
          #endif
        #endif

        ET_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

        // For other boards, to change if necessary
        #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
          // Must use library patch for Ethernet, EthernetLarge libraries
          // For RPI Pico using Arduino Mbed RP2040 core
          // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
          // For RPI Pico using E. Philhower RP2040 core
          // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
          // Default pin 5/17 to SS/CS
        
          //Ethernet.setCsPin (USE_THIS_SS_PIN);
          Ethernet.init (USE_THIS_SS_PIN);
        
        #elif USE_ETHERNET3
          // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
          #ifndef ETHERNET3_MAX_SOCK_NUM
            #define ETHERNET3_MAX_SOCK_NUM      4
          #endif
        
          Ethernet.setCsPin (USE_THIS_SS_PIN);
          Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
          
        #endif    //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

      #else   //defined(ESP8266)
      // unknown board, do nothing, use default SS = 10
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   10    // For other boards
      #endif
      
      #if defined(BOARD_NAME)
        ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
      #else
        ET_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
      #endif

      // For other boards, to change if necessary
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
        // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  
                        
      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
      
    #endif    //defined(ESP8266)
#endif  //#if !USE_UIP_ETHERNET
  }

#endif    //#if USE_ETHERNET_WRAPPER

