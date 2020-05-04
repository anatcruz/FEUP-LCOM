#include <stdint.h>
#include <stdbool.h>
#include "mouse.h"
#include "core_game_loop.h"

/** @defgroup Menu Menu
 * @{
 * 
 * @brief Menu-related functions
 */

/**
 * @brief It draws the frame of a rectangle, used for buttons 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the rectangle (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the rectangle (counting rightwards from the left)
 * @param len_x The width of the rectangle
 * @param len_y The height of the rectangle
 * @param len_edge The depth of the frame
 * @param color The color of the rectangle
 */
void set_rectangle_frame(uint8_t *base_ptr, uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y, uint16_t len_edge, uint32_t color);

/**
 * @brief Loads the XPMs for the menus, if they have not been already loaded
 */
void load_xpm_menu();

/**
 * @brief Draws the main menu with the options: play, help, options and exit. It also displays the current time.
 */
void drawMainMenu();

/**
 * @brief Draws the help menu that explains the players' commands.
 */
void drawHelpMenu();

/**
 * @brief Draws the options menu that allows the players to change some settings like if the player s want bouncy walls, infinite ammo, be affected by gravity and if they want wall damage.
 */
void drawOptionsMenu();

/**
 * @brief Checks if a pixel is inside a rectangle
 * @param pixel_x The x coordenate of the pixel
 * @param pixel_y The y coordenate of the pixel
 * @param x The x coordinate of the top left corner of the rectangle (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the rectangle (counting rightwards from the left)
 * @param len_x The width of the rectangle
 * @param len_y The height of the rectangle
 */
bool checkpixel_inbutton(uint16_t pixel_x, uint16_t pixel_y,uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y);
