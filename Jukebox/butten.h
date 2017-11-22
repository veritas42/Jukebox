/*
 * butten.h
 *
 * Created: 2017-11-20 오후 4:58:47
 *  Author: veritas
 */ 


#ifndef BUTTEN_H_
#define BUTTEN_H_

#define MAXSELECT 3

extern volatile unsigned char state;
extern volatile unsigned char select;

void butten_init(void);

#endif /* BUTTEN_H_ */