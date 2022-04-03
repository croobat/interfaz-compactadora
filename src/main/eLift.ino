//==================< Lift >=====================
void stateLift(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Levantar");
        Serial.println("Accion 1: ");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();
        Serial.println("Accion 2: ");
        while (Serial.available() == 0) {}
        accion2 = Serial.readStringUntil('\n');
        accion2.trim();

}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (accion == cylmid && accion2 == releaseliftbutton) {
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
