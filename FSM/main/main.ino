#include <YA_FSM.h>

// Pines de entradas
const byte ON_SWITCH = 2;
const byte DOOR_SENSOR = 3;
const byte WEIGHT_CBOARD = 4;
const byte LIFT_BUTTON = 5;
const byte COMPACT_BUTTON = 6;
const byte EMERGENCY_BUTTON = 7;
const byte CARR_CYL = 12;


// Pines de salidas
const byte GREEN_LED = 8;
const byte RED_LED = 9;
const byte SOUND_ALARM = 10;
const byte UPDATE_PRESSURE = 11;
const byte COMPACTING_CYL = 12;
const byte HALT_CYL = 13;


/* ---------------------- */
/* -  Ignorar  - */
/* ---------------------- */

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

// Librería para maquinas de estado
#include <StateMachine.h>

// Delay en loop
const int STATE_DELAY = 1000;
const int TEST_LED = 13;

// Maquina de estados principal
StateMachine machine = StateMachine();

// Maquina de estados secundaria (operando/no operando)
StateMachine opMachine = StateMachine();

// Estados de la maquina, funciones definidas abajo
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
/* -  Loop infinito  - */
/* ---------------------- */
void loop() {
    machine.run();
    delay(STATE_DELAY);
}
