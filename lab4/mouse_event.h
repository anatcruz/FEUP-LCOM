#ifndef MOUSE_EVENT
#define MOUSE_EVENT

#include <lcom/lcf.h>

bool state_machine_process(struct packet p, uint8_t x_len, uint8_t tolerance);

#endif
