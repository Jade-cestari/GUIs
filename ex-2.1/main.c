#include <SDL2/SDL.h>
#include <stdbool.h>

#define CLICK_TIMEOUT 250
#define MAX_QUADRADOS 1000

typedef struct {
    int clickCount;
    Uint32 lastTime;
    int lastX, lastY;
    bool counting;
} MultiClick;

typedef struct {
    int x, y, tamanho;
} Quadrado;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("ex-2.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

    MultiClick mc = {0,0,0,0,false};
    Quadrado quadrados[MAX_QUADRADOS];
    int count = 0;
    SDL_Event e;
    bool running = true;

    while (running) {
        int timeout = mc.counting ? (CLICK_TIMEOUT - (SDL_GetTicks() - mc.lastTime)) : 10;
        if (timeout < 0) timeout = 0;

        if (SDL_WaitEventTimeout(&e, timeout)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                Uint32 now = SDL_GetTicks();
                if (!mc.counting || now - mc.lastTime > CLICK_TIMEOUT) {
                    mc.clickCount = 1;
                    mc.lastX = e.button.x;
                    mc.lastY = e.button.y;
                    mc.counting = true;
                } else {
                    mc.clickCount++;
                }
                mc.lastTime = now;
            }
        }

        if (mc.counting && SDL_GetTicks() - mc.lastTime > CLICK_TIMEOUT) {
            if (count < MAX_QUADRADOS) {
                int tamanho = mc.clickCount * 20;
                quadrados[count].x = mc.lastX - tamanho/2;
                quadrados[count].y = mc.lastY - tamanho/2;
                quadrados[count].tamanho = tamanho;
                count++;
            }
            mc.counting = false;
            mc.clickCount = 0;
        }

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0xC8, 0x32, 0xC8, 0xFF);
        for (int i=0;i<count;i++) {
            SDL_Rect r = {quadrados[i].x, quadrados[i].y, quadrados[i].tamanho, quadrados[i].tamanho};
            SDL_RenderFillRect(ren, &r);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
