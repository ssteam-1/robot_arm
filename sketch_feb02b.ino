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

void run_stepper(AccelStepper stepper, int desired_steps, int stepper_speed, int time_delay){
  stepper.setCurrentPosition(0);

  // Run the motor backwards at 600 steps/second until the motor reaches -200 steps (1 revolution):
  while(stepper.currentPosition() != desired_steps) 
  {
    stepper.setSpeed(sign(desired_steps)*stepper_speed);
    stepper.runSpeed();
  }

  delay(time_delay);
}

int sign(int x){
  if(x < 0){
    return -1;
  }else{
    return 1;
  }
}

void arm_setup(){
  Serial.println("Which stepper would you like to move? 1: base, 2: shoulder, 3: elbow ");
  delay(3000);
  while (Serial.available() == 0) {
  }
  int current_stepper = Serial.parseInt();


  bool adjust = true;
  while(adjust){
    Serial.println("Insert the number of steps you would like to perform ...");
    delay(3000);
    while (Serial.available() == 0) {
    }
    int steps = Serial.parseInt();
    if(steps >= 10000){ 
      adjust = false;
      continue;  
    }

    if(current_stepper == 1){ 
      Serial.println("Moving base ...");
      run_stepper(base, steps, 250, 0);
    }else if(current_stepper == 2){
      Serial.println("Moving shoulder ...");
      run_stepper(shoulder, steps, 250, 0);
    }else if(current_stepper == 3){
      Serial.println("Moving elbow ...");
      run_stepper(elbow, steps, 250, 0);
    }else{
      Serial.println("Insert a valid number for the stepper.");
    } 
  }
}

void move_multyple_steppers(){
  long positions[3]; // Array of desired stepper positions
  //set the initial position of the stepper motors 
  positions[0] = 1500; //3.5 mm (1135/5 = 227)
  positions[1] = 1500;
  positions[2] = -1500;
  

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(3000);
  
  positions[0] = -1500; //3.5 mm (1135/5 = 227)
  positions[1] = -1500;
  positions[2] = 1500;
  

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}
