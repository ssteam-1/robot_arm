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
