/* Simple demo program in SDL2 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> // for getpid()
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_keycode.h>

#define RGB 256  // + 1 To get range (0 - 255) with rand() %

//Screen dimension constants
const int SCREEN_WIDTH = 340;
const int SCREEN_HEIGHT = 280;

int fps = 16;

int main( int argc, char* args[] ){
    bool paused = false;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    printf("-\\Dralines/-\n q = quit\n r = reset\n v/b = reduce/increment fps\n p = pause\n\n");
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } 
    else
    {
      //Create window
        window = SDL_CreateWindow( "Drawlines", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    }
        if(!window)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

         renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer) {
            printf("Renderer creation error: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        srand(time(NULL) ^ getpid()); //seed
          
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00); // black bg
        SDL_RenderClear(renderer);
        // Update screen
        SDL_RenderPresent(renderer);
        

    bool quit = false;
    SDL_Event event;
    
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
             if (event.type == SDL_KEYDOWN) {
                SDL_KeyboardEvent key = event.key;

                switch (key.keysym.sym) {

                 // q = quit
                  case SDLK_q:
                    quit = true;
                    break;
                
                 // r = reset
                  case SDLK_r:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00); // Set to black
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    printf("Reset!\n");
                    break;

                // v = reduce fps
                  case SDLK_v:
                  if (fps > 1){
                    fps--;
                    printf("ms per frame: %d\n",fps);
                    }
                    break;
              
               // b = aument fps
                  case SDLK_b:
                  if (fps < 60){
                    fps++;
                    printf("ms per frame: %d\n",fps);
                    }
                    break;
              // p = paused
                case SDLK_p:
                printf("Paused. >_< \n");
                paused = !paused;
                break;
            }
        }
    }        
      if (paused) {
        SDL_Delay(100);       
        continue;          
      }
    //main loop
        SDL_SetRenderDrawColor(renderer, rand() % RGB, rand() % RGB, rand() % RGB, 255);     
    SDL_RenderDrawLine(renderer, rand() % SCREEN_WIDTH + 1, rand() % SCREEN_HEIGHT + 1, rand() % SCREEN_WIDTH + 1, rand() % SCREEN_HEIGHT + 1 );

        SDL_RenderPresent(renderer);

        SDL_Delay(fps); //60 fps - 1000 ms / 60 frames ≈ 16.666... ms per frame
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("o7\n");
    return 0;
}
