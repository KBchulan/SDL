#ifndef BUTTON_CENTER_HPP
#define BUTTON_CENTER_HPP

#include "button.hpp"
#include "game_state.hpp"

extern GameState current_state;

class StartGameButton : public Button
{
public:
    StartGameButton() = default;
    ~StartGameButton() = default;

    StartGameButton(SDL_Rect rect, std::string idle_path, std::string hovered_path, std::string clicked_path)
        : Button(rect, idle_path, hovered_path, clicked_path) {}

protected:
    void on_click() override
    {
        // TODO: start game logic
        current_state = GameState::Game;
    }
};

class ExitGameButton : public Button
{
public:
    ExitGameButton() = default;
    ~ExitGameButton() = default;

    ExitGameButton(SDL_Rect rect, std::string idle_path, std::string hovered_path, std::string clicked_path)
        : Button(rect, idle_path, hovered_path, clicked_path) {}

protected:
    void on_click() override
    {
        // TODO: start game logic
        current_state = GameState::Quit;
    }
};

class CallbackButton final : public Button
{
public:
    CallbackButton() = default;
    ~CallbackButton() = default;

    CallbackButton(SDL_Rect rect, std::string idle_path, std::string hovered_path, std::string clicked_path)
        : Button(rect, idle_path, hovered_path, clicked_path) {}

protected:
    void on_click() override
    {
        current_state = GameState::Menu;
    }
};

#endif // BUTTON_CENTER_HPP