//==================< Halt >=====================
void stateHalt(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Alto");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();

}

//-----< De Alto a Compactar >-----
bool transitionHaltCompact(){
    if (accion == pushcompactbutton) {
        // Pulsar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia compactar");
        return true;
    }
    return false;
}

//-----< De Alto a Levantar >-----
bool transitionHaltLift(){
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

