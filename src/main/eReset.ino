//==================< Reset >=====================
void stateReset(){
    Serial.println("Reiniciar");
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
    Serial.println("Reiniciando cilindro...");
    Serial.println("Reiniciando luces...");
    Serial.println("Silenciando alarma...");
    // Reiniciar carrera, luces y alarma
    return true;
}

