float corr = 0;
//
//
//
//
//
//
//
//
void pid(float kp, float kd){
  float err = 0;
  int valsum = 0;
  int i=0;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    err += g*x;
    valsum += g;
  }
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;
  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}
//
//
//
//
//
//
//
//
void pid_right(float kp, float kd){
  float err = 0;
  int valsum = 0;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    if(i>3){
      g*=10;
    }
    err += g*x;
    valsum += g;
  }
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;

  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}
//
//
//
//
//
//
//
//
void pid_right_7adda(float kp, float kd){
  float err = 0;
  int valsum = 0;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    if(i>3){
      g*=10;
    }
    err += g*x;
    valsum += g;
  }

  if(valsum == 0){
    left(255);
    right(0);
    iswhite=true;
    return;
  }

  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;

  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}

void pid_right_bar(float kp, float kd){
  float err = 0;
  int valsum = 0;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get_bar(i);
    if(i>3){
      g*=10;
    }
    err += g*x;
    valsum += g;
  }
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;

  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}

void pid_right_bar_narrow(float kp, float kd){
  float err = 0;
  int valsum = 0;
  // left to right
  for(int i=2;i<6;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get_bar(i);
    if(i>3){
      g*=10;
    }
    err += g*x;
    valsum += g;
  }
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;

  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}