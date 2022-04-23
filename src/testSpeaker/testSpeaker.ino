int i=0;
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  for(i=700;i<800;i++){
  tone(9,i);
  delay(15);
  }
  for(i=800;i>700;i--){
  tone(9,i);
  delay(15);
  }
  }
