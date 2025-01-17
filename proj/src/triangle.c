#include "triangle.h"

//função para verificar se um pixel esta dentro do triangulo
bool check_pixel(float x_pixel, float y_pixel, float x1,float y1,float x2,float y2,float x3,float y3){
    float E1 = (x_pixel-x1)*(y2-y1)-(y_pixel-y1)*(x2-x1);
    float E2 = (x_pixel-x2)*(y3-y2)-(y_pixel-y2)*(x3-x2);
    float E3 = (x_pixel-x3)*(y1-y3)-(y_pixel-y3)*(x1-x3);

    if((E1 >= 0 && E2 >= 0 && E3 >= 0) || (E1 <= 0 && E2 <= 0 && E3 <= 0))
        return true;

    return false;
}

//funçao para determinar qual de 3 valores é o maior
int16_t give_max(int16_t x1, int16_t x2, int16_t x3){
    int16_t maior = x1;
    if(x2 > maior)
        maior = x2;
    if(x3 > maior)
        maior = x3;
    
    return maior;
}

//funçao para determinar qual de 3 valores é o menor
int16_t give_min(int16_t x1, int16_t x2, int16_t x3){
    int16_t menor = x1;
    if(x2 < menor)
        menor = x2;
    if(x3 < menor)
        menor = x3;
    
    return menor;
}

//funçao para desenhar as naves
void triangle_draw(uint8_t *base_ptr,int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint32_t color){
    int16_t maior_x = give_max(x1,x2,x3);
    int16_t maior_y = give_max(y1,y2,y3);

    int16_t menor_x = give_min(x1,x2,x3);
    int16_t menor_y = give_min(y1,y2,y3);

    for(int i = menor_x; i < maior_x; i++){
        for(int j = menor_y; j < maior_y; j++){
            if(check_pixel(i,j,x1,y1,x2,y2,x3,y3)){
                set_pixel(base_ptr,i,j,color);
            }
        }
    }
}



  
