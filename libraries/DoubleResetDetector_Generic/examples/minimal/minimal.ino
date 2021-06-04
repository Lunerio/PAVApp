/****************************************************************************************************************************
   minimal.ino
   DoubleResetDetector_Generic.h
   For AVR Mega, Teensy, STM32, nRF52, SAM DUE, SAMD21, SAMD51 boards

   DoubleResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32. etc. boards
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
/****************************************************************************************************************************
   This example will open a configuration portal when the reset button is pressed twice.
   This method works well on Wemos boards which have a single reset button on board. It avoids using a pin for launching the configuration portal.

   How It Works
   1) AVR Mega, Teensy, STM32
   Save data in EPPROM from address 1020, size 1024 bytes (both configurable)
   Note: Teensy 4.0 has only 1080 bytes of EEPROM-simulated Flash
   2) SAMD
   Save data in EEPROM-simulated FlashStorage from address 1020 (configurable to avoid conflict)
   3) SAM DUE
   Save data in DueFlashStorage from address 1020 (configurable to avoid conflict)
   3) Adafruit nRF52-based boards
   Save data in InternalFS, fle "/drd.dat" location 0

   So when the device starts up it checks the InternalFS file "/drd.dat", EEPROM or (Due)FlashStorage for a flag to see if it has been
   recently reset within the configurable timeout seconds
   It'll then set a flag, and display a message to signal if the DR is detected

   Settings
   There are two values to be set in the sketch.

   DRD_TIMEOUT - Number of seconds to wait for the second reset. Set to 10s in the example.
   DRD_ADDRESS - The address in ESP8266 RTC RAM to store the flag. This memory must not be used for other purposes in the same sketch. Set to 0 in the example.

   This example, originally relied on the Double Reset Detector library from https://github.com/datacute/DoubleResetDetector
   To support ESP32, use ESP_DoubleResetDetector library from https://github.com/khoih-prog/ESP_DoubleResetDetector
   To support AVR, Teensy, SAM DUE, SAMD and STM32, etc., use this DoubleResetDetector_Generic from //https://github.com/khoih-prog/DoubleResetDetector_Generic
 *****************************************************************************************************************************/

#define DRD_GENERIC_DEBUG       true  //false

#include <DoubleResetDetector_Generic.h>

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

#ifndef LED_BUILTIN
  #define LED_BUILTIN       13
#endif

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.println();

#if defined(BOARD_NAME)
  Serial.print(F("DoubleResetDetector minimal Example Program on ")); Serial.println(BOARD_NAME);
#else
  Serial.println(F("DoubleResetDetector minimal Example Program"));
#endif
  
  Serial.println(DOUBLERESETDETECTOR_GENERIC_VERSION);
  Serial.println("-----------------------------------");

  drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);

  if (drd->detectDoubleReset()) 
  {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  } 
  else 
  {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop()
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  drd->loop();
}
