#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer0_counter=0;
int hook_id=2;


uint8_t get_bits(uint8_t input, uint8_t lower_bit, uint8_t upper_bit) {
    if (lower_bit >= upper_bit || lower_bit < 0 || upper_bit > 8)
        return 255;

    input <<= (8 - upper_bit);
    input >>= (8 - upper_bit);

    input >>= lower_bit;

    return input;
}

uint8_t set_bits(uint8_t input, uint8_t lower_bit, uint8_t upper_bit, uint8_t payload) {
    if (lower_bit >= upper_bit || lower_bit < 0 || upper_bit > 8)
        return 255;
    if ((1 << (upper_bit - lower_bit)) <= payload)
        return 255;
    if ((1 << (upper_bit - lower_bit)) <= payload)
        return 255;
    
    uint8_t bitmask = 1;//Setting up the bitmask
    for (uint8_t i = 1; i < (upper_bit - lower_bit); i++) {
        bitmask <<= 1;
        bitmask |= 1;
        //printf("set_bits debug: bitmask value during loop: 0x%x\n", bitmask);

    }
    //printf("set_bits debug: bitmask value before shift: 0x%x\n", bitmask);
    bitmask <<= lower_bit;
    //printf("set_bits debug: bitmask value: 0x%x\n", bitmask);

    payload <<= lower_bit;

    input &= (~bitmask);
    input |= payload;

    return input;
}

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  //printf("(timer_set_frequency) call arguments: timer: %d, freq: %d\n", timer, freq);

  
  int port;

  switch (timer)
  {
  case 0:
    port = TIMER_0;
    break;

  case 1:
    port = TIMER_1;
    break;
  
  case 2:
    port = TIMER_2;
    break;

  default:
    return 1;
  }
  
  uint8_t conf;

  if (timer_get_conf(timer, &conf) != 0)
    return 1;

  // printf("(timer_set_frequency) debug: conf: 0x%x\n", conf);
  conf = set_bits(conf, 4, 6, 3); //LSB followed by MSB
  conf = set_bits(conf, 6, 8, timer); //Select the timer we want
  // printf("(timer_set_frequency) debug: timer from conf byte: %d\n", get_bits(conf, 6, 8));
  // printf("(timer_set_frequency) debug: conf after manipulation: 0x%x\n", conf);

  uint16_t initial_counter_value = TIMER_FREQ / freq;
  
  uint8_t LSB, MSB;
  util_get_LSB(initial_counter_value, &LSB);
  util_get_MSB(initial_counter_value, &MSB);
    //         write to control register        write LSB                         write MSB
  if (sys_outb(TIMER_CTRL, conf) == EINVAL || sys_outb(port, LSB) == EINVAL || sys_outb(port, MSB) == EINVAL)
    return 1;
  
  return 0;
}


int (timer_subscribe_int)(uint8_t *bit_no) {
     *bit_no=hook_id;
     return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
  
}


void (timer_int_handler)() {
  timer0_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  int port;

  switch (timer)
  {
  case 0:
    port = TIMER_0;
    break;

  case 1:
    port = TIMER_1;
    break;
  
  case 2:
    port = TIMER_2;
    break;

  default:
    return 1;
  }

  uint8_t command = 0;

  command = set_bits(command, 6, 8, 3); // Read-Back Command

  command = set_bits(command, 5, 6, 1); // We don't want count

  command = set_bits(command, timer + 1, timer + 2, 1); // Only one counter

  printf("(timer_get_conf) call: timer-> %d, command-> %x\n", timer, command);

  if (sys_outb(TIMER_CTRL, command) == EINVAL)
    return 1;
  
  uint8_t answer;

  if (util_sys_inb(port, &answer) != 0)
    return 1;

  *st = answer;
  return 0;
  
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val conf;
  switch (field)
  {
  case tsf_all:
    conf.byte = st;
    timer_print_config(timer, field, conf);
    return 0;
  case tsf_initial:
    conf.in_mode = get_bits(st,4,6);
    timer_print_config(timer, field, conf);
    return 0;
  case tsf_mode:
    printf("Mode debug: %d\n", get_bits(st,1,4)); // If 0b110 or 0b111, convert to 0b010 or 0b011
    conf.count_mode = get_bits(st,1,4) > 5 ? get_bits(st,1,4) - 4 : get_bits(st,1,4);
    timer_print_config(timer, field, conf);
    return 0;
  case tsf_base:
    conf.bcd = (get_bits(st,0,1)!=0);
    timer_print_config(timer, field, conf);
    return 0;
  }

}
