// Nextion libraries
#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>

// Definiendo hardware objects
const int led1 = 48;
const int led2 = 50;

// Definiendo software objects
NexButton bOn = NexButton(0, 2, "bOn");
NexButton bOff = NexButton(0, 3, "bOff");
NexSlider h0 = NexSlider(0, 4, "h0");
NexText tState = NexText(0, 5, "tState"); 
NexText tSlider = NexText(0, 6, "tSlider");

// Componentes táctiles
NexTouch *nex_listen_list[] = {
    &bOn,
    &bOff,
    &h0,
    NULL
};

// Funcion al soltar bOn
void bOnPopCallback(void *ptr) {
    tState.setText("State: on");
    digitalWrite(led1, HIGH);
}

// Funcion al soltar bOff
void bOffPopCallback(void *ptr) {
    tState.setText("State: off");
    digitalWrite(led1, LOW);
}

// Cambiar brillo del led al mover el slider
void h0PopCallback(void *ptr) {
    uint32_t number = 0;
    char temp[10] = {0};
    h0.getValue(&number);
    utoa(number, temp, 10);
    tSlider.setText(temp);
    analogWrite(led2, number); 
}

////// SETUP //////
void setup() {
    Serial.begin(9600);
    //Set baudrate for debugging Nextion screen
    nexInit();

    //Registrar eventos de botón y slider
    bOn.attachPop(bOnPopCallback, &bOn);
    bOff.attachPop(bOffPopCallback, &bOff);
    h0.attachPop(h0PopCallback, &h0);

    //Leds como salidas
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

////// LOOP //////
void loop() {
    nexLoop(nex_listen_list);
}
