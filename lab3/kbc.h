#ifndef KBC
#define KBC

#include <lcom/lcf.h>

#include "utils.h"

#define KBC_TICK_DELAY 20000

#define KBC_PARITY  BIT(7)
#define KBC_TIMEOUT BIT(6)
#define KBC_AUX     BIT(5)
#define KBC_INH     BIT(4)
#define KBC_A2      BIT(3)
#define KBC_SYS     BIT(2)
#define KBC_IBF     BIT(1)
#define KBC_OBF     BIT(0)

#define KBC_STAT_REG 0x64
#define KBC_COM_REG  0x64

#define KBC_OUT_BUF     0x60
#define KBC_COM_ARG_REG 0x60

#define KBC_READ_COM              0x20
#define KBC_WRITE_COM             0x60
#define KBC_SELF_TEST             0xAA
#define KBC_CHECK_KB_INTERFACE    0xAB
#define KBC_DISABLE_KBD_INTERFACE 0xAD
#define KBC_ENABLE_KBD_INTERFACE  0xAE

#define KBC_COM_BYTE_DIS2 BIT(5)
#define KBC_COM_BYTE_DIS  BIT(4)
#define KBC_COM_BYTE_INT2 BIT(1)
#define KBC_COM_BYTE_INT  BIT(0)

void kbc_delay(int delay);

int kbc_write_command(uint8_t command);
int kbc_write_command_arg(uint8_t arg);

int kbc_read_command_result(uint8_t *result);

int kbc_read_command_byte(uint8_t *command_byte);
int kbc_write_command_byte(uint8_t command_byte);

int kbc_read_status(uint8_t *status);

#endif
