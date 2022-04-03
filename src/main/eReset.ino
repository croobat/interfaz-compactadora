//==================< Reset >=====================
void stateReset(){
    Serial.println("Reiniciar");
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
    // Reiniciar carrera, luces y alarma
    return true;
}

