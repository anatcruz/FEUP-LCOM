#include "timer.h"

int timer_hook_id = TIMER_HOOK_ID;

static int timer_counter = 0;

int timer_get_counter() {
    return timer_counter;
}

int timer_ih_subscribe() {
    //printf("timer hook id: %d\n", timer_hook_id);
    timer_hook_id = TIMER_HOOK_ID;
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

