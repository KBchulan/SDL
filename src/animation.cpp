#include "../include/animation.hpp"

Animation::Animation()
{
    timer.set_one_shot(false);
    timer.set_on_timeout(
        [&]
        {
            idx_frame++;
            if (idx_frame >= rect_src_list.size())
            {
                idx_frame = is_loop ? 0 : rect_src_list.size() - 1;
                if (!is_loop && on_finished)
                {
                    on_finished();
                }
            }
        });
}

Animation::~Animation() = default;

void Animation::reset()
{
    timer.restart();
    idx_frame = 0;
}

void Animation::set_frame_data(SDL_Texture *texture, int num_h, int num_v, const std::vector<int> idx_list)
{
    int width_tex,
        height_tex;

    this->texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &width_tex, &height_tex);
    width_frame = width_tex / num_h;
    height_frame = height_tex / num_v;

    rect_src_list.resize(idx_list.size());
    for (size_t i = 0; i < idx_list.size(); i++)
    {
        int idx = idx_list[i];
        SDL_Rect &rect_src = rect_src_list[i];

        rect_src.x = (idx % num_h) * width_frame;
        rect_src.y = (idx / num_h) * height_frame;
        rect_src.w = width_frame;
        rect_src.h = height_frame;
    }
}

void Animation::set_loop(bool is_loop)
{
    this->is_loop = is_loop;
}

void Animation::set_interval(double interval)
{
    this->timer.set_wait_time(interval);
}

void Animation::set_on_finished(Animation::PlayCallback on_finished)
{
    this->on_finished = on_finished;
}

void Animation::on_update(double delta)
{
    timer.on_update(delta);
}

void Animation::on_render(SDL_Renderer *renderer, const SDL_Point &pos_dst, double angle = 0)
{
    static SDL_Rect rect_dst;

    rect_dst.x = pos_dst.x;
    rect_dst.y = pos_dst.y;
    rect_dst.w = width_frame;
    rect_dst.h = height_frame;

    SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}
