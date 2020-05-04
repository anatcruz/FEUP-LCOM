#include "keyboard.h"
#include "kbc.h"

static int keyboard_hook_id = KEYBOARD_HOOK_ID;

static bool keyboard_two_byte_scancode = false;
static bool new_press = false;

static uint8_t keyboard_kbc_status;
static uint8_t keyboard_scancode;

void (kbc_ih)(void) {
    kbc_read_status(&keyboard_kbc_status);
    util_sys_inb(KBC_OUT_BUF, &keyboard_scancode);
    //The byte must be read regardless of whether or not there was an error
    
    new_press = true;
}

//The non-critical part of the keyboard ih
bool keyboard_ih2(keyboard_packet *new_packet) {
    if (!new_press)
        return false;
    else
        new_press = false;
    

    if (((keyboard_kbc_status & (KBC_PARITY | KBC_TIMEOUT)) != 0) && 
         (keyboard_kbc_status & KBC_AUX) == 1) {
        //It's either an error or something we don't want
        keyboard_two_byte_scancode = false;
        return false;
    }
    
    if (keyboard_scancode == KEYBOARD_TWO_BYTES_MSB) {//Its a two byte scancode, wait for the next interrupt
        keyboard_two_byte_scancode = true;
        return false;
    }

    if (keyboard_two_byte_scancode) {
        new_packet->bytes[0] = KEYBOARD_TWO_BYTES_MSB;
        new_packet->bytes[1] = keyboard_scancode;
        new_packet->n_bytes = 2;
    } else {
        new_packet->bytes[0] = keyboard_scancode;
        new_packet->n_bytes = 1;
    }
    
    keyboard_two_byte_scancode = false;
    return true;
}

int keyboard_ih_subscribe() {
    keyboard_hook_id = KEYBOARD_HOOK_ID;
    return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int keyboard_ih_unsubscribe() {
    return sys_irqrmpolicy(&keyboard_hook_id);
}

int keyboard_ih_disable() {
    return sys_irqdisable(&keyboard_hook_id);
}

int keyboard_ih_enable() {
    return sys_irqenable(&keyboard_hook_id);
}
