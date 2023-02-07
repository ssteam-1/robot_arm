float jointToTransformI0(float q[]){
  float q0 = q[0];
  float T_I0[][4] = { {cos(q0), -sin(q0), 0, 0},
                      {sin(q0), cos(q0) , 0, 0},
                      {0,       0,       1, 0.078},
                      {0,       0,       0, 1}};
  return T_I0;
}
