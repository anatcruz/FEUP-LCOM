#pragma once

#include <stdio.h>
#include <math.h>
#include <lcom/lab5.h>
#include <lcom/xpm.h>

#include "core_game_settings.h"
#include "projectiles.h"
#include "video_card.h"
#include "keyboard.h"
#include "triangle.h"
#include "vector2.h"
#include "gravity.h"
#include "numbers.h"
#include "circle.h"
#include "player.h"
#include "mouse.h"
#include "timer.h"
#include "utils.h"
#include "ammo.h"
#include "kbc.h"
#include "rtc.h"


/** @defgroup core_game_loop core_game_loop
 * @{
 *
 * @brief Houses all the game logic, physics, collisions, rendering and interrupt-handling functions
 * 
 */

/**
 * @brief The high-level physics function
 * 
 * It updates all of the game objects' position for the next frame (players, projectiles and ammo).
 * One can this of this function as a single step of the physics simulation.
 */
void gravity_step();

/**
 * @brief Explodes one of the players
 * Rather unsurprisingly, calls to this function usually imply the end of the game
 * 
 * @param player The number of the player about to be exploded
 */
void explode_player(uint8_t player);

/**
 * @brief Deals damage one of the players.
 * If the player doesn't have enough HP to take the hit, explode_player(uint8_t player) is called and the game ends.
 * 
 * @param player The number of the player about to be damaged
 * @param damage The amount of damage to be taken by the player, measured in pixels
 */
void player_deal_damage(uint8_t player, uint16_t damage);

/**
 * @brief Spawns a projectile in front of p, with a given velocity
 * 
 * @param p A pointer to the player that wants to shoot
 */
void player_shoot(player *p);


/**
 * @brief The high-level shooting function
 * 
 * For each player it checks if the shooting conditions are met, and if so, calls player_shoot(player *p)
 */
void shooting();

/**
 * @brief The high-level collision-checking function
 * 
 * It performs collision checks and processing for each player, projectile and ammo 
 */
void collision();

/**
 * @brief Draws the players' life bars
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_life_bars(uint8_t *base_ptr);

/**
 * @brief Pretty much the same as set_xpm_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img),
 * with the notable exception that white pixels do not get drawn.
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the xpm image (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the xpm image (counting rightwards from the left)
 * @param img The xpm image (see <a href="https://web.fe.up.pt/~pfs/aulas/lcom2019/labs/lab5/src/doc/structxpm__image__t.html">this</a>)
 * @param invert Whether or not the image pixels should be inverted while drawn (white becomes black, etc)
 */
void draw_transparent_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img, bool invert);

/**
 * @brief If the game ended, displays a message on the top of the screen
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_message(uint8_t *base_ptr);

/**
 * @brief Draws the ammunition numbers, letting them know how many bullets they have
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_ammo_numbers(uint8_t *base_ptr);

/**
 * @brief The high-level frame-rendering function
 * 
 * It copies a background buffer (a buffer with background static stuff) to the double buffer,
 * draws all the game-related objects and UI, and finishes off by copying the double buffer to the frame buffer.
 */
void draw();

/**
 * @brief The high-level game loop function
 * 
 * Gets called every frame
 */
void game_loop();

/**
 * @brief Pretty much the same as set_xpm_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img),
 * with the notable exception that only pixels from a given distance from the center of the screen get drawn
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the xpm image (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the xpm image (counting rightwards from the left)
 * @param img The xpm image (see <a href="https://web.fe.up.pt/~pfs/aulas/lcom2019/labs/lab5/src/doc/structxpm__image__t.html">this</a>)
 */
void draw_sun(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img);

/**
 * @brief Loads the XPMs, if they have not been already loaded
 */
void load_xpms();

/**
 * @brief The highest-level function of this module
 * 
 * It deals not only with interruption subscribing/handling/unsubscribing but also with game related initialization
 */
void core_game_loop();

/** @} end of core_game_loop */
