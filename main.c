#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include "./pong.h"
#include "./puck.h"
#include "./paddle.h"




int main(int argc, char *argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Pong Game", 100, 100,
                                          WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL){
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(renderer == NULL){
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    //------------------------------------------------------------------------------------

    SDL_Event e;
    SDL_Rect rect1, rect2;
    //SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2;
    //SDL_Window *window;
    char font_path[] = "/usr/share/fonts/truetype/freefont/FreeMonoOblique.ttf";
    bool quit = false;

    /*if (argc == 1) {
        font_path = "FreeSans.ttf";
    } else if (argc == 2) {
        font_path = argv[1];
    } else {
        fprintf(stderr, "error: too many arguments\n");
        exit(EXIT_FAILURE);
    }*/

    Puck puck;
    int score_left = 0;
    int score_right = 0;
    puck_reset(&puck);
    
    Paddle left = {{0, 0, 20, 20}, {HEIGHT/2-50, HEIGHT/2+50, HEIGHT/2+50, HEIGHT/2-50}, 0};
    Paddle right = {{WIDTH-20, WIDTH-20, WIDTH, WIDTH}, {HEIGHT/2-50, HEIGHT/2+50, HEIGHT/2+50, HEIGHT/2-50}, 0};

    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    

    while(!quit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_a:
                            paddle_move(&left, -1);
                            break;
                        case SDLK_z:
                            paddle_move(&left, 1);
                            break;

                        case SDLK_k:
                            paddle_move(&right, -1);
                            break;
                        case SDLK_m:
                            paddle_move(&right, 1);
                            break;
                            
                    }
                    break;

                case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_a:
                            paddle_move(&left, 0);
                            break;
                        case SDLK_z:
                            paddle_move(&left, 0);
                            break;

                        case SDLK_k:
                            paddle_move(&right, 0);
                            break;
                        case SDLK_m:
                            paddle_move(&right, 0);
                            break;
                    }
                    break;

                default: {}
                    
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // drawing on the canvas happens here
        puck_show(renderer, &puck, &rect1, &rect2, texture1, texture2, font, &score_left, &score_right);
        puck_update(&puck);

        puck_edges(&puck, &score_left, &score_right);
        puck_check_left(&puck, &left);
        puck_check_right(&puck, &right);

        paddle_update(&left);
        paddle_update(&right);

        paddle_show(renderer, &left);
        paddle_show(renderer, &right);

        

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}


