#include "hardware/digital_io.hpp"
#include <avr/io.h>

namespace hardware
{
    void pinMode(uint8_t pin, PinMode mode) noexcept
    {
        if (mode == PinMode::Output)
        {
            DDRB |= (1 << pin);
        }
        else
        {
            DDRB &= ~(1 << pin);
        }
    }

    void digitalWrite(uint8_t pin, bool value) noexcept
    {
        if (value)
        {
            PORTB |= (1 << pin);
        }
        else
        {
            PORTB &= ~(1 << pin);
        }
    }
    
    bool digitalRead(uint8_t pin) noexcept
    {
        return (PINB & (1 << pin)) != 0;
    }
}
