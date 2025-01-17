#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  val &= 0x00ff;

  *lsb = (uint8_t) val;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  val >>= 8;

  *msb = (uint8_t) val;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  
  uint8_t space[4];
  printf("(util_sys_inb) call: port %d\n", port);
  if (sys_inb(port, (uint_fast32_t*)space) == EINVAL)
    return 1;

  *value = space[0];

  return 0;
}
