#include "pump/pump.hpp"
#include "hardware/digital_io.hpp"

namespace pump
{
    Pump::Pump(uint8_t pin) noexcept : controlPin(pin), running(false)
    {
        hardware::pinMode(controlPin, hardware::PinMode::Output);
    }

    void Pump::start() noexcept
    {
        running = true;
        hardware::digitalWrite(controlPin, LOW);
    }

    void Pump::stop() noexcept
    {
        running = false;
        hardware::digitalWrite(controlPin, HIGH);
    }

    bool Pump::isRunning() const noexcept
    {
        return running;
    }
}
