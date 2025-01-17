#pragma once

#include <stdint.h>
#include <stdbool.h>
/** @defgroup core_game_settings core_game_settings
 * @{
 *
 * @brief Global settings that impact the way that core_game_loop runs
 */
/**
 * @return The radius of the planet, in pixels
 */
uint16_t get_planet_radius();
/**
 * @return The <a href="https://en.wikipedia.org/wiki/Standard_gravitational_parameter">gravitational parameter</a> of the planet
 */
float get_planet_gravity();
/**
 * @param g The <a href="https://en.wikipedia.org/wiki/Standard_gravitational_parameter">gravitational parameter</a> of the planet
 */
void  set_planet_gravity(float g);
////////////////////////////////////////
/**
 * @return The velocity at which the projectile exits the player
 */
float get_projectile_shooting_speed();
/**
 * @param speed The velocity at which the projectile exits the player
 */
void  set_projectile_shooting_speed(float speed);
/**
 * @return The numbers of frames between two shots
 */
uint8_t get_projectile_shooting_cooldown();
/**
 * @param cooldown The numbers of frames between two shots
 */
void    set_projectile_shooting_cooldown(uint8_t cooldown);
/**
 * @return The color of the projectiles
 */
uint32_t get_projectile_color();
/**
 * @param color The color of the projectiles
 */
void     set_projectile_color(uint32_t color);
////////////////////////////////////////
/**
 * @return The color of player 1
 */
uint32_t get_player1_color();
/**
 * @param color The color of player 1
 */
void     set_player1_color(uint32_t color);
/**
 * @return The color of player 2
 */
uint32_t get_player2_color();
/**
 * @param color The color of player 2
 */
void     set_player2_color(uint32_t color);
/**
 * @return The players' size
 */
float get_player_size();
/**
 * @param size The players' size
 */
void  set_player_size(float size);
/**
 * @return The players' acceleration
 */
float get_player_acceleration();
/**
 * @param acc The players' acceleration
 */
void  set_player_acceleration(float acc);
////////////////////////////////////////
/**
 * @return Whether or not projectiles bounce back from the walls of the screen
 */
bool get_bouncy_walls();

/**
 * @param bouncy Whether or not projectiles bounce back from the walls of the screen
 */
void set_bouncy_walls(bool bouncy);

/**
 * @return Whether or not gravity is disabled
 */
bool get_disable_gravity();

/**
 * @param disable Whether or not gravity is disabled
 */
void set_disable_gravity(bool disable);

/**
 * @return Whether or not infinite ammo is enabled
 */
bool get_infinite_ammo();

/**
 * @param infinite Whether or not infinite ammo is enabled
 */
void set_infinite_ammo(bool infinite);

/**
 * @return Whether or not wall damage is disabled
 */
bool get_disable_wall_damage();

/**
 * @param damage Whether or not wall damage is disabled
 */
void set_disable_wall_damage(bool damage);

/** @} end of core_game_settings */
