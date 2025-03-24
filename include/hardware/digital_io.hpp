#ifndef DIGITAL_IO_HPP
#define DIGITAL_IO_HPP

#include <stdint.h>

namespace hardware
{
    enum class PinMode
    {
        Input,
        Output
    };
    void pinMode(uint8_t pin, PinMode mode) noexcept;
    void digitalWrite(uint8_t pin, bool value) noexcept;
    bool digitalRead(uint8_t pin) noexcept;
}

#endif // DIGITAL_IO_HPP