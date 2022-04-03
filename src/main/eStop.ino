//==================< Stop >=====================
void stateStop(){
    Serial.println("Paro de emergencia");
}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
    if (false) {
        // Pulsar botón de paro
        return true;
    }
    return false;
}
