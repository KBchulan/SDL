#ifndef GAME_MANAGER_H
#define GANE_MANAGER_H

#include "manager.hpp"
#include "config.hpp"

class GameManager : public Manager<GameManager>
{
    friend class Manager<GameManager>;

public:
    int run(int argc, char **argv)
    {
        // 动态延时实现
        Uint64 last_counter = SDL_GetPerformanceCounter();
        Uint64 quency_counter = SDL_GetPerformanceFrequency();

        while (running)
        {
            // 消息处理
            while (SDL_PollEvent(&event))
            {
                on_input();
            }

            // 数据更新
            Uint64 current_counter = SDL_GetPerformanceCounter();
            double delta = (current_counter - last_counter) / quency_counter;
            last_counter = current_counter;
            on_update(delta);

            // 渲染
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            on_renderer();
            SDL_RenderPresent(renderer);

            if (delta * 1000 < 1000 / FPS)
            {
                SDL_Delay((Uint32)(1000 / FPS - delta));
            }
        }

        return 0;
    }

protected:
    GameManager()
    {
        // 初始化
        init_assert(!TTF_Init(), u8"SDL2_ttf初始化失败!");
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        }
        init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2初始化失败!");
        init_assert(Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_MID), u8"SDL2_mixer初始化失败!");
        init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_JXL | IMG_INIT_TIF), u8"SDL2_image初始化失败!");

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

        window = SDL_CreateWindow("lowr_protect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
        init_assert(window, u8"窗口创建失败!");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        init_assert(renderer, u8"渲染器创建失败!");
    }
    ~GameManager()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        TTF_Quit();
    }

private:
    SDL_Event event;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

private:
    void init_assert(bool flags, const char *error_msg)
    {
        if (flags)
            return;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", error_msg, window);
        exit(-1);
    }

    void on_input()
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
    }

    void on_update(double delta)
    {
    }

    void on_renderer()
    {
    }
};

#endif // GAME_MANAGER_H