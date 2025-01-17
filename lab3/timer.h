#ifndef TIMER
#define TIMER 

#include <lcom/lcf.h>

#define TIMER_INTERRUPT_FREQ 60
#define TIMER_IRQ 0
#define TIMER_HOOK_ID 0
#define TIMER_MASK BIT(TIMER_HOOK_ID)


int timer_ih_subscribe();
int timer_ih_unsubscribe();

int timer_ih_enable();
int timer_ih_disable();

#endif

