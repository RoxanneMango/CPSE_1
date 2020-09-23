#include "note_printer.h"

int
main()
{
	const char * song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
	note_printer(song);
	return 0;
}

void
note_printer(const char * p)
//note_printer(const char * p, bool timing)
{
	uint8_t default_dur = 4;
	uint8_t default_oct = 6;
	int bpm = 63;
	//
	int num = 0;
	long wholenote = 0;
	long duration = 0;
	uint8_t note = 0;
	uint8_t scale = 0;

	while(*p != ':')
	{
//		printf("%c", *p);
		p++;					// ignore name
	}
//	printf(": ");
	p++;						// skip ':'

	// get default duration
	if(*p == 'd')
	{
		p++; p++;				// skip "d="
		num = 0;
		while(is_digit(*p))
		{
			num = (num * 10) + (*p++ - '0');
		}
		if(num > 0)
		{
			default_dur = num;
		}
		p++;					// skip comma
	}

	// get default octave
	if(*p == 'o')
	{
		p++; p++;				// skip "o="
		num = *p++ - '0';
		if(num >= 3 && num <=7)
		{
			default_oct = num;
		}
		p++;					// skip comma
	}

	// get BPM
	if(*p == 'b')
	{
		p++; p++;				// skip "b="
		num = 0;
		while(is_digit(*p))
		{
			num = (num * 10) + (*p++ - '0');
		}
		bpm = num;
		p++;					// skip colon
	}

	// BPM usually expresses the number of quarter notes per minute
	wholenote = (60 * 1000L / bpm) * 4;	// this is the time for whole note (in milliseconds)

	// now begin note loop
	while(*p)
	{
		char note_s = 0;
		char suffix_s = 0;
		char scale_s = 0;
		
		// first, get note duration, if available
		num = 0;
		while(is_digit(*p))
		{
			num = (num * 10) + (*p++ - '0');
		}

		if(num)
		{
			duration = wholenote / num;
		}
		else
		{
			duration = wholenote / default_dur;	// we will need to check if we are a dotted note after
		}
		// now get the note
		note = 0;

		switch(*p)
		{
			case 'c':
				note = 1;
				break;
			case 'd':
				note = 3;
				break;
			case 'e':
				note = 5;
				break;
			case 'f':
				note = 6;
				break;
			case 'g':
				note = 8;
				break;
			case 'a':
				note = 10;
				break;
			case 'b':
				note = 12;
				break;
			case 'p':
				default:
				note = 0;
		}
		
		note_s = *p;
		
		p++;

		// now, get optional '#' sharp
		if(*p == '#')
		{
			suffix_s = '#';
			note++;
			p++;
		}

		// now, get optional '.' dotted note
		if(*p == '.')
		{
			suffix_s = '.';
			duration += duration/2;
			p++;
		}

		// now, get scale
		if(is_digit(*p))
		{
			scale = *p - '0';
			p++;
		}
		else
		{
			scale = default_oct;
		}

		scale += OCTAVE_OFFSET;

		if(*p == ',')
		{
			p++;					// skip comma for next note (or we may be at the end)
		}
		
		if(note)
		{
			if((scale-OCTAVE_OFFSET) == default_oct)
			{
				printf("%c", note_s);
			}
			else
			{
				printf("%d%c", scale, note_s);
			}
			if(suffix_s)
			{
				printf("%c", suffix_s);
			}
			printf(" ");
			/* nanosleep function does not work with -std=g++17 flag
			if(timing)
			{
				struct timespec req = {0};
				req.tv_sec = 0;
				req.tv_nsec = duration * 1000000;
				nanosleep(&req, (struct timespec *)NULL);
			}
			*/
		}
		else
		{	
			/* nanosleep function does not work with -std=g++17 flag
			if(timing)
			{
				struct timespec req = {0};
				req.tv_sec = 0;
				req.tv_nsec = duration * 1000000;
				nanosleep(&req, (struct timespec *)NULL);
			}
			*/
		}
	}
}