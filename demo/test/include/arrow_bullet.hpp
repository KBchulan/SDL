#ifndef ARROW_BULLET_HPP
#define ARROW_BULLET_HPP

#include "bullet.hpp"
#include "resources_manager.hpp"

class ArrowBullet : public Bullet
{
public:
    ArrowBullet();
    ~ArrowBullet() = default;

    void on_collide(Enemy *enemy) override;
};

#endif // ARROW_BULLET_HPP