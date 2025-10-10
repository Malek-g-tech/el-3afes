#include <Arduino.h>
#define lm1 19
#define lm2 21


// right motor

#define rm1 22
#define rm2 23
int button = 5;
int capteurs[8] = {13, 25, 26, 27, 32, 33, 34, 35};

int avg0s[8],
    avg1s[8],
    thrsh[8];


// void pid(){
//   float sum = 0;
//   int valsum = 0;

//   // left to right
//   for(int i=0;i<8;i++){
//     int x = i < 4? i - 4 : i - 3;
//     int g = get(i);
//     sum += g*x;
//     valsum += g;
//   }
//   sum /= valsum;
//   Serial.print("Err: ");
//   Serial.print(sum);
//   //Serial.print("\n");
// }


void calibration(){
  digitalWrite(2, 1);
  delay(200);
  digitalWrite(2, 0);
  delay(5000);
  digitalWrite(2, 1);
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
  digitalWrite(2, 0);
  delay(200);
  digitalWrite(2, 1);
  delay(200);
  digitalWrite(2, 0);
  delay(5000);
  digitalWrite(2, 1);
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
  digitalWrite(2, 0);
  delay(200);
  digitalWrite(2, 1);
  delay(200);
  digitalWrite(2, 0);
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

// void hard_left(){
//   analogWrite(lm1,0);
//   analogWrite(lm2,0);

//   // forward right motor
//   analogWrite(rm1,255);
//   analogWrite(rm2,0);
// }


// void hard_right(){
//   analogWrite(lm1,255);
//   analogWrite(lm2,0);

  
//   // forward right motor


//   analogWrite(rm1,0);
//   analogWrite(rm2,0);

// }

int lasterr = 0;
int interr = 0;

// supposing that the infras are in a left to right layout

#define ch1 0

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
  // ledcAttachPin(19,ch1);
  // ledcSetup(ch1,1000,8);
  // setupMotors();
  //pinMode(ledr, OUTPUT);
  //pinMode(ledg, OUTPUT);
  //pinMode(button, INPUT);
  for(int i=0;i<8;i++){
    pinMode(capteurs[i], INPUT);
  }
  pinMode(2, OUTPUT);
}

void loop(){
  //while(digitalRead(button) != 1){}
  // calibration();
  // motorAForward(50);

  // while(!digitalRead(button));
  // analogWrite(lm1,50);
  // analogWrite(rm1,50);
  // delay(1000);
  // analogWrite(lm1,0);
  // analogWrite(rm1,0);


  // digitalWrite(lm1,HIGH);
  move_for(100);
  // digitalWrite(lm1, HIGH);
  // digitalWrite(lm2, LOW);

  // digitalWrite(rm1, HIGH);
  // digitalWrite(rm2, LOW);
  // delay(5000);
  // digitalWrite(lm1,LOW);
  // digitalWrite(rm1,HIGH);
  // ledcWrite(lm1,70);
  // while(1){
  //   Serial.print("IRs: ");
  //   int allblack = 1;
  //   for(int i=0;i<8;i++){
  //     //Serial.print(get(i));
  //     allblack = allblack*get(i);
  //     //Serial.print(" ");
  //     //Serial.println(digitalRead(button));
  //   }
  //   if(allblack){
  //     digitalWrite(2, 1);
  //   }else{
  //     digitalWrite(2, 0);
  //   }
  //   //Serial.print("\n");
  //   // pid();
  //   Serial.print("\n");
    
  // }
}
