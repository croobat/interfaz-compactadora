//==================< Compact >=====================
void stateCompact(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Compactar");
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
    if (accion == releasecompactbutton) {
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
    if (accion == emergencystop) {
        // Pulsar paro de emergencia

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia paro de emergencia");

        return true;
    }
    return false;
}

