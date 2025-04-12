#include "buzzer/buzzer.hpp"
#include "hardware/digital_io.hpp"

namespace buzzer
{
    Buzzer::Buzzer(uint8_t pin) noexcept : controlPin(pin)
    {
        hardware::pinMode(controlPin, hardware::PinMode::Output);
    }

    void Buzzer::alarm() noexcept
    {
        hardware::digitalWrite(controlPin, HIGH);
    }

    void Buzzer::stopAlarm() noexcept
    {
        hardware::digitalWrite(controlPin, LOW);
    }
}