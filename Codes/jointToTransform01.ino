float jointToTransform01(){

  float q1 = q(1);

  T_01(1, 1) = cos(q1);
  T_01(1, 2) = sin(q1);
  T_01(2, 1) = -sin(q1);
  T_01(2, 2) = cos(q1);
  
}
