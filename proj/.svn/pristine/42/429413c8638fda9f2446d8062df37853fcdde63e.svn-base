#ifndef VIDEO_CARD
#define VIDEO_CARD

#include <lcom/lcf.h>

#define BIOS_VIDEO_CALL 0x10
#define VBE_CALL        0x4f
#define MODE_INF        0x01
#define SET_VBE_MODE    0x02
#define CONTROLLER_INF  0x00
#define LINER_FRAMEBUFFER (0x1<<14)


/** @defgroup video_card video_card
 * @{
 *
 * @brief Functions related to graphic mode initialization and frame buffer modification.
 * 
 * All the functions provided have buffer boundary checks, which means that they are (as far as I'm concerned) safe to use given bogus coordinates
 */

/**
 * @return The vertical resolution of the screen
 */
uint16_t get_vres();

/**
 * @return The horizontal resolution of the screen
 */
uint16_t get_hres();

/**
 * @return The number of bytes per pixel
 */
uint16_t get_bytes_per_pixel();

/**
 * @return The size of the buffer, in bytes
 * 
 * Instead of this function, you may want to do get_vres() * get_hres() * get_bytes_per_pixel() for the same outcome.
 */
uint16_t get_buffer_size();

/**
 * @return A pointer to the frame buffer
 */
uint8_t* get_buffer_base_ptr();

/**
 * @brief Sets the pixel of the given buffer at the given coordinates to the given color
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the pixel (counting downwards from the top)
 * @param y The y coordinate of the pixel (counting rightwards from the left)
 * @param color The color to which the pixel will be set
 */
void set_pixel(uint8_t *base_ptr, uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a rectangle on the given buffer at the given coordinates with the given lenght and height to the given color
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the rectangle (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the rectangle (counting rightwards from the left)
 * @param len_x The width of the rectangle
 * @param len_y The height of the rectangle
 * @param color The color of the rectangle
 */
void set_rectangle(uint8_t *base_ptr, uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y, uint32_t color);

/**
 * @brief Draws the given xpm image on the given buffer at the given coordinates
 * 
 * @param base_ptr A pointer to a buffer (must be equal in size to the frame buffer)
 * @param x The x coordinate of the top left corner of the xpm image (counting downwards from the top)
 * @param y The y coordinate of the top left corner of the xpm image (counting rightwards from the left)
 * @param img The xpm image (see <a href="https://web.fe.up.pt/~pfs/aulas/lcom2019/labs/lab5/src/doc/structxpm__image__t.html">this</a>)
 */
void set_xpm_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img);

/**
 * @brief Sets all the bytes of the frame buffer to 0, meaning that the screen turns black
 */
void clean_screen();

/** @} end of video_card */

#endif
