#include "Main.h"
#include "Commands.h"
#include "StringTable.h"
#include "ProgramStates.h"

char g_programState = STATE_NULL;
char g_preProgramState = g_programState;  // :)
String strLastCmd;

void setup() {
  beginSerial();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Wish I knew how to use interrupts...

  // WAAAH! `CMD_CHECK_ITR = 1000`!:
  // pls lower ._.
  // ...and DO NOT put this into another function :joy:
  for (int i = 0; i < CMD_CHECK_ITR; i++) {
    if (Serial.available())
      takeChoice();
  }

  // (I really wanted to use "`checkSerial(CMD_CHECK_ITR, &takeChoice)`", though :P)
  // (...and yes, stupid ol' me needs to remember stuff, so... here:
  // [https://www.geeksforgeeks.org/function-pointer-in-c/]! :rofl:)

  // Tip: use an `if` for `STATE_NULL` and then use a `switch` for the others.
  // ...and put it into a function! The size of this thing will grow FAST!

  g_preProgramState = g_programState;

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

    default:
      Serial.println(STR.invalidCmd);
      break;
  }
}

void beginSerial() {
  Serial.begin(9600);
  while (!Serial)
    ;
}

void takeChoice(void) {
  String choice = Serial.readString();

  // Tell them what they typed!:
  Serial.print("Your choice: ");
  Serial.println(choice);

  choice.trim();         // Trim out a few characters!
  choice.toLowerCase();  // Yes! less characters to iterate through!
  // NOT HELPFUL: """^^^ WE HAVE `equalsIgnoreCase()`!"""".

  takeChoice(choice);

  //if (!(ptrLastCmd == nullptr || ptrLastCmd == NULL))
  //free(ptrLastCmd);

  if (!strLastCmd.equals(strLastCmd))
    //ptrLastCmd = choice.c_str();
    strLastCmd = choice;
}

void takeChoice(String p_choice) {
  // I *really* needed some spacing; thank you, Arduino:
  // PS Using `String.equals()` is too useless here...

  if (p_choice == CMD.start) {
    g_programState = STATE_HIGH;
  }

  else if (p_choice == CMD.stop) {
    g_programState = STATE_LOW;
  }

  else if (p_choice == CMD.lastCmd) {
    Serial.print("The last command entered was: `");
    Serial.print(strLastCmd);
    Serial.println("`.");
  }

  else {  // Impossible state!
    Serial.println(STR.ohHeyThere);
    g_programState = STATE_NULL;
    Serial.println(STR.unintendedState);
  }
}