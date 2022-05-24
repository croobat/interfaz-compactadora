//==================< Lift >=====================
void stateLift(){
    // Definición de estado actual
    actualState = "Levantando";
    playBeep();

    do {
        // Actualizar interfaz
        operando();
        actualizarPantalla();
        sbLift.Set_background_crop_picc(4);
        disminuirCarrera();

        // Activar cilindro (levantar)
        digitalWrite(relay_R, LOW);
    
        // Detectar cambios en actuadores    
        compactButton.loop();
        liftButton.loop();
        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState();
        compactButtonState = compactButton.getState();
        liftButtonState = liftButton.getState();
                
    } while (!isCompactPressed() && isLiftPressed() && !isEmergencyPressed());
}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (cylStroke > 0 && !isLiftPressed()) {
        // carrera cilindro > 0 & soltar botón levantar
        digitalWrite(relay_R, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}

//-----< De Levantar a Inactivo >-----
bool transitionLiftIdle(){
    if (cylStroke == 0) {
        // carrera cilindro = 0
        digitalWrite(relay_R, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}

//-----< De Levantar a Stop >-----
bool transitionLiftStop(){
    if (isEmergencyPressed()) {
        // Pulsar paro de emergencia
        digitalWrite(relay_R, HIGH);     // Desactivar cilindro
        return true;
    }
    return false;
}
