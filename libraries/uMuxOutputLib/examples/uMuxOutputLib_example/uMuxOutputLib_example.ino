/**
 * Really tiny library to control multiplexed outputs.
 *
 * It cycles among multiplexed outputs using a timer to control all pins.
 *
 * Functionality example
 *
 * @see <a href="https://github.com/Naguissa/uSevenSegmentLib">https://github.com/Naguissa/uSevenSegmentLib</a>
 * @see <a href="https://github.com/Naguissa/uTimerLib">https://github.com/Naguissa/uTimerLib</a> - Needed dependecy
 * @see <a href="https://www.foroelectro.net/librerias-arduino-ide-f29/usevensegmentlib-libreria-arduino-para-controlar-d-t193.html">https://www.foroelectro.net/librerias-arduino-ide-f29/usevensegmentlib-libreria-arduino-para-controlar-d-t193.html</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 */
#include "Arduino.h"
#include "uMuxOutputLib.h"

// Pin definitions. Change to fit your needs
#ifdef _VARIANT_ARDUINO_STM32_
	int pins[8] = {D4, D5, D6};
	int muxes[3] = {D3, D7};
#else
	int pins[8] = {4, 5, 6};
	int muxes[3] = {3, 7};
#endif

uMuxOutputLib muxed(3, 2, pins, muxes);

int i = 0;
uint8_t tmp;

void setup() {
	delay (1500);
	Serial.begin(57600);
	Serial.println("Serial OK");

	muxed.attachInterrupt();
}


void loop() {
	delay(1000);

	// Cycle among pins, only one active at a time
	i = (i + 1) % 6;
	for (tmp = 0; tmp < 6; tmp++) {
		muxed.setPinAbsolute(tmp, i == tmp);
	}
	Serial.print("Stored values: ");
	for (tmp = 0; tmp < 6; tmp++) {
		Serial.print(muxed.getPinAbsolute(tmp) ? '1' : '0');
	}
	Serial.println();
}

