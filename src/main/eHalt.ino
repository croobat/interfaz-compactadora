//==================< Halt >=====================
void stateHalt(){
    Serial.println("Alto");
}

//-----< De Alto a Compactar >-----
bool transitionHaltCompact(){
    if (false) {
        // Pulsar botón compactar
        return true;
    }
    return false;
}

//-----< De Alto a Levantar >-----
bool transitionHaltLift(){
    if (false) {
        // Pulsar botón levantar
        return true;
    }
    return false;
}

