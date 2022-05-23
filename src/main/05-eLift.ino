//==================< Lift >=====================
void stateLift(){

    playBeep();
    actualState = "Levantando";
    /* ---------------------- */
    /* -  test  - */
    /*  ---------------------- */
//        Serial.println("Levantar");
//        Serial.println("Accion 1 (cilindro): ");
//        while (Serial.available() == 0) {}
//        accion = Serial.readStringUntil('\n');
//        accion.trim();
    /* Serial.println("Accion 2: "); */
    /* while (Serial.available() == 0) {} */
    /* accion2 = Serial.readStringUntil('\n'); */
    /* accion2.trim(); */

     do {
        operando();
        actualizarPantalla();
        sbLift.Set_background_crop_picc(4);
        disminuirCarrera();

        digitalWrite(relay_R, LOW);
    
        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton emergencia
        compactButtonState = compactButton.getState();
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar

        
    } while (!isCompactPressed() && isLiftPressed() && !isEmergencyPressed());
}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (cylStroke > 0 && !isLiftPressed()) {
        // carrera cilindro > 0 & soltar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia alto");

        digitalWrite(relay_R, HIGH);

        return true;
    }
    return false;
}

//-----< De Levantar a Inactivo >-----
bool transitionLiftIdle(){
    if (cylStroke == 0) {
        // carrera cilindro = 0

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia inactivo");
        
        digitalWrite(relay_R, HIGH);

        return true;
    }
    return false;
}

//-----< De Levantar a Stop >-----
bool transitionLiftStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia paro de emergencia");

        digitalWrite(relay_R, HIGH);

        return true;
    }
    return false;
}
