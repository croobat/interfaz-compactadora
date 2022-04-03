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
#include <StateMachine.h>

// Delay en loop
const int STATE_DELAY = 1000;
//int randomState = 0; // test
//const int TEST_LED = 13;

// Maquina de estados principal
StateMachine machine = StateMachine();

// Maquina de estados secundaria (operando/no operando)
/* StateMachine opMachine = StateMachine(); */

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
const char* onswitch = "switch encendido";
const char* offswitch = "switch apagado";
const char* opendoor = "abrir puerta";
const char* closedoor = "cerrar puerta";
const char* cylbottom = "cilindro en inicio";
const char* cylmid = "cilindro en camino";
const char* cyltop = "cilindro en limite";
const char* kg20carton = "20 kg carton";
const char* lesskg20carton = "menos 20 kg carton";
const char* pushcompactbutton = "pulsar compactar";
const char* releasecompactbutton = "soltar compactar";
const char* pushliftbutton = "pulsar levantar";
const char* releaseliftbutton = "soltar levantar";
const char* emergencystop = "paro de emergencia";



/* ---------------------- */
/* -  Setup inicial  - */
/* ---------------------- */
void setup()
{
    Serial.begin(115200);
    //pinMode(TEST_LED, OUTPUT); // test
    //randomSeed(A0); // test

    /* ---------------------- */
    /* -  Transiciones  - */
    /* ---------------------- */

  //Edo. inicial           Condición booleana       Edo. futuro
    S0->      addTransition(&transitionS0Idle,        Idle);        // Al encender

    Idle->    addTransition(&transitionIdleFill,      Fill);        // Al abrir la puerta
    Idle->    addTransition(&transitionIdleReset,     Reset);       // Al apagar

    Fill->    addTransition(&transitionFillExtract,   Extract);     // >= 20 kg carton & abrir puerta
    Fill->    addTransition(&transitionFillCompact,   Compact);     // < 20 kg cartón & cerrar puerta & Pulsar botón compactar
    Fill->    addTransition(&transitionFillLift,      Lift);        // < 20 kg cartón & cerrar puerta & Pulsar botón levantar

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
    machine.run();
    delay(STATE_DELAY);
}

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
