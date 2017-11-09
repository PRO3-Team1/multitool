#ifndef TONE_H
#define TONE_H

#define DAC18PORT 0
#define DAC18PIN 26


typedef enum {
	SQUARE,
	RAMP,
	SINE
} wavetype;

void tone_init(void);
void tone_set (int period_us, wavetype wave);
void tone_play(int period_us, int num_cycles, wavetype wave);

#endif // TONE_H
