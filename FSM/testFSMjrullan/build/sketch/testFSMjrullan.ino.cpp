#include <Arduino.h>
#line 1 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSMjrullan/testFSMjrullan.ino"
/*/*****************************************************************/
/* **/
/* *                STATE MACHINE EXAMPLE SKETCH*/
/* **/
/* **/
/* *  This sketch is an example to learn how to use the state*/
/* *  machine. In this example we define a state machine with*/
/* *  6 states (S0-S5).*/
/* **/
/* *  STATES*/
/* *  There are two ways of declaring a state logic:*/
/* *  1. Through a lambda function (an anonymous function) declared*/
/* *  in the addState() method.*/
/* *  2. Defining the function normally and passing the address*/
/* *  to the addState() method.*/
/* **/
/* *  States contain the machine logic of the program. The machine*/
/* *  only evaluates the current state until a transition occurs*/
/* *  that points to another state.*/
/* **/
/* *  To evaluate a piece of code only once while the machine*/
/* *  is in a particular state, you can use the machine.evaluateOnce*/
/* *  attribute. It is true each time the machine enters a new state*/
/* *  until the first transition is evaluated.*/
/* **/
/* *  TRANSITIONS*/
/* *  Each state has transitions defined in setup(). Transitions*/
/* *  require two parameters,*/
/* *  1. The transition test function that*/
/* *  returns a boolean value indicating whether or not the*/
/* *  transition occured,*/
/* *  2. The number of the target state. The target state can also*/
/* *  be specified passing the state pointer. This could point to*/
/* *  the same state it is in, if you want to dynamically set the*/
/* *  transition target. To do so, use state->setTransition(). You*/
/* *  must pass the index of the transition you want to modify and*/
/* *  the number of the target state.*/
/* **/
/* *  Transitions are evaluated by the state machine after the state*/
/* *  logic has executed. If none of the transitions evaluate to*/
/* *  true, then the machine stays in the current state.*/
/* **/
/* **/
/* *  Author: Jose Rullan*/
/* *  Date: 10/December/17*/
/* *  Project's page: https://github.com/jrullan/StateMachine*/
/* *  License: MIT*/
/* ****************************************************************/
/*#include <StateMachine.h>*/

/*const int STATE_DELAY = 1000;*/
/*int randomState = 0;*/
/*const int LED = 13;*/

/*StateMachine machine = StateMachine();*/

/*/**/
/* * Example of using a lambda (or anonymous function) callback*/
/* * instead of providing the address of an existing function.*/
/* * Also example of using the attribute executeOnce to execute*/
/* * some part of the code only once per state.*/
/* */
/*State* S0 = machine.addState([](){*/
/*  Serial.println("State 0, anonymous function");*/
/*  if(machine.executeOnce){*/
/*    Serial.println("Execute Once");*/
/*    digitalWrite(LED,!digitalRead(LED));*/
/*  }*/
/*});;*/

/*/**/
/* * The other way to define states.*/
/* * (Looks cleaner)*/
/* * Functions must be defined in the sketch*/
/* */
/*State* S1 = machine.addState(&state1);*/
/*State* S2 = machine.addState(&state2);*/
/*State* S3 = machine.addState(&state3);*/
/*State* S4 = machine.addState(&state4);*/
/*State* S5 = machine.addState(&state5);*/

/*void setup() {*/
/*  Serial.begin(115200);*/
/*  pinMode(LED,OUTPUT);*/
/*  randomSeed(A0);*/

/*  /**/
/*   * Example of a transition that uses a lambda*/
/*   * function, and sets the transition (first one)*/
/*   * to a random state.*/
/*   **/
/*   * Add only one transition(index=0)*/
/*   * that points to randomly selected states*/
/*   * Initially points to itself.*/
/*   */
/*  S0->addTransition([](){*/
/*    randomState = random(0,6);*/
/*    Serial.print("Transitioning to random state ");*/
/*    Serial.println(randomState);*/
/*    S0->setTransition(0,randomState);*/
/*    return true;*/
/*  },S0);*/

/*  /**/
/*  * The other way to define transitions.*/
/*  * (Looks cleaner)*/
/*  * Functions must be defined in the sketch*/
/*  */
/*  S1->addTransition(&transitionS1S2,S2);*/
/*  S2->addTransition(&transitionS2S3,S3);*/
/*  S3->addTransition(&transitionS3S4,S4);*/
/*  S4->addTransition(&transitionS4S5,S5);*/
/*  S5->addTransition(&transitionS5S0,S0);*/
/*  S5->addTransition(&transitionS5S2,S2);*/
/*}*/

/*void loop() {*/
/*  machine.run();*/
/*  delay(STATE_DELAY);*/
/*}*/


/*//=======================================*/

/*void state1(){*/
/*  Serial.println("State 1");*/
/*}*/

/*bool transitionS1S2(){*/
/*  return true;*/
/*}*/

/*//-------------------------*/
/*void state2(){*/
/*  Serial.println("State 2");*/
/*}*/

/*bool transitionS2S3(){*/
/*  return true;*/
/*}*/

/*//------------------------*/
/*void state3(){*/
/*  Serial.println("State 3");*/
/*}*/

/*bool transitionS3S4(){*/
/*  return true;*/
/*}*/

/*//-------------------------*/
/*void state4(){*/
/*  Serial.println("State 4");*/
/*}*/

/*bool transitionS4S5(){*/
/*  return true;*/
/*}*/

/*//-------------------------*/
/*void state5(){*/
/*  Serial.println("State 5");*/
/*}*/

/*bool transitionS5S0(){*/
/*  return random(0,2);*/
/*}*/

/*bool transitionS5S2(){*/
/*  return true;*/
/*}*/


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
StateMachine opMachine = StateMachine();

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
#line 247 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSMjrullan/testFSMjrullan.ino"
void setup();
#line 247 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSMjrullan/testFSMjrullan.ino"
void setup()
{
    Serial.begin(115200);
    pinMode(TEST_LED, OUTPUT); // test
    randomSeed(A0); // test

}

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

