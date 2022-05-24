void actualizarPantalla() {
      tState.setText(actualState);           // Actualizar texto
      actualizarReloj();                                // Actualizar tiempo operando
      actualizarPeso();                               // Actualizar peso de celda de carga
      jProgress.setValue(cylStroke);        // Actualizar carrear cilindro
      
      String strCycles = String(cycles);
      tCycles.setText(strCycles.c_str()); // Actualizar ciclos
      vaciarDiagramaEstados();
}

void actualizarPeso(){
  static boolean newDataReady = 0;
  const int serialPrintInterval = 1000; //increase value to slow down serial print activity

  // Revisar si nueva data/ iniciar nueva conversión
  if (LoadCell.update()) newDataReady = true;

  // Obtener valor de conjunto de datos
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      weight = LoadCell.getData();

      // Actualizar string de peso
      String strWeight = String(weight, 2);
      strWeight.concat(" ");
      strWeight.concat(weightMeasureUnit);
      tPeso.setText(strWeight.c_str());

      newDataReady = 0;
      t = millis();
    }
  }
}

void actualizarReloj(){
    String readableTime = "";
  
    unsigned long seconds;
    unsigned long minutes;
    unsigned long hours;

    // Calcular tiempo a partir de millis() (tiempo total del arduino encendido en ms)
    currentMillis = millis();
    seconds = currentMillis / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    currentMillis %= 1000;
    seconds %= 60;
    minutes %= 60;
    hours %= 24;

    readableTime += String(hours) + " hr ";

    if (minutes < 10) {
        readableTime += "0";
    }
    readableTime += String(minutes) + " min ";

    if (seconds < 10) {
        readableTime += "0";
    }
    readableTime += String(seconds) + " seg";

    // Actualizar string de tiempo operando
    tRuntime.setText(readableTime.c_str());
}

void vaciarDiagramaEstados(){
    // Reiniciar diagrama de estados
    sbCompact.Set_background_crop_picc(3);
    sbExtract.Set_background_crop_picc(3);
    sbFill.Set_background_crop_picc(3);
    sbHalt.Set_background_crop_picc(3);
    sbIdle.Set_background_crop_picc(3);
    sbS0.Set_background_crop_picc(3);
    sbLift.Set_background_crop_picc(3);
    sbReset.Set_background_crop_picc(3);
    sbStop.Set_background_crop_picc(3);
}

void incrementarCarrera(){    // Unicamente en la interfaz
    if (cylStroke < 100) {
        cylStroke = cylStroke + CYL_STEP;
        jProgress.setValue(cylStroke);
    }
    else {
        cylStroke = 100;
        cylReachedLim = true;
    }
}

void disminuirCarrera(){    // Unicamente en la interfaz
    if (cylStroke > 0) {
        cylStroke = cylStroke - CYL_STEP;
        jProgress.setValue(cylStroke);
    }
    else {
        if (cylReachedLim) {
            // Si el cilindro llegó al limite y vuelve a casa agregar un ciclo de trabajo
            cylStroke = 0;
            cylReachedLim = false;
            cycles ++;
        }
    }
}
