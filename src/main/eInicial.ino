//==================< S0 >=====================
void state0(){

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Inicial");
        /* while (Serial.available() == 0) {} */
        /* accion = Serial.readStringUntil('\n'); */
        /* accion.trim(); */

    while (!onSwitch.isPressed()) {
        onSwitch.loop(); // Switch de encendido
    }
}

//-----< De S0 a Inactivo >-----
bool transitionS0Idle(){
    /* if (compareString("onswitch")) { */
    if (isSwitchOn()) {
        // Interruptor de encendido

        /* ---------------------- */
        /* -  test  - */
        /*  ---------------------- */
        Serial.println("Accion: " + accion + " | hacia inactivo");

        return true;
    }
    return false;
}

