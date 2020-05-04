#pragma once

#include "video_card.h"

/** @defgroup numbers numbers
 * @{
 *
 * @brief Number drawing utilities
 */
#define NUMBERS_LENGTH 56
#define NUMBERS_HEIGHT 32

/**
 * @brief Draws a two-digit number on the given buffer at the given coordinates
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the two-digit image (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the two-digit image (counting rightwards from the left)
 * @param n The two-digit number
 */
void draw_numbers(uint8_t *base_ptr, uint16_t x, uint16_t y, uint8_t n);

/** @} end of numbers */

