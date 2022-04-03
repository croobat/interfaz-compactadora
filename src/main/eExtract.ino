//==================< Extract >=====================
void stateExtract(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Extraer");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();

}

//-----< De Extraer a Inactivo >-----
bool transitionExtractIdle(){
    if (accion = closedoor) {
        // Sensor magnético cerrado

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia inactivo");

        return true;
    }
    return false;
}

