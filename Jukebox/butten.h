/*
 * butten.h
 *
 * Created: 2017-11-20 오후 4:58:47
 *  Author: veritas
 */ 


#ifndef BUTTEN_H_
#define BUTTEN_H_

#define MAXSELECT 16
#define MODENUM 2

extern volatile unsigned char state;
extern volatile unsigned char select;
extern volatile unsigned char mode;

void butten_init(void);
unsigned char state(void);
unsigned char select(void);
unsigned char mode(void);

#endif /* BUTTEN_H_ */