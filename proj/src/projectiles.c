#include "projectiles.h"
#include "core_game_settings.h"

static uint8_t n_projectiles = 0;

static projectile *proj_array = NULL; // Think of this as a circular buffer

static uint8_t n = 0;

uint8_t get_n_projectiles() {return n_projectiles;}

projectile *get_proj_array() {return proj_array;}

void projectile_alloc(uint8_t n_projectile) {
    if (proj_array != NULL)
        free((void *) proj_array);
    
    n_projectiles = n_projectile;
    proj_array = (projectile *) calloc(n_projectiles, sizeof(projectile));
    // 0 means false. Therefore, active is set to false (that's why I called calloc instead of malloc)
}

void new_projectile(vector2 pos, vector2 speed) {
    if (proj_array == NULL) return;

    n = (n + 1) % n_projectiles;

    proj_array[n].grav.position = pos;
    proj_array[n].grav.velocity = speed;
    proj_array[n].active        = true;
}

void draw_projectile(uint8_t *base_ptr, uint8_t index) {
    if (proj_array[index].active) {
        uint16_t x = proj_array[index].grav.position.x;
        uint16_t y = proj_array[index].grav.position.y;

        if ((x > 10000) || (y > 10000)) // Checking for underflows
            return;

        for (uint16_t i = x - 2; i != x + 2; i++) {
            for (uint16_t j = y - 2; j != y + 2; j++) {
                set_pixel(base_ptr, i, j, get_projectile_color());
            }
        }
    }
}

void draw_projectiles(uint8_t *base_ptr) {
    for (uint8_t i = 0; i < n_projectiles; i++)
        draw_projectile(base_ptr, i);
}
