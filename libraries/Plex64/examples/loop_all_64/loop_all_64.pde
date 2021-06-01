// Plex64 Analog Input Multiplexer shield example sketch, loop_all_64.pde
// Version 1, 2020-01-24
// https://github.com/steenerson/Plex64

#include <Plex64.h>
//#include <Wire.h>

// Setup pins and I2C address. These are the default values and are correct
// if the shield is plugged directly into Arduino with stock I2C solder jumpers
static const uint8_t plexE = A0;
static const uint8_t plexF = A1;
static const uint8_t plexG = A2;
static const uint8_t plexH = A3;
static const uint8_t plexAddress = 0x20;

//Create instance
Plex64 plex64(plexAddress, plexE, plexF, plexG, plexH);

void setup() {
  //Run begin(), required to setup I2C port and inputs
  plex64.begin();

  //Uncomment Wire.h include and this line to slow I2C speed from 400kHz->100kHz, may be
  //necessary on some 3.3V systems due to stock 4.7k pullup resistors.
  //Wire.setClock(100000);
  
  Serial.begin(115200);
  while (!Serial); 
  Serial.println("starting");
}

void loop() {
  for (int i = 0; i < 16 ; i++) {
    //set all 4 channels (E+F+G+H) to given input (0-15), wait 5ms to stabilize and then read+print all 4 channels
    plex64.setAllChannels(i); 
    delay(5);
    Serial.print("E");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(analogRead(plexE));
    Serial.print(", F");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(analogRead(plexF));
    Serial.print(", G");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(analogRead(plexG));
    Serial.print(", H");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(analogRead(plexH));
  }
  Serial.println();
  delay(1000);
}