#ifndef MENU_MANAGER_HPP
#define MENU_MANAGER_HPP

#include "manager.hpp"
#include "button_manager.hpp"

#include <SDL2/SDL.h>

class MenuManager : public Manager<MenuManager>
{
    friend class Manager<MenuManager>;

public:
    int run(int argc, char **argv)
    {
        button_list = ButtonManager::instance()->scene_button_pool[GameState::Menu];
        Uint64 last_counter = SDL_GetPerformanceCounter();
        const Uint64 counter_freq = SDL_GetPerformanceFrequency();
        while (!is_quit)
        {
            while (SDL_PollEvent(&event))
                on_input(event);

            Uint64 current_counter = SDL_GetPerformanceCounter();
            double delta = (double)(current_counter - last_counter) / counter_freq;
            last_counter = current_counter;
            if (delta * 1000 < 1000.0 / 60)
                SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

            on_update(delta);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            on_render(renderer);

            SDL_RenderPresent(renderer);
        }
        return 0;
    }

protected:
    MenuManager() = default;
    ~MenuManager() = default;

private:
    SDL_Event event;
    SDL_Renderer *renderer;
    bool is_quit = false;

private:
    std::vector<Button *> button_list;

    void on_input(const SDL_Event &event)
    {
        for (auto &button : button_list)
        {
            button->on_input(event);
        }
    }

    void on_update(double)
    {
    }

    void on_render(SDL_Renderer *renderer)
    {
        for (auto &button : button_list)
        {
            button->on_renderer(renderer);
        }
    }
};

#endif // MENU_MANAGER_HPP