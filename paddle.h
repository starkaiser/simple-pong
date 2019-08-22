#ifndef PADDLE_H_
#define PADDLE_H_

#include "pong.h"

typedef struct {
    short x[4];
    short y[4];
    short ychange;
} Paddle;

void paddle_update(Paddle *);
void paddle_move(Paddle *, short);
void paddle_show(SDL_Renderer *,Paddle *);

#endif