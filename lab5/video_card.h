#ifndef VIDEO_CARD
#define VIDEO_CARD

#include <lcom/lcf.h>

#define BIOS_VIDEO_CALL 0x10
#define VBE_CALL        0x4f
#define MODE_INF        0x01
#define SET_VBE_MODE    0x02
#define CONTROLLER_INF  0x00
#define LINER_FRAMEBUFFER (0x1<<14)


uint16_t get_vres();
uint16_t get_hres();
vbe_mode_info_t get_inf_memory();

void set_pixel(uint8_t *base_ptr, uint16_t x, uint16_t y, uint32_t color);
void set_rectangle(uint8_t *base_ptr, uint16_t x, uint16_t y, uint16_t len_x, uint16_t len_y, uint32_t color);
void set_xpm_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img);
#endif
