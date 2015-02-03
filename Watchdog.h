#ifndef WATCHDOGE_H
#define WATCHDOGE_H

#ifndef MBED_H
#include "mbed.h"
#endif

class Watchdog {
public:
// Load timeout value in watchdog timer and enable
  void setUp(float s);
// "kick" or "feed" the dog - reset the watchdog timer
// by writing this required bit pattern
  void kick();
};


#endif