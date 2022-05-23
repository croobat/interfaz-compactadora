// constants won't change
const int relay_RedLED = 46;
const int relay_GreenLED = 42;
const int relay_L = 28;
const int relay_R = 29;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin as an output.
  pinMode(relay_RedLED, OUTPUT);
  pinMode(relay_GreenLED, OUTPUT);
  pinMode(relay_L, OUTPUT);
  pinMode(relay_R, OUTPUT);  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(relay_RedLED, LOW);
  digitalWrite(relay_GreenLED, LOW);
  digitalWrite(relay_R, LOW);
  digitalWrite(relay_L, LOW);
  delay(500);
}
