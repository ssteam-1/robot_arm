/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: number of steps or revolutions. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>
#include <MultiStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define base_dirPin 2
#define base_stepPin 3
#define shoulder_dirPin 8
#define shoulder_stepPin 9
#define elbow_dirPin 11
#define elbow_stepPin 10
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper base = AccelStepper(motorInterfaceType, base_stepPin, base_dirPin);
AccelStepper shoulder = AccelStepper(motorInterfaceType, shoulder_stepPin, shoulder_dirPin);
AccelStepper elbow = AccelStepper(motorInterfaceType, elbow_stepPin, elbow_dirPin);

MultiStepper steppers;



void setup() {
  // Set the maximum speed in steps per second:
  base.setMaxSpeed(1000);
  shoulder.setMaxSpeed(1000);
  elbow.setMaxSpeed(1000);

  Serial.begin(9600);

  steppers.addStepper(base);
  steppers.addStepper(shoulder);
  steppers.addStepper(elbow);
}

void loop() { 

  arm_setup();
  //move_multyple_steppers();
  
}
