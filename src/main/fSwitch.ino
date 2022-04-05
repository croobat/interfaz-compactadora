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
