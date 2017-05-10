# Library to handle 28byj48 stepper motors

This library is compabitle with *esp8266* and it has been designed with simplicity in mind, so it's useful for education purposes. It can't handle acceleration, for that use [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) instead.

The library supports the three sequence methods: Wake Drive, Full Step and Half Step.

Examples
--------

One motor

```cpp

#include <SimpleStepper.h>

SimpleStepper stepper(SimpleStepper::FULLSTEP, D5, D6, D7, D8)

void loop ()
{
  stepper.steps(stepper.getFullRotationSteps());

  while ( ! stepper.ready())
  {
    stepper.step();
    delay(3);
    yield();
  }
}

```

Two motors

```cpp

#include <SimpleStepper.h>

SimpleStepper stepper1(SimpleStepper::FULLSTEP, D1, D2, D3, D4)
SimpleStepper stepper2(SimpleStepper::HALFSTEP, D5, D6, D7, D8)

void loop ()
{
  stepper1.steps(stepper1.getFullRotationSteps());
  stepper2.steps(stepper2.getFullRotationSteps());

  while ( ! stepper1.ready() || ! stepper2.ready() )
  {
    stepper1.step();
    stepper2.step();
    delay(3);
    yield();
  }
}

```
