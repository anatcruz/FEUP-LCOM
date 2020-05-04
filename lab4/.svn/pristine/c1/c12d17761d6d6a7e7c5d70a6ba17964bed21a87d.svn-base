#include "utils.h"

#ifdef LAB3
int cnt = 0;

int lab3_n_calls() {
  return kbd_print_no_sysinb(cnt);
}
#endif

int util_sys_inb(int port, uint8_t *value) {
  
  uint8_t space[4];
  //printf("(util_sys_inb) call: port 0x%x\n", port);
  if (sys_inb(port, (uint_fast32_t*)space) == EINVAL)
    return 1;

  *value = space[0];

  #ifdef LAB3
  cnt++;
  #endif

  return 0;
}
