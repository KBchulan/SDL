#ifndef SKELETON_ENEMY_H
#define SKELETON_ENEMY_H

#include "enemy.hpp"
#include "config_manager.hpp"
#include "resources_manager.hpp"

class SkeletonEnemy : public Enemy
{
public:
    SkeletonEnemy();
    ~SkeletonEnemy() = default;
};

#endif // SKELETON_ENEMY_H