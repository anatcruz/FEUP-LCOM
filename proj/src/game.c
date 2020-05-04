#include "game.h"

int16_t mouse_x;
int16_t mouse_y;


extern xpm_image_t mousepointer_img;
enum game {main_menu, help_menu, options_menu, exit_program, core_game};

enum game game_state = main_menu;

void handle_user_input(mouse_packet p1){
  mouse_x += p1.delta_x;
  mouse_y -= p1.delta_y; // It's inverted

  if (mouse_x < 0) {
    mouse_x = 0;
  }
  if (mouse_y < 0) {
    mouse_y = 0;
  }
  if (mouse_x > get_hres()) {
    mouse_x = get_hres();
  }
  if (mouse_y > get_vres()) {
    mouse_y = get_vres();
  }

  static bool wait_for_raised_lb = false;

  if (!p1.lb) {
    wait_for_raised_lb = false;
  }

  if (wait_for_raised_lb) {
    return;
  } else if (p1.lb) {
    wait_for_raised_lb = true;
  }
  if(game_state == main_menu){
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,500,250,130,80)){
      game_state = core_game;
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,500,350,130,80)){
      game_state = help_menu;
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,496,450,145,70)){
      game_state = options_menu;
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,1000,500,130,80)){
      game_state = exit_program;
    }
  }
  else if(game_state == help_menu){
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,1000,520,130,50)){
      game_state = main_menu;
    }
  }
  else if(game_state == options_menu){
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,1000,520,130,50)){
      game_state = main_menu;
    }
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,395,100,85,50)){
      set_bouncy_walls(true);
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,495,100,85,50)){
      set_bouncy_walls(false);
    }
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,395,200,85,50)){
      set_disable_gravity(false);
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,495,200,85,50)){
      set_disable_gravity(true);
    }
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,395,300,85,50)){
      set_infinite_ammo(true);
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,495,300,85,50)){
      set_infinite_ammo(false);
    }
    if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,395,400,85,50)){
      set_disable_wall_damage(false);
    }
    else if(p1.lb && checkpixel_inbutton(mouse_x,mouse_y,495,400,85,50)){
      set_disable_wall_damage(true);
    }
  }
}

void handle_state(){
   
  switch (game_state)
  {
  case core_game:
    if (timer_ih_unsubscribe()    != 0) return;
    if (mouse_ih_unsubscribe()    != 0) return;
    if (rtc_ih_unsubscribe()      != 0) return;
    core_game_loop();
    if (timer_ih_subscribe()    != 0) return;
    if (mouse_ih_subscribe()    != 0) return;
    if (rtc_ih_subscribe()      != 0) return;

    game_state = main_menu;
    break;
  case help_menu:
    drawHelpMenu();
    break;
  case options_menu:
    drawOptionsMenu();
    break;
  case main_menu:
    drawMainMenu();
    break;
  default:
    break;
  }

}


void letsplay(){
  if (timer_ih_subscribe()    != 0) return;
  if (mouse_ih_subscribe()    != 0) return;
  if (rtc_ih_subscribe()    != 0) return;


  uint8_t temp;
  util_sys_inb(KBC_OUT_BUF, &temp);

  rtc_read_reg(RTC_REGISTER_C);
  uint8_t rtc_reg_b = rtc_read_reg(RTC_REGISTER_B);
  rtc_write_reg(RTC_REGISTER_B, rtc_reg_b | RTC_REG_B_UIE);

  int r, ipc_status; // Some variables related to the IH loop
  message msg;

  mouse_packet    m_packet;

  mouse_x = 575;
  mouse_y = 290;

  drawMainMenu();

  while (game_state != exit_program)
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
        if(msg.m_notify.interrupts & MOUSE_MASK)
        {     /*subscribed interrupt*/
          mouse_ih();
          if(mouse_parse_packet(&m_packet)){
            handle_user_input(m_packet);
            //printf("%d\n",game_state);
          }

        }

        if (msg.m_notify.interrupts & TIMER_MASK)
        {     /*subscribed interrupt*/
          timer_int_handler();
          if (timer_get_counter() % 2 == 0) {
            handle_state();
          }
        }

        if (msg.m_notify.interrupts & RTC_MASK)
        {     /*subscribed interrupt*/
          rtc_ih();
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

  rtc_write_reg(RTC_REGISTER_B , rtc_reg_b); // Cleaning up after myself
  if (timer_ih_unsubscribe()    != 0) return;
  if (mouse_ih_unsubscribe()    != 0) return;
  if (rtc_ih_unsubscribe()    != 0) return;
}
