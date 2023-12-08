#include "./include/destroy.h"

extern App _app;
extern Sence _sence;

void destroy_resource(void)
{
    SDL_Log("Destroy All Resource.\n");

    SDL_DestroyTexture(_sence._sence_texture);
    SDL_DestroyRenderer(_app._renderer);
    SDL_DestroyWindow(_app._window);

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    SDL_Log("Done.\n");
    exit(EXIT_SUCCESS);
}