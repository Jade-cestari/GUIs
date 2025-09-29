#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool AUX_WaitEventTimeout(SDL_Event* e, int timeout_ms) {
    Uint32 start = SDL_GetTicks();
    while ((SDL_GetTicks() - start) < (Uint32)timeout_ms) {
        if (SDL_WaitEventTimeout(e, timeout_ms - (SDL_GetTicks() - start))) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    srand(time(NULL));

    SDL_Window* window = SDL_CreateWindow("ex-1.6", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 200, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* fonte = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);

    int linhaChegadaX = 500;
    SDL_Rect rect1 = {20, 30, 40, 40};
    SDL_Rect rect2 = {20, 80, 40, 40};
    SDL_Rect rect3 = {20, 130, 40, 40};
    int velocidade1 = rand()%4 + 2;
    int velocidade2 = rand()%4 + 2;
    int velocidade3 = rand()%4 + 2;
    bool chegou1 = false, chegou2 = false, chegou3 = false;
    int vencedor = 0;
    bool rodando = true;
    SDL_Event event;

    while (rodando) {
        AUX_WaitEventTimeout(&event, 10);
        if (event.type == SDL_QUIT) rodando = false;
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            rodando = false;

        if (!chegou1) {
            rect1.x += velocidade1;
            if (rect1.x + rect1.w >= linhaChegadaX) {
                rect1.x = linhaChegadaX - rect1.w;
                chegou1 = true;
                if (vencedor == 0) vencedor = 1;
            }
        }
        if (!chegou2) {
            rect2.x += velocidade2;
            if (rect2.x + rect2.w >= linhaChegadaX) {
                rect2.x = linhaChegadaX - rect2.w;
                chegou2 = true;
                if (vencedor == 0) vencedor = 2;
            }
        }
        if (!chegou3) {
            rect3.x += velocidade3;
            if (rect3.x + rect3.w >= linhaChegadaX) {
                rect3.x = linhaChegadaX - rect3.w;
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

            Uint32 start = SDL_GetTicks();
            while (SDL_GetTicks() - start < 2000) {
                AUX_WaitEventTimeout(&event, 10);
                if (event.type == SDL_QUIT) {
                    rodando = false;
                    break;
                }
            }

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
    }

    TTF_CloseFont(fonte);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
