#ifndef PUMP_HPP
#define PUMP_HPP

#include <stdint.h>

namespace pump
{
    class Pump
    {
        uint8_t controlPin;
        bool running;

    public:
        explicit Pump(uint8_t pin) noexcept;
        void start() noexcept;
        void stop() noexcept;
        bool isRunning() const noexcept;
    };
}

#endif // PUMP_HPP