// Revisar estado del Switch de encendido
bool isSwitchOn(){
    int state = onSwitch.getState();
    if (state == HIGH) {
        Serial.println("off");
        return false;
    }
    else {
        Serial.println("on");
        return true;
    }
}

// Revisar estado de la puerta
bool isDoorOpen(){
  if (doorState == 1) {
    return true;
  } else {
    return false;
  }
}
