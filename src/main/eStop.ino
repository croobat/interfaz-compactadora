//==================< Stop >=====================
void stateStop(){
    Serial.println("Paro de emergencia");
}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
    Serial.println("Emergencia: Reiniciando sistema")
    return true;
}
