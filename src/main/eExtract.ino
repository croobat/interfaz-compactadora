//==================< Extract >=====================
void stateExtract(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Extraer");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    while (doorState == 1) {
        doorState = digitalRead(doorSwitch); // Switch de puerta
    }
}

//-----< De Extraer a Inactivo >-----
bool transitionExtractIdle(){
    if (!isDoorOpen()) {
        // Sensor magnético cerrado

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia inactivo");

        return true;
    }
    return false;
}

