/*
 * sound.h
 *
 * Created: 2017-11-20 오후 1:57:56
 *  Author: veritas
 */ 


#ifndef SOUND_H_
#define SOUND_H_

extern volatile unsigned int bpm;

void ctc1_init(void);
void tone(double hz, int s_time);
void tone_oct(char oct[], double meter); //총 요소 3개 첫번째 : 옥타브  두번째 : 음  세번째 : 온음(w)/반음(h)



#endif /* SOUND_H_ */