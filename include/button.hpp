#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// 仅支持透明背景的按钮
class Button
{
public:
    Button() = default;
    ~Button()
    {
        SDL_DestroyTexture(idle_texture);
        SDL_DestroyTexture(hovered_texture);
        SDL_DestroyTexture(clicked_texture);
    }

    Button(SDL_Rect rect, std::string idle_path, std::string hovered_path, std::string clicked_path)
    {
        this->rect_dst = rect;
        idle_texture = IMG_LoadTexture(renderer, idle_path.c_str());
        hovered_texture = IMG_LoadTexture(renderer, hovered_path.c_str());
        clicked_texture = IMG_LoadTexture(renderer, clicked_path.c_str());
    }

    void set_renderer(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
    }

    void on_input(const SDL_Event &event)
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            if (status == Status::Idle && check_hovered(event.motion.x, event.motion.y))
            {
                status = Status::Hovered;
            }
            if (status == Status::Hovered && !check_hovered(event.motion.x, event.motion.y))
            {
                status = Status::Idle;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (status == Status::Hovered)
            {
                status = Status::Clicked;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (status == Status::Clicked)
            {
                on_click();
                status = Status::Idle;
            }
            break;

        default:
            break;
        }
    }

    // 渲染按钮
    void on_renderer(SDL_Renderer *renderer)
    {
        switch (status)
        {
        case Status::Idle:
            SDL_RenderCopy(renderer, idle_texture, nullptr, &rect_dst);
            break;
        case Status::Hovered:
            SDL_RenderCopy(renderer, hovered_texture, nullptr, &rect_dst);
            break;
        case Status::Clicked:
            SDL_RenderCopy(renderer, clicked_texture, nullptr, &rect_dst);
            break;
        }
    }

protected:
    virtual void on_click() = 0;

private:
    enum class Status
    {
        Idle = 0,
        Hovered,
        Clicked
    };

private:
    SDL_Rect rect_dst;
    SDL_Texture *idle_texture = nullptr;
    SDL_Texture *hovered_texture = nullptr;
    SDL_Texture *clicked_texture = nullptr;
    SDL_Renderer *renderer = nullptr;

    Status status = Status::Idle;

private:
    bool check_hovered(int x, int y)
    {
        return (x >= rect_dst.x && x <= rect_dst.x + rect_dst.w && y >= rect_dst.y && y <= rect_dst.y + rect_dst.h);
    }
};

#endif // BUTTON_HPP