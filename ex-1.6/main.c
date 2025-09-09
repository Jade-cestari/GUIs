#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    srand(time(NULL));

    SDL_Window* window = SDL_CreateWindow("ex-1.6",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 200, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    TTF_Font* fonte = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);
  

    int linhaChegadaX = 500;
    SDL_Rect rect1, rect2, rect3;
    int velocidade1, velocidade2, velocidade3;
    bool chegou1, chegou2, chegou3;
    int vencedor;

    rect1 = (SDL_Rect){20, 30, 40, 40};
    rect2 = (SDL_Rect){20, 80, 40, 40};
    rect3 = (SDL_Rect){20, 130, 40, 40};
    velocidade1 = rand()%4 + 2;
    velocidade2 = rand()%4 + 2;
    velocidade3 = rand()%4 + 2;
    chegou1 = chegou2 = chegou3 = false;
    vencedor = 0;

    bool rodando = true;
    SDL_Event event;

    while (rodando) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) rodando = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                rodando = false;
        }

        if (!chegou1) {
            rect1.x += velocidade1;
            if (rect1.x + rect1.w >= linhaChegadaX) {
                chegou1 = true;
                if (vencedor == 0) vencedor = 1;
            }
        }
        if (!chegou2) {
            rect2.x += velocidade2;
            if (rect2.x + rect2.w >= linhaChegadaX) {
                chegou2 = true;
                if (vencedor == 0) vencedor = 2;
            }
        }
        if (!chegou3) {
            rect3.x += velocidade3;
            if (rect3.x + rect3.w >= linhaChegadaX) {
                chegou3 = true;
                if (vencedor == 0) vencedor = 3;
            }
        }

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(ren, linhaChegadaX, 0, linhaChegadaX, 200);

        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect1);
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect2);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(ren, &rect3);

        if (chegou1 && chegou2 && chegou3) {
            char msg[64];
            snprintf(msg, sizeof(msg), "Objeto %d venceu!", vencedor);
            SDL_Color cor = {0x00, 0x00, 0x00, 0xFF};
            SDL_Surface* surf = TTF_RenderUTF8_Blended(fonte, msg, cor);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
            SDL_Rect dst = { (640 - surf->w)/2, (200 - surf->h)/2, surf->w, surf->h };
            SDL_FreeSurface(surf);
            SDL_RenderCopy(ren, tex, NULL, &dst);
            SDL_RenderPresent(ren);
            SDL_Delay(2000);
            SDL_DestroyTexture(tex);
            rect1.x = rect2.x = rect3.x = 20;
            chegou1 = chegou2 = chegou3 = false;
            vencedor = 0;
            velocidade1 = rand()%4 + 2;
            velocidade2 = rand()%4 + 2;
            velocidade3 = rand()%4 + 2;
        } else {
            SDL_RenderPresent(ren);
        }

        SDL_Delay(10);
    }

    TTF_CloseFont(fonte);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
