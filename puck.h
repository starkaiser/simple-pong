#ifndef PUCK_H_
#define PUCK_H_

#include "pong.h"
#include "paddle.h"

typedef struct {
    double x;
    double y;
    double r;
    double xspeed;
    double yspeed;  
} Puck;

void puck_show(SDL_Renderer *, Puck *, SDL_Rect *, SDL_Rect *,
               SDL_Texture *, SDL_Texture *, TTF_Font *, int *, int *);
void puck_update(Puck *);
void puck_check_left(Puck *, Paddle *);
void puck_check_right(Puck *, Paddle *);
void puck_reset(Puck *);
void puck_edges(Puck *, int *, int *);
void puck_set_score(int *);
void get_text_and_rect(SDL_Renderer *, int, int, char *,
        TTF_Font *, SDL_Texture **, SDL_Rect *);
#endif