#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "timer.hpp"
#include "config.hpp"

class Animation
{
public:
    typedef std::function<void()> PlayCallback;

public:
    Animation();
    ~Animation();

    void reset();

    void set_frame_data(SDL_Texture *texture, int num_h, int num_v, const std::vector<int> idx_list);

    void set_loop(bool is_loop);

    void set_interval(double interval);

    void set_on_finished(PlayCallback on_finished);

    void on_update(double delta);

    void on_render(SDL_Renderer *renderer, const SDL_Point &pos_dst, double angle = 0);

private:
    Timer timer;
    bool is_loop = true;
    size_t idx_frame = 0;
    PlayCallback on_finished;
    SDL_Texture *texture = nullptr;
    std::vector<SDL_Rect> rect_src_list;

    int width_frame = 0,
        height_frame = 0;
};

#endif // ANIMATION_HPP