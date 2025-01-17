#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "gravity.h"
#include "kbc.h"
#include "keyboard.h"
#include "mouse.h"
#include "vector2.h"
#include "circle.h"

/** @defgroup player player
 * @{
 *
 * @brief Player-related functions
 * 
 * You may be interested in how two players with different input devices (keyboard and mouse)
 * can be represented by the same struct. We have a have an abstraction layer in the struct player
 * (player.input_accelerate , player.input_shooting and player.input_direction_delta) that gets updated
 * with different functions (handle_player1_input(keyboard_packet p1) and handle_player2_input(mouse_packet p2)).
 * 
 * 
 */

#define LEFT_BUTTON_M  0x4b
#define RIGHT_BUTTON_M 0x4d
#define UP_BUTTON_M    0x48
#define SPACEBAR_M     0x39
#define LEFT_BUTTON_B  0xcb
#define RIGHT_BUTTON_B 0xcd
#define UP_BUTTON_B    0xc8
#define SPACEBAR_B     0xb9
#define DIST_FROM_MIDDLE_POINT 20
#define ANGLE_OFFSET 2.5

/**
 * @brief Struct that represents one of our game's players
 * 
 * The players, in our game, are represented by triangles. The reason the players' vertices are
 * stored in the struct is because they necessary, not only for triangle drawing, but also for collision checking.
 * Therefore, for sake of both convenience and efficiency, the players' vertices are only computed once per frame
 * and stored in the struct itself.
 */
typedef struct player
{
  gravity_object state; /**< @brief The position and velocity of the player
                              (the position is actually the triangle's
                              <a href="https://en.wikipedia.org/wiki/Triangle_center#Circumcenter">circumcenter</a>)*/
  float direction; /**< @brief The orientation of the player, in radians*/
  bool alive; /**< @brief Whether or not the player is alive*/

  uint16_t p1x; /**< @brief The x coordinate of the first vertex of the player's triangle*/
  uint16_t p1y; /**< @brief The y coordinate of the first vertex of the player's triangle*/
  uint16_t p2x; /**< @brief The x coordinate of the second vertex of the player's triangle*/
  uint16_t p2y; /**< @brief The y coordinate of the second vertex of the player's triangle*/
  uint16_t p3x; /**< @brief The x coordinate of the third vertex of the player's triangle*/
  uint16_t p3y; /**< @brief The y coordinate of the third vertex of the player's triangle*/

  uint8_t shooting_cooldown; /**< @brief A cooldown counter to prevent the player from shooting every frame. If it is equal to 0, the player can shoot. Decrements once per frame.*/
  uint8_t n_bullets; /**< @brief The number of bullets the player currently has*/

  bool  input_accelerate; /**< @brief Whether or not the player should accelerate this frame*/
  bool  input_shooting; /**< @brief Whether or not the player should fire a shot this frame*/
  float input_direction_delta; /**< @brief By how much should the player turn this frame*/

  uint16_t hp; /**< @brief The health points of the player, measured in pixels*/
}player;

/**
 * @brief It computes the player's triangle's vertices (player.p1x, player.p1y, player.p2x, etc.), given the player's position and orientation
 * @param p A pointer to he player whose vertices are going to get updated
 */
void get_triangle(player *p);

/**
 * @param player The number of the player (either 1 or 2)
 * @return A player pointer
 */
player *get_player(uint8_t player);

/**
 * @brief Updates the players' orientations with the given player.input_direction_delta
 */
void update_players_headings();

/**
 * @brief Updates player 1's inputs.
 * @param p1 The keyboard packet
 */
void handle_player1_input(keyboard_packet p1);

/**
 * @brief Updates player 2's inputs.
 * @param p2 The mouse packet
 */
void handle_player2_input(mouse_packet p2);

/**
 * @brief Draws the players (that are alive) on the given buffer
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_players(uint8_t *base_ptr);

/**
 * @param p A pointer to a player whose heading we want
 * @return The heading as a normalized vector2
 */
vector2 get_player_normalized_heading(player *p);

/**
 * @return true if the players are touching each other, otherwise false
 */
bool players_colide();

/**
 * @param p A pointer to the player we want to check
 * @param circle_x The x coordinate of the circle
 * @param circle_y The y coordinate of the circle
 * @param radius The radius of the circle
 * @return true if the player is touching the circle, otherwise false
 */
bool player_touches_circle(player *p, uint16_t circle_x, uint16_t circle_y, uint16_t radius);

/**
 * @param p A pointer to the player we want to check
 * @return true if the player is hitting the top of the screen, otherwise false
 */
bool player_hits_top(player *p);

/**
 * @param p A pointer to the player we want to check
 * @return true if the player is hitting the bottom of the screen, otherwise false
 */
bool player_hits_bottom(player *p);

/**
 * @param p A pointer to the player we want to check
 * @return true if the player is hitting the right of the screen, otherwise false
 */
bool player_hits_right(player *p);

/**
 * @param p A pointer to the player we want to check
 * @return true if the player is hitting the left of the screen, otherwise false
 */
bool player_hits_left(player *p);

/** @} end of player */
