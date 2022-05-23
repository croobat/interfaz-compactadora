//==================< Compact >=====================
void stateCompact(){
    
    playBeep();
    actualState = "Compactando";
    /* ---------------------- */
    /* -  test  - */
    /*  ---------------------- */
//    Serial.println("Compactar");
    /* while (Serial.available() == 0) {} */
    /* accion = Serial.readStringUntil('\n'); */
    /* accion.trim(); */

    do {
        operando();
        actualizarPantalla();
        sbCompact.Set_background_crop_picc(4);
        incrementarCarrera();

        digitalWrite(relay_L, LOW);
    
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
//        Serial.println("Accion: " + accion + " | hacia levantar");
        
        digitalWrite(relay_L, HIGH);

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
//        Serial.println("Accion: " + accion + " | hacia alto");
        
        digitalWrite(relay_L, HIGH);

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
//        Serial.println("Accion: " + accion + " | hacia paro de emergencia");
        
        digitalWrite(relay_L, HIGH);

        return true;
    }
    return false;
}
