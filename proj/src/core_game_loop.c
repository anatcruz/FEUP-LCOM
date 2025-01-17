#include "core_game_loop.h"

#include "player1wins.xpm"
#include "player2wins.xpm"
#include "nebula.xpm"
#include "draw.xpm"
#include "ammo.xpm"
#include "sun.xpm"


#define BREAK_ESC_KEY 0x81
#define DELTA_T 0.03333333333

enum game_state {playing, player1_wins, player2_wins, tie};

static vector2  screen_center;
static uint8_t *double_buffer;
static uint8_t *background_buffer;
static enum game_state state;
xpm_image_t nebula_background_img;
static xpm_image_t sun_img;
static xpm_image_t player1_wins_img;
static xpm_image_t player2_wins_img;
static xpm_image_t draw_img;
static xpm_image_t ammo_img;

void gravity_step() {
  for (uint8_t player = 1; player < 3; player++) {
    vector2 p1_acc = gravity_acc_vector(screen_center, get_disable_gravity() ? 0 : get_planet_gravity(), &(get_player(player)->state));
    
    if (get_player(player)->input_accelerate) {
        vector2 acc = vector2_scalar_product(get_player_normalized_heading(get_player(player)), get_player_acceleration());
        p1_acc = vector2_add(p1_acc, acc); 
    }
    update_gravity_object(&(get_player(player)->state), p1_acc, DELTA_T);

    get_triangle(get_player(player));
  }

  projectile * proj_array = get_proj_array();
  uint8_t n_projectiles = get_n_projectiles();

  for (uint8_t i = 0; i < n_projectiles; i++) {

    if (proj_array[i].active) {
      vector2 proj_acc = gravity_acc_vector(screen_center, get_disable_gravity() ? 0 : get_planet_gravity(), &(proj_array[i].grav));
      
      update_gravity_object(&(proj_array[i].grav), proj_acc, DELTA_T);
    }
  }

  for (uint8_t b = 1; b < 4; b++) {

    if (get_ammo(b)->active) {
      vector2 proj_acc = gravity_acc_vector(screen_center, get_disable_gravity() ? 0 : get_planet_gravity(), &(get_ammo(b)->grav));
      
      update_gravity_object(&(get_ammo(b)->grav), proj_acc, DELTA_T);
    }
  }
}

void explode_player(uint8_t player) {
  get_player(player)->alive = false;
  get_player(player)->hp    = 0;

  vector2 v1 = {.x = 30, .y = 15},
          v2 = {.x = 20, .y = 5}, 
          v3 = {.x = 15, .y = -13}, 
          v4 = {.x =  3, .y = 20}, 
          v5 = {.x =  -4, .y = -13}, 
          v6 = {.x =  2, .y = -20},
          v7 = {.x = -20, .y = 15}, 
          v8 = {.x = -25, .y = 5}, 
          v9 = {.x = -30, .y = -25};
  
  vector2 pos = get_player(player)->state.position;
  vector2 vec = get_player(player)->state.velocity;

  new_projectile(pos, vector2_add(vec, v1));
  new_projectile(pos, vector2_add(vec, v2));
  new_projectile(pos, vector2_add(vec, v3));
  new_projectile(pos, vector2_add(vec, v4));
  new_projectile(pos, vector2_add(vec, v5));
  new_projectile(pos, vector2_add(vec, v6));
  new_projectile(pos, vector2_add(vec, v7));
  new_projectile(pos, vector2_add(vec, v8));
  new_projectile(pos, vector2_add(vec, v9));
}

void player_deal_damage(uint8_t player, uint16_t damage) {
  if (state == playing) {
    if (get_player(player)->hp < damage) {
      get_player(player)->hp = 0;
      explode_player(player);
      if (player == 1) {
        state = player2_wins;
      } else {
        state = player1_wins;
      }
    } else {
      get_player(player)->hp -= damage;
    }
  }
}

void player_shoot(player *p) {
  vector2 pos, speed;

  pos.x = p->state.position.x + DIST_FROM_MIDDLE_POINT*1.1*sin(p->direction);
  pos.y = p->state.position.y + DIST_FROM_MIDDLE_POINT*1.1*(-cos(p->direction));
  
  speed.x = p->state.velocity.x + get_projectile_shooting_speed()*sin(p->direction);
  speed.y = p->state.velocity.y + get_projectile_shooting_speed()*(-cos(p->direction));
  
  new_projectile(pos, speed);
}

void shooting() {
  for (uint8_t p = 1; p < 3; p++) {
    if (get_player(p)->shooting_cooldown != 0)
      get_player(p)->shooting_cooldown--;
    
    if (get_player(p)->shooting_cooldown == 0 && get_player(p)->input_shooting && get_player(p)->alive && ((get_player(p)->n_bullets != 0) || get_infinite_ammo())) {
      get_player(p)->n_bullets--;
      get_player(p)->shooting_cooldown = get_projectile_shooting_cooldown();
      player_shoot(get_player(p));
    }
  }
}

void collision() {
  uint8_t no_projectiles = get_n_projectiles();
  projectile *projects_array = get_proj_array();

  player* p1 = get_player(1);
  player* p2 = get_player(2);

  static uint8_t players_collide_counter = 0;

  if (players_collide_counter != 0) {
    players_collide_counter--;
  }

  for(uint8_t i = 0; i < no_projectiles; i++){
    if(projects_array[i].active){
      //projetil acertar no jogador 1
      if (p1->alive) {
        if(check_pixel(projects_array[i].grav.position.x,projects_array[i].grav.position.y,
          p1->p1x,p1->p1y,p1->p2x,p1->p2y,p1->p3x,p1->p3y)){
            projects_array[i].active = false;
            player_deal_damage(1, 100);
          }
      }
      //projetil acertar no jogador 2
      if (p2->alive) {
        if(check_pixel(projects_array[i].grav.position.x,projects_array[i].grav.position.y,
          p2->p1x,p2->p1y,p2->p2x,p2->p2y,p2->p3x,p2->p3y)){
            projects_array[i].active = false;
            player_deal_damage(2, 100);
          }
      }
      //projetil acertar no planeta - PROJETIL DEIXA DE ESTAR ATIVO
      if(local_pixel(projects_array[i].grav.position.x,projects_array[i].grav.position.y,screen_center.x,screen_center.y,get_planet_radius()) && (!get_disable_gravity())){
        projects_array[i].active = false;
      }

      if (get_bouncy_walls()) {
        if ((projects_array[i].grav.position.y < 0) && (projects_array[i].grav.velocity.y < 0)) {
          projects_array[i].grav.velocity.y = -projects_array[i].grav.velocity.y;
        }
        if ((projects_array[i].grav.position.y > get_vres()) && (projects_array[i].grav.velocity.y > 0)) {
          projects_array[i].grav.velocity.y = -projects_array[i].grav.velocity.y;
        }
        if ((projects_array[i].grav.position.x < 0) && (projects_array[i].grav.velocity.x < 0)) {
          projects_array[i].grav.velocity.x = -projects_array[i].grav.velocity.x;
        }
        if ((projects_array[i].grav.position.x > get_hres()) && (projects_array[i].grav.velocity.x > 0)) {
          projects_array[i].grav.velocity.x = -projects_array[i].grav.velocity.x;
        }
      }
    }
  }

  if (state == playing){
    //os jogadores colidirem - EMPATE
    if(players_colide() && (players_collide_counter == 0)) {
      if ((p1->hp < 100) && (p2->hp < 100)) {
        players_collide_counter = 15;
        explode_player(1);
        explode_player(2);
        state = tie;
      } else {
        vector2 temp = p1->state.velocity;
        p1->state.velocity = p2->state.velocity;
        p2->state.velocity = temp;

        player_deal_damage(1, 100);
        player_deal_damage(2, 100);
      }
    }
    if (!get_disable_gravity()) {
      //um jogador colidir com o planeta - KABOOOM
      if (player_touches_circle(p1, screen_center.x, screen_center.y, get_planet_radius())) {
        explode_player(1);
        state = player2_wins;
      }
      if (player_touches_circle(p2, screen_center.x, screen_center.y, get_planet_radius())) {
        explode_player(2);
        state = player1_wins;
      }
    }
  }

  for (uint8_t p = 1; p < 3; p++) {
    if (player_hits_top(get_player(p)) && (get_player(p)->state.velocity.y < 0)) {
      get_player(p)->state.velocity.y = -get_player(p)->state.velocity.y;
      player_deal_damage(p, get_disable_wall_damage() ? 0 : 100);
    }
    if (player_hits_bottom(get_player(p)) && (get_player(p)->state.velocity.y > 0)) {
      get_player(p)->state.velocity.y = -get_player(p)->state.velocity.y;
      player_deal_damage(p, get_disable_wall_damage() ? 0 : 100);
    }
    if (player_hits_left(get_player(p)) && (get_player(p)->state.velocity.x < 0)) {
      get_player(p)->state.velocity.x = -get_player(p)->state.velocity.x;
      player_deal_damage(p, get_disable_wall_damage() ? 0 : 100);
    }
    if (player_hits_right(get_player(p)) && (get_player(p)->state.velocity.x > 0)) {
      get_player(p)->state.velocity.x = -get_player(p)->state.velocity.x;
      player_deal_damage(p, get_disable_wall_damage() ? 0 : 100);
    }

    //Ammo caches
    for (uint8_t b = 1; b < 4; b++) {
      if (get_ammo(b)->active) {
        if (player_touches_circle(get_player(p), get_ammo(b)->grav.position.x, get_ammo(b)->grav.position.y, 20)) {
          get_ammo(b)->active = false;
          get_player(p)->n_bullets += get_ammo(b)->n_bullets;
          if (get_player(p)->n_bullets > 99) {
            get_player(p)->n_bullets = 99;
          }
        }
      }
    }
  }

  for (uint8_t b = 1; b < 4; b++) {
      if (get_ammo(b)->active) {
        if (ammo_hits_top(get_ammo(b)) && (get_ammo(b)->grav.velocity.y < 0)) {
          get_ammo(b)->grav.velocity.y = -get_ammo(b)->grav.velocity.y;
        }
        if (ammo_hits_bottom(get_ammo(b)) && (get_ammo(b)->grav.velocity.y > 0)) {
          get_ammo(b)->grav.velocity.y = -get_ammo(b)->grav.velocity.y;
        }
        if (ammo_hits_left(get_ammo(b)) && (get_ammo(b)->grav.velocity.x < 0)) {
          get_ammo(b)->grav.velocity.x = -get_ammo(b)->grav.velocity.x;
        }
        if (ammo_hits_right(get_ammo(b)) && (get_ammo(b)->grav.velocity.x > 0)) {
          get_ammo(b)->grav.velocity.x = -get_ammo(b)->grav.velocity.x;
        }
      }
    }

}

void draw_life_bars(uint8_t *base_ptr) {
  set_rectangle(base_ptr, 0, get_vres() - get_player(1)->hp, 10, get_player(1)->hp, get_player1_color());
  set_rectangle(base_ptr, get_hres() - 10, get_vres() - get_player(2)->hp, 10, get_player(2)->hp, get_player2_color());
}

void draw_transparent_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img, bool invert) {
  uint16_t stop_x = x + img.width;
  uint16_t stop_y = y + img.height;

  uint8_t *img_ptr = img.bytes;
  //printf("HI\n");
  for (; y < stop_y; y++) {
    for (uint16_t temp_x = x; temp_x < stop_x; temp_x++) {
      if (((*(uint32_t*) img_ptr) != 0x00ffffff)) {
        if (invert) {
          set_pixel(base_ptr, temp_x, y, ~(*(uint32_t*) img_ptr));
        } else {
          set_pixel(base_ptr, temp_x, y,   *(uint32_t*) img_ptr);
        }
      }
      img_ptr += get_bytes_per_pixel();
    }
  }
}

void draw_message(uint8_t *base_ptr) {
  switch (state) {
    case player1_wins:
      draw_transparent_image(base_ptr, get_hres() / 2 - player1_wins_img.width / 2, 0, player1_wins_img, true);
      break;
    case player2_wins:
      draw_transparent_image(base_ptr, get_hres() / 2 - player2_wins_img.width / 2, 0, player2_wins_img, true);
      break;
    case tie:
      draw_transparent_image(base_ptr, get_hres() / 2 - draw_img.width / 2, 0, draw_img, true);
      break;
    default:
      break;
  }
}

void draw_ammo_numbers(uint8_t *base_ptr) {
  draw_numbers(base_ptr, 10, 0, get_player(1)->n_bullets);

  draw_numbers(base_ptr, get_hres() - 10 - NUMBERS_LENGTH, 0, get_player(2)->n_bullets);
}

void draw() {
  memcpy(double_buffer, background_buffer, get_hres() * get_vres() * get_bytes_per_pixel());
  draw_life_bars(double_buffer);
  if (!get_infinite_ammo()) {
    draw_ammo_numbers(double_buffer);
  }
  draw_projectiles(double_buffer);
  draw_players(double_buffer);
  draw_ammo(double_buffer);
  draw_message(double_buffer);
  memcpy(get_buffer_base_ptr(), double_buffer, get_hres() * get_vres() * get_bytes_per_pixel());
}

void game_loop() {
  update_players_headings();
  gravity_step();
  shooting();
  collision();
  draw();
}


void draw_sun(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img) {
  uint16_t stop_x = x + img.width;
  uint16_t stop_y = y + img.height;

  uint8_t *img_ptr = img.bytes;

  for (; y < stop_y; y++) {
    for (uint16_t temp_x = x; temp_x < stop_x; temp_x++) {
      if (local_pixel(temp_x, y, get_hres()/2, get_vres()/2, get_planet_radius())) {
        set_pixel(base_ptr, temp_x, y, *(uint32_t*) img_ptr);
      }
      img_ptr += get_bytes_per_pixel();
    }
  }
}

void load_xpms() {
  enum xpm_image_type type = XPM_8_8_8_8;
  if (nebula_background_img.bytes == NULL) {
    xpm_load(nebula_xpm, type, &nebula_background_img);
  }
  if (sun_img.bytes == NULL) {
    xpm_load(sun_xpm, type, &sun_img);
  }
  if (player1_wins_img.bytes == NULL) {
    xpm_load(player1wins_xpm, type, &player1_wins_img);
  }

  if (player2_wins_img.bytes == NULL) {
    xpm_load(player2wins_xpm, type, &player2_wins_img);
  }

  if (draw_img.bytes == NULL) {
    xpm_load(draw_xpm, type, &draw_img);
  }

  if (ammo_img.bytes == NULL) {
    xpm_load(ammo_xpm, type, &ammo_img);
  }
}

void core_game_loop() {
  ///////////////////////
  //Driver initialization
  if (keyboard_ih_subscribe() != 0) return;
  if (timer_ih_subscribe()    != 0) return;
  if (mouse_ih_subscribe()    != 0) return;
  if (rtc_ih_subscribe()      != 0) return;

  uint8_t temp;
  util_sys_inb(KBC_OUT_BUF, &temp);

  rtc_read_reg(RTC_REGISTER_C);
  uint8_t rtc_reg_b = rtc_read_reg(RTC_REGISTER_B);
  uint8_t rtc_seconds_alarm = rtc_read_reg(RTC_SECONDS_ALARM);
  uint8_t rtc_minutes_alarm = rtc_read_reg(RTC_MINUTES_ALARM);
  uint8_t rtc_hours_alarm = rtc_read_reg(RTC_HOURS_ALARM);

  rtc_write_reg(RTC_REGISTER_B, rtc_reg_b | RTC_REG_B_UIE | RTC_REG_B_AIE);
  rtc_write_reg(RTC_SECONDS_ALARM, decimal_to_bcd((bcd_to_decimal(rtc_read_reg(RTC_SECONDS)) + 6) % 60));
  rtc_write_reg(RTC_MINUTES_ALARM, 0xff);
  rtc_write_reg(RTC_HOURS_ALARM  , 0xff);

  int r, ipc_status; // Some variables related to the IH loop
  message msg;

  keyboard_packet k_packet;
  mouse_packet    m_packet;

  if (double_buffer == NULL) {
    double_buffer = (uint8_t *)malloc(get_hres() * get_vres() * get_bytes_per_pixel());
  }
  if (background_buffer == NULL) {
    background_buffer = (uint8_t *)malloc(get_hres() * get_vres() * get_bytes_per_pixel());
  }

  screen_center.x = get_hres() / 2;
  screen_center.y = get_vres() / 2;
  ///////////////////////
  //Game-related stuff initialization
  load_xpms();
  set_xpm_image(background_buffer, 0, 0, nebula_background_img);
  
  if (!get_disable_gravity()) {
    draw_sun(background_buffer, get_hres() / 2 - sun_img.width / 2, get_vres() / 2 - sun_img.height / 2, sun_img);
  }

  if (!get_infinite_ammo()) {
    draw_transparent_image(background_buffer, 10 + NUMBERS_LENGTH, 1, ammo_img, false);
    draw_transparent_image(background_buffer, get_hres() - 10 - NUMBERS_LENGTH - ammo_img.width, 2, ammo_img, false);
  }
  set_player1_color(0x00ff0000);
  set_player2_color(0x0000ff00);

  float radius = 300;
  float v = sqrt(get_planet_gravity()/radius);

  get_player(1)->state.position.x      = get_hres() / 2;
  get_player(1)->state.position.y      = get_vres() / 2 + radius;
  get_player(1)->state.velocity.x      = v;
  get_player(1)->state.velocity.y      = 0;
  get_player(1)->alive                 = true;
  get_player(1)->hp                    = get_vres();
  get_player(1)->input_accelerate      = false;
  get_player(1)->input_shooting        = false;
  get_player(1)->input_direction_delta = 0;
  get_player(1)->n_bullets             = 10;

  get_player(2)->state.position.x      = get_hres() / 2;
  get_player(2)->state.position.y      = get_vres() / 2 - radius;
  get_player(2)->state.velocity.x      = -v;
  get_player(2)->state.velocity.y      = 0;
  get_player(2)->alive                 = true;
  get_player(2)->hp                    = get_vres();
  get_player(2)->input_accelerate      = false;
  get_player(2)->input_shooting        = false;
  get_player(2)->input_direction_delta = 0;
  get_player(2)->n_bullets             = 10;

  get_ammo(1)->active = false;
  get_ammo(2)->active = false;
  get_ammo(3)->active = false;

  state = playing;
  uint8_t game_ended_countdown = 30 * 5;

  projectile_alloc(100);
  ///////////////////////
  //The IH loop itself
  bool esc_key_pressed = false;
  while ((!esc_key_pressed) && (game_ended_countdown != 0))
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
          if (keyboard_ih2(&k_packet)) {
            handle_player1_input(k_packet);

            if ((k_packet.n_bytes == 1) && (k_packet.bytes[0] == BREAK_ESC_KEY)) {
              esc_key_pressed = true;
            }
          }
        }
        if(msg.m_notify.interrupts & MOUSE_MASK)
        {     /*subscribed interrupt*/
          mouse_ih();
          if(mouse_parse_packet(&m_packet)){
            handle_player2_input(m_packet);
          }

        }

        if (msg.m_notify.interrupts & TIMER_MASK)
        {     /*subscribed interrupt*/
          timer_int_handler();
          if (timer_get_counter() % 2 == 0) {
            if (state != playing) {
              game_ended_countdown--;
            }

            game_loop();
          }
        }

        if (msg.m_notify.interrupts & RTC_MASK)
        {     /*subscribed interrupt*/
          if (rtc_ih()) {
            rtc_write_reg(RTC_SECONDS_ALARM, decimal_to_bcd((rtc_get_second() + 12) % 60)); // Move the alarm by 6 seconds
            
            if (!get_infinite_ammo()) {
              spawn_ammo();
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
  ///////////////////////
  //Driver unsubs
  rtc_write_reg(RTC_REGISTER_B   , rtc_reg_b        );
  rtc_write_reg(RTC_SECONDS_ALARM, rtc_seconds_alarm);
  rtc_write_reg(RTC_MINUTES_ALARM, rtc_minutes_alarm);
  rtc_write_reg(RTC_HOURS_ALARM  , rtc_hours_alarm  );
  if (keyboard_ih_unsubscribe() != 0) return;
  if (timer_ih_unsubscribe()    != 0) return;
  if (mouse_ih_unsubscribe()    != 0) return;
  if (rtc_ih_unsubscribe()      != 0) return;
}
