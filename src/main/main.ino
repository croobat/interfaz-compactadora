/******************************************************************************
* File:             main.ino
*
* Author:           Luis Antonio Ramírez García, Anel Madai Perales Avila
* Created:          02/16/22
* Description:      Código principal de la máquina de estados para la
*                   compactadora de cartón
*****************************************************************************/

/* ---------------------- */
/* -  Librerias  - */
/* ---------------------- */
#include <math.h>
//State Machine library
#include <StateMachine.h>
// Multibutton helper library
#include <ezButton.h>
// HX711 load cell amplifier library
#include <HX711_ADC.h>
// EEPROM
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
// Nextion Libraries
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

/* --------------- */
/* -  Hardware objects  - */
/* --------------- */
ezButton onSwitch(3);
const int doorSwitch = 23;
const int speaker = 9;
const int relay_RedLED = 46;
const int relay_GreenLED = 42;
const int relay_L = 28;
const int relay_R = 29;
ezButton compactButton(37);
ezButton liftButton(33);
ezButton emergencyButton(35);
const int HX711_dout = 4;
const int HX711_sck = 5;

/* --------------- */
/* -  Software objects  - */
/* --------------- */
// Main page
NexButton bOff = NexButton(0, 8, "bApagar");
NexButton bReset = NexButton(0, 9, "bReiniciar");
NexText tPeso = NexText (0, 11, "tPeso");
NexText tEstado = NexText (0, 12, "tEstado");
NexText tRuntime = NexText (0, 13, "tRuntime");
NexText tCycles = NexText(0, 14, "tCiclos");
NexProgressBar jProgress = NexProgressBar(0, 15, "jProgress");
NexButton sbRedLed = NexButton(0, 16, "redLed");
NexButton sbGreenLed = NexButton(0, 17, "greenLed");
NexButton sbSoundLed = NexButton(0, 18, "soundLed");

// State machine page
NexButton sbS0 = NexButton(1, 3, "S0");
NexButton sbIdle = NexButton(1, 4, "Idle");
NexButton sbFill = NexButton(1, 5, "Fill");
NexButton sbExtract = NexButton(1, 6, "Extract");
NexButton sbCompact = NexButton(1, 7, "Compact");
NexButton sbLift = NexButton(1, 8, "LIft");
NexButton sbHalt = NexButton(1, 9, "Halt");
NexButton sbStop = NexButton(1, 10, "Stop");
NexButton sbReset = NexButton(1, 11, "Reset");

/* --------------- */
/* -  Variables  - */
/* --------------- */
int onSwitchState;
int doorState;
int compactButtonState;
int liftButtonState;
int emergencyButtonState;
int speakerFreq = 600;
bool isSpeakerON = false;
bool beepFlag = true;
int cylStroke = 0;
int cylStep = 20;
bool cylReachedLim = false;
int cycles = 0;
unsigned long currentMillis;
const char* actualState = "";
/* bool OPState = false; */
float weight = 0;

// Delay en loop
const int STATE_DELAY = 50;
float TARGET_WEIGHT = 20000;
//int randomState = 0; // test
//const int TEST_LED = 13;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

// Maquina de estados principal
StateMachine machine = StateMachine();

// Definición de estados de la maquina, funciones definidas abajo
State* S0       = machine.addState(&state0);
State* Idle     = machine.addState(&stateIdle);
State* Fill     = machine.addState(&stateFill);
State* Extract  = machine.addState(&stateExtract);
State* Compact  = machine.addState(&stateCompact);
State* Lift     = machine.addState(&stateLift);
State* Halt     = machine.addState(&stateHalt);
State* Reset    = machine.addState(&stateReset);
State* Stop     = machine.addState(&stateStop);

// Debug
//String accion = "";
//String accion2 = "";
//String accion3 = "";
/* const char* onswitch = "switch encendido"; */
/* const char* offswitch = "switch apagado"; */
/* const char* opendoor = "abrir puerta"; */
/* const char* closedoor = "cerrar puerta"; */
//const char* cylbottom = "lim";
//const char* cylmid = "mid";
/* const char* cyltop = "cilindro en limite"; */
//const char* kg20carton = "mas";
//const char* lesskg20carton = "menos";
/* const char* pushcompactbutton = "pulsar compactar"; */
/* const char* releasecompactbutton = "soltar compactar"; */
/* const char* pushliftbutton = "pulsar levantar"; */
/* const char* releaseliftbutton = "soltar levantar"; */
/* const char* emergencystop = "paro de emergencia"; */



/* ---------------------- */
/* -  Setup inicial  - */
/* ---------------------- */
void setup()
{
    Serial.begin(9600);

    // Pinmodes
    pinMode(doorSwitch, INPUT_PULLUP); // Pin de puerta en modo input pullup
    pinMode(speaker, OUTPUT); // Pin de bocina en modo salida
    pinMode(relay_L, OUTPUT);
    pinMode(relay_R, OUTPUT);  
    pinMode(relay_RedLED, OUTPUT);
    pinMode(relay_GreenLED, OUTPUT);

    // Asignando antirrebotes de los botones y switches (count falling)
    onSwitch.setDebounceTime(5);
    compactButton.setDebounceTime(5);
    liftButton.setDebounceTime(5);
    emergencyButton.setDebounceTime(5);
    compactButton.setCountMode(COUNT_FALLING);
    liftButton.setCountMode(COUNT_FALLING);
    emergencyButton.setCountMode(COUNT_FALLING);

   // Configuración celda de carga

//    #if defined(ESP8266) || defined(ESP32)
//        //EEPROM.begin(512); // uncomment this if you use ESP8266 and want to fetch this value from eeprom
//    #endif
//        //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch this value from eeprom

    LoadCell.begin();
    unsigned long stabilizingtime = 2000; // precision right after power-up can be improved by adding a few seconds of stabilizing time
    boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
    LoadCell.start(stabilizingtime, _tare);
   // while (!LoadCell.update());
        //calibrarCelda(); //start calibration procedure

    /* ---------------------- */
    /*     -  test  - */
    /* ---------------------- */
    //pinMode(TEST_LED, OUTPUT); // test
    //randomSeed(A0); // test
    /* delay(0); */
    /* Serial.println("Introducir la accion como aparece en main - debug (switch encendido, soltar levantar...)"); */
    /* Serial.println("Si se necesita más de una acción dar prioridad según aparezca (esto mientras testeamos)"); */
    /* Serial.println("Más importante > Medio importante > Menos importante"); */
//    Serial.println("Iniciando maquina");

    reiniciar();

    /* ---------------------- */
    /* -  Transiciones  - */
    /* ---------------------- */

  //Edo. inicial           Condición booleana       Edo. futuro
    S0->      addTransition(&transitionS0Idle,        Idle);        // Al encender

    Idle->    addTransition(&transitionIdleFill,      Fill);        // Al abrir la puerta
    Idle->    addTransition(&transitionIdleReset,     Reset);       // Al apagar

    Fill->    addTransition(&transitionFillCompact,   Compact);     // < 20 kg cartón & cerrar puerta & Pulsar botón compactar
    Fill->    addTransition(&transitionFillLift,      Lift);        // < 20 kg cartón & cerrar puerta & Pulsar botón levantar
    Fill->    addTransition(&transitionFillExtract,   Extract);     // >= 20 kg carton & abrir puerta

    Extract-> addTransition(&transitionExtractIdle,   Idle);        // Al cerrar la puerta

    Compact-> addTransition(&transitionCompactLift,   Lift);        // Pulsar botón levantar
    Compact-> addTransition(&transitionCompactHalt,   Halt);        // Soltar botón compactar
    Compact-> addTransition(&transitionCompactStop,   Stop);        // Pulsar paro de emergencia

    Lift->    addTransition(&transitionLiftHalt,      Halt);        // carrera cilindro > 0 & soltar botón levantar
    Lift->    addTransition(&transitionLiftIdle,      Idle);        // carrera cilindro = 0
    Lift->    addTransition(&transitionLiftStop,      Stop);        // Pulsar paro de emergencia

    Halt->    addTransition(&transitionHaltCompact,   Compact);     // Pulsar botón compactar
    Halt->    addTransition(&transitionHaltLift,      Lift);        // Pulsar botón levantar
    Halt->    addTransition(&transitionHaltStop,      Stop);        // Pulsar paro de emergencia

    Reset->   addTransition(&transitionResetS0,       S0);          // Tras reiniciar carrera, luces y alarma

    Stop->    addTransition(&transitionStopReset,     Reset);       // Pulsar botón de paro

}


/* ---------------------- */
/* -  Loop infinito  - */
/* ---------------------- */
void loop() {
    // Llamando loops de botones y switches
    onSwitch.loop();
    compactButton.loop();
    liftButton.loop();
    emergencyButton.loop();
    
    // Iniciando maquina de estados
    machine.run();

    // Retraso del sistema
    delay(STATE_DELAY);
}
