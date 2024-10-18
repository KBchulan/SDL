#include "../include/bullet_manager.hpp"

void BulletManager::on_update(double delta)
{
    for (Bullet *bullet : bullet_list)
        bullet->on_update(delta);

    bullet_list.erase(std::remove_if(
                          bullet_list.begin(), bullet_list.end(),
                          [](const Bullet *bullet)
                          {
                              bool deletable = bullet->can_remove();
                              if (deletable)
                                  delete bullet;
                              return deletable;
                          }),
                      bullet_list.end());
}

void BulletManager::on_render(SDL_Renderer *renderer)
{
    for (Bullet *bullet : bullet_list)
        bullet->on_render(renderer);
}

BulletManager::BulletList &BulletManager::get_bullet_list()
{
    return bullet_list;
}

void BulletManager::fire_bullet(BulletType type, const Vector2 &position, const Vector2 &velocity, double damage)
{
    Bullet *bullet = nullptr;

    switch (type)
    {
    case Arrow:
        bullet = new ArrowBullet();
        break;
    case Axe:
        bullet = new AxeBullet();
        break;
    case Shell:
        bullet = new ShellBullet();
        break;
    default:
        bullet = new ArrowBullet();
        break;
    }

    bullet->set_position(position);
    bullet->set_velocity(velocity);
    bullet->set_damage(damage);

    bullet_list.push_back(bullet);
}

BulletManager::~BulletManager()
{
    for (Bullet *bullet : bullet_list)
        delete bullet;
}