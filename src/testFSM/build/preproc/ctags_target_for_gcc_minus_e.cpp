# 1 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
# 2 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 2

const byte BTN_CALL = 2;
const byte GREEN_LED = 12;
const byte YELLOW_LED = 11;
const byte RED_LED = 10;

// Create new FSM
YA_FSM stateMachine;

// State Alias
enum State {RED, GREEN, YELLOW, CALL};

// Helper for print labels instead integer when state change
const char * const stateName[] 
# 15 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                              __attribute__((__progmem__)) 
# 15 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                                      = { "RED", "GREEN", "YELLOW", "CALL"};

// Pedestrian traffic light -> green ligth ON until button pressed




// Input (trig transition from GREEN to CALL state, the others transitions on timeout)
bool callButton = false;

// Output variables
bool redLed = false;
bool greenLed = false;
bool yellowLed = false;

/////////// STATE MACHINE CALLBACK FUNCTIONS //////////////////
// Define "on entering" callback function (the same for all "light" states)
void onEnter() {
  Serial.print(stateMachine.ActiveStateName());
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 34 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 34 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                " light ON"
# 34 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                ); &__c[0];}))
# 34 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                )));
}
// Define "on leaving" callback function (the same for all "light"  states)
void onExit() {
  Serial.print(stateMachine.ActiveStateName());
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 39 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 39 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                " light OFF\n"
# 39 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                ); &__c[0];}))
# 39 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                )));
}
// Define "on enter" for CALL button state
void onEnterCall() {
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 43 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 43 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                "Call registered, please wait a little time."
# 43 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                ); &__c[0];}))
# 43 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                )));
}

// Setup the State Machine
void setupStateMachine() {

  // Follow the order of defined enumeration for the state definition (will be used as index)
  // Add States => name,timeout, onEnter cb, onState cb, onLeave cb
  stateMachine.AddState(stateName[RED], 10000, onEnter, nullptr, onExit);
  stateMachine.AddState(stateName[GREEN], 0, onEnter, nullptr, onExit);
  stateMachine.AddState(stateName[YELLOW], 2000, onEnter, nullptr, onExit);
  stateMachine.AddState(stateName[CALL], 5000, onEnterCall, nullptr, nullptr);

  stateMachine.AddAction(RED, YA_FSM::N, redLed); // N -> while state is active red led is ON
  stateMachine.AddAction(GREEN, YA_FSM::S, greenLed); // S -> SET green led on
  stateMachine.AddAction(YELLOW, YA_FSM::R, greenLed); // R -> RESET the green led
  stateMachine.AddAction(YELLOW, YA_FSM::N, yellowLed); // N -> while state is active yellow led is ON

  // Add transitions with related trigger input callback functions
  // In this example it's just a simple lambda function that return state timeout value
  stateMachine.AddTransition(RED, GREEN, [](){return stateMachine.CurrentState()->timeout;} );
  stateMachine.AddTransition(YELLOW, RED, [](){return stateMachine.CurrentState()->timeout;} );
  stateMachine.AddTransition(CALL, YELLOW, [](){return stateMachine.CurrentState()->timeout;});
  stateMachine.AddTransition(GREEN, CALL, callButton);
}

void setup() {
  // Setup Input/Output
  pinMode(BTN_CALL, 0x2);
  pinMode(GREEN_LED, 0x1);
  pinMode(YELLOW_LED, 0x1);
  pinMode(RED_LED, 0x1);

  Serial.begin(115200);
  while(!Serial) {} // Needed for native USB port only
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 78 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 78 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                "Starting the Finite State Machine...\n"
# 78 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                ); &__c[0];}))
# 78 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                )));
  setupStateMachine();
}

void loop() {
  // Read inputs
  callButton = (digitalRead(BTN_CALL) == 0x0);

  // Update State Machine
  if(stateMachine.Update()){
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 88 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 88 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                "Active state: "
# 88 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino" 3
                ); &__c[0];}))
# 88 "/home/tony/OneDrive - Instituto Politecnico Nacional/Documents/UPIIZ/10º Semestre/Trabajo Terminal 2/interfaz-compactadora/FSM/testFSM/testFSM.ino"
                )));
    Serial.println(stateMachine.ActiveStateName());
  }

  // Set outputs
  digitalWrite(RED_LED, redLed);
  digitalWrite(GREEN_LED, greenLed);
  digitalWrite(YELLOW_LED, yellowLed);
}
