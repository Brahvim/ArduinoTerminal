#pragma once

// This is where I store the string table for commands, `CMD`!
// (Broke 'conventions' again :rofl:):

const int CMD_CHECK_ITR = 10;

// Put `const` either here, or right before the instance list!

/*const*/ struct {
  const char *stop = "stop";
  const char *start = "start";
  const char *lastCmd = "lastcmd";
} const CMD;  // Takes less memory when `const`!