#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = SDL_CreateWindow("Exemplo SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          200, 300, 0);

    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect rect1 = {20, 50, 40, 40};
    SDL_Rect rect2 = {80, 50, 40, 40};
    SDL_Rect rect3 = {140, 50, 40, 40};

    int velocidade = 3;
    bool rodando = true;
    SDL_Event event;

    while (rodando) {
        if (SDL_WaitEventTimeout(&event, 10)) {
            if (event.type == SDL_QUIT) {
                rodando = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    rodando = false;
            }
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

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect1);

        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect2);

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(ren, &rect3);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
