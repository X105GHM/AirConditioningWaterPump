#ifndef ANALOG_IO_HPP
#define ANALOG_IO_HPP

#include <stdint.h>

namespace analog_io
{
    void initADC();

    uint16_t readADC(uint8_t channel);
}

#endif // ANALOG_IO_HPP
