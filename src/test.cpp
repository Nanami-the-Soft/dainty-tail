#include "SDL2/SDL.h"


int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;
    SDL_Window * window = nullptr;
    window = SDL_CreateWindow("Dainty Test", SDL_WINDOWPOS_UNDEFINED,
     SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if (window != nullptr) {
        SDL_Renderer * renderer = nullptr;
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer != nullptr) {
            SDL_Event event;
            while (true) {
                if (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) break;
                };
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
            };
            SDL_DestroyRenderer(renderer);
        };
        SDL_DestroyWindow(window);
    };
    SDL_Quit();
};
