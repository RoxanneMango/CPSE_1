#ifndef MISSIONIMP_H
#define MISSIONIMP_H

#include "melody.h"

class MissionImp : public Melody
{
public:
	void play(Note_player & p)
	{
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_DS6, 	78 } );
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_DS6, 	78 } );
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_DS6, 	78 } );
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_DS6, 	78 } );
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_D6, 	78 } );
		p.play( Note { NOTE_DS6, 	78 } );
		p.play( Note { NOTE_E6, 	78 } );
		p.play( Note { NOTE_F6, 	78 } );
		p.play( Note { NOTE_FS6, 	78 } );
		p.play( Note { NOTE_G6, 	78 } );
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_AS6, 	157 } );
		delay(157);
		p.play( Note { NOTE_C7, 	157 } );
		delay(157);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_F6, 	157 } );
		delay(157);
		p.play( Note { NOTE_FS6, 	157 } );
		delay(157);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_AS6, 	157 } );
		delay(157);
		p.play( Note { NOTE_C7, 	157 } );
		delay(157);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_G6, 	157 } );
		delay(315);
		p.play( Note { NOTE_F6, 	157 } );
		delay(157);
		p.play( Note { NOTE_FS6, 	157 } );
		delay(157);
		p.play( Note { NOTE_AS6, 	157 } );
		p.play( Note { NOTE_G6, 	157 } );
		p.play( Note { NOTE_D6, 	1262 } );
		delay(78);
		p.play( Note { NOTE_AS6, 	157 } );
		p.play( Note { NOTE_G6, 	157 } );
		p.play( Note { NOTE_CS6, 	1262 } );
		delay(78);
		p.play( Note { NOTE_AS6, 	157 } );
		p.play( Note { NOTE_G6, 	157 } );
		p.play( Note { NOTE_C6, 	1262 } );
		p.play( Note { NOTE_AS5, 	157 } );
		p.play( Note { NOTE_C6, 	315 } );
		delay(1262);
		delay(78);
		p.play( Note { NOTE_AS5, 	157 } );
		p.play( Note { NOTE_G5, 	157 } );
		p.play( Note { NOTE_FS6, 	1262 } );
		delay(78);
		p.play( Note { NOTE_AS5, 	157 } );
		p.play( Note { NOTE_G5, 	157 } );
		p.play( Note { NOTE_F6, 	1262 } );
		delay(78);
		p.play( Note { NOTE_AS5, 	157 } );
		p.play( Note { NOTE_G5, 	157 } );
		p.play( Note { NOTE_E6, 	1262 } );
		p.play( Note { NOTE_DS6, 	157 } );
		p.play( Note { NOTE_D6, 	315 } );
	}
};

#endif // MISSIONIMP_H