// Revisar estado del Switch de encendido
bool isSwitchOn(){
    int state = onSwitch.getState();
    if (state == HIGH) {
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

// Encender bocina
void speakerON(){
        for(speakerFreq=400; speakerFreq<500; speakerFreq++){
            tone(speaker,speakerFreq);
            delay(5);
        }
        for(speakerFreq=500; speakerFreq>400; speakerFreq--){
            tone(speaker,speakerFreq);
            delay(5);
    }
}

// Apagar bocina
void speakerOFF(){
    noTone(speaker);
}

void operando(){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    speakerON();
}

void noOperando(){
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    speakerOFF();
}

void reiniciar(){
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    speakerOFF();
}
