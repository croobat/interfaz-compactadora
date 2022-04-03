//==================< Compact >=====================
void stateCompact(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Rellenar");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();

}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    if (accion == pushliftbutton) {
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
    if (accon == releasecompactbutton) {
        // Soltar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia levantar");

        return true;
    }
    return false;
}

