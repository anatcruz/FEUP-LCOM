#include "circle.h"

//funçao que verifica se o pixel esta dentro do circulo
bool local_pixel(uint16_t x_pixel, uint16_t y_pixel,uint16_t x1,uint16_t y1,uint16_t r){

    float x = x_pixel - x1;
    float y =y_pixel - y1;
    if(x*x + y*y <= r*r)
        return true;
    return false;
}

//funçao para desenhar o planeta
void draw_circle(uint8_t *base_ptr,uint16_t x1,uint16_t y1,uint16_t r, uint32_t color){
    for(int i = x1-r; i < x1+r; i++){
        for(int j = y1-r; j < y1+r; j++){
            if(local_pixel(i,j,x1,y1,r))
                set_pixel(base_ptr,i,j,color);
        }
    }
    
}
