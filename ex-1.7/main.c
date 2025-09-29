#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

bool AUX_WaitEventTimeout(SDL_Event* e, int timeout_ms) {
    Uint32 start = SDL_GetTicks();
    while ((SDL_GetTicks() - start) < (Uint32)timeout_ms) {
        if (SDL_WaitEventTimeout(e, timeout_ms - (SDL_GetTicks() - start))) {
            return true;
        }
    }
    return false;
}

int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("ex-1.7",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "pikachu.png");
    assert(img != NULL);

    int isup = 1;
    int x = -100;
    Uint32 lastTime = SDL_GetTicks();
    SDL_Event event;
    bool rodando = true;

    while (rodando) {
        AUX_WaitEventTimeout(&event, 10);
        if (event.type == SDL_QUIT) break;

        Uint32 now = SDL_GetTicks();
        if (now - lastTime >= 250) {
            x = (x + 10) % 400;
            isup = !isup;
            lastTime = now;
        }

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_Rect r = { x,50, 100,80 };
        SDL_Rect c;
        if (isup) {
            c = (SDL_Rect) { 0,0, 100,80 };
        } else {
            c = (SDL_Rect) { 100,0, 100,80 };
        }
        SDL_RenderCopy(ren, img, &c, &r);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
