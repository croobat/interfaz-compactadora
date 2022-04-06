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

// Revisar estado botón compactar
bool isCompactPressed(){
  if (compactButtonState == 0) {
    return true;
  } else {
    return false;
  }
}

// Revisar estado botón levantar
bool isLiftPressed(){
  if (liftButtonState == 0) {
    return true;
  } else {
    return false;
  }
}

// Revisar estado botón emergencia
bool isEmergencyPressed(){
  if (emergencyButtonState == 0) {
    return true;
  } else {
    return false;
  }
}
