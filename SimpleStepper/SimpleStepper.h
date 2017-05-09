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

#include <Arduino.h>

#ifndef SimpleStepper_h
#define SimpleStepper_h

#define STEPS_PER_MOTOR_REVOLUTION_FS 32
#define STEPS_PER_OUTPUT_REVOLUTION_FS 2038 // ~(32 * 63.68395)
#define STEPS_PER_MOTOR_REVOLUTION_HS 64
#define STEPS_PER_OUTPUT_REVOLUTION_HS 4076 // ~(64 * 63.68395)

#define MOTOR_SPEED_US 10000


class SimpleStepper
{
  public:
    // secuences
    static const uint8_t WAKEDRIVE = 0;
    static const uint8_t FULLSTEP  = 1;
    static const uint8_t HALFSTEP  = 2;

    // directions
    static const uint8_t FORWARD  = 0;
    static const uint8_t BACKWARD = 1;

    SimpleStepper(uint8_t sequence,
                  uint8_t pin1, uint8_t pin2,
                  uint8_t pin3, uint8_t pin4);

    void steps(int steps);
    void step();

    int getFullRotationSteps();

  private:
    void _writeMotor(int step);

    int _steps = 0; // absolute steps

    uint8_t _actualStep = 0; // values: 0 - 7
    uint8_t _pins[4]; // motor pins
    uint8_t _sequence; // the motor sequence

    bool _clockwise;

    const uint8_t _motorSequences[3][8] = {
      // wake drive
      {B01000, B00100, B00010, B00001,
       B01000, B00100, B00010, B00001},
      // full step
      {B01100, B00110, B00011, B01001,
       B01100, B00110, B00011, B01001},
      // half step
      {B01000, B01100, B00100, B00110,
       B00010, B00011, B00001, B01001}
    };
};

#endif
