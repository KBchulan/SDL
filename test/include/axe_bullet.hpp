#ifndef AXE_BULLET_HPP
#define AXE_BULLET_HPP

#include "bullet.hpp"
#include "resources_manager.hpp"

class AxeBullet : public Bullet
{
public:
	AxeBullet();
	~AxeBullet() = default;

	void on_collide(Enemy* enemy) override;

};

#endif // AXE_BULLET_HPP