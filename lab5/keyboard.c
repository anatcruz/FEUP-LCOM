#include "keyboard.h"
#include "kbc.h"

int keyboard_hook_id = KEYBOARD_HOOK_ID;

bool keyboard_two_byte_scancode = false;
bool new_press = false;

bool    keyboard_make;
uint8_t keyboard_size;
uint8_t keyboard_bytes[2];

uint8_t keyboard_kbc_status;
uint8_t keyboard_scancode;

void (kbc_ih)(void) {
    kbc_read_status(&keyboard_kbc_status);
    util_sys_inb(KBC_OUT_BUF, &keyboard_scancode);
    //The byte must be read regardless of whether or not there was an error
    
    new_press = true;
}

//The non-critical part of the keyboard ih
bool keyboard_ih2() {
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
        keyboard_make = (keyboard_scancode & 0x80) == 0;
        keyboard_bytes[0] = KEYBOARD_TWO_BYTES_MSB;
        keyboard_bytes[1] = keyboard_scancode;
        keyboard_size = 2;
        return true;
    } else {
        keyboard_make = (keyboard_scancode & 0x80) == 0;
        keyboard_bytes[0] = keyboard_scancode;
        keyboard_size = 1;
        return true;
    }
}

int keyboard_ih_subscribe() {
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
