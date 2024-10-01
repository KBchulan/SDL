#define SDL_MAIN_HANDLED

// 个人头文件
#include "../include/config.hpp"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    // 音频采样率，格式，通道数（2为立体声），缓冲区大小（大一些可以提高音频播放的实时性）

    printf("Mix_OpenAudio error: %s\n", Mix_GetError());

    SDL_Window *window = SDL_CreateWindow(u8"样例程序", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    // 图片从文件加载成SDL_Surface，再通过renderer转换成SDL_Texture
    SDL_Surface *sur_img = IMG_Load("../resources/frame_0.png");
    SDL_Texture *tex_img = SDL_CreateTextureFromSurface(renderer, sur_img);

    // 字体从文件加载成TTF_Font
    TTF_Font *font = TTF_OpenFont("../resources/ipix.ttf", 32);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *sur_text = TTF_RenderText_Blended(font, u8"Hello SDL", color);
    SDL_Texture *tex_text = SDL_CreateTextureFromSurface(renderer, sur_text);

    // 音乐从文件加载成Mix_Chunk
    Mix_Music *music = Mix_LoadMUS("../resources/Skyline.mp3");
    Mix_FadeInMusic(music, -1, 1500);

    SDL_Point mouse_pos = {0, 0};
    SDL_Rect rect_img, rect_text;
    Uint64 last_coiunter = SDL_GetPerformanceCounter();
    Uint64 conter_freq = SDL_GetPerformanceFrequency();

    rect_img.w = sur_img->w;
    rect_img.h = sur_img->h;

    rect_text.w = sur_text->w;
    rect_text.h = sur_text->h;

    while (running)
    {
        // 处理输入
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEMOTION:
                mouse_pos.x = event.motion.x;
                mouse_pos.y = event.motion.y;
                break;

            default:
                break;
            }
        }

        Uint64 current_counter = SDL_GetPerformanceCounter();
        double delta = (current_counter - last_coiunter) / (double)conter_freq;
        last_coiunter = current_counter;

        // 处理数据
        rect_img.x = mouse_pos.x;
        rect_img.y = mouse_pos.y;

        rect_text.x = mouse_pos.x;
        rect_text.y = mouse_pos.y;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 渲染
        SDL_RenderCopy(renderer, tex_img, nullptr, &rect_img);
        filledCircleRGBA(renderer, mouse_pos.x, mouse_pos.y, 50, 212, 56, 113, 125);
        SDL_RenderCopy(renderer, tex_text, nullptr, &rect_text);

        SDL_RenderPresent(renderer);

        if (delta * 1000 < 1000.0 / FPS)
        {
            SDL_Delay((Uint32)(1000.0 / FPS - delta * 1000));
        }
    }

    return 0;
}