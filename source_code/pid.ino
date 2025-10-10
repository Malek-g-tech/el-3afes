float corr = 0;
//bool isLeft;



void pid(float kp, float kd){
  float err = 0;
  int valsum = 0;
  int i=0;
  /*isLeft = 0; 
  if(!get(0)){
    isLeft = 1;
  }*/
  /*int v[6];
  while(valsum!=0 && i!=6)
  { 
    if(analogRead(capteurs[j])>=thrsh)
      v.push_back()
  }*/
  //int basespeed = 80;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    err += g*x;
    valsum += g;
  }

  /*if(valsum == 0){
    corr = isLeft?20:-20;
    int spd1 = constrain(basespeed + 2*corr , 0, 100);
    int spd2 = constrain(basespeed - 2*corr, 0, 100);
    left(spd1);
    right(spd2);
    
    return;
  }*/
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;
  // interr += err; // Ki == 0 for now
  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}

void pid_right(float kp, float kd){
  float err = 0;
  int valsum = 0;
  /*isLeft = 0; 
  if(!get(0)){
    isLeft = 1;
  }*/
  /*int v[6];
  while(valsum!=0 && i!=6)
  { 
    if(analogRead(capteurs[j])>=thrsh)
      v.push_back()
  }*/
  //int basespeed = 80;
  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    if(i>3){
      g*=4;
    }
    err += g*x;
    valsum += g;
  }

  /*if(valsum == 0){
    corr = isLeft?20:-20;
    int spd1 = constrain(basespeed + 2*corr , 0, 100);
    int spd2 = constrain(basespeed - 2*corr, 0, 100);
    left(spd1);
    right(spd2);
    
    return;
  }*/
  if(valsum == 0){ // handle all white case
    return;
  }
  err /= valsum;

  float derr = err - lasterr;
  lasterr = err;
  // interr += err; // Ki == 0 for now
  
  corr = kp*err+kd*derr;
  

  int spd1 = constrain(basespeed + corr, -maxspeed, maxspeed);
  int spd2 = constrain(basespeed - corr, -maxspeed, maxspeed);

  left(spd1);
  right(spd2);
}