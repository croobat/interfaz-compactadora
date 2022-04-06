//==================< Idle >=====================
void stateIdle(){

    /* ---------------------- */
    /* -  Actualizar peso  - */
    /* ---------------------- */


        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Inactivo");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    while (doorState == 1) {delay(10);}

    while (!onSwitch.isReleased() && doorState == 0) {
        onSwitch.loop(); // Switch de encendido
        doorState = digitalRead(doorSwitch); // Switch de puerta
    }
}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    if (isDoorOpen()) {
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
    if (!isSwitchOn()) {
        // Interruptor de apagado

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia reiniciar");

        return true;
    }
    return false;
}

