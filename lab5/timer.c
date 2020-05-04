#include "timer.h"

int timer_hook_id = TIMER_HOOK_ID;

int timer_counter = 0;

int timer_ih_subscribe() {
    //printf("timer hook id: %d\n", timer_hook_id);
    return sys_irqsetpolicy(TIMER_IRQ, IRQ_REENABLE , &timer_hook_id);
}

int timer_ih_unsubscribe() {
    return sys_irqrmpolicy(&timer_hook_id);
}

int timer_ih_disable() {
    return sys_irqdisable(&timer_hook_id);
}

int timer_ih_enable() {
    return sys_irqenable(&timer_hook_id);
}

void (timer_int_handler)() {
  timer_counter++;
}

