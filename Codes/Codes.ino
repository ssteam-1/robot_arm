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
    }else if(current_stepper == 4){
      move_multyple_steppers();
    } else{
      Serial.println("Insert a valid number for the stepper.");
    } 
  }
}
