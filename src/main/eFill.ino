//==================< Fill >=====================
void stateFill(){


        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Rellenar");
    if (accion != lesskg20carton || accion != kg20carton) {
        Serial.println("Accion 1 (cartón): ");
        while (Serial.available() == 0) {}
        accion = Serial.readStringUntil('\n');
        accion.trim();
    }
        /* Serial.println("Accion 2: "); */
        /* while (Serial.available() == 0) {} */
        /* accion2 = Serial.readStringUntil('\n'); */
        /* accion2.trim(); */

     do {
        /* OPState = false; */
        /* speakerOFF(); */
        noOperando();


        compactButton.loop();
        liftButton.loop();
        doorState = digitalRead(doorSwitch); // Switch de puerta
        compactButtonState = compactButton.getState(); // Actualizar estado boton compactar
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
    } while (!isCompactPressed() && !isLiftPressed() && !isDoorOpen());

}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    if (accion == lesskg20carton && !isDoorOpen() && isCompactPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia compactar");

        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (accion == lesskg20carton && !isDoorOpen() && isLiftPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia levantar");

        return true;
    }
    return false;
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (accion == kg20carton && isDoorOpen()) {
        // Peso >= 20 kg & abrir puerta

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia extraer");

        return true;
    }
    return false;
}

