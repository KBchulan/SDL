#define SDL_MAIN_HANDLED

#include "../include/config.hpp"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_MID);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_JXL | IMG_INIT_TIF);
    TTF_Init();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}