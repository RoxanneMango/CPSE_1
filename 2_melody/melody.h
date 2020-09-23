#ifndef MELODY_H
#define MELODY_H

#include "note.h"
#include "pitches.h"
#include "note_player.h"

class Melody
{
public:
	virtual void play(Note_player & p) = 0;	
};


#endif // MELODY_H