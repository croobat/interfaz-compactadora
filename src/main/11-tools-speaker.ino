// Reproducir beep
void playBeep(){
    tone(speaker, SPEAKER_FREQ + 100);
    delay(10);
    noTone(speaker);
}

// Encender bocina
void speakerON(){
    // Determinar alarma
    if (actualState == "Compactando") {
        tone(speaker,SPEAKER_FREQ);
    } else if (actualState == "Levantando") {
        tone(speaker,SPEAKER_FREQ-200);
    }
    else if (actualState == "Paro de emergencia") {
        playAlarm();
    }
    // Encender indicador HMI
    sbSoundLed.Set_background_crop_picc(2);
}

// Reproducir alarma de emergencia
void playAlarm(){
    for(int speakerFreqTemp=SPEAKER_FREQ-50; speakerFreqTemp<SPEAKER_FREQ; speakerFreqTemp++){
            tone(speaker,speakerFreqTemp);
            delay(5);
        }
        for(int speakerFreqTemp=SPEAKER_FREQ; speakerFreqTemp>SPEAKER_FREQ - 50; speakerFreqTemp--){
            tone(speaker,speakerFreqTemp);
            delay(5);
        }
}

// Apagar bocina
void speakerOFF(){
     noTone(speaker);    
    sbSoundLed.Set_background_crop_picc(1);
}
