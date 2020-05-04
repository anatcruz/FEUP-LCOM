#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "video_card.h"
#include "kbc.h"
#include "keyboard.h"

#define BREAK_ESC_KEY 0x81


extern bool two_byte_scancode;

extern bool    keyboard_make;
extern uint8_t keyboard_size;
extern uint8_t keyboard_bytes[2];

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

void wait_for_enter();

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if(vg_init(mode) == NULL){
    vg_exit();
    return 1;
  }
  
  kbc_delay(delay * 1000000);
  vg_exit();
  return 0;
}

int(video_test_rectangle)(uint16_t mode,
                          uint16_t x,     uint16_t y,
                          uint16_t width, uint16_t height,
                          uint32_t color) {
  
  void *base_ptr = vg_init(mode);

  if( base_ptr == NULL){
    vg_exit();
    return 1;
  }
  
  set_rectangle((uint8_t*) base_ptr, x, y, width, height, color);
  
  wait_for_enter();
  vg_exit();
  return 0;
}

int32_t calculate_rect_color(uint16_t mode, uint32_t first, uint8_t step, uint8_t no_rects,
                             uint16_t rect_x, uint16_t rect_y) {
  
  if (mode == 0x105) {
    return (first + (rect_y * no_rects + rect_x) * step) % (1 << 8);
  }

  vbe_mode_info_t useful_info = get_inf_memory();

  uint8_t r_first = (first >> useful_info.RedFieldPosition) % (1 << useful_info.RedMaskSize);
  uint8_t g_first = (first >> useful_info.GreenFieldPosition) % (1 << useful_info.GreenMaskSize);
  uint8_t b_first = (first >> useful_info.BlueFieldPosition) % (1 << useful_info.BlueMaskSize);

  uint32_t red = (r_first + rect_x * step) % (1 << useful_info.RedMaskSize); 
  uint32_t green = (g_first + rect_y * step) % (1 << useful_info.GreenMaskSize);
  uint32_t blue = (b_first + (rect_x + rect_y) * step) % (1 << useful_info.BlueMaskSize);

  return (red   << useful_info.RedFieldPosition)   |
         (green << useful_info.GreenFieldPosition) |
         (blue  << useful_info.BlueFieldPosition);
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  void *base_ptr = vg_init(mode);

  if( base_ptr == NULL){
    vg_exit();
    return 1;
  }
  
  uint16_t lenght = get_hres() / no_rectangles;
  uint16_t height = get_vres() / no_rectangles;

  for (uint8_t rect_x = 0; rect_x < no_rectangles; rect_x++) {
    for (uint8_t rect_y = 0; rect_y < no_rectangles; rect_y++) {
      uint32_t color = calculate_rect_color(mode, first, step, no_rectangles, rect_x, rect_y);
      set_rectangle((uint8_t*) base_ptr, rect_x * lenght, rect_y * height, lenght, height, color);
    }
  }
  
  wait_for_enter();
  vg_exit();
  return 0;
  
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  void *base_ptr = vg_init(0x105);
  //printf("AAAAAAAAAAAAAAAAAAAAAAA\n");
  if( base_ptr == NULL){
    vg_exit();
    return 1;
  }

  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, type, &img);
  if (sprite == NULL) return 1;

  set_xpm_image((uint8_t*) base_ptr, x, y, img);

  wait_for_enter();
  vg_exit();
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}


void wait_for_enter() {

  if (keyboard_ih_subscribe() != 0)
    return;
   
  int r, ipc_status;
  message msg;
  bool esc_key_pressed = false;

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
          if (keyboard_ih2()) {
            if (keyboard_bytes[0] == BREAK_ESC_KEY) {
              esc_key_pressed = true;
            }
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

  keyboard_ih_unsubscribe();
}
