# 1 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
# 2 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino" 2

const int BUTTON = 2;
const int LED = 3;
int BUTTONstate = 0;

void setup()
{
  pinMode(BUTTON, 0x0);
  pinMode(LED, 0x1);
}

void loop()
{
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == 0x1)
  {
    digitalWrite(LED, 0x1);
  }
  else{
    digitalWrite(LED, 0x0);
  }
}
