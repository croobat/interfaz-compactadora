#include <Arduino.h>
#line 1 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
#include <StateMachine.h>

const int BUTTON = 2;
const int LED = 3;
int BUTTONstate = 0;

#line 7 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void setup();
#line 13 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void loop();
#line 7 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void setup()
{
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == HIGH)
  {
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}

