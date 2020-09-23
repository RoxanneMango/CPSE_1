// nanosleep code taken from : http://timmurphy.org/2009/09/29/nanosleep-in-c-c/

#ifndef NOTE_PRINTER_H
#define NOTE_PRINTER_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "pitches.h"

void note_printer(const char * p);
//void note_printer(const char * p, bool timing);

#endif // NOTE_PRINTER_H