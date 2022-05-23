//==================< Stop >=====================
void stateStop(){
  
    playBeep();
    actualState = "Paro de emergencia";

    do {
        actualizarPantalla();
        sbStop.Set_background_crop_picc(4);
        tEstado.Set_background_crop_picc(5);  

        emergencyButton.loop();
        emergencyButtonState = emergencyButton.getState(); // Actualizar estado boton compactar
        
    } while (isEmergencyPressed());
//    Serial.println("Paro de emergencia");

}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
//    if (!isEmergencyPressed()) {
    if (!isEmergencyPressed()) {
        tEstado.Set_background_crop_picc(1);
        return true;
    }
//    Serial.println("Emergencia: Reiniciando sistema");
      return false;
}
