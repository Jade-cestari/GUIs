#include <SDL2/SDL.h>
#include <stdbool.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
    Uint32 inicio = SDL_GetTicks();
    int resultado = SDL_WaitEventTimeout(evt, *ms);
    Uint32 fim = SDL_GetTicks();
    Uint32 decorrido = fim - inicio;
    if (decorrido >= *ms) {
        *ms = 0;
    } else {
        *ms -= decorrido;
    }
    return resultado;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = SDL_CreateWindow("ex-1.5.2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          200, 300, 0);
 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect rect1 = {20, 50, 40, 40};  
    SDL_Rect rect2 = {80, 50, 40, 40};  
    SDL_Rect rect3 = {140, 50, 40, 40};  

    int velocidade = 3;
    bool rodando = true;
    SDL_Event event;

    Uint32 tempoRestante = 50;

    while (rodando) {
        if (AUX_WaitEventTimeoutCount(&event, &tempoRestante)) {
            if (event.type == SDL_QUIT) {
                rodando = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    rodando = false;
            }
        } else {
            tempoRestante = 50;
        }

        rect1.x += 2;
        if (rect1.x > 200) rect1.x = -rect1.w;

        const Uint8* teclado = SDL_GetKeyboardState(NULL);
        if (teclado[SDL_SCANCODE_UP]) rect2.y -= velocidade;
        if (teclado[SDL_SCANCODE_DOWN]) rect2.y += velocidade;
        if (teclado[SDL_SCANCODE_LEFT]) rect2.x -= velocidade;
        if (teclado[SDL_SCANCODE_RIGHT]) rect2.x += velocidade;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        rect3.x = mouseX - rect3.w / 2;
        rect3.y = mouseY - rect3.h / 2;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect1);

        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect2);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &rect3);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
