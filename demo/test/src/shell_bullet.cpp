#include "../include/shell_bullet.hpp"

ShellBullet::ShellBullet()
{
    static SDL_Texture *tex_shell = ResourcesManager::instance()
                                        ->get_texture_pool()
                                        .find(ResID::Tex_BulletShell)
                                        ->second;
    static SDL_Texture *tex_explode = ResourcesManager::instance()
                                          ->get_texture_pool()
                                          .find(ResID::Tex_EffectExplode)
                                          ->second;

    static const std::vector<int> idx_list = {0, 1};
    static const std::vector<int> idx_explode_list = {0, 1, 2, 3, 4};

    animation.set_loop(true);
    animation.set_interval(0.1);
    animation.set_frame_data(tex_shell, 2, 1, idx_list);

    animation_explode.set_loop(false);
    animation_explode.set_interval(0.1);
    animation_explode.set_frame_data(tex_explode, 5, 1, idx_explode_list);
    animation_explode.set_on_finished(
        [&]()
        {
            make_invalid();
        });

    damage_range = 96;
    size.x = 48, size.y = 48;
}

void ShellBullet::on_update(double delta)
{
    if (can_collide())
    {
        Bullet::on_update(delta);
        return;
    }

    animation_explode.on_update(delta);
}

void ShellBullet::on_render(SDL_Renderer *renderer)
{
    if (can_collide())
    {
        Bullet::on_render(renderer);
        return;
    }

    static SDL_Point point;

    point.x = (int)(position.x - 96 / 2);
    point.y = (int)(position.y - 96 / 2);

    animation_explode.on_render(renderer, point);
}

void ShellBullet::on_collide(Enemy *enemy)
{
    static const ResourcesManager::SoundPool &sound_pool = ResourcesManager::instance()->get_sound_pool();

    Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_ShellHit)->second, 0);

    disable_collide();
}
