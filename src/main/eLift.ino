//==================< Lift >=====================
void stateLift(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Levantar");
        Serial.println("Accion 1 (cilindro): ");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();
        /* Serial.println("Accion 2: "); */
        /* while (Serial.available() == 0) {} */
        /* accion2 = Serial.readStringUntil('\n'); */
        /* accion2.trim(); */

     do {
        operando();
        vaciarDiagramaEstados();
        sbLift.Set_background_crop_picc(4);
        tEstado.setText("Levantando");
        actualizarReloj();

        liftButton.loop();
        emergencyButton.loop();
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton emergencia

        digitalWrite(relay_R, HIGH);
        
    } while (isCompactPressed() && !isLiftPressed() && !isEmergencyPressed());
}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (accion == cylmid && !isLiftPressed()) {
        // carrera cilindro > 0 & soltar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia alto");

        digitalWrite(relay_R, LOW);

        return true;
    }
    return false;
}

//-----< De Levantar a Inactivo >-----
bool transitionLiftIdle(){
    if (accion == cylbottom) {
        // carrera cilindro = 0

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia inactivo");
        digitalWrite(relay_R, LOW);

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
        Serial.println("Accion: " + accion + " | hacia paro de emergencia");

        digitalWrite(relay_R, LOW);

        return true;
    }
    return false;
}
