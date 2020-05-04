#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "video_card.h"


/** @defgroup triangle triangle
 * @{
 *
 * @brief Triangle drawing and collision-checking functions.
 */

/**
 * @brief Draws a triangle on the given buffer with the given vertices and color
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x1 The x coordinate of the first vertex
 * @param y1 The y coordinate of the first vertex
 * @param x2 The x coordinate of the second vertex
 * @param y2 The y coordinate of the second vertex
 * @param x3 The x coordinate of the third vertex
 * @param y3 The y coordinate of the third vertex
 * @param color The color of the triangle
 */
void triangle_draw(uint8_t *base_ptr,int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint32_t color);

/**
 * @brief Checks whether or not a given point is inside a triangle
 * 
 * @param x_pixel The x coordinate of the point to be checked
 * @param y_pixel The y coordinate of the point to be checked
 * @param x1 The x coordinate of the first vertex of the triangle
 * @param y1 The y coordinate of the first vertex of the triangle
 * @param x2 The x coordinate of the second vertex of the triangle
 * @param y2 The y coordinate of the second vertex of the triangle
 * @param x3 The x coordinate of the third vertex of the triangle
 * @param y3 The y coordinate of the third vertex of the triangle
 * 
 * @return true if the pixel is inside of the triangle, otherwise false
 */
bool check_pixel(float x_pixel, float y_pixel, float x1,float y1,float x2,float y2,float x3,float y3);

/** @} end of triangle */

