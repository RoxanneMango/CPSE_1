#ifndef NOTE_PLAYER_H
#define NOTE_PLAYER_H

#include "note.h"

class Note_player_i
{
public:
	virtual void play( const Note & n ) = 0;
};

#endif // NOTE_PLAYER_H