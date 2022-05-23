//==================< S0 >=====================
void state0(){
    
    actualState = "Inicial";
        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Inicial");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    do {
        actualizarPantalla();
        sbS0.Set_background_crop_picc(4);
        
        onSwitch.loop(); // Switch de encendido
    } while (!onSwitch.isPressed());
}

//-----< De S0 a Inactivo >-----
bool transitionS0Idle(){
    /* if (compareString("onswitch")) { */
    if (isSwitchOn()) {
        // Interruptor de encendido

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
//        Serial.println("Accion: " + accion + " | hacia inactivo");

        return true;
    }
    return false;
}
