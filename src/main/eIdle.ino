//==================< Idle >=====================
void stateIdle(){
    Serial.println("Inactivo");
    // Actualizar peso
}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    if (false) {
        // Sensor magnético abierto
        return true;
    }
    return false;
}

//-----< De Inactivo a Reiniciar >-----
bool transitionIdleReset(){
    if (false) {
        // Interruptor de apagado
        return true;
    }
    return false;
}

