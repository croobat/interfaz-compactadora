#include <ezButton.h>

ezButton compactButton(39);
ezButton liftButton(37);
ezButton emergencyButton(35);

void setup() {
  Serial.begin(9600);
  compactButton.setDebounceTime(50); // set debounce time to 50 milliseconds
  liftButton.setDebounceTime(50); // set debounce time to 50 milliseconds
  emergencyButton.setDebounceTime(50); // set debounce time to 50 milliseconds
  compactButton.setCountMode(COUNT_FALLING);
  liftButton.setCountMode(COUNT_FALLING);
  emergencyButton.setCountMode(COUNT_FALLING);
}

void loop() {
  delay(500);
  compactButton.loop(); // MUST call the loop() function first
  liftButton.loop(); // MUST call the loop() function first
  emergencyButton.loop(); // MUST call the loop() function first

  int compactButtonState = compactButton.getState();
  int liftButtonState = liftButton.getState();
  int emergencyButtonState = emergencyButton.getState();
  Serial.print("compact button state: ");
  Serial.println(compactButtonState);
  Serial.print("lift button state: ");
  Serial.println(liftButtonState);
  Serial.print("emergency button state: ");
  Serial.println(emergencyButtonState);

  unsigned long compactButtonCount = compactButton.getCount();
  unsigned long liftButtonCount = liftButton.getCount();
  unsigned long emergencyButtonCount = emergencyButton.getCount();
  Serial.print("compact button count: ");
  Serial.println(compactButtonCount);
  Serial.print("lift button count: ");
  Serial.println(liftButtonCount);
  Serial.print("emergency button count: ");
  Serial.println(emergencyButtonCount);

  if(compactButton.isPressed())
    Serial.println("The compact button is pressed");

  if(compactButton.isReleased())
    Serial.println("The compact button is released");

  if(liftButton.isPressed())
    Serial.println("The lift button is pressed");

  if(liftButton.isReleased())
    Serial.println("The lift button is released");

  if(emergencyButton.isPressed())
    Serial.println("The emergency button is pressed");

  if(emergencyButton.isReleased())
    Serial.println("The emergency button is released");

  Serial.println("-------------------------------");
}
