//==================< Halt >=====================
void stateHalt(){
    // Definición de estado actual
    actualState = "Detenido";
    playBeep();

    do {
        // Actualizar interfaz
        operando();
        actualizarPantalla();
        sbHalt.Set_background_crop_picc(4);

        // Detectar cambios en actuadores    
        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        compactButtonState = compactButton.getState();
        liftButtonState = liftButton.getState();
        emergencyButtonState = emergencyButton.getState();
        
    } while (!isCompactPressed() && !isLiftPressed() && !isEmergencyPressed());
}

//-----< De Alto a Compactar >-----
bool transitionHaltCompact(){
    if (isCompactPressed()) {
        // Pulsar botón compactar
        return true;
    }
    return false;
}

//-----< De Alto a Levantar >-----
bool transitionHaltLift(){
    if (isLiftPressed()) {
        // Pulsar botón levantar
        return true;
    }
    return false;
}

//-----< De Alto a Stop >-----
bool transitionHaltStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia
        return true;
    }
    return false;
}
