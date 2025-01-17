#include "Menu.h"
#include "video_card.h"
#include "core_game_settings.h"
#include "core_game_loop.h"
#include "rtc.h"
#include <lcom/lab5.h>
#include <lcom/xpm.h>
#include "playbutton.xpm"
#include "helpbutton.xpm"
#include "optionsbutton.xpm"
#include "exitbutton.xpm"
#include "title.xpm"
#include "mouserb.xpm"
#include "mouselb.xpm"
#include "mouse.xpm"
#include "leftarrow.xpm"
#include "rightarrow.xpm"
#include "spacebar.xpm"
#include "right.xpm"
#include "up.xpm"
#include "left.xpm"
#include "player1.xpm"
#include "player2.xpm"
#include "move.xpm"
#include "shoot.xpm"
#include "accelerate.xpm"
#include "back.xpm"
#include "yes.xpm"
#include "no.xpm"
#include "bouncywalls.xpm"
#include "walldamage.xpm"
#include "infiniteammo.xpm"
#include "gravity.xpm"
#include "mousepointer.xpm"
#include "numbers.h"
#include "doispontos.xpm"

extern xpm_image_t nebula_background_img;
static xpm_image_t playbutton_img;
static xpm_image_t helpbutton_img;
static xpm_image_t optionsbutton_img;
static xpm_image_t exitbutton_img;
static xpm_image_t title_img;
static xpm_image_t mouserb_img;
static xpm_image_t mouselb_img;
static xpm_image_t mouse_img;
static xpm_image_t leftarrow_img;
static xpm_image_t rightarrow_img;
static xpm_image_t spacebar_img;
static xpm_image_t right_img;
static xpm_image_t up_img;
static xpm_image_t left_img;
static xpm_image_t player1_img;
static xpm_image_t player2_img;    
static xpm_image_t move_img;
static xpm_image_t shoot_img;
static xpm_image_t accelerate_img;
static xpm_image_t back_img;
static xpm_image_t bouncywalls_img;
static xpm_image_t gravity_img;
static xpm_image_t infiniteammo_img;
static xpm_image_t walldamage_img;
static xpm_image_t yes_img;
static xpm_image_t no_img;
xpm_image_t mousepointer_img;
static xpm_image_t doispontos_img;

static uint8_t *double_buffer;

extern int16_t mouse_x;
extern int16_t mouse_y;

void set_rectangle_frame(uint8_t *base_ptr, uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y, uint16_t len_edge, uint32_t color) {
  set_rectangle(base_ptr, x, y, len_x, len_edge, color);
  set_rectangle(base_ptr, x, y, len_edge, len_y, color);

  set_rectangle(base_ptr, x, y + len_y - len_edge, len_x, len_edge, color);
  set_rectangle(base_ptr, x + len_x - len_edge, y, len_edge, len_y, color);
}

void load_xpm_menu() {
  enum xpm_image_type type = XPM_8_8_8_8;

  if (double_buffer == NULL) {
    double_buffer = (uint8_t *)malloc(get_hres() * get_vres() * get_bytes_per_pixel());
  }

  if (playbutton_img.bytes == NULL) {
    xpm_load(playbutton_xpm, type, &playbutton_img);
  }

  if (helpbutton_img.bytes == NULL) {
    xpm_load(helpbutton_xpm, type, &helpbutton_img);
  }

  if (optionsbutton_img.bytes == NULL) {
    xpm_load(optionsbutton_xpm, type, &optionsbutton_img);
  }

  if (exitbutton_img.bytes == NULL) {
    xpm_load(exitbutton_xpm, type, &exitbutton_img);
  }

  if (title_img.bytes == NULL) {
    xpm_load(title_xpm, type, &title_img);
  }

  if (mouserb_img.bytes == NULL) {
    xpm_load(mouserb_xpm, type, &mouserb_img);
  }

  if (mouselb_img.bytes == NULL) {
    xpm_load(mouselb_xpm, type, &mouselb_img);
  }

  if (mouse_img.bytes == NULL) {
    xpm_load(mouse_xpm, type, &mouse_img);
  }

  if (leftarrow_img.bytes == NULL) {
    xpm_load(leftarrow_xpm, type, &leftarrow_img);
  }

  if (rightarrow_img.bytes == NULL) {
    xpm_load(rightarrow_xpm, type, &rightarrow_img);
  }

  if (spacebar_img.bytes == NULL) {
    xpm_load(spacebar_xpm, type, &spacebar_img);
  }

  if (right_img.bytes == NULL) {
    xpm_load(right_xpm, type, &right_img);
  }

  if (up_img.bytes == NULL) {
    xpm_load(up_xpm, type, &up_img);
  }
  
  if (left_img.bytes == NULL) {
    xpm_load(left_xpm, type, &left_img);
  }

  if (player1_img.bytes == NULL) {
    xpm_load(player1_xpm, type, &player1_img);
  }

  if (player2_img.bytes == NULL) {
    xpm_load(player2_xpm, type, &player2_img);
  }

  if (shoot_img.bytes == NULL) {
    xpm_load(shoot_xpm, type, &shoot_img);
  }

  if (move_img.bytes == NULL) {
    xpm_load(move_xpm, type, &move_img);
  }

  if (accelerate_img.bytes == NULL) {
    xpm_load(accelerate_xpm, type, &accelerate_img);
  }

  if (back_img.bytes == NULL) {
    xpm_load(back_xpm, type, &back_img);
  }

  if (bouncywalls_img.bytes == NULL) {
    xpm_load(bouncywalls_xpm, type, &bouncywalls_img);
  }

  if (gravity_img.bytes == NULL) {
    xpm_load(gravity_xpm, type, &gravity_img);
  }

  if (infiniteammo_img.bytes == NULL) {
    xpm_load(infiniteammo_xpm, type, &infiniteammo_img);
  }

  if (walldamage_img.bytes == NULL) {
    xpm_load(walldamage_xpm, type, &walldamage_img);
  }

  if (yes_img.bytes == NULL) {
    xpm_load(yes_xpm, type, &yes_img);
  }

  if (no_img.bytes == NULL) {
    xpm_load(no_xpm, type, &no_img);
  }

  if (mousepointer_img.bytes == NULL) {
    xpm_load(mousepointer_xpm, type, &mousepointer_img);
  }

  if (doispontos_img.bytes == NULL) {
    xpm_load(doispontos_xpm, type, &doispontos_img);
  }

}

void drawMainMenu(){

  load_xpms();
  load_xpm_menu();
  set_xpm_image(double_buffer, 0, 0, nebula_background_img);
  draw_transparent_image(double_buffer,300,100,title_img,true);
  draw_transparent_image(double_buffer,500,250,playbutton_img,true);
  set_rectangle_frame(double_buffer,500,250,130,80,5,0xb2b2b2);
  draw_transparent_image(double_buffer,500,350,helpbutton_img,true);
  set_rectangle_frame(double_buffer,500,350,130,80,5,0xb2b2b2);
  draw_transparent_image(double_buffer,496,450,optionsbutton_img,true);
  set_rectangle_frame(double_buffer,496,450,145,70,5,0xb2b2b2);
  draw_transparent_image(double_buffer,1000,495,exitbutton_img,true);
  set_rectangle_frame(double_buffer,1000,500,130,80,5,0xb2b2b2);

  
  draw_numbers(double_buffer,30,515,rtc_get_hour());
  draw_transparent_image(double_buffer,80,514,doispontos_img,true);
  draw_numbers(double_buffer,100,515,rtc_get_minute());
  draw_transparent_image(double_buffer,150,514,doispontos_img,true);
  draw_numbers(double_buffer,170,515,rtc_get_second());

  draw_transparent_image(double_buffer,mouse_x,mouse_y,mousepointer_img,true);
  memcpy(get_buffer_base_ptr(), double_buffer, get_hres() * get_vres() * get_bytes_per_pixel());
}

void drawHelpMenu(){
  
  load_xpms();
  load_xpm_menu();
  set_xpm_image(double_buffer, 0, 0, nebula_background_img);
  draw_transparent_image(double_buffer,500,40,helpbutton_img,true);
  
  draw_transparent_image(double_buffer,100,60,player1_img,true);
  draw_transparent_image(double_buffer,850,60,player2_img,true);
  
  draw_transparent_image(double_buffer,480,170,accelerate_img,true);
  draw_transparent_image(double_buffer,510,310,move_img,true);
  draw_transparent_image(double_buffer,515,450,shoot_img,true);
  
  draw_transparent_image(double_buffer,870,160,mouserb_img,true);
  draw_transparent_image(double_buffer,873,300,mouse_img,true);
  draw_transparent_image(double_buffer,819,320,leftarrow_img,true);
  draw_transparent_image(double_buffer,950,320,rightarrow_img,true);
  draw_transparent_image(double_buffer,873,440,mouselb_img,true);

  set_xpm_image(double_buffer,140,170,up_img);
  set_xpm_image(double_buffer,200,300,right_img);
  set_xpm_image(double_buffer,90,300,left_img);
  set_xpm_image(double_buffer,100,469,spacebar_img);

  draw_transparent_image(double_buffer,1000,500,back_img,true);
  set_rectangle_frame(double_buffer,1000,520,130,50,5,0xb2b2b2);

  draw_transparent_image(double_buffer,mouse_x,mouse_y,mousepointer_img,true);
  memcpy(get_buffer_base_ptr(), double_buffer, get_hres() * get_vres() * get_bytes_per_pixel());
}

void drawOptionsMenu(){

  uint32_t GREY = 0xb2b2b2, GREEN = 0x7cfc00;
  
  load_xpms();
  load_xpm_menu();
  set_xpm_image(double_buffer, 0, 0, nebula_background_img);
  draw_transparent_image(double_buffer,500,25,optionsbutton_img,true);

  draw_transparent_image(double_buffer,100,100,bouncywalls_img,true);
  draw_transparent_image(double_buffer,100,200,gravity_img,true);
  draw_transparent_image(double_buffer,100,300,infiniteammo_img,true);
  draw_transparent_image(double_buffer,100,400,walldamage_img,true);

  draw_transparent_image(double_buffer,400,100,yes_img,true);
  set_rectangle_frame(double_buffer,395,100,85,50,5, get_bouncy_walls() ? GREEN : GREY);
  draw_transparent_image(double_buffer,500,99,no_img,true);
  set_rectangle_frame(double_buffer,495,100,85,50,5, get_bouncy_walls() ? GREY : GREEN);

  draw_transparent_image(double_buffer,400,200,yes_img,true);
  set_rectangle_frame(double_buffer,395,200,85,50,5, get_disable_gravity() ? GREY : GREEN);
  draw_transparent_image(double_buffer,500,199,no_img,true);
  set_rectangle_frame(double_buffer,495,200,85,50,5, get_disable_gravity() ? GREEN : GREY);

  draw_transparent_image(double_buffer,400,300,yes_img,true);
  set_rectangle_frame(double_buffer,395,300,85,50,5, get_infinite_ammo() ? GREEN : GREY);
  draw_transparent_image(double_buffer,500,299,no_img,true);
  set_rectangle_frame(double_buffer,495,300,85,50,5, get_infinite_ammo() ? GREY : GREEN);

  draw_transparent_image(double_buffer,400,400,yes_img,true);
  set_rectangle_frame(double_buffer,395,400,85,50,5, get_disable_wall_damage() ? GREY : GREEN);
  draw_transparent_image(double_buffer,500,399,no_img,true);
  set_rectangle_frame(double_buffer,495,400,85,50,5, get_disable_wall_damage() ? GREEN : GREY);

  draw_transparent_image(double_buffer,1000,500,back_img,true);
  set_rectangle_frame(double_buffer,1000,520,130,50,5,0xb2b2b2);

  draw_transparent_image(double_buffer,mouse_x,mouse_y,mousepointer_img,true);
  memcpy(get_buffer_base_ptr(), double_buffer, get_hres() * get_vres() * get_bytes_per_pixel());
}

bool checkpixel_inbutton(uint16_t pixel_x, uint16_t pixel_y,uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y){
  uint16_t top_left_x = x;
  uint16_t top_left_y = y;
  uint16_t bottom_right_x = x + len_x;
  uint16_t bottom_right_y = y + len_y;

  if(pixel_x > top_left_x && pixel_x < bottom_right_x && pixel_y > top_left_y && pixel_y < bottom_right_y){
    return true;
  }

  return false;
}
