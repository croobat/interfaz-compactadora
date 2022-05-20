//==================< Idle >=====================
void stateIdle(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Inactivo");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    while (doorState == 1) {delay(10);}

    do {
        actualizarPeso();
        actualizarReloj();

        /* OPState = false; */
        /* speakerOFF(); */
        noOperando();
       vaciarDiagramaEstados();
       sbIdle.Set_background_crop_picc(4);
       tEstado.setText("Inactivo");

        onSwitch.loop(); // Switch de encendido
        doorState = digitalRead(doorSwitch); // Switch de puerta
    } while (!onSwitch.isReleased() && !isDoorOpen());
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
