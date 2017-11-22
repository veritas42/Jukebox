#ifndef TIMER_H_

#define TIMER_H_

extern volatile unsigned long long delay;

void timer_init(void);
void delay_ms(unsigned int val);

#endif