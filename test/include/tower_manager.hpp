#ifndef TOWER_MANAGER_HPP
#define TOWER_MANAGER_HPP

#include "tower.hpp"
#include "tower_type.hpp"
#include "archer_tower.hpp"
#include "axeman_tower.hpp"
#include "gunner_tower.hpp"
#include "config_manager.hpp"
#include "resources_manager.hpp"

class TowerManager : public Manager<TowerManager>
{
    friend class Manager<TowerManager>;

public:
    void on_update(double delta);

    void on_render(SDL_Renderer *renderer);

    double get_place_cost(TowerType type);

    double get_upgrade_cost(TowerType type);

    double get_damage_range(TowerType type);

    void place_tower(TowerType type, const SDL_Point &idx);

    void upgrade_tower(TowerType type);

protected:
    TowerManager() = default;
    ~TowerManager() = default;

private:
    std::vector<Tower *> tower_list;
};

#endif // TOWER_MANAGER_HPP