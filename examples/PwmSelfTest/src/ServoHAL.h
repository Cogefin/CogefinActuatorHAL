#ifndef __SERVO_HAL_H__
#define __SERVO_HAL_H__

#include <stdint.h>
#include <Arduino.h>

#include "../config.h"

#ifdef USE_SERVO

#ifdef ARDUINO_NANO_ESP32
#include <ESP32Servo.h>
#else
#include <Servo.h>
#endif



typedef enum {
  SERVO_FUNCTION_UNSUPPORTED = 1,
  SERVO_FUNCTION_SUCCESS,
  SERVO_FUNCTION_FAIL
} ServoHalFunctionReturnValue;

class ServoHal {
public:
  ServoHal(Servo * myservo);
  ServoHalFunctionReturnValue write(int angle);
  ServoHalFunctionReturnValue writeMS(int sec);
protected:
  Servo * _servo;
};
#endif /* USE_SERVO */

#endif /* __SERVO_HAL_H__ */
