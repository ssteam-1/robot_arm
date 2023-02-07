float jointToTransformI0(){
  
  T_I0[0][0] = cos(q0);
  T_I0[0][1] = -sin(q0);
  T_I0[1][0] = sin(q0);
  T_I0[1][1] = cos(q0);
  
}
