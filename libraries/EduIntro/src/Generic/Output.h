#include "Arduino.h"

#ifndef Output_h
#define Output_h

class Output
{
    public:
    Output (uint8_t _pin);
    void write(int value);
    inline int state() { return _state; }
    void on();
    void off();
    void blink(int delay);
    void blink(int delay1, int delay2);

protected:
    uint8_t pin;
    int _state;
    boolean isPWM();
};

#endif
