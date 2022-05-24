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
//Math library
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
/* -  Hardware definitions  - */
/* --------------- */
ezButton onSwitch(3);
ezButton compactButton(37);
ezButton liftButton(33);
ezButton emergencyButton(35);

const int relay_RedLED = 46;
const int relay_GreenLED = 42;
const int relay_L = 28;
const int relay_R = 29;

const int doorSwitch = 23;
const int speaker = 9;

const int HX711_dout = 4;
const int HX711_sck = 5;

/* --------------- */
/* -  Software definitions  - */
/* --------------- */
// Start page
NexPage startPage = NexPage(2, 0, "startPage");


// Main page
NexPage mainPage = NexPage(0, 0, "mainPage");

NexButton bReset = NexButton(0, 9, "bReiniciar");

NexButton sbRedLed = NexButton(0, 16, "redLed");
NexButton sbGreenLed = NexButton(0, 17, "greenLed");
NexButton sbSoundLed = NexButton(0, 18, "soundLed");

NexText tPeso = NexText (0, 11, "tPeso");
NexText tState = NexText (0, 12, "tEstado");
NexText tRuntime = NexText (0, 13, "tRuntime");
NexText tCycles = NexText(0, 14, "tCiclos");

NexProgressBar jProgress = NexProgressBar(0, 15, "jProgress");


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


// Config page
NexButton bApply = NexButton(3, 4, "bAplicar");
NexButton bCalcZero = NexButton(3, 15, "bCalcZero");
NexButton bKg = NexButton(3, 16, "bKg");
NexButton bLb = NexButton(3, 17, "bLb");
NexButton bYesEEPROM = NexButton(3, 21, "bYesEEPROM");
NexButton bNoEEPROM = NexButton(3, 22, "bNoEEPROM");

NexNumber tConfWCal = NexNumber(3, 30, "tConfWCal");
NexNumber tConfFreq = NexNumber(3, 31, "tConfFreq");
NexNumber tConfDelay = NexNumber(3, 32, "tConfDelay");
NexNumber tConfStep = NexNumber(3, 33, "tConfStep");
NexNumber tConfWObj = NexNumber(3, 34, "tConfWObj");
NexNumber tConfCalV = NexNumber(3, 35, "tConfCalV");

/* --------------- */
/* -  Parametros  - */
/* --------------- */
int SPEAKER_FREQ = 600;
int CYL_STEP = 20;
const int STATE_DELAY = 50;
float TARGET_WEIGHT = 20000;

/* --------------- */
/* -  Variables  - */
/* --------------- */
const char* actualState = "";

//Hardware State flags
int onSwitchState;
int doorState;
int compactButtonState;
int liftButtonState;
int emergencyButtonState;
bool isSpeakerON = false;
bool beepFlag = true;
bool cylReachedLim = false;

//Software State Flags
bool isNextionResetPressed = false;

//GUI Variables
//Cylinder
int cylStroke = 0;
int cycles = 0;
//Runtime
unsigned long currentMillis;
//Weight
const char* weightMeasureUnit = "kg";
float weight = 0;


/* --------------- */
/* -  Constructores  - */
/* --------------- */
//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

// Maquina de estados principal
StateMachine machine = StateMachine();


/* --------------- */
/* -  Máquina de estados  - */
/* --------------- */
// Definición de estados de la máquina, funciones definidas abajo
State* S0       = machine.addState(&state0);
State* Idle     = machine.addState(&stateIdle);
State* Fill     = machine.addState(&stateFill);
State* Extract  = machine.addState(&stateExtract);
State* Compact  = machine.addState(&stateCompact);
State* Lift     = machine.addState(&stateLift);
State* Halt     = machine.addState(&stateHalt);
State* Reset    = machine.addState(&stateReset);
State* Stop     = machine.addState(&stateStop);

/* --------------- */
/* -  Nextion lista de eventos  - */
/* --------------- */
NexTouch *nex_listen_list[] = {
      &bReset,
      &bApply,
      &bCalcZero,
      &bKg,
      &bLb,
      &bYesEEPROM,
      &bNoEEPROM,
      NULL
};

/* ---------------------- */
/* -  Setup inicial  - */
/* ---------------------- */
void setup()
{
    Serial.begin(9600);

    // Configuración de pines hardware
    pinMode(doorSwitch, INPUT_PULLUP); // Pin de puerta en modo input pullup
    pinMode(speaker, OUTPUT); // Pin de bocina en modo salida
    pinMode(relay_L, OUTPUT);
    pinMode(relay_R, OUTPUT);  
    pinMode(relay_RedLED, OUTPUT);
    pinMode(relay_GreenLED, OUTPUT);

    // Configuración de botónes (antirebotes y estilo de conteo
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
    unsigned long stabilizingtime = 2000; // Tiempo de estabilización tras encendido de máquina
    boolean _tare = true; // Cambiar a false para no calcular tara en el siguiente paso
    LoadCell.start(stabilizingtime, _tare);
   // while (!LoadCell.update());
        //calibrarCelda(); //start calibration procedure


    reiniciar();  // Reiniciar máquina tras encendido en caso de un apagado incorrecto

    /* ---------------------- */
    /* -  Configuración de transiciones de estados  - */
    /* ---------------------- */

  //Edo. inicial           Condición booleana       Edo. futuro
    S0->           addTransition(&transitionS0Idle,            Idle);           // Al encender

    Idle->         addTransition(&transitionIdleFill,             Fill);            // Al abrir la puerta
    Idle->         addTransition(&transitionIdleReset,        Reset);       // Al apagar

    Fill->           addTransition(&transitionFillCompact,    Compact);   // < 20 kg cartón & cerrar puerta & Pulsar botón compactar
    Fill->           addTransition(&transitionFillLift,             Lift);           // < 20 kg cartón & cerrar puerta & Pulsar botón levantar
    Fill->           addTransition(&transitionFillExtract,       Extract);     // >= 20 kg carton & abrir puerta

    Extract->    addTransition(&transitionExtractIdle,      Idle);          // Al cerrar la puerta

    Compact-> addTransition(&transitionCompactLift,    Lift);           // Pulsar botón levantar
    Compact-> addTransition(&transitionCompactHalt,   Halt);          // Soltar botón compactar
    Compact-> addTransition(&transitionCompactStop,  Stop);        // Pulsar paro de emergencia

    Lift->          addTransition(&transitionLiftHalt,           Halt);          // carrera cilindro > 0 & soltar botón levantar
    Lift->          addTransition(&transitionLiftIdle,            Idle);          // carrera cilindro = 0
    Lift->          addTransition(&transitionLiftStop,          Stop);         // Pulsar paro de emergencia

    Halt->         addTransition(&transitionHaltCompact,   Compact);  // Pulsar botón compactar
    Halt->         addTransition(&transitionHaltLift,            Lift);          // Pulsar botón levantar
    Halt->         addTransition(&transitionHaltStop,         Stop);        // Pulsar paro de emergencia

    Reset->      addTransition(&transitionResetS0,         S0);           // Tras reiniciar carrera, luces y alarma

    Stop->        addTransition(&transitionStopReset,      Reset);      // Pulsar botón de paro


    // Inicializando componentes nextion
    nexInit();
        // Asignando funciones a evento de soltar botón
        bReset.attachPop(bResetPopCallback, &bReset);

}


/* ---------------------- */
/* -  Loop infinito  - */
/* ---------------------- */
void loop() {
    // Iniciando maquina de estados
    machine.run();

    // Retraso del sistema
    delay(STATE_DELAY);
}
