#ifndef BANNER_HPP
#define BANNER_HPP

#include "timer.hpp"
#include "vector2.hpp"
#include "config_manager.hpp"
#include "resources_manager.hpp"

class Banner
{
public:
    Banner();
    ~Banner() = default;

    void set_center_position(const Vector2 &pos);

    void on_update(double delta);

    void on_render(SDL_Renderer *renderer);

    bool check_end_dispaly();

private:
    Vector2 pos_center;

    Vector2 size_foreground;
    Vector2 size_background;

    SDL_Texture *tex_foreground = nullptr;
    SDL_Texture *tex_background = nullptr;

    Timer timer_display;
    bool is_end_display = false;
};

#endif // BANNER_HPP