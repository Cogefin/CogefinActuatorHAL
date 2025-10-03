#include "../config.h"

#ifdef USE_SERVO

#include "ServoHAL.h"

ServoHal::ServoHal(Servo * myservo):
  _servo(myservo)
{}

ServoHalFunctionReturnValue ServoHal::write(int angle) {
  _servo->write(angle);
  return SERVO_FUNCTION_SUCCESS;
}

ServoHalFunctionReturnValue ServoHal::writeMS(int sec) {
  _servo->writeMicroseconds(sec);
  return SERVO_FUNCTION_SUCCESS;
}



#endif /* USE_SERVO */
