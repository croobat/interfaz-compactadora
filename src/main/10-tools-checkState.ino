/* ---------------------- */
/* -  Hardware  - */
/* ---------------------- */
// Revisar estado del Switch de encendido
bool isSwitchOn(){
    onSwitchState = onSwitch.getState();
    if (onSwitchState == HIGH) {
        return false;
    }
    else {
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

/* ---------------------- */
/* -  HMI  - */
/* ---------------------- */
// Revisar estado botón Reiniciar HMI
void bResetPopCallback(void *ptr) {
    isNextionResetPressed = true;
    tState.setText("test");
}
