#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow("ex-1.3.1",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         400, 400, SDL_WINDOW_SHOWN);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect r = {190, 100, 20, 20};

    int step = 1;
    int dir = 0;
    int count = 0;
    int side = 90;
    bool running = true;
    bool speedBoost = false;
    bool red = false;

    Uint32 lastTick = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        if (SDL_WaitEventTimeout(&e, 1)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                speedBoost = true;
                red = true;
            } else if (e.type == SDL_KEYUP) {
                speedBoost = false;
                red = false;
            }
        }

        Uint32 now = SDL_GetTicks();
        if (now - lastTick >= 100) {
            lastTick = now;

            int oldStep = step;
            if (speedBoost) step = 2; else step = 1;

            if (dir == 0) r.y += step;
            else if (dir == 1) r.x += step;
            else if (dir == 2) r.y -= step;
            else if (dir == 3) r.x -= step;

            count += step;
            if (count >= side) {
                dir = (dir + 1) % 4;
                count = 0;
            }

            step = oldStep;
        }

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        if (red)
            SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        else
            SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);

        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
