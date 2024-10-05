#ifndef BULLET_HPP
#define BULLET_HPP

#include "vector2.hpp"
#include "animation.hpp"

class Bullet
{
public:

protected:
	Vector2 size;
	Vector2 velocity;
	Vector2 position;

	Animation animation;
	bool can_rotated = false;

	double damage = 0;
	double damage_range = -1;

private:
	bool is_valid = true;
	bool is_collisional = true;
	double angle_anim_rotated = 0;
};

#endif // BULLET_HPP