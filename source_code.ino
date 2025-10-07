int ledr = 5, ledg = 6;
int button = 7;
int infra1 = A0;

int avg0, avg1;

void calibration(){
  digitalWrite(ledr, 1);
  delay(200);
  digitalWrite(ledr, 0);
  delay(2000);
  digitalWrite(ledr, 1);
  avg0 = 0;
  for(int i=0;i<100;i++){
    int r = analogRead(infra1);
    avg0 += r;
  }
  avg0 /= 100;
  digitalWrite(ledr,0);
  digitalWrite(ledg, 1);
  delay(200);
  digitalWrite(ledg,0)

  digitalWrite(ledr, 1);
  delay(200);
  digitalWrite(ledr, 0);
  delay(2000);
  digitalWrite(ledr, 1);
  avg1 = 0;
  for(int i=0;i<100;i++){
    int r = analogRead(infra1);
    avg1 += r;
  }
  digitalWrite(ledr,0)
  digitalWrite(ledg,1)
  avg1 /= 100;


}

void setup(){
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(button, INPUT);
  pinMode(infra1, INPUT);
}

void loop(){
  while(1){ // calibration
  }
  while(1){ // phase 1
  }
  while(1){ // phase 2
  }
  while(1){ // phase 3
  }
  while(1){ // phase 4
  }
}
