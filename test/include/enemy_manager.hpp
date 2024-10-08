#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

#include "enemy.hpp"
#include "slim_enemy.hpp"
#include "coin_manager.hpp"
#include "goblin_enemy.hpp"
#include "home_manager.hpp"
#include "bullet_manager.hpp"
#include "config_manager.hpp"
#include "skeleton_enemy.hpp"
#include "king_slim_enemy.hpp"
#include "goblin_priest_enemy.hpp"

class EnemyManager : public Manager<EnemyManager>
{
    friend class Manager<EnemyManager>;

public:
    typedef std::vector<Enemy *> EnemyList;

public:
    void on_update(double delta);

    void on_render(SDL_Renderer *renderer);

    void spawn_enemy(EnemyType type, int idx_spawn_point);

    bool check_cleared();

    EnemyManager::EnemyList &get_enemy_list();

protected:
    EnemyManager() = default;
    ~EnemyManager();

private:
    EnemyList enemy_list;

    void process_home_collision();

    void process_bullet_collision();

    void remove_invalid_enemy();

    void try_spawn_coin_prop(const Vector2 &position, double ratio);
};

#endif // ENEMY_MANAGER_HPP