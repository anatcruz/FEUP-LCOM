// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "kbc.h"
#include "timer.h"
#include "mouse_event.h"

extern int timer_counter;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */ 
  if (mouse_ih_subscribe() != 0)
    return 1;
  
  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_ENABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();
  
  struct packet temp;
  
   
  int r, ipc_status;
  message msg;

  while (cnt != 0)
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
        if (msg.m_notify.interrupts & MOUSE_MASK)
        {     /*subscribed interrupt*/
          mouse_ih();

          if (mouse_parse_packet(&temp)) {
            mouse_print_packet(&temp);
            cnt--;
          }
        }
        break;
      default:
        break; /*no other notifications expected: do nothing*/
      }
    }
    else
    { /*received a standard message, not a notification*/ /*no standard messages expected: do nothing*/
    }
  }

  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_DISABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();
  
  return mouse_ih_unsubscribe();
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    
    struct packet temp;

    while(cnt != 0){
      if(mouse_send_command(MOUSE_COM_READ_DATA)!=0) return 1;

      for(int i = 0; i < 3; i++){ // 3 bytes per packet
        
        while(true) { // Wait until OBF and AUX are set
          uint8_t status_byte;
          if(kbc_read_status(&status_byte)!=0) return 1;
          if(((KBC_OBF & status_byte) != 0) && ((KBC_AUX & status_byte) != 0))
            break;
          
          kbc_delay(20 * 1000);
        }

        mouse_ih();
        if (mouse_parse_packet(&temp)) {
          mouse_print_packet(&temp);
          cnt--;
        }
      }

      kbc_delay(period * 1000);
    }

    if(mouse_send_command(MOUSE_COM_SET_STREAM_MODE)!=0) return 1;
    if(mouse_send_command(MOUSE_COM_DISABLE_DATA_REPORTING)!=0) return 1;
    if(kbc_write_command_byte(minix_get_dflt_kbc_cmd_byte())!=0) return 1;
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
   
  if (mouse_ih_subscribe() != 0)
    return 1;

  const int timeout = idle_time * sys_hz();
   
  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_ENABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();

  if(timer_ih_subscribe() != 0)
    return 1;
  
  struct packet temp;
  
   
  int r, ipc_status;
  message msg;

  while (timer_counter < timeout)
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
        if (msg.m_notify.interrupts & MOUSE_MASK)
        {     /*subscribed interrupt*/
          timer_counter = 0;
          mouse_ih();

          if (mouse_parse_packet(&temp)) {
            mouse_print_packet(&temp);
            
          }
        }
        if(msg.m_notify.interrupts & TIMER_MASK){
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
  }

  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_DISABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();
  
  if(timer_ih_unsubscribe() != 0) return 1;
  return mouse_ih_unsubscribe();
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
  
  if (mouse_ih_subscribe() != 0)
    return 1;
  
  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_ENABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();

  struct packet temp;
  
  int r, ipc_status;
  message msg;

  bool yay = false;

  while (!yay)
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
        if (msg.m_notify.interrupts & MOUSE_MASK)
        {     /*subscribed interrupt*/
          mouse_ih();

          if (mouse_parse_packet(&temp)) {
            if (state_machine_process(temp, x_len, tolerance)) yay = true;
            mouse_print_packet(&temp);
          }
        }
        break;
      default:
        break; /*no other notifications expected: do nothing*/
      }
    }
    else
    { /*received a standard message, not a notification*/ /*no standard messages expected: do nothing*/
    }
  }

  mouse_ih_disable();
  if (mouse_send_command(MOUSE_COM_DISABLE_DATA_REPORTING) != 0) return 1;
  mouse_ih_enable();
  
  return mouse_ih_unsubscribe();
}
