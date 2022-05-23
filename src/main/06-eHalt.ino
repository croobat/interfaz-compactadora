//==================< Halt >=====================
void stateHalt(){

    playBeep();
    actualState = "Detenido";
        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Alto");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

     do {
        operando();
        actualizarPantalla();
        sbHalt.Set_background_crop_picc(4);

        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        compactButtonState = compactButton.getState(); // Actualizar estado boton compactar
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton emergency
    } while (!isCompactPressed() && !isLiftPressed() && !isEmergencyPressed());

}

//-----< De Alto a Compactar >-----
bool transitionHaltCompact(){
    if (isCompactPressed()) {
        // Pulsar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia compactar");
        return true;
    }
    return false;
}

//-----< De Alto a Levantar >-----
bool transitionHaltLift(){
    if (isLiftPressed()) {
        // Pulsar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia levantar");
        return true;
    }
    return false;
}

//-----< De Alto a Stop >-----
bool transitionHaltStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia paro de emergencia");

        return true;
    }
    return false;
}
