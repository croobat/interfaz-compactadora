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
//State Machine library
#include <StateMachine.h>
// Multibutton helper library
#include <ezButton.h>
//// Nextion Libraries
//#include <NexNumber.h>
//#include <doxygen.h>
//#include <NexButton.h>
//#include <NexCheckbox.h>
//#include <NexConfig.h>
//#include <NexCrop.h>
//#include <NexDualStateButton.h>
//#include <NexGauge.h>
//#include <NexGpio.h>
//#include <NexHardware.h>
//#include <NexHotspot.h>
//#include <NexObject.h>
//#include <NexPage.h>
//#include <NexPicture.h>
//#include <NexProgressBar.h>
//#include <NexRadio.h>
//#include <NexRtc.h>
//#include <NexScrolltext.h>
//#include <NexSlider.h>
//#include <NexText.h>
//#include <NexTimer.h>
//#include <Nextion.h>
//#include <NexTouch.h>
//#include <NexUpload.h>
//#include <NexVariable.h>
//#include <NexWaveform.h>


// Conexiones
ezButton onSwitch(2);
const int doorSwitch = 23;
const int speaker = 9;
const int redLED = 42;
const int greenLED = 46;
ezButton compactButton(37);
ezButton liftButton(35);
ezButton emergencyButton(33);

/* --------------- */
/* -  Variables  - */
/* --------------- */
int doorState;
int compactButtonState;
int liftButtonState;
int emergencyButtonState;
int speakerFreq;
/* bool OPState = false; */

// Delay en loop
const int STATE_DELAY = 500;
//int randomState = 0; // test
//const int TEST_LED = 13;

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
String accion = "";
String accion2 = "";
String accion3 = "";
/* const char* onswitch = "switch encendido"; */
/* const char* offswitch = "switch apagado"; */
/* const char* opendoor = "abrir puerta"; */
/* const char* closedoor = "cerrar puerta"; */
const char* cylbottom = "lim";
const char* cylmid = "mid";
/* const char* cyltop = "cilindro en limite"; */
const char* kg20carton = "mas";
const char* lesskg20carton = "menos";
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
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    // Asignando antirrebotes de los botones y switches (count falling)
    onSwitch.setDebounceTime(50);
    compactButton.setDebounceTime(50);
    liftButton.setDebounceTime(50);
    emergencyButton.setDebounceTime(50);
    compactButton.setCountMode(COUNT_FALLING);
    liftButton.setCountMode(COUNT_FALLING);
    emergencyButton.setCountMode(COUNT_FALLING);

    /* ---------------------- */
    /*     -  test  - */
    /* ---------------------- */
    //pinMode(TEST_LED, OUTPUT); // test
    //randomSeed(A0); // test
    /* delay(0); */
    /* Serial.println("Introducir la accion como aparece en main - debug (switch encendido, soltar levantar...)"); */
    /* Serial.println("Si se necesita más de una acción dar prioridad según aparezca (esto mientras testeamos)"); */
    /* Serial.println("Más importante > Medio importante > Menos importante"); */
    Serial.println("Iniciando maquina");

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

/* ---------- */
/* -  test  - */
/* ---------- */

bool compareString(String comp) {
  if (Serial.available()) {
    String accion = Serial.readStringUntil('\n');
    accion.trim();
    if (accion == comp) {
      return true;
    } else {
      return false;
    }
  }
}
