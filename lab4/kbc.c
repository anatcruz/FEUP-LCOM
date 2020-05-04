#include "kbc.h"

#include <minix/sysutil.h>
#include "utils.h"

void kbc_delay(int delay) {
    tickdelay(micros_to_ticks(delay));
}

//Mildly modified from the slides
int kbc_write_command(uint8_t command) {
  uint8_t status;

  for (int i = 0; i < 4; i++) {
    if (kbc_read_status(&status) != 0) return 1;

    if ((status & KBC_IBF) == 0) {
        sys_outb(KBC_COM_REG, command); /*no args command*/
        return 0;
    }
    
    kbc_delay(KBC_TICK_DELAY);
  }

  return 1;
}

//Mildly modified from the slides
int kbc_write_command_arg(uint8_t arg){
  uint8_t status;

  for (int i = 0; i < 4; i++) {
    if (kbc_read_status(&status) != 0) return 1;

    if ((status & KBC_IBF) == 0) {
        sys_outb(KBC_COM_ARG_REG, arg); /*no args command*/
        return 0;
    }
    
    kbc_delay(KBC_TICK_DELAY);
  }

  return 1;
}

//Mildly modified from the slides
int kbc_read_command_result(uint8_t *result) {
  uint8_t status, data;

  for (int i = 0; i < 4; i++) {
    if (kbc_read_status(&status) != 0) return 1;

    if (status & KBC_OBF) {
      if (util_sys_inb(KBC_OUT_BUF, &data) != 0) return 1;

      if ((status & (KBC_PARITY | KBC_TIMEOUT)) == 0) {
        *result = data;
        return 0;
      }
      else
        return 1;
    }
    kbc_delay(KBC_TICK_DELAY);
  }

  return 1;
}

int kbc_read_command_byte(uint8_t *command_byte) {
    if (kbc_write_command(KBC_DISABLE_KBD_INTERFACE) != 0) return 1;

    if (kbc_write_command(KBC_READ_COM) != 0) return 1;

    if (kbc_read_command_result(command_byte) != 0) return 1;

    if (kbc_write_command(KBC_ENABLE_KBD_INTERFACE) != 0) return 1;
    return 0;    
}

int kbc_write_command_byte(uint8_t command_byte) {
    if (kbc_write_command(KBC_DISABLE_KBD_INTERFACE) != 0) return 1;
    
    if (kbc_write_command(KBC_WRITE_COM) != 0) return 1;

    if (kbc_write_command_arg(command_byte) != 0) return 1;

    if (kbc_write_command(KBC_ENABLE_KBD_INTERFACE) != 0) return 1;
    return 0;
}

int kbc_read_status(uint8_t *status) {
    return util_sys_inb(KBC_STAT_REG, status);
}
