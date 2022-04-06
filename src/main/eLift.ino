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
        liftButton.loop();
        emergencyButton.loop();
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton emergencia
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

        return true;
    }
    return false;
}
