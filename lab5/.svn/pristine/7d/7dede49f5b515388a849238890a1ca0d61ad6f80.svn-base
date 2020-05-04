#include "video_card.h"

static vbe_mode_info_t inf_memory;

static uint16_t hres;
static uint16_t vres;
static uint8_t bytes_per_pixel;

uint16_t get_hres() {return hres;}
uint16_t get_vres() {return vres;}
vbe_mode_info_t get_inf_memory() {return inf_memory;}



void *(vg_init)(uint16_t mode){

  memset(&inf_memory, 0, sizeof(inf_memory));
  
  if (vbe_get_mode_info(mode,&inf_memory) != 0){
    return NULL;
  }

  int r;
  struct minix_mem_range mr; /* physical memory range */
  unsigned int vram_base = inf_memory.PhysBasePtr; /* VRAM’s physical addresss */

  hres = inf_memory.XResolution;
  vres = inf_memory.YResolution;
  
  bytes_per_pixel = inf_memory.BitsPerPixel/8;
  if ((inf_memory.BitsPerPixel % 8) != 0)
    bytes_per_pixel++; //Round up if necessary

  unsigned int vram_size = hres * vres * bytes_per_pixel; /* VRAM’s size, but you can use the frame-buffer size, instead */
  void *video_mem; /* frame-buffer VM address */
  struct reg86 r86;

  /* Allow memory mapping */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn’t map video memory");

  /* Specify the appropriate register values */
  memset(&r86, 0, sizeof(r86));	/* zero the structure */

  r86.ah = VBE_CALL;
  r86.intno = BIOS_VIDEO_CALL;
  r86.al = SET_VBE_MODE;
  r86.bx = LINER_FRAMEBUFFER | mode;
  r86.ax = 0x4F02;

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return NULL;
  }
    return video_mem;
}

void set_pixel(uint8_t *base_ptr, uint16_t x, uint16_t y, uint32_t color) {
  if ((x >= hres) || (y >= vres)) return; // Out of bounds
  //printf("Hi\n");
  uint8_t *pixel_ptr = base_ptr + ((y * hres) + x) * bytes_per_pixel;

  uint8_t *color_byte = (uint8_t*) &color;

  for (uint8_t i = 0; i < bytes_per_pixel; i++, pixel_ptr++, color_byte++) {
    *pixel_ptr = *color_byte;
  }
}

void set_rectangle(uint8_t *base_ptr,
                   uint16_t x,     uint16_t y, 
                   uint16_t len_x, uint16_t len_y,
                   uint32_t color) {
  uint16_t stop_x = x + len_x;
  uint16_t stop_y = y + len_y;
  
  for (; y < stop_y; y++) {
    for (uint16_t temp_x = x; temp_x < stop_x; temp_x++)
      set_pixel(base_ptr, temp_x, y, color);
  }
}

void set_xpm_image(uint8_t *base_ptr, uint16_t x, uint16_t y, xpm_image_t img) {
  uint16_t stop_x = x + img.width;
  uint16_t stop_y = y + img.height;

  uint8_t *img_ptr = img.bytes;
  //printf("HI\n");
  for (; y < stop_y; y++) {
    for (uint16_t temp_x = x; temp_x < stop_x; temp_x++) {
      set_pixel(base_ptr, temp_x, y, *(uint32_t*) img_ptr);
      img_ptr += bytes_per_pixel;
    }
  }
}
