#include "./pong.h"
#define SPEED 5

double to_radians(double degrees){
    return degrees * (M_PI/180.0);
}
void puck_show(SDL_Renderer *renderer, Puck *puck, SDL_Rect *rect1, SDL_Rect *rect2,
               SDL_Texture *texture1, SDL_Texture *texture2, TTF_Font *font, int *score_left, int *score_right){
    filledCircleRGBA(renderer, puck->x, puck->y, puck->r, 255, 255, 255, 255);
    char score_l[50], score_r[50];
    sprintf(score_l, "%d", *score_left);
    sprintf(score_r, "%d", *score_right);
    get_text_and_rect(renderer, 30, 0, score_l, font, &texture1, rect1);
    get_text_and_rect(renderer, WIDTH-50, 0, score_r, font, &texture2, rect2);
    SDL_RenderCopy(renderer, texture1, NULL, rect1);
    SDL_RenderCopy(renderer, texture2, NULL, rect2);
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
    TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

void puck_set_score(int *score){
    (*score)++; 
}

void puck_update(Puck *puck){
    puck->x += puck->xspeed;
    puck->y += puck->yspeed;
}

void puck_edges(Puck *puck, int *left, int *right){
    if(puck->y < 0 || puck->y > HEIGHT)
        puck->yspeed *= -1;

    if(puck->x - puck->r > WIDTH){ 
        puck_reset(puck);
        puck_set_score(left);
    }

    else if(puck->x + puck->r < 0){
        puck_reset(puck);
        puck_set_score(right);
    }
}

void puck_check_right(Puck *puck, Paddle *paddle){
    if((puck->y - puck->r) < paddle->y[1] &&
       (puck->y + puck->r) > paddle->y[0] &&
       (puck->x + puck->r) > paddle->x[0]){
           if(puck->x < paddle->x[0] + 10){
               double diff = puck->y - (double)paddle->y[0];
                double angle;
                double cell = 100.0/8.0;
                if(diff >= 0 && diff <= cell)
                    angle = to_radians(-135.0);
                else if(diff > cell && diff <= 2*cell)
                    angle = to_radians(-150.0);
                else if(diff > 2*cell && diff <= 3*cell)
                    angle = to_radians(-165.0);
                else if(diff > 3*cell && diff <= 5*cell)
                    angle = to_radians(180.0);
                else if(diff > 5*cell && diff <= 6*cell)
                    angle = to_radians(165.0);
                else if(diff > 6*cell && diff <= 7*cell)
                    angle = to_radians(150.0);
                else if(diff > 7*cell && diff <= 100.0)
                    angle = to_radians(135.0);
                
                puck->xspeed = SPEED * cos(angle);
                puck->yspeed = SPEED * sin(angle);
                puck->x = (double)paddle->x[0] - puck->r;
            }
       }
}

void puck_check_left(Puck *puck, Paddle *paddle){
    double puck_x = puck->x;
    double puck_y = puck->y;
    double puck_r = puck->r;

    if((puck_y - puck_r) < paddle->y[1] && 
       (puck_y + puck_r) > paddle->y[0] && 
       (puck_x - puck_r) < paddle->x[3]){
        if(puck_x > (paddle->x[0] + 10)){
            double diff = puck_y - (double)paddle->y[0];
            double angle;
            double cell = 100.0/8.0;
            if(diff >= 0 && diff <= cell)
                angle = to_radians(-45.0);
            else if(diff > cell && diff <= 2*cell)
                angle = to_radians(-30.0);
            else if(diff > 2*cell && diff <= 3*cell)
                angle = to_radians(-15.0);
            else if(diff > 3*cell && diff <= 5*cell)
                angle = to_radians(0.0);
            else if(diff > 5*cell && diff <= 6*cell)
                angle = to_radians(15.0);
            else if(diff > 6*cell && diff <= 7*cell)
                angle = to_radians(30.0);
            else if(diff > 7*cell && diff <= 100.0)
                angle = to_radians(45.0);
            puck->xspeed = SPEED * cos(angle);
            puck->yspeed = SPEED * sin(angle);
            puck->x = (double)paddle->x[3] + puck_r;
        }
    }
}

void puck_reset(Puck *puck){
    puck->x = WIDTH / 2;
    puck->y = HEIGHT / 2;

    time_t t;
    srand(time(&t));
    puck->r = 8;

    double angle = (double)rand()/RAND_MAX*(M_PI/2.0) - M_PI/4.0;

    puck->xspeed = SPEED * cos(angle);
    puck->yspeed = SPEED * sin(angle);

    if((rand()%1) < 0.5)
        puck->xspeed *= -1;
}
