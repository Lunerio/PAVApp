/*******************************************************************************************************************
** Example program for using the DS3231M library which allows access to the DS3231M real-time-clock chip. The     **
** library as well as the most current version of this program is available at GitHub using the address           **
** https://github.com/SV-Zanshin/DS3231M and a more detailed description of this program (and the library) can be **
** found at https://github.com/SV-Zanshin/DS3231M/wiki/Demo.ino                                                   **
**                                                                                                                **
** The DS3231M library uses the standard SPI Wire library for communications with the RTC chip and has also used  **
** the class definitions of the standard RTClib library from Adafruit/Jeelabs. The data sheet for the DS3231M is  **
** located at https://datasheets.maximintegrated.com/en/ds/DS3231M.pdf.                                           **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
** Vers.  Date       Developer                     Comments                                                       **
** ====== ========== ============================= ============================================================== **
** 1.0.1  2019-01-27 https://github.com/SV-Zanshin Issue #5. Changes to sscanf() for Esp32 Implementation         **
** 1.0.0  2017-08-13 https://github.com/SV-Zanshin Initial coding                                                 **
**                                                                                                                **
*******************************************************************************************************************/
#include <DS3231M.h>                                                          // Include the DS3231M RTC library  //
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED        = 115200;                                  // Set the baud rate for Serial I/O //
const uint8_t  SPRINTF_BUFFER_SIZE =     32;                                  // Buffer size for sprintf()        //
const uint8_t  LED_PIN             =     13;                                  // Built-in Arduino green LED pin   //
/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
DS3231M_Class DS3231M;                                                        // Create an instance of the DS3231M//
char          inputBuffer[SPRINTF_BUFFER_SIZE];                               // Buffer for sprintf()/sscanf()    //
/*******************************************************************************************************************
** Method Setup(). This is an Arduino IDE method which is called upon boot or restart. It is only called one time **
** and then control goes to the main loop, which loop indefinately.                                               **
*******************************************************************************************************************/
void setup() {                                                                // Arduino standard setup method    //
  pinMode(LED_PIN,OUTPUT);                                                    // Make the LED light an output pin //
  Serial.begin(SERIAL_SPEED);                                                 // Start serial port at Baud rate   //
  #ifdef  __AVR_ATmega32U4__                                                  // If this is a 32U4 processor, then//
    delay(3000);                                                              // wait 3 seconds for the serial    //
  #endif                                                                      // interface to initialize          //
  Serial.print(F("\nStarting Set program\n"));                                // Show program information         //
  Serial.print(F("- Compiled with c++ version "));                            //                                  //
  Serial.print(F(__VERSION__));                                               // Show compiler information        //
  Serial.print(F("\n- On "));                                                 //                                  //
  Serial.print(F(__DATE__));                                                  //                                  //
  Serial.print(F(" at "));                                                    //                                  //
  Serial.print(F(__TIME__));                                                  //                                  //
  Serial.print(F("\n"));                                                      //                                  //
  while (!DS3231M.begin()) {                                                  // Initialize RTC communications    //
    Serial.println(F("Unable to find DS3231MM. Checking again in 3s."));      // Show error text                  //
    delay(3000);                                                              // wait a second                    //
  } // of loop until device is located                                        //                                  //
  DS3231M.pinSquareWave();                                                    // Make INT/SQW pin toggle at 1Hz   //
  Serial.println(F("DS3231M initialized."));                                  //                                  //
  DS3231M.adjust();                                                           // Set to library compile Date/Time //
  Serial.print(F("DS3231M chip temperature is "));                            //                                  //
  Serial.print(DS3231M.temperature()/100.0,1);                                // Value is in 100ths of a degree   //
  Serial.println("\xC2\xB0""C");                                              //                                  //
  Serial.println(F("\nEnter on of the following serial commands:"));          //                                  //
  Serial.println(F("SETDATE yyyy-mm-dd hh:mm:ss"));                           //                                  //
} // of method setup()                                                        //                                  //
/*******************************************************************************************************************
** Method readCommand(). This function checks the serial port to see if there has been any input. If there is data**
** it is read until a terminator is discovered and then the command is parsed and acted upon                      **
*******************************************************************************************************************/
void readCommand() {                                                          //                                  //
  static uint8_t inputBytes = 0;                                              // Variable for buffer position     //
  while (Serial.available()) {                                                // Loop while incoming serial data  //
    inputBuffer[inputBytes] = Serial.read();                                  // Get the next byte of data        //
    if (inputBuffer[inputBytes]!='\n' && inputBytes<SPRINTF_BUFFER_SIZE)      // keep on reading until a newline  //
      inputBytes++;                                                           // shows up or the buffer is full   //
    else {                                                                    //                                  //
      inputBuffer[inputBytes] = 0;                                            // Add the termination character    //
      for (uint8_t i=0;i<inputBytes;i++)                                      // Convert the whole input buffer   //
        inputBuffer[i] = toupper(inputBuffer[i]);                             // to uppercase characters          //
      Serial.print(F("\nCommand \""));                                        //                                  //
      Serial.write(inputBuffer);                                              //                                  //
      Serial.print(F("\" received.\n"));                                      //                                  //
      /*************************************************************************************************************
      ** Parse the single-line command and perform the appropriate action. The current list of commands           **
      ** understood are as follows:                                                                               **
      **                                                                                                          **
      ** SETDATE      - Set the device time                                                                       **
      **                                                                                                          **
      *************************************************************************************************************/
      enum commands { SetDate, Unknown_Command };                             // of commands enumerated type      //
      commands command;                                                       // declare enumerated type          //
      char workBuffer[10];                                                    // Buffer to hold string compare    //
      sscanf(inputBuffer,"%s %*s",workBuffer);                                // Parse the string for first word  //
      if      (!strcmp(workBuffer,"SETDATE" )) command = SetDate;             // Set command number when found    //
      else command = Unknown_Command;                                         // Otherwise set to not found       //
      unsigned int tokens,year,month,day,hour,minute,second;                  // Variables to hold parsed dt/tm   //
      switch (command) {                                                      // Action depending upon command    //
        /***********************************************************************************************************
        ** Set the device time and date                                                                           **
        ***********************************************************************************************************/
        case SetDate:                                                         // Set the RTC date/time            //
          tokens = sscanf(inputBuffer,"%*s %u-%u-%u %u:%u:%u;",               // Use sscanf() to parse the date/  //
                          &year,&month,&day,&hour,&minute,&second);           // time into variables              //
          if (tokens!=6)                                                      // Check to see if it was parsed    //
            Serial.print(F("Unable to parse date/time\n"));                   //                                  //
          else {                                                              //                                  //
            DS3231M.adjust(DateTime(year,month,day,hour,minute,second));      // Adjust the RTC date/time         //
            Serial.print(F("Date has been set."));                            //                                  //
          } // of if-then-else the date could be parsed                       //                                  //
          break;                                                              //                                  //
        /***********************************************************************************************************
        ** Unknown command                                                                                        **
        ***********************************************************************************************************/
        case Unknown_Command:                                                 // Show options on bad command      //
        default:                                                              //                                  //
          Serial.println(F("Unknown command. Valid commands are:"));          //                                  //
          Serial.println(F("SETDATE yyyy-mm-dd hh:mm:ss"));                   //                                  //
      } // of switch statement to execute commands                            //                                  //
      inputBytes = 0; // reset the counter                                    //                                  //
    } // of if-then-else we've received full command                          //                                  //
  } // of if-then there is something in our input buffer                      //                                  //
} // of method readCommand                                                    //                                  //
/*******************************************************************************************************************
** This is the main program for the Arduino IDE, it is an infinite loop and keeps on repeating.                   **
*******************************************************************************************************************/
void loop() {                                                                 //                                  //
  static uint8_t secs;                                                        // store the seconds value          //
  DateTime now = DS3231M.now();                                               // get the current time             //
  if (secs != now.second()) {                                                 // Output if seconds have changed   //
    sprintf(inputBuffer,"%04d-%02d-%02d %02d:%02d:%02d", now.year(),          // Use sprintf() to pretty print    //
            now.month(), now.day(), now.hour(), now.minute(), now.second());  // date/time with leading zeros     //
    Serial.println(inputBuffer);                                              // Display the current date/time    //
    secs = now.second();                                                      // Set the counter variable         //
  } // of if the seconds have changed                                         //                                  //
  readCommand();                                                              // See if serial port had incoming  //
} // of method loop()                                                         //----------------------------------//