#include <Arduino.h>
#define rm1 19
#define rm2 21

// right motor

#define lm1 22
#define lm2 23

// led
bool iswhite=false;

#define blue_led 2 


int button = 5;
int capteurs[8] = {13, 25, 26, 27, 32, 33, 34, 35};

int avg0s[8],
    avg1s[8],
    thrsh[8];




void calibration(){
  digitalWrite(blue_led, 1);
  delay(200);
  digitalWrite(blue_led, 0);
  delay(2000);
  digitalWrite(blue_led, 1);
  for(int j=0;j<8;j++){
    avg0s[j] = 0;
  }
  for(int i=0;i<100;i++){
    for(int j=0;j<8;j++){
      avg0s[j] += analogRead(capteurs[j]);
    }
  }
  for(int j=0;j<8;j++){
    avg0s[j] /= 100;
  }
  digitalWrite(blue_led, 0);
  delay(200);
  digitalWrite(blue_led, 1);
  delay(200);
  digitalWrite(blue_led, 0);
  delay(2000);
  digitalWrite(blue_led, 1);
  for(int j=0;j<8;j++){
    avg1s[j] = 0;
  }
  for(int i=0;i<100;i++){
    for(int j=0;j<8;j++){
      avg1s[j] += analogRead(capteurs[j]);
    }
  }
  for(int j=0;j<8;j++){
    avg1s[j] /= 100;
  }
  digitalWrite(blue_led, 0);
  delay(200);
  digitalWrite(blue_led, 1);
  delay(200);
  digitalWrite(blue_led, 0);
  for(int j=0;j<8;j++){
    thrsh[j] = (avg0s[j]+avg1s[j])/2;
  }
  digitalWrite(2, 1);
}

int get(int i){
  int a = analogRead(capteurs[i]);
  return a >= thrsh[i];
}

int get_bar(int i){
  int a = analogRead(capteurs[i]);
  return a < thrsh[i];
}

void move_for(int speed) {
  //forward left motor
  ledcWrite(lm1,speed);
  ledcWrite(lm2,0);
  // forward right motor
  ledcWrite(rm1,speed);
  ledcWrite(rm2,0);
}

void right(int speed){
  // forward right motor
  if(speed>0){
    ledcWrite(rm1,speed);
    ledcWrite(rm2,0);
  }else{
    ledcWrite(rm1,0);
    ledcWrite(rm2,-speed);
  }
}


void left(int speed){
  if(speed>0){
    analogWrite(lm1,speed);
    analogWrite(lm2,0);
  }else{
    analogWrite(lm1,0);
    analogWrite(lm2,-speed);
  }

}

void move_back(int speed){
  ledcWrite(lm1,0);
  ledcWrite(lm2,speed);


  ledcWrite(rm1,0);
  ledcWrite(rm2,speed);

}


int lasterr = 0;
int interr = 0;

// supposing that the infras are in a left to right layout

#define ch1 0
int basespeed = 120;
int maxspeed  = 255;
void setup(){
  Serial.begin(9600);
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  ledcAttach(lm1,5000,8);
  ledcAttach(lm2,5000,8);
  ledcAttach(rm1,5000,8);
  ledcAttach(rm2,5000,8);
  
  //pinMode(ledr, OUTPUT);
  //pinMode(ledg, OUTPUT);
  //pinMode(button, INPUT);
  for(int i=0;i<8;i++){
    pinMode(capteurs[i], INPUT);
  }
  pinMode(2, OUTPUT);
  pinMode(5,INPUT_PULLUP);
}

void loop(){
  
  calibration();
 

  
  while(digitalRead(button));
  delay(500);
 
//   // bda sibaa9
  while(1){ // morabba3
    pid(4, 1);  // pid(kp,kd)
    int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
    }
    if(!allblack){
      break;
    }
  }

  while(1){ // awel 50%
    pid(30, 10);
    int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
    }
    if(allblack){
      break;
      
    }
  }
  basespeed = 60;
   maxspeed = 255;
  int t = 3000;
  int test = 1;
  while(1){ // hexagon
    pid_right(30, 4);
    if (test == 1){
      delay(500);

    }
    basespeed = 90;
    test *= 0;
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get(i);
    }
    if((allblack>6) && t < 0){
      break;
    }
    t--;
  }

  left(150);
  right(20);
  delay(500);
  //delay(300);
  //move_for(0);
  //delay(500);
  basespeed = 75;
  maxspeed = 255;

  unsigned long startTime = millis();  // record current time
  while(startTime + 4500 > millis()){ // mit9atta3
    
    pid(25, 4);
    

    
   }
   basespeed = 120;


  while(1){ // el7aadda
    pid_right_7adda(35, 5);
    int err = 0;
    for(int i=0;i<8;i++){
      int x = i < 4? i - 4 : i - 3;
      int g = get(i);
      err += g*x;
    }
    //if(err>6) break;
    if(get(4)&&get(5)&&get(6)&&get(7)) break; // thabbet faaha
  }

  left(255);
  right(50);
  delay(500);

  basespeed = 150;
  while(1){ // 9bal rondpoint
    pid(45, 10);
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get(i);
    }
    if(get(4)&&get(5)&&get(6)){
      break;
    }
  }

  move_for(255);
  delay(105);
  move_for(0);
  right(255);
  left(-255);
  delay(290);
  

  while(1){  //rond point
    left(255);
    right(103);
    if(get(0)||get(1)||get(2)||get(3)||get(4)||get(5)||get(6)||get(7)){
      break;
    }
  }


  while(1){
    pid_left(50,10);
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get(i);
    }
    if (allblack > 6){
      break;
    }
  }

  basespeed = 70;

  startTime = millis();
  while(1){ // mo555 (first 50%)
    pid_right_bar(30, 4);
    if((millis()-startTime) > 2000){
      break;
    }
  }

  while(1){ // second 50% (pid b 4 capteuret bark)
    pid_right_bar_narrow(30, 4);
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get_bar(i);
    }
    if(allblack>5){
      break;
    }
  } // kammel mo55



  while(1){
    pid_right(30, 4);
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get_bar(i);
      
    }
    if(allblack==8){
      break;
    }
  }

  left(255);
  right(50);
  delay(400);

  move_for(255);
  delay(200);

  move_for(0);
  while(1);

  
}