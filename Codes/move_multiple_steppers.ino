void move_multyple_steppers(){
  long positions[3]; // Array of desired stepper positions
  //set the initial position of the stepper motors 
  positions[0] = 1500; //3.5 mm (1135/5 = 227)
  positions[1] = 1500;
  positions[2] = -1500;
  

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(3000);
  
  positions[0] = -1500; 
  positions[1] = -1500;
  positions[2] = 1500;
  

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}
