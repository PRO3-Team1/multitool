#include <math.h>
#include "tone.h"
#include "board.h"
#include "us_timer.h"

#define NUM_STEPS (64)

//It is a 10 bit DAC. 1023 is max.
#define MAX_DAC_CODE (1024-1)
#define PI (3.1415927)

wavetype toneType = SINE;

int step;
int sine_table[NUM_STEPS];

void playNextSample (void);
/**
 * @brief initialize sinewave lookuptable, to avoid computing sin()
 * on every function call, when generating samples
 * */
void sinewave_init (void)
{
	int n;

	for (n = 0; n < NUM_STEPS; n++)
	{
		sine_table[n] =(int) ((MAX_DAC_CODE) * (1 + sin(n * 2 * PI / NUM_STEPS))/2);
	}
}

void tone_init (void)
{
	/* Setup DAC pins for pin 0.26 -AOUT, P18 on the LPC4088 QSB
	 * see section 7.3 in UM10562 for details, table 85 & 86  */
	Chip_IOCON_PinMuxSet(LPC_IOCON, DAC18PORT, DAC18PIN, (IOCON_FUNC2 | IOCON_DAC_EN ));

	Chip_DAC_Init (LPC_DAC);

	sinewave_init ();
}

void tone_set (int freq, wavetype wave)
{
	//We divide by two because the APB pheripihal clock has a CLKDIV of 2
	us_timer_start(120000000 / freq / 2 / NUM_STEPS, &playNextSample);
	step = 0;
	toneType = wave;
}
void playNextSample (void)
{
	int sample;
	step++;

	if (step >= NUM_STEPS)
	{
		step = 0;
	}
	/* what to play */
	switch (toneType)
	{
		case SINE:
			sample = sine_table[step];
			break;
		case SQUARE:
			sample = step < NUM_STEPS / 2 ? 0 : MAX_DAC_CODE;
			break;
		case RAMP:
			sample = (step * MAX_DAC_CODE) / NUM_STEPS;
			break;
	}

	Chip_DAC_UpdateValue (LPC_DAC, sample);
}



