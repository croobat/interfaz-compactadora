//==================< Compact >=====================
void stateCompact(){
    Serial.println("Compactar");
}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    if (false) {
        // Pulsar botón levantar
        return true;
    }
    return false;
}

//-----< De Compactar a Alto >-----
bool transitionCompactHalt(){
    if (false) {
        // Soltar botón compactar
        return true;
    }
    return false;
}

