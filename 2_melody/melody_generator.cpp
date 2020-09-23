#include "melody_generator.h"

int
main()
{
	const char * song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
	melody_generator(song);
	return 0;
}

void
melody_generator(const char * p)
{
	const char notes[][50] = { "0",
		"NOTE_C4", "NOTE_CS4", "NOTE_D4", "NOTE_DS4", "NOTE_E4", "NOTE_F4", "NOTE_FS4", "NOTE_G4", "NOTE_GS4", "NOTE_A4", "NOTE_AS4", "NOTE_B4",
		"NOTE_C5", "NOTE_CS5", "NOTE_D5", "NOTE_DS5", "NOTE_E5", "NOTE_F5", "NOTE_FS5", "NOTE_G5", "NOTE_GS5", "NOTE_A5", "NOTE_AS5", "NOTE_B5",
		"NOTE_C6", "NOTE_CS6", "NOTE_D6", "NOTE_DS6", "NOTE_E6", "NOTE_F6", "NOTE_FS6", "NOTE_G6", "NOTE_GS6", "NOTE_A6", "NOTE_AS6", "NOTE_B6",
		"NOTE_C7", "NOTE_CS7", "NOTE_D7", "NOTE_DS7", "NOTE_E7", "NOTE_F7", "NOTE_FS7", "NOTE_G7", "NOTE_GS7", "NOTE_A7", "NOTE_AS7", "NOTE_B7"
	};

	uint8_t default_dur = 4;
	uint8_t default_oct = 6;
	int bpm = 63;
	//
	int num = 0;
	long wholenote = 0;
	long duration = 0;
	uint8_t note = 0;
	uint8_t scale = 0;

	char PATH [128] = {"../"};
	char name[64] = {0};

	while(*p != ':')
	{
		strncat(name, p, 1);
		p++;					// ignore name
	}
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
	
	strcat(PATH, name);
	strncat(PATH, ".h", 3);
	
	// Create file etc.
	FILE * FP;
	if((FP = fopen(PATH, "w")) < 0)
//	if((FP = fopen("melody.cpp", "w")) < 0)
	{
		printf("could not open file at %s\n", PATH);
		return;
	}
	fclose(FP);
	
	if((FP = fopen(PATH, "a")) < 0)
//	if((FP = fopen("melody.cpp", "a")) < 0)
	{
		printf("could not open file at %s\n", PATH);
		return;
	}
	

	fprintf(FP, "#ifndef ");
	for(int i = 0; i < strlen(name); ++i)
	{
		fprintf(FP, "%c", toupper(name[i]));
	}
	fprintf(FP, "_H\n#define ");
	for(int i = 0; i < strlen(name); ++i)
	{
		fprintf(FP, "%c", toupper(name[i]));
	}
	fprintf(FP, "_H\n\n#include \"melody.h\"\n\nclass %s : public Melody\n{\npublic:\n", name);
	
	//fprintf(FP, "#include \"melody.h\"\n\nclass %s : public Melody\n{\npublic:\n", name);
	fprintf(FP, "\tvoid play(Note_player & p)\n\t{\n");

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
			fprintf(FP, "\t\tp.play( Note { %s, \t%d } );\n", notes[(scale - 4) * 12 + note], duration);
		}
		else
		{
			fprintf(FP, "\t\tdelay(%d);\n", duration);
		}
	}

	fprintf(FP, "\t}\n};\n\n#endif // ");
	//fprintf(FP, "\t}\n};");
	for(int i = 0; i < strlen(name); ++i)
	{
		fprintf(FP, "%c", toupper(name[i]));
	}
	fprintf(FP, "_H");
	
	fclose(FP);
}