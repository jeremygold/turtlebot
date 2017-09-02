#ifdef SERVO_MOTOR
#include <string.h>
#include <Servo.h>
#include "motor.h"
const int left_servo_pin = 5;
const int right_servo_pin = 4;

const int left_servo_zero = 94;
const int right_servo_zero = 91;

Servo left_servo;
Servo right_servo;

void setup_implementation(void){
  left_servo.attach(left_servo_pin);
  right_servo.attach(right_servo_pin);
}
String handle_speed_implementation(String arg0, String arg1){
  // Assume arg 1 is left wheel speed (in degrees), and arg 2 is right speed
  String response = "";
  String left_arg = arg0;
  int left_speed = left_arg.toInt();

  String right_arg = arg1;
  int right_speed = right_arg.toInt();

  // Right side gets negative speed since it's physically mounted the
  // other way around.
  left_servo.write(left_servo_zero + left_speed);
  right_servo.write(right_servo_zero - right_speed);

  response = "Left: ";
  response += left_arg;
  response += ", Right: ";
  response += right_arg;
}
#endif
