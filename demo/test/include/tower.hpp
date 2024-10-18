#ifndef TOWER_HPP
#define TOWER_HPP

#include "facing.hpp"
#include "vector2.hpp"
#include "animation.hpp"
#include "tower_type.hpp"
#include "enemy_manager.hpp"
#include "bullet_manager.hpp"

class Tower
{
public:
    Tower();
    ~Tower() = default;

    void set_position(const Vector2 &position);

    const Vector2 &get_size() const;

    const Vector2 &get_position() const;

    void on_update(double delta);

    void on_render(SDL_Renderer *renderer);

protected:
    Vector2 size;

    Animation anim_idle_up;
    Animation anim_idle_down;
    Animation anim_idle_left;
    Animation anim_idle_right;
    Animation anim_fire_up;
    Animation anim_fire_down;
    Animation anim_fire_left;
    Animation anim_fire_right;

    TowerType tower_type = TowerType::Archer;

    double fire_speed = 0;
    BulletType bullet_type = BulletType::Arrow;

private:
    Timer timer_fire;
    Vector2 position;
    bool can_fire = true;
    Facing facing = Facing::Right;
    Animation *anim_current = &anim_idle_right;

private:
    void update_idle_animation();
    
    void update_fire_animation();

    Enemy *find_target_enemy();

    void on_fire();
};

#endif // TOWER_HPP