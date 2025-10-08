int ledr = 5, ledg = 6;
//int button = 7;
int capteurs[8] = {13, 25, 26, 27, 32, 33, 34, 35};

int avg0s[8],
    avg1s[8],
    thrsh[8];



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
  delay(5000);
}

int get(int i){
  int a = analogRead(capteurs[i]);
  return a >= thrsh[i];
}



void move_for(int speed) {
  //forward left motor
  analogWrite(lm1,speed);
  analogWrite(lm3,speed);
  analogWrite(lm2,0);
  analogWrite(lm4,0);
  // forward right motor
  analogWrite(rm1,speed);
  analogWrite(rm3,speed);
  analogWrite(rm2,0);
  analogWrite(rm4,0);
}

void hard_left(){
  analogWrite(lm1,0);
  analogWrite(lm3,0);
  analogWrite(lm2,0);
  analogWrite(lm4,0);
  // forward right motor
  analogWrite(rm1,255);
  analogWrite(rm3,255);
  analogWrite(rm2,0);
  analogWrite(rm4,0);
}


void hard_right(){
  analogWrite(lm1,255);
  analogWrite(lm3,255);
  analogWrite(lm2,0);
  analogWrite(lm4,0);
  // forward right motor
  analogWrite(rm1,0);
  analogWrite(rm3,0);
  analogWrite(rm2,0);
  analogWrite(rm4,0);
}

int lasterr = 0;
int interr = 0;

// supposing that the infras are in a left to right layout

void setup(){
  Serial.begin(9600);
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
  calibration();
  while(1){
    Serial.print("IRs: ");
    int allblack = 1;
    for(int i=0;i<8;i++){
      Serial.print(get(i));
      allblack = allblack*get(i);
      Serial.print(" ");
    }
    
    if(allblack){
      digitalWrite(2, 1);
    }else{
      digitalWrite(2, 0);
    }
    Serial.print(" ");
    for(int i=0;i<8;i++){
      Serial.print(thrsh[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
}