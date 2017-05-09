/* vim: set ft=c : */

/**
 * ESP8266 library to handle two 28byj-48 motor steppers.
 *
 * https://github.com/minirobots/simple-stepper
 *
 * Gear Reduction ratio: 1 / 64 (Not really exact: probably 63.68395.:1 )
 * Step Angle (Full Step sequence: Internal Motor alone): 11.25° (32 steps per revolution)
 * Step Angle (Half Step sequence: Internal Motor alone): 5.625° (64 steps per revolution)
 * SO: it takes 32*64 = 2048 steps per output shaft revolution.. In Full Step sequence.
 * SO: it takes 64*64 = 4096 steps per output shaft revolution.. In Half Step sequence.
 *
 * Useful links:
 *   - 28BYJ-48 Stepper Motor and ULN2003 Driver Intro
 *     https://youtu.be/B86nqDRskVU
 *   - 28BYJ-48: Small Stepper Motor and Driver Board
 *     https://arduino-info.wikispaces.com/SmallSteppers
 *
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */


#include <SimpleStepper.h>


SimpleStepper::SimpleStepper (uint8_t sequence,
                              uint8_t pin1, uint8_t pin2,
                              uint8_t pin3, uint8_t pin4)
{
  _sequence = sequence;

  _pins[0] = pin1;
  _pins[1] = pin2;
  _pins[2] = pin3;
  _pins[3] = pin4;

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}

void SimpleStepper::steps (int steps)
{
  _steps = abs(steps);
  _clockwise = steps > 0;
}

void SimpleStepper::step ()
{
  if (_steps)
  {
    _writeMotor(_actualStep);

    _actualStep = (_clockwise == true)
      ? (_actualStep < 7 ? _actualStep + 1 : 0)
      : (_actualStep > 0 ? _actualStep - 1 : 7)
    ;

    _steps--;
  }
}

int SimpleStepper::getFullRotationSteps ()
{
  switch (_sequence)
  {
    case SimpleStepper::WAKEDRIVE:
    case SimpleStepper::FULLSTEP:
      return STEPS_PER_OUTPUT_REVOLUTION_FS;

    case SimpleStepper::HALFSTEP:
      return STEPS_PER_OUTPUT_REVOLUTION_HS;
  }

  return 0;
}

/** private **/

void SimpleStepper::_writeMotor (int step)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    digitalWrite(_pins[i], bitRead(_motorSequences[_sequence][step], i));
  }
}
