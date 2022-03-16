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

// Maquina de estados general
YA_FSM mainStateMachine;
// Maquina de estados para operando o noop (necesaria para los led y alarma)
YA_FSM opStateMachine;

// State Alias
enum State {INACTIVO, RELLENAR, COMPACTAR, LEVANTAR, DETENER, REINICIO, PARO};
// Helper para imprimir labels en cambios de estado
const char * const stateName[] PROGMEM = {"INACTIVO", "RELLENAR", "COMPACTAR", "LEVANTAR", "DETENER", "REINICIO", "PARO", "CALL"};

// Constantes de prueba (timepo de extraccion y tiempo de carrera del cilindro)
#define CYL_CARRERA 5000
#define CARTON_EXTRACCION 2000
