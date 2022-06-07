//==================< Fill >=====================
void stateFill(){
    // Definición de estado actual
    actualState = "Rellenando";
    if (beepFlag) {
        playBeep();
        beepFlag = false;
    }

    do {
        // Actualizar interfaz
        noOperando();
        actualizarPantalla();
        sbFill.Set_background_crop_picc(4);

        // Detectar cambios en actuadores
        compactButton.loop();
        liftButton.loop();
        compactButtonState = compactButton.getState();
        liftButtonState = liftButton.getState();
        
        doorState = digitalRead(doorSwitch);
        
    } while (!isCompactPressed() && !isLiftPressed() && !isDoorOpen());

}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    if (weight < TARGET_WEIGHT && !isDoorOpen() && isCompactPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón compactar
        beepFlag = true;
        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (weight < TARGET_WEIGHT && !isDoorOpen() && isLiftPressed()) {
        // Peso < 20 kg & cerrar puerta & pulsar botón levantar
        beepFlag = true;
        return true;
    }
    return false;
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (weight >= TARGET_WEIGHT && isDoorOpen()) {
        // Peso >= 20 kg & abrir puerta
        beepFlag = true;
        return true;
    }
    return false;
}

//-----< De Rellenar a Reiniciar >-----
bool transitionFillReset(){
    if (!isSwitchOn() || isNextionResetPressed) {
        isNextionResetPressed = false;
        // Interruptor de apagado
        return true;
    }
    return false;
}
