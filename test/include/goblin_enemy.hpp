#ifndef GOBLIN_ENEMY_H
#define GOBLIN_ENEMY_H

#include "enemy.hpp"
#include "config_manager.hpp"
#include "resources_manager.hpp"

class GoblinEnemy : public Enemy
{
public:
	GoblinEnemy();
	~GoblinEnemy() = default;

};

#endif // GOBLIN_ENEMY_H