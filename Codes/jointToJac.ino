void jointToJac(){

  // Compute the relative homogeneous transformation matrices.
  jointToTransformI0();
  jointToTransform01();
  jointToTransform12();

  // Compute the homogeneous transformation matrices from frame k to the inertial frame I.
  //T_I0;
  T_I1 = T_I0 * T_01;
  T_I2 = T_I1 * T_12;
  T_IE = T_12 * T_2E;

  // Extract the rotation matrices from each homogeneous transformation matrix.
  BLA::Matrix <3,3> R_I0; 
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      R_I0(i,j) = T_I0(i,j);
    }
  }
  
  BLA::Matrix <3,3> R_I1; 
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      R_I1(i,j) = T_I1(i,j);
    }
  }
  
  BLA::Matrix <3,3> R_I2; 
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      R_I2(i,j) = T_I2(i,j);
    }
  }

  // Extract the position vectors from each homogeneous transformation matrix.
  BLA::Matrix <3,1> I_r_I0;
  for(int i=0; i<3; i++)I_r_I0(i) = T_I0(i,3);
  
  BLA::Matrix <3,1> I_r_I1;
  for(int i=0; i<3; i++)I_r_I1(i) = T_I1(i,3);
  
  BLA::Matrix <3,1> I_r_I2;
  for(int i=0; i<3; i++)I_r_I2(i) = T_I2(i,3);

  // Define the unit vectors around which each link rotates in the precedent coordinate frame.
  BLA::Matrix <3,1> n_0 = {0, 0, 1};
  BLA::Matrix <3,1> n_1 = {1, 0, 0};
  BLA::Matrix <3,1> n_2 = {1, 0, 0};

  // Compute the end-effector position vector.
  jointToPosition();

  // Compute the translational jacobian.
  BLA::Matrix <3,1> I_r_0E = I_r_IE - I_r_I0;
  BLA::Matrix <3,1> J_P_1 = {n_0(1)*I_r_0E(2) - n_0(2)*I_r_0E(1),
                             - n_0(0)*I_r_0E(2) + n_0(2)*I_r_0E(0),
                             n_0(0)*I_r_0E(1) - n_0(1)*I_r_0E(0)};
  
  BLA::Matrix <3,1> I_n_1 = R_I1*n_1;
  BLA::Matrix <3,1> I_r_1E = I_r_IE - I_r_I1;
  BLA::Matrix <3,1> J_P_2 = {I_n_1(1)*I_r_1E(2) - I_n_1(2)*I_r_1E(1),
                             - I_n_1(0)*I_r_1E(2) + I_n_1(2)*I_r_1E(0),
                             I_n_1(0)*I_r_1E(1) - I_n_1(1)*I_r_1E(0)};
  
  BLA::Matrix <3,1> I_n_2 = R_I2*n_2;
  BLA::Matrix <3,1> I_r_2E = I_r_IE - I_r_I2;
  BLA::Matrix <3,1> J_P_3 = {I_n_2(1)*I_r_2E(2) - I_n_2(2)*I_r_2E(1),
                             - I_n_2(0)*I_r_2E(2) + I_n_2(2)*I_r_2E(0),
                             I_n_2(0)*I_r_2E(1) - I_n_2(1)*I_r_2E(0)};                                                         


  // Position Jacobian
  BLA::Matrix <3,3> J_P = J_P_1 || J_P_2 || J_P_3;
  // Rotation Jacobian
  BLA::Matrix <3,3> J_R = n_0 || I_n_1 || I_n_2;

  // Stacked Jacobians
  BLA::Matrix <6,3> J = J_P && J_R;

  //Serial << 'r' << J << '\n';
}
