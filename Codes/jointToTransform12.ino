float jointToTransform12(){

  float q2 = q(2);  

  T_12(1,1) = cos(q2);
  T_12(1,2) = sin(q2);
  T_12(2,1) = -sin(q2);
  T_12(2,2) = cos(q2);
  
}
