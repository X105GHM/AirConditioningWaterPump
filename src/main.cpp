#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform/arduino_compat.hpp"
#include "sensor/sensor.hpp"
#include "pump/pump.hpp"
#include "buzzer/buzzer.hpp"
#include "hardware/analog_io.hpp"

volatile uint32_t platform::timerMillis = 0;

void initTimer0()
{
  TCCR0A = (1 << WGM01);
  OCR0A = 124;
  TIMSK |= (1 << OCIE0A);
  TCCR0B = (1 << CS01);
}

ISR(TIMER0_COMPA_vect)
{
  platform::timerMillis++;
}

uint32_t getPumpDuration()
{
  uint16_t adcValue = analog_io::readADC(0);
  const uint32_t minDuration = 30000UL;
  const uint32_t maxDuration = 1200000UL;
  return minDuration + ((uint32_t)adcValue * (maxDuration - minDuration)) / 1023;
}

int main() noexcept
{

  initTimer0();
  analog_io::initADC();
  sei();

  sensor::Sensor waterSensor(0);
  pump::Pump waterPump(1);
  buzzer::Buzzer errorBuzzer(2);

  uint32_t pumpDuration = getPumpDuration();

  while (true)
  {
    if (waterSensor.isTriggered())
    {
      uint32_t startTime = platform::millis();
      uint32_t cycleTime = 0;
      while (waterSensor.isTriggered() && cycleTime < 180000)
      {
        waterPump.start();
        uint32_t cycleStart = platform::millis();
      
        while ((platform::millis() - cycleStart) < pumpDuration);
        waterPump.stop();
        if (!waterSensor.isTriggered())
          break;
        cycleTime = platform::millis() - startTime;
      }
      if (waterSensor.isTriggered())
      {
        errorBuzzer.alarm();
        while (waterSensor.isTriggered());
        errorBuzzer.stopAlarm();
      }
    }
    platform::delay(100);
  }
  return 0;
}
