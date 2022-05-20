//==================< Reset >=====================
void stateReset(){
    vaciarDiagramaEstados();
    sbReset.Set_background_crop_picc(4);    
    Serial.println("Reiniciar");
    tEstado.setText("Reiniciando...");
    actualizarReloj();
    reiniciar();
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
    Serial.println("Reiniciando cilindro...");
    Serial.println("Reiniciando luces...");
    /* Serial.println("Silenciando alarma..."); */
    // Reiniciar carrera, luces y alarma
    return true;
}
