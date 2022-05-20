//==================< Stop >=====================
void stateStop(){
    vaciarDiagramaEstados();
    sbStop.Set_background_crop_picc(4);    
    Serial.println("Paro de emergencia");
    tEstado.setText("¡Paro de emergencia!");
    actualizarReloj();

}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
    Serial.println("Emergencia: Reiniciando sistema");
    return true;
}
