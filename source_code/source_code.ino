#include <Arduino.h>
#define rm1 19
#define rm2 21

// right motor

#define lm1 22
#define lm2 23

// led

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
  delay(5000);
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
  delay(5000);
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
int basespeed = 80;
int maxspeed  = 150;
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
}

void loop(){
  /*while(1){ // dump
    for(int i=0;i<8;i++){
      Serial.print(analogRead(capteurs[i]));
      Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    Serial.println("");
  }*/
  /*right(50);
  left(124);
  while(1);*/
  while(digitalRead(button) != 1){}
  calibration();
 

  delay(5000);
  while(!digitalRead(button));
 
  // bda sibaa9
  while(1){ // morabba3
    pid(4, 1);  // pid(kp,kd)
    int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
      //Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    if(!allblack){
      break;
    }
  }

  while(1){ // awel 50%
    pid(15, 2);
    int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
      //Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    if(allblack){
      break;
    }
  }
  basespeed = 50;
  maxspeed = 100;
  int t = 100;
  while(1){ // hexagon
    pid_right(15, 2);
    int allblack = 0;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack += get(i);
      //Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    if(allblack>6 && t < 0){
      break;
    }
    t--;
  }
  move_for(0);
  delay(1000);
  //delay(300);
  //move_for(0);
  //delay(500);
  basespeed = 60;
  maxspeed = 120;
  for(int i=0;i<200;i++){ // ba3d hexa (mit9atta3)
    pid_right(15, 2);
    /*int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
      //Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    if(allblack){
      break;
    }*/
  }

  while(1){ // el7aadda
    pid_right(15, 2);
    int err = 0;
    for(int i=0;i<8;i++){
      int x = i < 4? i - 4 : i - 3;
      int g = get(i);
      err += g*x;
    }

    if(err>6) // very bad conditional
      break;
  }

  move_for(0);
  while(1);
  /*while(1){
    Serial.print("IRs: ");
    int allblack = 1;
    for(int i=0;i<8;i++){
      //Serial.print(get(i));
      allblack = allblack*get(i);
      //Serial.print(" ");
      //Serial.println(digitalRead(button));
    }
    if(allblack){
      digitalWrite(2, 1);
    }else{
      digitalWrite(2, 0);
    }
    //Serial.print("\n");
    pid(10,0.5);
    Serial.print("\n");
    
  }*/
}
