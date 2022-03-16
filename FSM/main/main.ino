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

  //Edo. inicial           Condición booleana       Edo. futuro
    S0->      addTransition(&transitionS0Idle,        Idle);        // Al encender

    Idle->    addTransition(&transitionIdleFill,      Fill);        // Al abrir la puerta
    Idle->    addTransition(&transitionIdleReset,     Reset);       // Al apagar

    Fill->    addTransition(&transitionFillExtract,   Extract);     // >= 20 kg carton & al cerrar la puerta
    Fill->    addTransition(&transitionFillCompact,   Compact);     // < 20 kg cartón  & Pulsar botón compactar
    Fill->    addTransition(&transitionFillLift,      Lift);        // < 20 kg cartón  & Pulsar botón levantar

    Extract-> addTransition(&transitionExtractIdle,   Idle);        // Al cerrar la puerta

    Compact-> addTransition(&transitionCompactLift,   Lift);        // Pulsar botón levantar
    Compact-> addTransition(&transitionCompactHalt,   Halt);        // Soltar botón compactar

    Lift->    addTransition(&transitionLiftHalt,      Halt);        // carrera cilindro > 0 & soltar botón levantar
    Lift->    addTransition(&transitionLiftIdle,      Idle);        // carrera cilindro = 0

    Halt->    addTransition(&transitionHaltCompact,   Compact);     // Pulsar botón compactar
    Halt->    addTransition(&transitionHaltLift,      Lift);        // PUlsar botón levantar

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
    if (true) {
        // Interruptor de encendido
        return true;
    }
    return false;
}

//==================< Idle >=====================
void stateIdle(){
    Serial.println("Inactivo");
    // Actualizar peso
}

//-----< De Inactivo a Rellenar >-----
bool transitionIdleFill(){
    if (true) {
        // Sensor magnético abierto
        return true;
    }
    return false;
}

//-----< De Inactivo a Reiniciar >-----
bool transitionIdleReset(){
    if (true) {
        // Interruptor de apagado
        return true;
    }
    return false;
}

//==================< Fill >=====================
void stateFill(){
    Serial.println("Rellenar");
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (true && true) {
        // Peso >= 20 kg & sensor magnético cerrado
        return true;
    }
    return false;
}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    if (true && true) {
        // Peso < 20 kg & pulsar botón compactar
        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (true && true) {
        // Peso < 20 kg & pulsar botón levantar
        return true;
    }
    return false;
}

//==================< Extract >=====================
void stateExtract(){
    Serial.println("Extraer");
}

//-----< De Extraer a Inactivo >-----
bool transitionExtractIdle(){
    if (true) {
        // Sensor magnético cerrado
        return true;
    }
    return false;
}

//==================< Compact >=====================
void stateCompact(){
    Serial.println("Compactar");
}

//-----< De Compactar a Levantar >-----
bool transitionCompactLift(){
    if (true) {
        // Pulsar botón levantar
        return true;
    }
    return false;
}

//-----< De Compactar a Alto >-----
bool transitionCompactHalt(){
    if (true) {
        // Soltar botón compactar
        return true;
    }
    return false;
}

//==================< Lift >=====================
void stateLift(){
    Serial.println("Levantar");
}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (true && true) {
        // carrera cilindro > 0 & soltar botón levantar
        return true;
    }
    return false;
}

//-----< De Levantar a Inactivo >-----
bool transitionLiftIdle(){
    if (true) {
        // carrera cilindro = 0
        return true;
    }
    return false;
}

//==================< Halt >=====================
void stateHalt(){
    Serial.println("Alto");
}

//-----< De Alto a Compactar >-----
bool transitionHaltCompact(){
    if (true) {
        // Pulsar botón compactar
        return true;
    }
    return false;
}

//-----< De Alto a Levantar >-----
bool transitionHaltLift(){
    if (true) {
        // Pulsar botón levantar
        return true;
    }
    return false;
}

//==================< Reset >=====================
void stateReset(){
    Serial.println("Reiniciar");
}

//-----< De Reiniciar a S0 >-----
bool transitionResetS0(){
    // Reiniciar carrera, luces y alarma
    return true;
}

//==================< Stop >=====================
void stateStop(){
    Serial.println("Paro de emergencia");
}

//-----< De Paro a Inactivo >-----
bool transitionStopReset(){
    if (true) {
        // Pulsar botón de paro
        return true;
    }
    return false;
}
