#include "./pong.h"

void paddle_update(Paddle *paddle){
    
    int i;
    for(i = 0; i < 4; i++){
        if(i == 0 || i == 3)
            if((paddle->y[i] + paddle->ychange) < 0 || (paddle->y[i] + paddle->ychange) > (HEIGHT-100)){
                paddle->ychange = 0;
                paddle->y[i] += paddle->ychange;
            }
            else
                paddle->y[i] += paddle->ychange;

        else
            paddle->y[i] += paddle->ychange;
    }
}

void paddle_move(Paddle *paddle, short steps){
    paddle->ychange = steps;
}

void paddle_show(SDL_Renderer *renderer,Paddle *paddle){
    filledPolygonRGBA(renderer, paddle->x, paddle->y, 4, 255, 255, 255, 255);
}