#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stdint.h>

namespace sensor
{
    class Sensor
    {
        uint8_t sensorPin;

    public:
        explicit Sensor(uint8_t pin) noexcept;
        bool isTriggered() const noexcept;
    };
}

#endif // SENSOR_HPP
