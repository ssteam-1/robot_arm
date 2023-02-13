#include <AccelStepper.h>
#include <MultiStepper.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

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
BLA::Matrix <3,1> q = {0, 3.14/2, 0};
float q0 = q(0);
float q1 = q(1);
float q2 = q(2);

// Homogeneous transformation matrices
BLA::Matrix <4,4> T_I0 = {cos(q0), -sin(q0), 0, 0,
                          sin(q0), cos(q0) , 0, 0,
                          0,       0,        1, 0.078,
                          0,       0,        0, 1};

BLA::Matrix <4,4> T_01 = {1, 0,        0,        0,
                          0, cos(q1),  sin(q1),  0,
                          0, -sin(q1), cos(q1),  0.036,
                          0, 0,        0,        1};

BLA::Matrix <4,4> T_12 = {1, 0,        0,        0,
                          0, cos(q2),  sin(q2),  0,
                          0, -sin(q2), cos(q2),  0.122,
                          0, 0,        0,        1};   

BLA::Matrix <4,4> T_2E = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0.109,
                          0, 0, 0, 1};      

BLA::Matrix <4,4> T_I1 = T_I0 * T_01;
BLA::Matrix <4,4> T_I2 = T_I1 * T_12;
BLA::Matrix <4,4> T_IE = T_12 * T_2E;     

// End-effector position
BLA::Matrix <3,1> I_r_IE;


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

  // Initialize end-effector position
  jointToPosition();                                                           
  
}


void loop() { 
  run_stepper(elbow, 3000, 500, 2500);
  run_stepper(elbow, -3000, 500, 2500);
  //arm_setup();
  //move_multyple_steppers();
  
}
