//==================< Fill >=====================
void stateFill(){

    if (beepFlag) {
        playBeep();
        beepFlag = false;
    }
    actualState = "Rellenando";
        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Rellenar");
//    if (accion != lesskg20carton || accion != kg20carton) {
//        Serial.println("Accion 1 (cartón): ");
//        while (Serial.available() == 0) {}
//        accion = Serial.readStringUntil('\n');
//        accion.trim();
//    }
        /* Serial.println("Accion 2: "); */
        /* while (Serial.available() == 0) {} */
        /* accion2 = Serial.readStringUntil('\n'); */
        /* accion2.trim(); */

     do {
        noOperando();
        actualizarPantalla();
        sbFill.Set_background_crop_picc(4);

        compactButton.loop();
        liftButton.loop();
        doorState = digitalRead(doorSwitch); // Switch de puerta
        compactButtonState = compactButton.getState(); // Actualizar estado boton compactar
        liftButtonState = liftButton.getState(); // Actualizar estado botón levantar
//              Serial.println(weight);
//              Serial.println("/n");
//              Serial.println(TARGET_WEIGHT);
    } while (!isCompactPressed() && !isLiftPressed() && !isDoorOpen());

}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    //if (accion == lesskg20carton && !isDoorOpen() && isCompactPressed()) {
    if (weight < TARGET_WEIGHT && !isDoorOpen() && isCompactPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón compactar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia compactar");
        beepFlag = true;
        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (weight < TARGET_WEIGHT && !isDoorOpen() && isLiftPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón levantar

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia levantar");
        beepFlag = true;
        return true;
    }
    return false;
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (weight >= TARGET_WEIGHT && isDoorOpen()) {
        // Peso >= 20 kg & abrir puerta

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia extraer");

        beepFlag = true;
        return true;
    }
    return false;
}
