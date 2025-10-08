int ledr = 5, ledg = 6;
//int button = 7;
int capteurs[8] = {13, 25, 26, 27, 32, 33, 34, 35};

int avg0s[8],
    avg1s[8],
    thrsh[8];

void calibration(){
  //digitalWrite(ledr, 1);
  //delay(200);
  //digitalWrite(ledr, 0);
  //delay(2000);
  //digitalWrite(ledr, 1);
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
  /*digitalWrite(ledr,0)
  digitalWrite(ledg, 1);
  delay(200);
  digitalWrite(ledg,0)

  digitalWrite(ledr, 1);
  delay(200);
  digitalWrite(ledr, 0);*/
  delay(2000);
  //digitalWrite(ledr, 1);
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
  /*digitalWrite(ledr,0)
  digitalWrite(ledg,1)*/
  for(int j=0;j<8;j++){
    thrsh[j] = (avg0s[j]+avg1s[j])/2;
  }
}

int get(int i){
  int a = analogRead(capteurs[i]);
  return a >= thrsh[i];
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
}

void loop(){
  //while(digitalRead(button) != 1){}
  calibration();
  while(1){
    Serial.print("IRs: ");
    for(int i=0;i<8;i++){
      Serial.print(get(i));
      Serial.print(" ");
    }
    Serial.print("\n");
  }
}
