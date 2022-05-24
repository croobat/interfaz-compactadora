//==================< S0 >=====================
void state0(){
    // Definición de estado actual
    actualState = "Inicial";

    do {
        // Actualizar interfaz
        actualizarPantalla();
        sbS0.Set_background_crop_picc(4);

        // Detectar cambios en actuadores
        onSwitch.loop();
        
    } while (!onSwitch.isPressed());
}

//-----< De S0 a Inactivo >-----
bool transitionS0Idle(){
    if (isSwitchOn()) {
        // Interruptor de encendido
        mainPage.show();
        return true;
    }
    return false;
}
