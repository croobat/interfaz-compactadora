//#include <ezButton.h>
//
//ezButton doorSwitch(23);
//bool     doorState;
//
//void setup() {
//  Serial.begin(9600);
//  doorSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
//}
//
//void loop() {
//  int state = doorSwitch.getState();
//  if (state == HIGH)
//    Serial.println("The switch: OFF");
//  else
//    Serial.println("The switch: ON");
//}

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-door-sensor
 */

const int DOOR_SENSOR_PIN = 23; // Arduino pin connected to door sensor's pin

int doorState;

void setup() {
  Serial.begin(9600);                     // initialize serial
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
}

void loop() {
  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    Serial.println("The door is open");
  } else {
    Serial.println("The door is closed");
  }
}
