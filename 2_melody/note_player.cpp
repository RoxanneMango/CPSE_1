#include "note_player.h"

Note_player::Note_player()
{
	// Configure pin 2 as timer output
	pmc_enable_periph_clk( ID_PIOB ) ;
	PIO_Configure( PIOB, PIO_PERIPH_B, PIO_PB25B_TIOA0, PIO_DEFAULT);

	pmc_set_writeprotect(false);
	pmc_enable_periph_clk(ID_TC0); // channel 0
	TC_Configure(chTC, chNo,
		   TC_CMR_TCCLKS_TIMER_CLOCK4 |
		   TC_CMR_WAVE |         // Waveform mode
		   TC_CMR_WAVSEL_UP_RC | // Counter running up and reset when equals to RC
		   TC_CMR_ACPA_SET |     // RA compare sets TIOA
		   TC_CMR_ACPC_CLEAR );  // RC compare clears TIOA

	chTC->TC_CHANNEL[chNo].TC_IER=TC_IER_CPCS;  // RC compare interrupt
	chTC->TC_CHANNEL[chNo].TC_IDR=~TC_IER_CPCS;
}

void Note_player::play(const Note & note)
{ 
	if(note.frequency < 0 || note.frequency > 100001) {
		TC_Stop(chTC, chNo);
		return;
	}
	if(!note.frequency)
	{
		delay(note.duration);
	}
	const uint32_t rc = VARIANT_MCK / 128 / note.frequency;
	const uint32_t ra = rc >> 1; // 50% duty cycle
	//const uint32_t ra = rc >> 2; // 20% duty cycle
	TC_Stop(chTC, chNo);
	TC_SetRA(chTC, chNo, ra);
	TC_SetRC(chTC, chNo, rc);
	TC_Start(chTC, chNo);
	
	delay(note.duration);
	
	TC_Stop(chTC, chNo);
}