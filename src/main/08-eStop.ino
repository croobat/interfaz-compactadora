//==================< Stop >=====================
void stateStop(){
    // Definición de estado actual  
    actualState = "Paro de emergencia";
    playBeep();

    do {
        // Actualizar interfaz
        actualizarPantalla();
        sbStop.Set_background_crop_picc(4);
        tState.Set_background_crop_picc(5);  

        // Detectar cambios en actuadores    
        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState();
        
    } while (isEmergencyPressed());
}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
//    if (!isEmergencyPressed()) {
    if (!isEmergencyPressed()) {
        //Paro de emergencia presionado
        tState.Set_background_crop_picc(1);
        return true;
    }
    return false;
}
