#include "player.h"
#include "triangle.h"
#include "core_game_settings.h"
#include "video_card.h"

player player1; //jogador com o teclado
player player2; //jogador com o rato

void get_triangle(player *p){

  float posx = p->state.position.x;
  float posy = p->state.position.y;
  float dir = p->direction;

  p->p1x = posx + get_player_size()*sin(dir);
  p->p2x = posx + get_player_size()*sin(dir + ANGLE_OFFSET);
  p->p3x = posx + get_player_size()*sin(dir-ANGLE_OFFSET);

  p->p1y = posy + get_player_size()*(-cos(dir));
  p->p2y = posy + get_player_size()*(-cos(dir+ANGLE_OFFSET));
  p->p3y = posy + get_player_size()*(-cos(dir-ANGLE_OFFSET));
}

void update_players_headings() {
  player1.direction += player1.input_direction_delta;
  player2.direction += player2.input_direction_delta;
}

player *get_player(uint8_t player){
  if(player == 1)
    return &player1;

  if(player == 2)
    return &player2;
  
  return NULL;
}

void draw_players(uint8_t *base_ptr) {
  float posx, posy, dir;
  uint16_t p1x, p2x, p3x, p1y, p2y, p3y;
  
  if (player1.alive) {
    triangle_draw(base_ptr, player1.p1x,player1.p1y,
                            player1.p2x,player1.p2y,
                            player1.p3x,player1.p3y, 0xc0c0c0c0);
    
    posx = player1.state.position.x;
    posy = player1.state.position.y;
    dir = player1.direction;

    p1x = posx + get_player_size()*sin(dir) * 0.7;
    p2x = posx + get_player_size()*sin(dir + ANGLE_OFFSET) * 0.7;
    p3x = posx + get_player_size()*sin(dir-ANGLE_OFFSET) * 0.7;

    p1y = posy + get_player_size()*(-cos(dir)) * 0.7;
    p2y = posy + get_player_size()*(-cos(dir+ANGLE_OFFSET)) * 0.7;
    p3y = posy + get_player_size()*(-cos(dir-ANGLE_OFFSET)) * 0.7;

    triangle_draw(base_ptr, p1x, p1y, p2x, p2y, p3x, p3y, get_player1_color());
  }

  ///////////////////////////////////////////////////////
  if (player2.alive) {
    triangle_draw(base_ptr, player2.p1x,player2.p1y,
                            player2.p2x,player2.p2y,
                            player2.p3x,player2.p3y, 0xc0c0c0c0);
    
    posx = player2.state.position.x;
    posy = player2.state.position.y;
    dir = player2.direction;

    p1x = posx + get_player_size()*sin(dir) * 0.7;
    p2x = posx + get_player_size()*sin(dir + ANGLE_OFFSET) * 0.7;
    p3x = posx + get_player_size()*sin(dir-ANGLE_OFFSET) * 0.7;

    p1y = posy + get_player_size()*(-cos(dir)) * 0.7;
    p2y = posy + get_player_size()*(-cos(dir+ANGLE_OFFSET)) * 0.7;
    p3y = posy + get_player_size()*(-cos(dir-ANGLE_OFFSET)) * 0.7;

    triangle_draw(base_ptr, p1x, p1y, p2x, p2y, p3x, p3y, get_player2_color());
  }
}

void handle_player1_input(keyboard_packet p1){
  if(!player1.alive)
    return;
  else{
    if(p1.n_bytes == 1){
      switch (p1.bytes[0])
      {
      case SPACEBAR_M:
        player1.input_shooting = true;
        break;
      case SPACEBAR_B:
        player1.input_shooting = false;
        break;
      default:
        break;
      }
    }
    if(p1.n_bytes == 2){
      switch (p1.bytes[1])
      {
      case LEFT_BUTTON_M:
        player1.input_direction_delta = -0.1;
        break;
      case LEFT_BUTTON_B:
        player1.input_direction_delta = 0;
        break;
      case RIGHT_BUTTON_M:
        player1.input_direction_delta = 0.1;
        break;
      case RIGHT_BUTTON_B:
        player1.input_direction_delta = 0;
        break;
      case UP_BUTTON_M:
        player1.input_accelerate = true;
        break;
      case UP_BUTTON_B:
        player1.input_accelerate = false;
        break;
      default:
        break;
      }
    }
  }
}

void handle_player2_input(mouse_packet p2){
  if(!player2.alive)
    return;
  else{
    player2.input_shooting = p2.lb;
    player2.input_accelerate = p2.rb;
    player2.direction += 0.002*p2.delta_x;
  }
}


vector2 get_player_normalized_heading(player *p) {
  vector2 res;
  res.x =  sin(p->direction);
  res.y = -cos(p->direction);

  return res;
}

bool players_colide(){
  if(check_pixel((int16_t)player2.p1x,(int16_t)player2.p1y,(int16_t)player1.p1x,(int16_t)player1.p1y,(int16_t)player1.p2x,(int16_t)player1.p2y,(int16_t)player1.p3x,(int16_t)player1.p3y))
    return true;
  else if(check_pixel((int16_t)player2.p2x,(int16_t)player2.p2y,(int16_t)player1.p1x,(int16_t)player1.p1y,(int16_t)player1.p2x,(int16_t)player1.p2y,(int16_t)player1.p3x,(int16_t)player1.p3y))
    return true;
  else if(check_pixel((int16_t)player2.p3x,(int16_t)player2.p3y,(int16_t)player1.p1x,(int16_t)player1.p1y,(int16_t)player1.p2x,(int16_t)player1.p2y,(int16_t)player1.p3x,(int16_t)player1.p3y))
    return true;
  else if(check_pixel((int16_t)player1.p1x,(int16_t)player1.p1y,(int16_t)player2.p1x,(int16_t)player2.p1y,(int16_t)player2.p2x,(int16_t)player2.p2y,(int16_t)player2.p3x,(int16_t)player2.p3y))
    return true;
  else if(check_pixel((int16_t)player1.p2x,(int16_t)player1.p2y,(int16_t)player2.p1x,(int16_t)player2.p1y,(int16_t)player2.p2x,(int16_t)player2.p2y,(int16_t)player2.p3x,(int16_t)player2.p3y))
    return true;
  else if(check_pixel((int16_t)player1.p3x,(int16_t)player1.p3y,(int16_t)player2.p1x,(int16_t)player2.p1y,(int16_t)player2.p2x,(int16_t)player2.p2y,(int16_t)player2.p3x,(int16_t)player2.p3y))
    return true;

  return false;
}

bool player_touches_circle(player *p, uint16_t circle_x, uint16_t circle_y, uint16_t radius) {
  if(local_pixel(p->p1x,p->p1y, circle_x, circle_y, radius))
    return true;
  if(local_pixel(p->p2x,p->p2y, circle_x, circle_y, radius))
    return true;
  if(local_pixel(p->p3x,p->p3y, circle_x, circle_y, radius))
    return true;
  
  return false;
}



bool dot_hits_top(uint16_t x, uint16_t y) {
  return y > 50000; //underflow
}

bool dot_hits_bottom(uint16_t x, uint16_t y) {
  return (get_vres() < y) && (y < 10000);
}
bool dot_hits_right(uint16_t x, uint16_t y) {
    return (get_hres() < x) && (x < 10000);
}
bool dot_hits_left(uint16_t x, uint16_t y) {
    return x > 50000; //underflow
}

bool player_hits_top(player *p) {
  return dot_hits_top(p->p1x, p->p1y)    || dot_hits_top(p->p2x, p->p2y)    || dot_hits_top(p->p3x, p->p3y);
}
bool player_hits_bottom(player *p) {
  return dot_hits_bottom(p->p1x, p->p1y) || dot_hits_bottom(p->p2x, p->p2y) || dot_hits_bottom(p->p3x, p->p3y);
}
bool player_hits_right(player *p) {
  return dot_hits_right(p->p1x, p->p1y)  || dot_hits_right(p->p2x, p->p2y)  || dot_hits_right(p->p3x, p->p3y);
}
bool player_hits_left(player *p) {
  return dot_hits_left(p->p1x, p->p1y)   || dot_hits_left(p->p2x, p->p2y)   || dot_hits_left(p->p3x, p->p3y);
}
