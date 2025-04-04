#ifndef ARDUINO_COMPAT_HPP
#define ARDUINO_COMPAT_HPP

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

namespace platform
{
    extern volatile uint32_t timerMillis;

    inline uint32_t millis() noexcept
    {
        uint32_t m;
        cli();
        m = timerMillis;
        sei();
        return m;
    }

    inline void delay(uint32_t ms) noexcept
    {
        uint32_t start = millis();
        while (millis() - start < ms);
    }

    inline void delayMicroseconds(uint16_t us) noexcept
    {
        uint16_t iterations = (us + 3) / 4;
        __asm__ volatile (
            "1: sbiw %0, 1 \n\t"  
            "brne 1b"      
            : "=w" (iterations)
            : "0" (iterations)
        );
    }
}

#endif // ARDUINO_COMPAT_HPP