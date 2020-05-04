#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "timer.h"
#include "keyboard.h"
#include "kbc.h"

#define BREAK_ESC_KEY 0x81
extern bool two_byte_scancode;

extern bool    keyboard_make;
extern uint8_t keyboard_size;
extern uint8_t keyboard_bytes[2];

extern int timer_counter;


bool esc_key_pressed = false;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

// int keyboard_user_callback(bool make, uint8_t size, uint8_t *bytes) {
//   //printf("Hi\n");
//   if (bytes[0] == BREAK_ESC_KEY) {
//     esc_key_pressed = true;
//   }

//   return kbd_print_scancode(make, size, bytes);
// }

int(kbd_test_scan)() {

  if (keyboard_ih_subscribe() != 0)
    return 1;
   
  int r, ipc_status;
  message msg;

  while (!esc_key_pressed)
  { /*You may want to use a different condition*/ /*Get a request message.*/
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /*received notification*/
      //printf("HI\n");
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /*hardware interrupt notification*/
        if (msg.m_notify.interrupts & KEYBOARD_MASK)
        {     /*subscribed interrupt*/
          kbc_ih();
        }
        break;
      default:
        break; /*no other notifications expected: do nothing*/
      }
    }
    else
    { /*received a standard message, not a notification*/ /*no standard messages expected: do nothing*/
    }

    if (keyboard_ih2()) {
      if (keyboard_bytes[0] == BREAK_ESC_KEY) {
        esc_key_pressed = true;
      }

      if (kbd_print_scancode(keyboard_make, keyboard_size, keyboard_bytes) != 0) return 1;
    }
  }

  #ifdef LAB3
  if (lab3_n_calls() != 0) return 1;
  #endif

  return keyboard_ih_unsubscribe();
}


int(kbd_test_poll)() {
  
  while (!esc_key_pressed)
  { 
    while (true) { // This infinite (not really) loop basically does the same thing
                   // that driver_receive does in kbd_test_scan: block until something interesting shows up
      uint8_t status;
      if (kbc_read_status(&status) != 0) return 1;
      
      if ((status & KBC_OBF) != 0) break;

      kbc_delay(KBC_TICK_DELAY * 5);
    }

    //kbc_ih(); // Given that this function's logic doesn't depend on 
              // ih function calls whatsoever, we might as well reuse it:)
    kbc_ih();
    if (keyboard_ih2()) {
      if (keyboard_bytes[0] == BREAK_ESC_KEY) {
        esc_key_pressed = true;
      }
      if (kbd_print_scancode(keyboard_make, keyboard_size, keyboard_bytes) != 0) return 1;
    }
  }

  uint8_t command_byte; // Reenabling keyboard interrupts
  if (kbc_read_command_byte(&command_byte) != 0) return 1;

  command_byte |= KBC_COM_BYTE_INT;

  if (kbc_write_command_byte(command_byte) != 0) return 1;


  #ifdef LAB3
  if (lab3_n_calls() != 0) return 1;
  #endif

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  
  int timeout = n * TIMER_INTERRUPT_FREQ;
  printf("timeout %d\n", timeout);

  if (keyboard_ih_subscribe() != 0)
    return 1;
  
  if (timer_ih_subscribe() != 0)
    return 1;
  
  int r, ipc_status;
  message msg;

  while (!esc_key_pressed && timer_counter < timeout)
  { /*You may want to use a different condition*/ /*Get a request message.*/
    // printf("timer counter: %d\n", timer_counter);
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /*received notification*/
      //printf("HI\n");
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /*hardware interrupt notification*/
        if (msg.m_notify.interrupts & KEYBOARD_MASK)
        {     /*subscribed interrupt*/
          kbc_ih();
          timer_counter = 0;
        }
        if (msg.m_notify.interrupts & TIMER_MASK)
        {     /*subscribed interrupt*/
          timer_int_handler();
        }
        break;
      default:
        break; /*no other notifications expected: do nothing*/
      }
    }
    else
    { /*received a standard message, not a notification*/ /*no standard messages expected: do nothing*/
    }

    if (keyboard_ih2()) {
      if (keyboard_bytes[0] == BREAK_ESC_KEY) {
        esc_key_pressed = true;
      }
      if (kbd_print_scancode(keyboard_make, keyboard_size, keyboard_bytes) != 0) return 1;
    }
  }
  
  if (keyboard_ih_unsubscribe() == 0 && timer_ih_unsubscribe() == 0)
    return 0;
  else 
    return 1;
}
