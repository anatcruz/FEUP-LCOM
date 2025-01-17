#include "gravity.h"
#include "stdint.h"
#include <stdbool.h>


/** @defgroup ammo ammo
 * @{
 *
 * @brief Ammo-related functions
 * 
 */

/**
 * @brief Struct that represents one of the ammo "balls" that give you more bullets
 */
typedef struct ammo
{
    gravity_object grav; /**< @brief The position and velocity of the ammo*/
    bool active; /**< @brief You can think of this as whether or not the ammo exists*/
    float radius; /**< @brief The radius of the outer circle*/
    float inner_radius; /**< @brief The radius of the inner circle (for rendering purposes)*/
    uint32_t color;  /**< @brief The color of the ammo (gold, silver or bronze)*/
    uint32_t edge_color; /**< @brief The color of the edge of the ammo (darker than the main color)*/
    uint8_t n_bullets; /**< @brief The number of bullets this ammo gives*/
} ammo;


/**
 * @param n either 1, 2 or 3
 * @return An ammo pointer
 */
ammo *get_ammo(uint8_t n);

/**
 * @brief Draws the ammo "balls" (that are active) on the given buffer
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 */
void draw_ammo(uint8_t *base_ptr);

/**
 * @brief Spawns an ammo "ball"
 */
void spawn_ammo();

/**
 * @param b A pointer to the ammo we want to check
 * @return true if the ammo is hitting the top of the screen, otherwise false
 */
bool ammo_hits_top(ammo *b);

/**
 * @param b A pointer to the ammo we want to check
 * @return true if the ammo is hitting the bottom of the screen, otherwise false
 */
bool ammo_hits_bottom(ammo *b);

/**
 * @param b A pointer to the ammo we want to check
 * @return true if the ammo is hitting the left of the screen, otherwise false
 */
bool ammo_hits_left(ammo *b);

/**
 * @param b A pointer to the ammo we want to check
 * @return true if the ammo is hitting the right of the screen, otherwise false
 */
bool ammo_hits_right(ammo *b);

/** @} end of ammo */
