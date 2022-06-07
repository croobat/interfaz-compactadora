//==================< Compact >=====================
void stateCompact(){
    // Definición de estado actual    
    actualState = "Compactando";
    playBeep();


    do {
        // Actualizar interfaz
        operando();
        actualizarPantalla();
        sbCompact.Set_background_crop_picc(4);
        incrementarCarrera();
        
        // Activar cilindro (compactar)
        digitalWrite(relay_L, LOW);

        // Detectar cambios en actuadores    
        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState();
        compactButtonState = compactButton.getState();
        liftButtonState = liftButton.getState();
        
    } while (isCompactPressed() && !isLiftPressed() && !isEmergencyPressed());
}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    if (isLiftPressed()) {
        // Pulsar botón levantar
        digitalWrite(relay_L, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}

//-----< De Compactar a Alto >-----
bool transitionCompactHalt(){
    if (!isCompactPressed()) {
        // Soltar botón compactar
        digitalWrite(relay_L, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}

//-----< De Compactar a Stop >-----
bool transitionCompactStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia
        digitalWrite(relay_L, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}
