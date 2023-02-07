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

// Create new instances of the AccelStepper class, one for each joint:
AccelStepper base = AccelStepper(motorInterfaceType, base_stepPin, base_dirPin);
AccelStepper shoulder = AccelStepper(motorInterfaceType, shoulder_stepPin, shoulder_dirPin);
AccelStepper elbow = AccelStepper(motorInterfaceType, elbow_stepPin, elbow_dirPin);
// Create new instance of the MultyStepper class, which will manage multyple steppers at once:
MultiStepper steppers;

// ARM PARAMETERS
// Generalized coordinates
float q[3];
float q0 = q[0];
float q1 = q[1];
float q2 = q[2];

// Homogeneous transformation matrices
float T_I0[][4] = { {cos(q0), -sin(q0), 0, 0},
                    {sin(q0), cos(q0) , 0, 0},
                    {0,       0,        1, 0.078},
                    {0,       0,        0, 1}};
float T_01[][4] = { {1, 0,        0,        0},
                    {0, cos(q1),  sin(q1),  0},
                    {0, -sin(q1), cos(q1),  0.036},
                    {0, 0,        0,        1}};
float T_12[][4] = { {1, 0,        0,        0},
                    {0, cos(q2),  sin(q2),  0},
                    {0, -sin(q2), cos(q2),  0.122},
                    {0, 0,        0,        1}};                    


void setup() {
  // Set the maximum speed in steps per second:
  base.setMaxSpeed(1000);
  shoulder.setMaxSpeed(1000);
  elbow.setMaxSpeed(1000);

  // Serial
  Serial.begin(9600);

  // Add steppers into the container
  steppers.addStepper(base);
  steppers.addStepper(shoulder);
  steppers.addStepper(elbow);
}


void loop() { 

  arm_setup();
  //move_multyple_steppers();
  
}
