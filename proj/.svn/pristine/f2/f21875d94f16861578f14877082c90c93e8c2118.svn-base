#ifndef MOUSE
#define MOUSE

#include <lcom/lcf.h>

#define MOUSE_IRQ 12
#define MOUSE_HOOK_ID 2
#define MOUSE_MASK BIT(MOUSE_HOOK_ID)

#define MOUSE_BYTE_1_Y_OVFL       BIT(7)
#define MOUSE_BYTE_1_X_OVFL       BIT(6)
#define MOUSE_BYTE_1_MSB_Y_DELTA  BIT(5)
#define MOUSE_BYTE_1_MSB_X_DELTA  BIT(4)
#define MOUSE_BYTE_1_BIT_SET_TO_1 BIT(3)
#define MOUSE_BYTE_1_MB           BIT(2)
#define MOUSE_BYTE_1_RB           BIT(1)
#define MOUSE_BYTE_1_LB           BIT(0)

#define MOUSE_COM_RESET                  0xFF
#define MOUSE_COM_RESEND                 0xFE
#define MOUSE_COM_SET_DEFAULTS           0xF6
#define MOUSE_COM_DISABLE_DATA_REPORTING 0xF5
#define MOUSE_COM_ENABLE_DATA_REPORTING  0xF4
#define MOUSE_COM_SET_SAMPLE_RATE        0xF3
#define MOUSE_COM_SET_REMOTE_MODE        0xF0
#define MOUSE_COM_READ_DATA              0xEB
#define MOUSE_COM_SET_STREAM_MODE        0xEA
#define MOUSE_COM_STATUS_REQUEST         0xE9
#define MOUSE_COM_SET_RESOLUTION         0xE8
#define MOUSE_COM_SET_SCALING_2_1        0xE7
#define MOUSE_COM_SET_SCALING_1_1        0xE6

#define MOUSE_RESPONSE_ACK   0xFA
#define MOUSE_RESPONSE_NACK  0xFE
#define MOUSE_RESPONSE_ERROR 0xFC

int mouse_send_command(uint8_t command);
int mouse_send_command_and_arg(uint8_t command, uint8_t, uint8_t arg);

bool mouse_parse_packet(struct packet *mouse_packet);

int mouse_ih_subscribe();
int mouse_ih_unsubscribe();

int mouse_ih_enable();
int mouse_ih_disable();

#endif
