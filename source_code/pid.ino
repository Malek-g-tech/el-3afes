void pid(){
  float sum = 0;
  int valsum = 0;

  // left to right
  for(int i=0;i<8;i++){
    int x = i < 4? i - 4 : i - 3;
    int g = get(i);
    sum += g*x;
    valsum += g;
  }
  sum /= valsum;
  Serial.print("Err: ");
  Serial.print(sum);
  // Serial.print("\n");
}

