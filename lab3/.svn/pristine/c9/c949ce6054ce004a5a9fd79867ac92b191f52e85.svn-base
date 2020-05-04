#ifndef KEYBOARD
#define KEYBOARD

#include <lcom/lcf.h>

#define KEYBOARD_IRQ 1
#define KEYBOARD_HOOK_ID 1
#define KEYBOARD_MASK BIT(KEYBOARD_HOOK_ID)

#define KEYBOARD_TWO_BYTES_MSB 0xE0

bool keyboard_ih2();

int keyboard_ih_subscribe();
int keyboard_ih_unsubscribe();

int keyboard_ih_enable();
int keyboard_ih_disable();
#endif

