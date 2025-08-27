#include <SDL2/SDL.h>
#include <stdio.h>

#define MAX_RECTS 10

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("ex-1.4.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };  

    SDL_Rect fixedRects[MAX_RECTS];  
    int rectCount = 0;


    SDL_Color rectColors[MAX_RECTS] = {
        {0xFF,0x00,0x00,0xFF}, {0x00,0xFF,0x00,0xFF}, {0x00,0x00,0xFF,0xFF},
        {0xFF,0xFF,0x00,0xFF}, {0xFF,0x00,0xFF,0xFF}, {0x00,0xFF,0xFF,0xFF},
        {0x80,0x00,0x80,0xFF}, {0xFF,0x80,0x00,0xFF}, {0x00,0x80,0x80,0xFF}, {0x80,0x80,0x00,0xFF}
    };

    SDL_Event evt;
    int running = 1;

    while (running) {
        SDL_WaitEvent(&evt);

        switch (evt.type) {
            case SDL_QUIT:
                running = 0;
                break;

            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        r.y -= 5;
                        break;
                    case SDLK_DOWN:
                        r.y += 5;
                        break;
                    case SDLK_LEFT:
                        r.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        r.x += 5;
                        break;
                }

            
                if (r.x < 0) r.x = 0;
                if (r.y < 0) r.y = 0;
                if (r.x + r.w > 200) r.x = 200 - r.w;
                if (r.y + r.h > 100) r.y = 100 - r.h;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (rectCount < MAX_RECTS) {
                    fixedRects[rectCount].x = evt.button.x;
                    fixedRects[rectCount].y = evt.button.y;
                    fixedRects[rectCount].w = 10;
                    fixedRects[rectCount].h = 10;
                    rectCount++;
                }
                break;
        }

       
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);

       
        for (int i = 0; i < rectCount; i++) {
            SDL_Color c = rectColors[i];
            SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
            SDL_RenderFillRect(ren, &fixedRects[i]);
        }

       
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0xFF);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
