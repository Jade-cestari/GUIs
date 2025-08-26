#include <SDL2/SDL.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("ex-1.3.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect r = {90, 90, 20, 20};
    int step = 10;
    int dir = 0;  

    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        SDL_Delay(100);

        if (dir == 0) { r.x += step; r.y += step; if (r.x >= 110) dir = 1; }
        else if (dir == 1) { r.x -= step; r.y += step; if (r.y >= 110) dir = 2; }
        else if (dir == 2) { r.x -= step; r.y -= step; if (r.x <= 90) dir = 3; }
        else if (dir == 3) { r.x += step; r.y -= step; if (r.y <= 90) dir = 0; }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

