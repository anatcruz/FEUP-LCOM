#include "ammo.h"
#include "video_card.h"
#include "bullet.xpm"
#include "circle.h"
#include "core_game_settings.h"
#include <math.h>
#include <lcom/xpm.h>

static xpm_image_t bullet_img;

ammo bronze = { .active = false, .radius = 20, .inner_radius = 16 , .color = 0x00cd7f32, .edge_color = 0x00905923, .n_bullets = 5};

ammo silver = { .active = false, .radius = 20, .inner_radius = 16 , .color = 0x00c0c0c0, .edge_color = 0x009a9a9a, .n_bullets = 10};

ammo gold   = { .active = false, .radius = 20, .inner_radius = 16 , .color = 0x00ffd700, .edge_color = 0x00ccac00, .n_bullets = 20};


ammo *get_ammo(uint8_t n) {
  switch (n) {
    case 1:
      return &bronze;
    case 2:
      return &silver;
    case 3:
      return &gold;
    default:
      return NULL;
  }
}


void draw_1ammo(uint8_t *base_ptr, ammo *b) {

  if (bullet_img.bytes == NULL) {
    xpm_load(bullet_xpm, XPM_8_8_8_8, &bullet_img);
  }

  if (!b->active) {
    return;
  }

  draw_circle(base_ptr, b->grav.position.x, b->grav.position.y, b->radius, b->edge_color);
  draw_circle(base_ptr, b->grav.position.x, b->grav.position.y, b->inner_radius, b->color);

  uint16_t x = b->grav.position.x - bullet_img.width / 2;
  uint16_t y = b->grav.position.y - bullet_img.height/ 2;
  
  uint16_t stop_x = x + bullet_img.width;
  uint16_t stop_y = y + bullet_img.height;

  uint8_t *img_ptr = bullet_img.bytes;
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

void draw_ammo(uint8_t *base_ptr) {
    draw_1ammo(base_ptr, &bronze);

    draw_1ammo(base_ptr, &silver);

    draw_1ammo(base_ptr, &gold);
}

void spawn_ammo() {
  for (uint8_t i = 3; i != 0; i--) {
    if (get_ammo(i)->active) {
      continue;
    } else {
      get_ammo(i)->active = true;

      float radius = 0;

      switch (i) {
        case 1:
          radius = 330;
          break;
        case 2:
          radius = 200;
          break;
        case 3:
          radius = 80;
          break;
      }

      float v = sqrt(get_planet_gravity()/radius);

      get_ammo(i)->grav.position.x      = get_hres() / 2;
      get_ammo(i)->grav.position.y      = get_vres() / 2 + radius;
      get_ammo(i)->grav.velocity.x      = v;
      get_ammo(i)->grav.velocity.y      = get_disable_gravity() ? v : 0;
      break;
    }
  }
}

bool ammo_hits_top(ammo *b) {
  return b->grav.position.y < 0 + 20;
}

bool ammo_hits_bottom(ammo *b) {
  return b->grav.position.y > get_vres() -20;
}

bool ammo_hits_left(ammo *b) {
  return b->grav.position.x < 0 + 20;
}

bool ammo_hits_right(ammo *b) {
  return b->grav.position.x > get_hres() -20;
}
