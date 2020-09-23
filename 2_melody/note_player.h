/*
* Originally taken from the following forum thread:
* https://forum.arduino.cc/index.php?topic=363557.0
* Pastebin link: https://paste.ubuntu.com/5703102/
* Written by Dan Corneanu at Sun, 26 May 2013 11:35:26 +0000
* known on the forums as Palliser 
*/

#ifndef TONE_H
#define TONE_H

#include <stdint.h>
#include <Arduino.h>

#include "pitches.h"
#include "note_player_i.h"

// Accurate frequency generator emulating Tone function for Due
// Code created by mantoui and cdan and modified by Palliser (2015)

//#define TONE_PIN      2 // TIOA0

class Note_player : public Note_player_i
{
private:
	constexpr static Tc * chTC = TC0; //(Pio *)0x40080000U
	const static uint32_t chNo = 0;
public:
	Note_player();
	void play(const Note & note);
};

#endif // TONE_H