// Revisar estado del Switch de encendido
bool isSwitchOn(){
    int state = onSwitch.getState();
    if (state == HIGH) {
        return false;
    }
    else {
        return true;
    }
}

// Revisar estado de la puerta
bool isDoorOpen(){
  if (doorState == 1) {
    return true;
  } else {
    return false;
  }
}

// Revisar estado botón compactar
bool isCompactPressed(){
  if (compactButtonState == 0) {
    return true;
  } else {
    return false;
  }
}

// Revisar estado botón levantar
bool isLiftPressed(){
  if (liftButtonState == 0) {
    return true;
  } else {
    return false;
  }
}

// Revisar estado botón emergencia
bool isEmergencyPressed(){
  if (emergencyButtonState == 0) {
    return true;
  } else {
    return false;
  }
}

// Encender bocina
void speakerON(){
        for(speakerFreq=400; speakerFreq<500; speakerFreq++){
            tone(speaker,speakerFreq);
            delay(5);
        }
        for(speakerFreq=500; speakerFreq>400; speakerFreq--){
            tone(speaker,speakerFreq);
            delay(5);
    }
}

// Apagar bocina
void speakerOFF(){
    noTone(speaker);
}

void operando(){
//    digitalWrite(redLED, HIGH);
//    digitalWrite(greenLED, LOW);
    digitalWrite(relay_RedLED, HIGH);
    digitalWrite(relay_GreenLED, LOW);
    speakerON();
}

void noOperando(){
//    digitalWrite(redLED, LOW);
//    digitalWrite(greenLED, HIGH);
    digitalWrite(relay_RedLED, LOW);
    digitalWrite(relay_GreenLED, HIGH);
    speakerOFF();
}

void reiniciar(){
//    digitalWrite(redLED, LOW);
//    digitalWrite(greenLED, LOW);
    digitalWrite(relay_RedLED, LOW);
    digitalWrite(relay_GreenLED, LOW);
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

void actualizarPeso(){
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float weight = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(weight);
      String strWeight = String(weight, 2);
      strWeight.concat(" kg");
     tWeight.setText(strWeight.c_str());
      newDataReady = 0;
      t = millis();
    }
  }
}

void actualizarReloj(){
  String readableTime = "";
  
  unsigned long currentMillis;
  unsigned long seconds;
  unsigned long minutes;
  unsigned long hours;

  currentMillis = millis();
  seconds = currentMillis / 1000;
  minutes = seconds / 60;
  hours = minutes / 60;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  if (hours > 0) {
    readableTime += String(hours) + "hr";
  }

  if (minutes < 10) {
    readableTime += "0";
  }
  readableTime += String(minutes) + "min";

  if (seconds < 10) {
    readableTime += "0";
  }
  readableTime += String(seconds) + " seg";

  tRuntime.setText(readableTime.c_str());
}

void vaciarDiagramaEstados(){
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
