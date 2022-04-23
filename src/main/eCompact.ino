//==================< Compact >=====================
void stateCompact(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Compactar");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

     do {
        operando();

        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton compactar
        compactButtonState = compactButton.getState(); // Actualizar estado boton compactar
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
    } while (isCompactPressed() && !isLiftPressed() && !isEmergencyPressed());
}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    if (isLiftPressed()) {
        // Pulsar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia levantar");

        return true;
    }
    return false;
}

//-----< De Compactar a Alto >-----
bool transitionCompactHalt(){
    if (!isCompactPressed()) {
        // Soltar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia alto");

        return true;
    }
    return false;
}

//-----< De Compactar a Stop >-----
bool transitionCompactStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia paro de emergencia");

        return true;
    }
    return false;
}

