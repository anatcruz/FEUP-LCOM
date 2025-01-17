#include "mouse.h"
#include "kbc.h"

int mouse_hook_id = MOUSE_HOOK_ID;

uint8_t mouse_byte;

void (mouse_ih)(void) {
    util_sys_inb(KBC_OUT_BUF, &mouse_byte);
}

bool mouse_parse_packet(struct packet *mouse_packet) {
    static uint8_t mouse_byte_ctr = 0;
    static uint8_t bytes[3];

    switch (mouse_byte_ctr)
    {
    case 0:
        if ((mouse_byte & MOUSE_BYTE_1_BIT_SET_TO_1) != 0) {
            bytes[mouse_byte_ctr] = mouse_byte;
            mouse_byte_ctr++;
        }
        return false;
    case 1:
        bytes[mouse_byte_ctr] = mouse_byte;
        mouse_byte_ctr++;
        return false;
    case 2:
        bytes[mouse_byte_ctr] = mouse_byte;
        mouse_byte_ctr = 0;

        mouse_packet->bytes[0] = bytes[0];
        mouse_packet->bytes[1] = bytes[1];
        mouse_packet->bytes[2] = bytes[2];

        mouse_packet->delta_x = (uint16_t) bytes[1];
        if (bytes[0] & MOUSE_BYTE_1_MSB_X_DELTA)
            mouse_packet->delta_x -= 256;
        
        mouse_packet->delta_y = (uint16_t) bytes[2];
        if (bytes[0] & MOUSE_BYTE_1_MSB_Y_DELTA)
            mouse_packet->delta_y -= 256;
        
        mouse_packet->rb   = (bytes[0] & MOUSE_BYTE_1_RB)     != 0;
        mouse_packet->lb   = (bytes[0] & MOUSE_BYTE_1_LB)     != 0;
        mouse_packet->mb   = (bytes[0] & MOUSE_BYTE_1_MB)     != 0;
        mouse_packet->x_ov = (bytes[0] & MOUSE_BYTE_1_X_OVFL) != 0;
        mouse_packet->y_ov = (bytes[0] & MOUSE_BYTE_1_Y_OVFL) != 0;

        return true;
    default:
        return false;
    }
}

int mouse_send_command(uint8_t command) {
    for (size_t i = 0; i < 3; i++) {
        //printf("1\n");
        if (kbc_write_command(KBC_WRITE_BYTE_TO_MOUSE) != 0) return 1;
        //printf("2\n");
        if (kbc_write_command_arg(command)) return 1;
        //printf("3\n");
        uint8_t answer;
        if (kbc_read_command_result(&answer)) return 1;
        //printf("4\n");
        if (answer == MOUSE_RESPONSE_ACK)
            return 0;
    }

    return 1;
}

int mouse_ih_subscribe() {
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int mouse_ih_unsubscribe() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

int mouse_ih_disable() {
    return sys_irqdisable(&mouse_hook_id);
}

int mouse_ih_enable() {
    return sys_irqenable(&mouse_hook_id);
}
