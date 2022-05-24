//==================< Reset >=====================
void stateReset(){
    // Definición de estado actual
    actualState = "Reiniciando...";
    playBeep();

    do {
        // Actualizar interfaz
        actualizarPantalla();
        sbLift.Set_background_crop_picc(4);

        // Reiniciar máquina
        reiniciar();
        
    } while (cylStroke > 0);
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
    if (cylStroke <= 0) {
      // Cilindro en posición inicial
      return true;
    }
    return false;
}
