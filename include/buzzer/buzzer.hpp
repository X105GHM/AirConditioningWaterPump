#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <stdint.h>

namespace buzzer
{
    class Buzzer
    {
        uint8_t controlPin;

    public:
        explicit Buzzer(uint8_t pin) noexcept;
        void alarm() noexcept;
        void stopAlarm() noexcept;
    };
}

#endif // BUZZER_HPP