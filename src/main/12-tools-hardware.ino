void reiniciar(){
    // Desactivar relevadores de potencia
    digitalWrite(relay_L, HIGH);
    digitalWrite(relay_RedLED, HIGH);
    digitalWrite(relay_GreenLED, HIGH);
    // Apagar bocina
    speakerOFF();
    // Reiniciar indicadores HMI
    sbGreenLed.Set_background_crop_picc(1);
    sbRedLed.Set_background_crop_picc(1);
    // Reiniciar variables de control
    currentMillis = millis() - currentMillis;
    weight = 0;
    cycles = 0;

    // Reiniciar carrera del cilindro
    while (cylStroke > 0) {
        // Activar cilindro (levantar) hasta llegar a posición de casa
        digitalWrite(relay_R, LOW); 
        cylStroke = cylStroke - CYL_STEP;
        jProgress.setValue(cylStroke);
        delay(1000);
    } 

    digitalWrite(relay_R, HIGH);     // Desactivar cilindro

    tState.setText("Reinicio completado");
    delay(1000);
    startPage.show();
    
    playBeep();
    delay(300);
    playBeep();
    delay(300);
    playBeep();

}

void operando(){
    // Activar/desactivar actuadores
    digitalWrite(relay_RedLED, LOW);
    digitalWrite(relay_GreenLED, HIGH);
    
    // Activar desactivar indicadores HMI
    sbRedLed.Set_background_crop_picc(2);
    sbGreenLed.Set_background_crop_picc(1);

    // Encender bocina
    speakerON();
}

void noOperando(){
    // Activar/desactivar actuadores
    digitalWrite(relay_RedLED, HIGH);
    digitalWrite(relay_GreenLED, LOW);
    
    // Activar desactivar indicadores HMI
    sbGreenLed.Set_background_crop_picc(2);
    sbRedLed.Set_background_crop_picc(1);

    // Apagar bocina
    speakerOFF();
}

void calibrarCelda(){
Serial.println("***");
  Serial.println("Start calibration:");
  Serial.println("Place the load cell an a level stable surface.");
  Serial.println("Remove any load applied to the load cell.");
  Serial.println("Send 't' from serial monitor to set the tare offset.");

  boolean _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') LoadCell.tareNoDelay();
      }
    }
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tare complete");
      _resume = true;
    }
  }

  Serial.println("Now, place your known mass on the loadcell.");
  Serial.println("Then send the weight of this mass (i.e. 100.0) from serial monitor.");

  float known_mass = 0;
  _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      known_mass = Serial.parseFloat();
      if (known_mass != 0) {
        Serial.print("Known mass is: ");
        Serial.println(known_mass);
        _resume = true;
      }
    }
  }

  LoadCell.refreshDataSet(); //refresh the dataset to be sure that the known mass is measured correct
  float newCalibrationValue = LoadCell.getNewCalibration(known_mass); //get the new calibration value

  Serial.print("New calibration value has been set to: ");
  Serial.print(newCalibrationValue);
  Serial.println(", use this as calibration value (calFactor) in your project sketch.");
  Serial.print("Save this value to EEPROM adress ");
  Serial.print(calVal_eepromAdress);
  Serial.println("? y/n");

  _resume = false;
  while (_resume == false) {
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 'y') {
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.begin(512);
#endif
        EEPROM.put(calVal_eepromAdress, newCalibrationValue);
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.commit();
#endif
        EEPROM.get(calVal_eepromAdress, newCalibrationValue);
        Serial.print("Value ");
        Serial.print(newCalibrationValue);
        Serial.print(" saved to EEPROM address: ");
        Serial.println(calVal_eepromAdress);
        _resume = true;

      }
      else if (inByte == 'n') {
        Serial.println("Value not saved to EEPROM");
        _resume = true;
      }
    }
  }

  Serial.println("End calibration");
}
