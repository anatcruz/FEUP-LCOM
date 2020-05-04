#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "video_card.h"

/** @defgroup circle circle
 * @{
 *
 * @brief Circle drawing and collision-checking functions.
 */

/**
 * @brief Checks whether or not a given point is inside a circle
 * 
 * @param x_pixel The x coordinate of the point to be checked
 * @param y_pixel The y coordinate of the point to be checked
 * @param x1 The x coordinate of the center of the circle
 * @param y1 The y coordinate of the center of the circle
 * @param r  The radius of the circle
 * 
 * @return true if the pixel is inside of the circle, otherwise false
 */
bool local_pixel(uint16_t x_pixel, uint16_t y_pixel,uint16_t x1,uint16_t y1,uint16_t r);

/**
 * @brief Draws a circle on the given buffer with the given center, radius and color
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x1 The x coordinate of the center of the circle
 * @param y1 The y coordinate of the center of the circle
 * @param r  The radius of the circle
 * @param color The color of the circle
 */
void draw_circle(uint8_t *base_ptr,uint16_t x1,uint16_t y1,uint16_t r, uint32_t color);

/** @} end of circle */
