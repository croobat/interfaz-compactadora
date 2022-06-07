//==================< Idle >=====================
void stateIdle(){
    // Definición de estado actual
    actualState = "Inactivo";
    playBeep();

    while (doorState == 1) {delay(10);}

    //boolean _resume = false;
    //while (_resume == false) {

   // }
    
    do {
        // Actualizar interfaz
        noOperando();
        actualizarPantalla();
        sbIdle.Set_background_crop_picc(4);

        // Detectar cambios en HMI
        nexLoop(nex_listen_list);
        // Detectar cambios en actuadores
        onSwitch.loop();
        doorState = digitalRead(doorSwitch);
        
    } while (!onSwitch.isReleased() && !isDoorOpen() && !isNextionResetPressed);
}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    if (isDoorOpen()) {
        // Sensor magnético abierto
        return true;
    }
    return false;
}

//-----< De Inactivo a Reiniciar >-----
bool transitionIdleReset(){
    if (!isSwitchOn() || isNextionResetPressed) {
        isNextionResetPressed = false;
        // Interruptor de apagado
        return true;
    }
    return false;
}
