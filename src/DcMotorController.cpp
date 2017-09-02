#ifdef DC_MOTOR
#include <string.h>
#include "motor.h"
#include "Arduino.h"
const int left_motor_pin = 5;
const int right_motor_pin = 4;


void setup_implementation(void){
  /*pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);*/
}
String handle_speed_implementation(String arg0, String arg1){
  // Assume arg 1 is left wheel speed (in degrees), and arg 2 is right speed
  String response = "";
  String left_arg = arg0;
  int left_speed = left_arg.toInt();

  String right_arg = arg1;
  int right_speed = right_arg.toInt();

 //do motor things
  response = "Left: ";
  response += left_arg;
  response += ", Right: ";
  response += right_arg;
  return response;
}
#endif
