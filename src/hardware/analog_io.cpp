#include "hardware/analog_io.hpp"
#include "platform/arduino_compat.hpp"
#include <avr/io.h>

namespace analog_io
{
    void initADC()
    {
        ADMUX = 0;
        ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
    }

    uint16_t readADC(uint8_t channel)
    {
        ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
        platform::delayMicroseconds(100);
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        uint8_t low = ADCL;
        uint8_t high = ADCH;
        return (static_cast<uint16_t>(high) << 8) | low;
    }
}
