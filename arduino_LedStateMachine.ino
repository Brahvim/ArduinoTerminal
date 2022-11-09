#include "Main.h"
#include "Commands.h"
#include "StringTable.h"
#include "ProgramStates.h"

char g_programState = STATE_NULL;

void setup() {
  beginSerial();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Wish I knew how to use interrupts...

  for (int i = 0; i < 1000; i++) {
    if (Serial.available())
      takeChoice();
  }

  switch (g_programState) {
    case STATE_NULL:
      Serial.println(STR.stateNull);

      Serial.setTimeout(10);
      while (!Serial.available())
        ;

      takeChoice();
      break;

    case STATE_LOW:
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      break;

    case STATE_HIGH:
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      break;
  }
}

void takeChoice(void) {
  String choice = Serial.readString();
  choice.trim();         // Trim out a few characters!
  choice.toLowerCase();  // Yes! less characters to iterate through!

  Serial.print("Your choice: ");
  Serial.println(choice);

  takeChoice(choice);
}

void takeChoice(String p_choice) {
  if (p_choice == CMD.start) {
    g_programState = STATE_HIGH;
  } else if (p_choice == CMD.stop) {
    g_programState = STATE_LOW;
  } else {  // Impossible state!
    Serial.println(STR.ohHeyThere);
    g_programState = STATE_NULL;
    Serial.println(STR.unintendedState);
  }
}

void beginSerial() {
  Serial.begin(9600);
  while (!Serial)
    ;
}