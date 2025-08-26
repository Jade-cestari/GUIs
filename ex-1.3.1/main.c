#include <SDL2/SDL.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("ex-1.3.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect r = {190, 100, 20, 20}; 

    int step = 1;       
    int dir = 0;       
    int count = 0;      
    int side = 90;      

    while (1) {
       
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        SDL_Delay(100);

        if (dir == 0) r.y += step;      
        else if (dir == 1) r.x += step;  
        else if (dir == 2) r.y -= step;  
        else if (dir == 3) r.x -= step;  

        count += step;
        if (count >= side) {
            dir = (dir + 1) % 4;
            count = 0;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
