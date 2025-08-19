#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("ex-1.2.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);


    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_Rect r = { 40,20, 10,10 };
    SDL_RenderFillRect(ren, &r);
    

    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0xFF,0x00);
    SDL_Rect r1 = { 80, 20, 20, 15};
    SDL_RenderFillRect(ren, &r1);


    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
    SDL_Rect r2 = { 150, 20, 20, 30};
    SDL_RenderFillRect(ren, &r2);
   

    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0xFF,0x00);
    SDL_RenderDrawLine(ren, 100, 50, 0, 100);


    SDL_SetRenderDrawColor(ren, 0x00,0xA5,0xFF,0x00);
    SDL_RenderDrawLine(ren, 150, 50, 100, 40);   

    SDL_SetRenderDrawColor(ren, 0xFF,0xA5,0x00,0x00);
    SDL_RenderDrawLine(ren, 80, 40, 160, 80); 

    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_RenderDrawPoint(ren, 120, 50);

    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_RenderDrawPoint(ren, 120, 70);

    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_RenderDrawPoint(ren, 80, 50);
   

    SDL_RenderPresent(ren);
    
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
