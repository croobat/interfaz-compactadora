//==================< Idle >=====================
void stateIdle(){

    /* ---------------------- */
    /* -  Actualizar peso  - */
    /* ---------------------- */


        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Inactivo");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();

}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    if (accion == opendoor) {
        // Sensor magnético abierto

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia rellenar");

        return true;
    }
    return false;
}

//-----< De Inactivo a Reiniciar >-----
bool transitionIdleReset(){
    if (accion == offswitch) {
        // Interruptor de apagado

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia reiniciar");

        return true;
    }
    return false;
}

