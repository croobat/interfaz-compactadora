//==================< Fill >=====================
void stateFill(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Rellenar");
        Serial.println("Accion 1: ");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();
        Serial.println("Accion 2: ");
        while (Serial.available() == 0) {}
        accion2 = Serial.readStringUntil('\n');
        accion2.trim();
        Serial.println("Accion 3: ");
        while (Serial.available() == 0) {}
        accion3 = Serial.readStringUntil('\n');
        accion3.trim();

}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    if (accion == lesskg20carton && accion2 == closedoor && accion3 == pushcompactbutton) {
        // Peso < 20 kg & cerrar puerta & pulsar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia compactar");

        return true;
    }
    return false;
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (accion == kg20carton && accion2 == opendoor) {
        // Peso >= 20 kg & abrir puerta

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia extraer");

        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (accion == lesskg20carton && accion2 == closedoor && accion3 == pushliftbutton) {
        // Peso < 20 kg & cerrar puerta & pulsar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia levantar");

        return true;
    }
    return false;
}

