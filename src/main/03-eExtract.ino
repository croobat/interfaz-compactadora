//==================< Extract >=====================
void stateExtract(){
    // Definición de estado actual
    actualState = "Extrayendo bloque";
    playBeep();

    do {
        // Actualizar interfaz
        noOperando();
        actualizarPantalla();
        sbExtract.Set_background_crop_picc(4);

        // Detectar cambios en actuadores
        doorState = digitalRead(doorSwitch);
        
    } while (doorState == 1);
}

//-----< De Extraer a Inactivo >-----
bool transitionExtractIdle(){
    if (!isDoorOpen()) {
        // Sensor magnético cerrado
        return true;
    }
    return false;
}
