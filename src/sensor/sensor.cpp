#include "sensor/sensor.hpp"
#include "hardware/digital_io.hpp"

namespace sensor
{
    Sensor::Sensor(uint8_t pin) noexcept : sensorPin(pin)
    {
        hardware::pinMode(sensorPin, hardware::PinMode::Input);
    }
    bool Sensor::isTriggered() const noexcept
    {
        return hardware::digitalRead(sensorPin);
    }
}
