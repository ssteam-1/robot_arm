float jointToTransform01(float q[]){
  float q1 = q[1];
  float T_01[][4] = { {1, 0,        0,        0},
                      {0, cos(q1),  sin(q1),  0},
                      {0, -sin(q1), cos(q1),  0.036},
                      {0, 0,        0,        1}};

  return T_01;
}
