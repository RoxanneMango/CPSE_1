/*
* play_rtttl body logic originally taken from:
* https://codebender.cc/example/Tone/RTTTL#RTTTL.ino
* Author unknown
*/

#ifndef RTTTL_PLAYER_H
#define RTTTL_PLAYER_H

#include "note_player.h"

#define isdigit(n) (n >= '0' && n <= '9')
#define OCTAVE_OFFSET 0

void play_rtttl(Note_player & note_player, const char * p);

#endif // RTTTL_PLAYER_H