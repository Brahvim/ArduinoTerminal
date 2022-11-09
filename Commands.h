#pragma once

// This is where I store the string table for commands, `CMD`!
// (Broke 'conventions' again :rofl:):

const int CMD_CHECK_ITR = 1000;

struct {
  const char *stop = "stop";
  const char *start = "start";
} CMD;