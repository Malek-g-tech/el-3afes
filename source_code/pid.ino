void pid(float kp, float kd){
  float err = 0;
  int valsum = 0;

  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    err += g*x;
    valsum += g;
  }
  if(valsum != 0)
    err /= valsum;

  float derr = err - lasterror;
  lasterror = err;
  // interr += err; // Ki == 0 for now
  
  float corr = kp*err+kd*derr;

  int basespeed = 180;

  int spd1 = constrain(basespeed + corr, 0, 255);
  int spd2 = constrain(basespeed - corr, 0, 255);

  motorAForward(spd1);
  motorBForward(spd2);
}
