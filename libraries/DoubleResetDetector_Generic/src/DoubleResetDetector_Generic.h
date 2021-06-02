/****************************************************************************************************************************
   DoubleResetDetector_Generic.h
   Arduino AVR, Teensy, SAM-DUE, SAMD, STM32, nRF52, etc. boards

   DoubleResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32, nRF52, etc. boards
   to enable trigger configure mode by resetting the boards twice within configurable timeout seconds.

   Based on and modified from DataCute https://github.com/datacute/DoubleResetDetector and 
   https://github.com/khoih-prog/ESP_DoubleResetDetector 

   Built by Khoi Hoang https://github.com/khoih-prog/DoubleResetDetector_Generic
   Licensed under MIT license
   Version: 1.2.0

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
   1.0.0   K Hoang      14/04/2020 Initial coding for boards such as AVR, Teensy, SAM DUE, SAMD and STM32, etc.
   1.0.1   K Hoang      01/05/2020 Add support to Adafruit nRF52 boards, such as Feather, Itsy-Bitsy nRF52840, NINA_W302_ublox.
   1.0.2   K Hoang      04/05/2020 Fix not-detected DRD bug for SAMD boards.
   1.0.3   K Hoang      28/12/2020 Suppress all possible compiler warnings
   1.1.0   K Hoang      27/04/2021 Use new FlashStorage_STM32 library. Add support to new STM32 core v2.0.0 and STM32L5
   1.2.0   K Hoang      12/05/2021 Add support to RASPBERRY_PI_PICO
 *****************************************************************************************************************************/

#pragma once

#ifndef DoubleResetDetector_Generic_H
#define DoubleResetDetector_Generic_H

#define DOUBLERESETDETECTOR_GENERIC_VERSION       "DoubleResetDetector_Generic v1.2.0"

#if ( defined(ESP32) || defined(ESP8266) )
  #error Please use ESP_DoubleResetDetector library (https://github.com/khoih-prog/ESP_DoubleResetDetector) for ESP8266 and ESP32!
#endif

// For AVR, Teensy, STM32 boards, use EEPROM
// For SAM DUE, use DueFlashStorage. For SAMD, use FlashStorage_SAMD

#define  DRD_FILENAME     "/drd.dat"
#define  DRD_FLAG_OFFSET  0

#if defined(ARDUINO) && (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define DRD_GENERIC_USE_EEPROM      true

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(DRD_GENERIC_USE_SAM_DUE)
    #undef DRD_GENERIC_USE_SAM_DUE
  #endif
  #define DRD_GENERIC_USE_SAM_DUE     true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use SAM-DUE and DueFlashStorage
#elif ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(DRD_GENERIC_USE_SAMD)
    #undef DRD_GENERIC_USE_SAMD
  #endif
  #define DRD_GENERIC_USE_SAMD      true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use SAMD and FlashStorage
  
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) )    

  #if defined(DRD_GENERIC_USE_NRF52)
    #undef DRD_GENERIC_USE_NRF52
  #endif
  #define DRD_GENERIC_USE_NRF52      true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use NRF52 and LittleFS / InternalFS

#elif ( defined(ARDUINO_ARCH_RP2040) )
  #if defined(DRD_GENERIC_USE_RP2040)
    #undef DRD_GENERIC_USE_RP2040
  #endif
  #define DRD_GENERIC_USE_RP2040      true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use RP2040 (such as RASPBERRY_PI_PICO) and LittleFS

#else
  #if defined(CORE_TEENSY)
    #warning Use TEENSY and EEPROM
  #elif ( defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_ESPLORA) \
      || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_GEMMA) || defined(ARDUINO_AVR_LEONARDO) \
      || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_LILYPAD_USB) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) \
      || defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_NG) \
      || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_ROBOT_CONTROL) || defined(ARDUINO_AVR_ROBOT_MOTOR) || defined(ARDUINO_AVR_UNO) \
      || defined(ARDUINO_AVR_YUN) )        
    #warning Use AVR and EEPROM
  #else
    #warning Use Unknown board and EEPROM
  #endif
#endif
 
//default to use EEPROM, otherwise, use DueFlashStorage or FlashStorage_SAMD
/////////////////////////////
#if DRD_GENERIC_USE_EEPROM
  #include <EEPROM.h>

  #define  FLAG_DATA_SIZE     4

  #ifndef DRD_EEPROM_SIZE
    // Please change according to your application to avoid overwriting or being overwritten
    #define DRD_EEPROM_SIZE     (E2END + 1)
  #endif

/////////////////////////////
#elif DRD_GENERIC_USE_SAMD
  // Include EEPROM-like API for FlashStorage
  #include <FlashAsEEPROM_SAMD.h>             //https://github.com/khoih-prog/FlashStorage_SAMD
  
/////////////////////////////  
#elif DRD_GENERIC_USE_SAM_DUE
  //Use DueFlashStorage to simulate EEPROM
  #include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage
  DueFlashStorage dueFlashStorage;

/////////////////////////////
#elif DRD_GENERIC_USE_NRF52
  // Include LittleFS similar to SPIFFS
  #include <Adafruit_LittleFS.h>
  #include <InternalFileSystem.h>
  using namespace Adafruit_LittleFS_Namespace;
  
  File DRD_file(InternalFS);

/////////////////////////////
#elif DRD_GENERIC_USE_RP2040

  //Use LittleFS for RPI Pico
  #include <FS.h>
  #include <LittleFS.h>

  FS* filesystem =      &LittleFS;
  #define FileFS        LittleFS

/////////////////////////////
#elif DRD_GENERIC_USE_STM32

  /////////////////////////////////////////////
      
  #if defined(DATA_EEPROM_BASE)
      // For STM32 devices having integrated EEPROM.
      #include <EEPROM.h>
      #warning STM32 devices have integrated EEPROM. Not using buffered API.   
  #else  
      /**
       Most STM32 devices don't have an integrated EEPROM. To emulate a EEPROM, the STM32 Arduino core emulated
       the operation of an EEPROM with the help of the embedded flash.
       Writing to a flash is very expensive operation, since a whole flash page needs to be written, even if you only
       want to access the flash byte-wise.
       The STM32 Arduino core provides a buffered access API to the emulated EEPROM. The library has allocated the
       buffer even if you don't use the buffered API, so it's strongly suggested to use the buffered API anyhow.
       */
      #include <FlashStorage_STM32.h>       // https://github.com/khoih-prog/FlashStorage_STM32
      #warning STM32 devices have no integrated EEPROM. Using buffered API with FlashStorage_STM32 library
  #endif    // #if defined(DATA_EEPROM_BASE)

  //////////////////////////////////////////////
 
#endif    //#if DRD_GENERIC_USE_EEPROM



#ifndef DRD_GENERIC_DEBUG
  #define DRD_GENERIC_DEBUG       false
#endif

#define DOUBLERESETDETECTOR_GENERIC_FLAG_SET    0xD0D01234
#define DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR  0xD0D04321

/////////////////////////////////////////////

class DoubleResetDetector_Generic
{
  public:
  
    /////////////////////////////////////////////
    
    DoubleResetDetector_Generic(unsigned long timeout, int address)
    {
      this->timeout = timeout * 1000;
      this->DRD_EEPROM_START = address;
      doubleResetDetected = false;
      waitingForDoubleReset = false;

/////////////////////////////
#if (DRD_GENERIC_USE_EEPROM)

      EEPROM.begin();
      
  #if (DRD_GENERIC_DEBUG)
      Serial.print("\nEEPROM size = ");
      Serial.print(DRD_EEPROM_SIZE);
      Serial.print(", start = ");
      Serial.println(DRD_EEPROM_START);
  #endif

/////////////////////////////
#elif (DRD_GENERIC_USE_STM32)

  #if defined(DATA_EEPROM_BASE)      
      EEPROM.begin();
  #endif   
      
  #if (DRD_GENERIC_DEBUG)
      Serial.print("\n(Emulated-)EEPROM size = ");
      Serial.print(EEPROM.length());
      Serial.print(", start = ");
      Serial.println(DRD_EEPROM_START);
  #endif

/////////////////////////////        
#elif DRD_GENERIC_USE_SAMD
      // Do something to init FlashStorage
      
/////////////////////////////      
#elif DRD_GENERIC_USE_SAM_DUE
      // Do something to init DueFlashStorage

/////////////////////////////      
#elif DRD_GENERIC_USE_NRF52
      // Do something to init LittleFS / InternalFS
      // Initialize Internal File System
      InternalFS.begin();

/////////////////////////////      
#elif DRD_GENERIC_USE_RP2040

      bool beginOK = FileFS.begin();

  #if (DRD_GENERIC_DEBUG)      
      if (!beginOK)
      {
        Serial.println("\nLittleFS error");
      }
  #endif

/////////////////////////////    
#else
      #error Un-identifiable board selected. Please check your Tools->Board setting.
#endif
    };
    
    /////////////////////////////////////////////

    bool detectDoubleReset()
    {
      doubleResetDetected = detectRecentlyResetFlag();

      if (doubleResetDetected)
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("doubleResetDetected");
#endif

        clearRecentlyResetFlag();
      }
      else
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("No doubleResetDetected");
#endif

        setRecentlyResetFlag();
        waitingForDoubleReset = true;
      }

      return doubleResetDetected;

    };
    
    /////////////////////////////////////////////

    void loop()
    {
      if ( waitingForDoubleReset && (millis() > timeout) )
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("Stop doubleResetDetecting");
#endif

        stop();
      }
    };

    /////////////////////////////////////////////
    
    void stop()
    {
      clearRecentlyResetFlag();
      waitingForDoubleReset = false;
    };
    
    /////////////////////////////////////////////

    bool doubleResetDetected;
    
    /////////////////////////////////////////////


  private:
    uint32_t DOUBLERESETDETECTOR_FLAG;
    unsigned long timeout;
    int DRD_EEPROM_START;
    bool waitingForDoubleReset;
    
    /////////////////////////////////////////////

#if (DRD_GENERIC_USE_SAMD)

    /////////////////////////////////////////////

    uint32_t readFlagSAMD()
    {        
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        *_pointer = EEPROM.read(offset);
      }
      
      return DOUBLERESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif (DRD_GENERIC_USE_SAM_DUE)

    /////////////////////////////////////////////

    uint32_t readFlagSAM_DUE()
    {           
      byte* dataPointer = (byte* ) dueFlashStorage.readAddress(DRD_EEPROM_START);
      
      memcpy(&DOUBLERESETDETECTOR_FLAG, dataPointer, sizeof(DOUBLERESETDETECTOR_FLAG));  
      
      return DOUBLERESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif DRD_GENERIC_USE_NRF52

    /////////////////////////////////////////////

    uint32_t readFlagNRF52()
    {           
      DRD_file.open(DRD_FILENAME, FILE_O_READ);
      
      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.read((char *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));

  #if (DRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
  #endif

        DRD_file.close(); 
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Loading DRD file failed");
  #endif
      }
           
      return DOUBLERESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif DRD_GENERIC_USE_RP2040

    /////////////////////////////////////////////

    uint32_t readFlagRP2040()
    {           
      File file = FileFS.open(DRD_FILENAME, "r");
      
      if (file)
      {
        file.seek(DRD_FLAG_OFFSET);
        file.read((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));

  #if (DRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
  #endif

        file.close(); 
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Loading DRD file failed");
  #endif
      }
           
      return DOUBLERESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////

#endif

    /////////////////////////////////////////////
      
    bool detectRecentlyResetFlag()
    {
/////////////////////////////    
#if (DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG;

/////////////////////////////
#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code  
      doubleResetDetectorFlag = readFlagSAMD();

/////////////////////////////         
#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code    
      doubleResetDetectorFlag = readFlagSAM_DUE();
      
/////////////////////////////      
#elif DRD_GENERIC_USE_NRF52
      // nRF52 code    
      doubleResetDetectorFlag = readFlagNRF52(); 

/////////////////////////////      
#elif DRD_GENERIC_USE_RP2040      
      // RP2040 code    
      doubleResetDetectorFlag = readFlagRP2040(); 
      
#endif    //(DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)
/////////////////////////////

#if (DRD_GENERIC_DEBUG)
      Serial.println("Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif

      doubleResetDetected = (doubleResetDetectorFlag == DOUBLERESETDETECTOR_GENERIC_FLAG_SET);
      return doubleResetDetected;
    };
    
    /////////////////////////////////////////////

    void setRecentlyResetFlag()
    {
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_GENERIC_FLAG_SET;

      DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_GENERIC_FLAG_SET;

/////////////////////////////
#if (DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)
      EEPROM.put(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);

  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
  #endif

/////////////////////////////
#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
  #endif      

/////////////////////////////
#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(DRD_EEPROM_START, (byte *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
      
  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
  #endif

/////////////////////////////
#elif DRD_GENERIC_USE_NRF52

      // nRF52 code
      DRD_file.open(DRD_FILENAME, FILE_O_WRITE);
      
  #if (DRD_GENERIC_DEBUG)
      Serial.print("Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
  #endif

      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
        DRD_file.close();
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
  #endif
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
  #endif
      }

/////////////////////////////    
#elif DRD_GENERIC_USE_RP2040

      // RP2040 code
      File file = FileFS.open(DRD_FILENAME, "w");  
      
  #if (DRD_GENERIC_DEBUG)
      Serial.print("Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        file.seek(DRD_FLAG_OFFSET);
        file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
        file.close();
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
  #endif
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
  #endif
      }
      
/////////////////////////////               
#endif    //(DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)

#if (DRD_GENERIC_DEBUG)
      Serial.println("SetFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif
    };
    
    /////////////////////////////////////////////

    void clearRecentlyResetFlag()
    {
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR;
      DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR;

/////////////////////////////
      
#if (DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)
      EEPROM.put(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);

  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
  #endif
  
/////////////////////////////

#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
  #endif
  
/////////////////////////////

#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(DRD_EEPROM_START, (byte *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
      
  #if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
  #endif

/////////////////////////////

#elif DRD_GENERIC_USE_NRF52

      // nRF52 code
      DRD_file.open(DRD_FILENAME, FILE_O_WRITE);
  #if (DRD_GENERIC_DEBUG)
      Serial.print("Saving to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
  #endif

      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG)); 
   
        DRD_file.close();
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
  #endif
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagNRF52();

/////////////////////////////

#elif DRD_GENERIC_USE_RP2040

      // RP2040 code
      File file = FileFS.open(DRD_FILENAME, "w");
      
  #if (DRD_GENERIC_DEBUG)
      Serial.print("Saving to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        file.seek(DRD_FLAG_OFFSET);
        file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG)); 
   
        file.close();
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
  #endif
      }
      else
      {
  #if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagRP2040();
   
#endif    //(DRD_GENERIC_USE_EEPROM || DRD_GENERIC_USE_STM32)

/////////////////////////////

#if (DRD_GENERIC_DEBUG)
      Serial.println("ClearFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif
    };
    
    /////////////////////////////////////////////

    uint32_t doubleResetDetectorFlag;
};
#endif // DoubleResetDetector_Generic_H
