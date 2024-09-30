#define SDL_MAIN_HANDLED

#include <SDL3/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>

bool running = true;

int main()
{
    SDL_Init(SDL_INIT_EVENTS);
    // IMG_Init(IMG_INIT_JPG);
    // Mix_Init(MIX_INIT_MP3);
    // TTF_Init();

    // // 音频采样率，格式，通道数（2为立体声），缓冲区大小（大一些可以提高音频播放的实时性）
    // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window *window = SDL_CreateWindow("test",1280, 720, SDL_WINDOW_RESIZABLE);


}