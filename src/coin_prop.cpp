#include "../include/coin_prop.hpp"

CoinProp::CoinProp()
{
    timer_jump.set_one_shot(true);
    timer_jump.set_wait_time(interval_jump);
    timer_jump.set_on_timeout(
        [&]()
        {
            is_jumping = false;
        });

    timer_disappear.set_one_shot(true);
    timer_disappear.set_wait_time(interval_disappear);
    timer_disappear.set_on_timeout(
        [&]()
        {
            is_valid = false;
        });

    velocity.x = (rand() % 2 ? 1 : -1) * 2 * TILE_SIZE;
    velocity.y = -3 * TILE_SIZE;
}

void CoinProp::set_position(const Vector2 &position)
{
    this->position = position;
}

const Vector2 &CoinProp::get_position() const
{
    return position;
}

const Vector2 &CoinProp::get_size() const
{
    return size;
}

void CoinProp::make_invalid()
{
    is_valid = false;
}

bool CoinProp::can_remove()
{
    return !is_valid;
}

void CoinProp::on_update(double delta)
{
    timer_jump.on_update(delta);
    timer_disappear.on_update(delta);

    if (is_jumping)
    {
        velocity.y += gravity * delta;
    }
    else
    {
        velocity.x = 0;
        velocity.y = sin(SDL_GetTicks64() / 1000.0 * 4) * 30;
    }

    position += velocity * delta;
}

void CoinProp::on_render(SDL_Renderer *renderer)
{
    static SDL_Rect rect = {0, 0, (int)size.x, (int)size.y};
    static SDL_Texture *tex_coin = ResourcesManager::instance()
                                       ->get_texture_pool()
                                       .find(ResID::Tex_Coin)
                                       ->second;

    rect.x = (int)(position.x - size.x / 2);
    rect.y = (int)(position.y - size.y / 2);

    SDL_RenderCopy(renderer, tex_coin, nullptr, &rect);
}