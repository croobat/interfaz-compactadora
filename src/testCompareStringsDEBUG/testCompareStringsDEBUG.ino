const char* onswitch = "onswitch";
String accion = "";

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    accion = Serial.readStringUntil('\n');
    accion.trim();
    if (accion == onswitch) {
      Serial.println("si");
    } else {
      Serial.println("no");
    }
  }
}
