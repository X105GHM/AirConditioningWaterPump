#ifndef F_CPU
#define F_CPU 1000000UL
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform/arduino_compat.hpp"
#include "sensor/sensor.hpp"
#include "pump/pump.hpp"
#include "buzzer/buzzer.hpp"

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

int main() noexcept
{
  initTimer0();
  sei();
  sensor::Sensor waterSensor(0);
  pump::Pump waterPump(1);
  buzzer::Buzzer errorBuzzer(2);
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
        while ((platform::millis() - cycleStart) < 30000);
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