#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include "button.hpp"
#include "manager.hpp"
#include "game_state.hpp"
#include "button_center.hpp"

#include <vector>
#include <string>
#include <unordered_map>

enum class ButtonID
{
    MENU_StartGame,
    MENU_ExitGame,
    QUIT_callback
};

class ButtonManager : public Manager<ButtonManager>
{
    friend class Manager<ButtonManager>;

public:
    bool load_buttons(SDL_Renderer *renderer)
    {
        button_pool[ButtonID::MENU_StartGame] = new StartGameButton({600, 300, 200, 100}, "../resources/buttons/menu_start_game_idle.png", "../resources/buttons/menu_start_game_hovered.png", "../resources/buttons/menu_start_game_clicked.png");
        button_pool[ButtonID::MENU_ExitGame] = new ExitGameButton({600, 450, 200, 100}, "../resources/buttons/menu_menu_exit_game_idle.png", "../resources/buttons/menu_exit_game_hovered.png", "../resources/buttons/menu_exit_game_clicked.png");
        button_pool[ButtonID::QUIT_callback] =  new CallbackButton({700,240,150,220},"../resources/buttons/quit_call_idle.png","../resources/buttons/quit_call_hovered.png","../resources/buttons/quit_call_pushed.png");
        scene_button_pool[GameState::Menu].push_back(button_pool[ButtonID::MENU_StartGame]);
        scene_button_pool[GameState::Menu].push_back(button_pool[ButtonID::MENU_ExitGame]);
        scene_button_pool[GameState::Quit].push_back(button_pool[ButtonID::QUIT_callback]);

        for (auto &button : button_pool)
        {
            button.second->set_renderer(renderer);
        }
        
        for (const auto &button : button_pool)
        {
            if (!button.second)
                return false;
        }

        return true;
    }

    void on_input(const SDL_Event &event)
    {
        for (auto &button : button_pool)
        {
            button.second->on_input(event);
        }
    }

    void on_render(SDL_Renderer *renderer)
    {
        for (const auto &button : button_pool)
        {
            button.second->on_renderer(renderer);
        }
    }

protected:
    ButtonManager() = default;
    ~ButtonManager() = default;

public:
    std::unordered_map<ButtonID, Button *> button_pool;
    std::unordered_map<GameState, std::vector<Button*>> scene_button_pool;
};

#endif // BUTTON_MANAGER_HPP