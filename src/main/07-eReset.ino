//==================< Reset >=====================
void stateReset(){

    playBeep();
    actualState = "Reiniciando...";

    do {
        actualizarPantalla();
        sbLift.Set_background_crop_picc(4);
        reiniciar();
    } while (cylStroke > 0);
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
//    Serial.println("Reiniciando cilindro...");
//    Serial.println("Reiniciando luces...");
    /* Serial.println("Silenciando alarma..."); */
    // Reiniciar carrera, luces y alarma
    if (cylStroke <= 0) {
      return true;
    }
    return false;
}
