/**
 * \mainpage
 * \brief Really tiny library to control multiplexed outputs.
 *
 * It cycles among multiplexed outputs using a timer to control all pins.
 *
 * Library depends on uTimerLib library, https://github.com/Naguissa/uTimerLib
 *
 * @see <a href="https://github.com/Naguissa/uMuxOutputLib">https://github.com/Naguissa/uMuxOutputLib</a>
 * @see <a href="https://github.com/Naguissa/uSevenSegmentLib">https://github.com/Naguissa/uTimerLib</a> - Needed dependecy
 * @see <a href="https://www.foroelectro.net/librerias-arduino-ide-f29/umuxoutputlib-libreria-arduino-para-controlar-mult-t293.html">https://www.foroelectro.net/librerias-arduino-ide-f29/umuxoutputlib-libreria-arduino-para-controlar-mult-t293.html</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @version 1.0.2
 */
/** \file uSevenSegmentLib.h
 *   \brief uSevenSegmentLib header file
 */

#ifndef _uMuxOutputLib_
	/**
	 * \brief Prevent multiple inclussion
	 */
	#define _uMuxOutputLib_

	#include "Arduino.h"
	#include "uTimerLib.h"

	class uMuxOutputLib {
		public:
			// Constructors
			uMuxOutputLib(uint8_t, uint8_t, int *, int *);
			uMuxOutputLib(uint8_t, uint8_t, int *, int *, unsigned int);

			// Set and get
			void setPinAbsolute(uint16_t, bool);
			void setPinMuxPin(uint8_t, uint8_t, bool);
			bool getPinAbsolute(uint16_t);
			bool getPinMuxPin(uint8_t, uint8_t);

			// To run main interrupt of this library; call it when you want to it start working.
			void attachInterrupt();

			// Used to set enabled/disabled values on MUXES
			bool activeMuxValue = false; // Se to FALSE to invert logic.

			// Aux methods
			static void interrupt(void);
			static uMuxOutputLib *_instance;

		private:
			void _interrupt(void);

			uint8_t _npins, _nmuxes;
			uint8_t  *_values = NULL;

			int *_muxes = NULL;
			int *_pins = NULL;

			int _freq = 70;

			unsigned char _currentMux = 0;
			unsigned char _lastMux = 0;
	};
#endif

