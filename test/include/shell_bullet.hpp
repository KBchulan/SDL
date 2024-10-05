#ifndef SHELL_BULLET_HPP
#define SHELL_BULLET_HPP


#include "bullet.hpp"
#include "resources_manager.hpp"

class ShellBullet : public Bullet
{
public:
	ShellBullet();
	~ShellBullet() = default;

	void on_update(double delta) override;

	void on_render(SDL_Renderer* renderer) override;

	void on_collide(Enemy* enemy) override;

private:
	Animation animation_explode;

};

#endif // SHELL_BULLET_HPP