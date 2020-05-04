#include "numbers.h"
#include <lcom/xpm.h>

#include "number0.xpm"
#include "number1.xpm"
#include "number2.xpm"
#include "number3.xpm"
#include "number4.xpm"
#include "number5.xpm"
#include "number6.xpm"
#include "number7.xpm"
#include "number8.xpm"
#include "number9.xpm"


static xpm_image_t number0_img;
static xpm_image_t number1_img;
static xpm_image_t number2_img;
static xpm_image_t number3_img;
static xpm_image_t number4_img;
static xpm_image_t number5_img;
static xpm_image_t number6_img;
static xpm_image_t number7_img;
static xpm_image_t number8_img;
static xpm_image_t number9_img;

void load_nums() {
  enum xpm_image_type type = XPM_8_8_8_8;
  
  if (number0_img.bytes == NULL) {
    xpm_load(number0_xpm, type, &number0_img);
  }

  if (number1_img.bytes == NULL) {
    xpm_load(number1_xpm, type, &number1_img);
  }
  
  if (number2_img.bytes == NULL) {
    xpm_load(number2_xpm, type, &number2_img);
  }
  
  if (number3_img.bytes == NULL) {
    xpm_load(number3_xpm, type, &number3_img);
  }
  
  if (number4_img.bytes == NULL) {
    xpm_load(number4_xpm, type, &number4_img);
  }
  
  if (number5_img.bytes == NULL) {
    xpm_load(number5_xpm, type, &number5_img);
  }
  
  if (number6_img.bytes == NULL) {
    xpm_load(number6_xpm, type, &number6_img);
  }
  
  if (number7_img.bytes == NULL) {
    xpm_load(number7_xpm, type, &number7_img);
  }
  
  if (number8_img.bytes == NULL) {
    xpm_load(number8_xpm, type, &number8_img);
  }
  
  if (number9_img.bytes == NULL) {
    xpm_load(number9_xpm, type, &number9_img);
  }
}

void draw_number(uint8_t *base_ptr, uint16_t x, uint16_t y, uint8_t n) {
  
  xpm_image_t img;
  
  switch(n){
      case 0:
        img = number0_img;
        break;
      case 1:
        img = number1_img;
        break;
      case 2:
        img = number2_img;
        break;
      case 3:
        img = number3_img;
        break;
      case 4:
        img = number4_img;
        break;
      case 5:
        img = number5_img;
        break;
      case 6:
        img = number6_img;
        break;
      case 7:
        img = number7_img;
        break;
      case 8:
        img = number8_img;
        break;
      case 9:
        img = number9_img;
        break;
    default:
        img = number0_img;
        break;
  }

  uint16_t stop_x = x + img.width;
  uint16_t stop_y = y + img.height;

  uint8_t *img_ptr = img.bytes;
  //printf("HI\n");
  for (; y < stop_y; y++) {
    for (uint16_t temp_x = x; temp_x < stop_x; temp_x++) {
      if ((*(uint32_t*) img_ptr) != 0x00ffffff) {
        set_pixel(base_ptr, temp_x, y, ~(*(uint32_t*) img_ptr));
      }
      img_ptr += get_bytes_per_pixel();
    }
  }
}

void draw_numbers(uint8_t *base_ptr, uint16_t x, uint16_t y, uint8_t n) {
    load_nums();
    draw_number(base_ptr, x, y, n / 10);
    draw_number(base_ptr, x + 28, y, n % 10);
}
