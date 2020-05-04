#pragma once

#include "video_card.h"
#include "gravity.h"
#include "vector2.h"

/** @defgroup projectiles projectiles
 * @{
 *
 * @brief projectile-related functions
 * 
 * The bullets that you see on screen while playing
 * are allocated here (when you call projectile_alloc(uint8_t n_projectiles))
 * as an array of n_projectiles elements. This array is, in the context of this module,
 * a circular buffer. When projectile_alloc is called, all the projectiles are initialized
 * with the atribute "active" set as false. As the function new_projectile is called,
 * the "active" atribute of more and more elements get set to true. When you want to
 * "delete" a projectile, you simply set that projectile's "active" attribute to false.
 */

/**
 * @brief Struct that represents one of our game's bullets
 */
typedef struct projectile
{
    gravity_object grav; /**< @brief The position and velocity of the bullet*/
    bool active; /**< @brief You can think of this as whether or not the bullet exists*/
} projectile;

/**
 * @return The size of the projectile array
 */
uint8_t get_n_projectiles();

/**
 * @return A pointer to the beginning of the projectile array
 */
projectile *get_proj_array();

/**
 * @return A pointer to the beginning of the projectile array
 */
void projectile_alloc(uint8_t n_projectiles);

/**
 * @brief Spawns a new projectile with the given position and velocity
 * 
 * It overwrites a projectile in buffer with the new position and speed, and sets "active" to true
 * 
 * @param pos The position of the new projectile
 * @param speed The speed of the new projectile
 */
void new_projectile(vector2 pos, vector2 speed);

/**
 * @brief Draws the projectiles on the given buffer
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_projectiles(uint8_t *base_ptr);

/** @} end of projectiles */
