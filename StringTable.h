#pragma once

// Yeah, breaking conventions!
// ...as if C++ has any!:

// Please use C++ 11 raw strings as well ^^

struct {
  const char *stateNull = "Enter \"stop\" or \"start\" to change the state of the LED!";
  const char *ohHeyThere = "Oh hey there :|";
  const char *unintendedState = "The code just hit a state that wasn't intended...";
  const char *invalidCmd = "The following is unrecognized:";
  //const char *sameState = "That changed nothing!";
} const STR;  // Takes less memory when `const`!