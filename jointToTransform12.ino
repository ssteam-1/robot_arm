float jointToTransform12(float q[]){
  float q1 = q[2];
  float T_12[][4] = { {1, 0,        0,        0},
                      {0, cos(q2),  sin(q2),  0},
                      {0, -sin(q2), cos(q2),  0.122},
                      {0, 0,        0,        1}};

  return T_12;
}
