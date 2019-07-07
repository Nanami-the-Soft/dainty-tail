#include "SDL2/SDL.h"
#include "pixmap.hpp"


int main()
{
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;
    SDL_Window * window = nullptr;
    window = SDL_CreateWindow("Dainty Test", SDL_WINDOWPOS_UNDEFINED,
     SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (window != nullptr) {
        SDL_Renderer * renderer = nullptr;
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer != nullptr) {
            SDL_SetRenderDrawColor(renderer, 187, 107, 57, 255);
            dainty::PixmapImage image{"test.png"};
            SDL_Surface * surface = nullptr;
            surface = SDL_CreateRGBSurfaceFrom(image.get_data(),
             image.get_width(), image.get_height(), 32, 4 * image.get_width(),
             rmask, gmask, bmask, amask);
            if (surface != nullptr) {
                SDL_Texture * texture = nullptr;
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture != nullptr) {
                    SDL_Event event;
                    while (true) {
                        if (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) break;
                        };
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, 0, 0);
                        SDL_RenderPresent(renderer);
                    };
                    SDL_DestroyTexture(texture);
                };
                SDL_FreeSurface(surface);
            };
            SDL_DestroyRenderer(renderer);
        };
        SDL_DestroyWindow(window);
    };
    SDL_Quit();
};
