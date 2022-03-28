#include <Arduino.h>
#line 1 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
/******************************************************************************
* File:             main.ino
*
* Author:           Luis Antonio Ramírez García, Anel Madai Perales Avila
* Created:          02/16/22
* Description:      Código principal de la máquina de estados
*****************************************************************************/
#include <StateMachine.h>
/* #include <YA_FSM.h> */

/* ---------------------- */
/* -  Ignorar  - */
/* ---------------------- */

/* // Pines de entradas */
/* const byte ON_SWITCH = 2; */
/* const byte DOOR_SENSOR = 3; */
/* const byte WEIGHT_CBOARD = 4; */
/* const byte LIFT_BUTTON = 5; */
/* const byte COMPACT_BUTTON = 6; */
/* const byte EMERGENCY_BUTTON = 7; */
/* const byte CARR_CYL = 12; */


/* // Pines de salidas */
/* const byte GREEN_LED = 8; */
/* const byte RED_LED = 9; */
/* const byte SOUND_ALARM = 10; */
/* const byte UPDATE_PRESSURE = 11; */
/* const byte COMPACTING_CYL = 12; */
/* const byte HALT_CYL = 13; */



/* // Maquina de estados general */
/* YA_FSM mainStateMachine; */
/* // Maquina de estados para operando o noop (necesaria para los led y alarma) */
/* YA_FSM opStateMachine; */

/* // State Alias */
/* enum State {INACTIVO, RELLENAR, COMPACTAR, LEVANTAR, DETENER, REINICIO, PARO}; */
/* // Helper para imprimir labels en cambios de estado */
/* const char * const stateName[] PROGMEM = {"INACTIVO", "RELLENAR", "COMPACTAR", "LEVANTAR", "DETENER", "REINICIO", "PARO", "CALL"}; */

/* // Constantes de prueba (timepo de extraccion y tiempo de carrera del cilindro) */
/* #define CYL_CARRERA 5000 */
/* #define CARTON_EXTRACCION 2000 */

// Delay en loop
const int STATE_DELAY = 1000;
int randomState = 0; // test
const int TEST_LED = 13;

// Maquina de estados principal
StateMachine machine = StateMachine();

// Maquina de estados secundaria (operando/no operando)
/* StateMachine opMachine = StateMachine(); */

// Definición de estados de la maquina, funciones definidas abajo
#line 74 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void setup();
#line 99 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void loop();
#line 110 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void state0();
#line 116 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionS0Idle();
#line 121 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateIdle();
#line 126 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionIdleFill();
#line 131 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateFill();
#line 136 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionFillExtract();
#line 141 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateExtract();
#line 146 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionExtractCompact();
#line 151 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateCompact();
#line 156 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionCompactLift();
#line 161 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateLift();
#line 166 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionLiftHalt();
#line 171 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateHalt();
#line 176 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionHaltReset();
#line 181 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateReset();
#line 186 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionResetStop();
#line 191 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
void stateStop();
#line 196 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
bool transitionStopIdle();
#line 61 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/main/main.ino"
State* S0       = machine.addState(&state0);
State* Idle     = machine.addState(&stateIdle);
State* Fill     = machine.addState(&stateFill);
State* Extract  = machine.addState(&stateExtract);
State* Compact  = machine.addState(&stateCompact);
State* Lift     = machine.addState(&stateLift);
State* Halt     = machine.addState(&stateHalt);
State* Reset    = machine.addState(&stateReset);
State* Stop     = machine.addState(&stateStop);

/* ---------------------- */
/* -  Setup inicial  - */
/* ---------------------- */
void setup()
{
    Serial.begin(115200);
    pinMode(TEST_LED, OUTPUT); // test
    randomSeed(A0); // test

    /* ---------------------- */
    /* -  Transiciones  - */
    /* ---------------------- */

    S0->      addTransition(&transitionS0Idle,        Idle);
    Idle->    addTransition(&transitionIdleFill,      Fill);
    Fill->    addTransition(&transitionFillExtract,   Extract);
    Extract-> addTransition(&transitionExtractCompact,Compact);
    Compact-> addTransition(&transitionCompactLift,   Lift);
    Lift->    addTransition(&transitionLiftHalt,      Halt);
    Halt->    addTransition(&transitionHaltReset,     Reset);
    Reset->   addTransition(&transitionResetStop,     Stop);
    Stop->    addTransition(&transitionStopIdle,      S0);
}


/* ---------------------- */
/* -  Loop infinito  - */
/* ---------------------- */
void loop() {
    machine.run();
    delay(STATE_DELAY);
}


/* ---------------------- */
/* -  Estados  - */
/* ---------------------- */

//==================< S0 >=====================
void state0(){
    Serial.println("State 0");
    digitalWrite(TEST_LED, !digitalRead(TEST_LED));
}

//-----< De S0 a Inactivo >-----
bool transitionS0Idle(){
    return true;
}

//==================< Idle >=====================
void stateIdle(){
    Serial.println("Inactivo");
}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    return true;
}

//==================< Fill >=====================
void stateFill(){
    Serial.println("Rellenar");
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    return true;
}

//==================< Extract >=====================
void stateExtract(){
    Serial.println("Extraer");
}

//-----< De Extraer a Compactar >-----
bool transitionExtractCompact(){
    return true;
}

//==================< Compact >=====================
void stateCompact(){
    Serial.println("Compactar");
}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    return true;
}

//==================< Lift >=====================
void stateLift(){
    Serial.println("Levantar");
}

//-----< De Levantar a Detener >-----
bool transitionLiftHalt(){
    return true;
}

//==================< Halt >=====================
void stateHalt(){
    Serial.println("Alto");
}

//-----< De Detener a Reiniciar >-----
bool transitionHaltReset(){
    return true;
}

//==================< Reset >=====================
void stateReset(){
    Serial.println("Reiniciar");
}

//-----< De Reiniciar a Paro >-----
bool transitionResetStop(){
    return true;
}

//==================< Stop >=====================
void stateStop(){
    Serial.println("Paro de emergencia");
}

//-----< De Paro a Inactivo >-----
bool transitionStopIdle(){
    return true;
}

