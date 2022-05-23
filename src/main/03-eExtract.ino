//==================< Extract >=====================
void stateExtract(){

    playBeep();
    actualState = "Extrayendo bloque";
        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Extraer");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    do {
        noOperando();
        actualizarPantalla();
        sbExtract.Set_background_crop_picc(4);

        doorState = digitalRead(doorSwitch); // Switch de puerta
    } while (doorState == 1);
}

//-----< De Extraer a Inactivo >-----
bool transitionExtractIdle(){
    if (!isDoorOpen()) {
        // Sensor magnético cerrado

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia inactivo");

        return true;
    }
    return false;
}
