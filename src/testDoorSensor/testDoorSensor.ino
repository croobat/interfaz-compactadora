const int DOOR_SENSOR_PIN  = 13; // Arduino pin connected to the OUTPUT pin of door sensor
const int LED_PIN          = 5;  // Arduino pin connected to LED's pin

int doorState;

void setup() {
  Serial.begin(9600);                     // initialize serial
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(LED_PIN, OUTPUT);               // set arduino pin to output mode
}

void loop() {
  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    Serial.println("The door is open");;
    digitalWrite(LED_PIN, HIGH); // turn on LED
  } else {
    Serial.println("The door is closed");
    digitalWrite(LED_PIN, LOW);  // turn off LED
  }
}
