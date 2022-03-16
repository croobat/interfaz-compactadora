#include <StateMachine.h>

const int BUTTON = 2;
const int LED = 3;
int BUTTONstate = 0;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == HIGH)
  {
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}

void fsm() {

}
