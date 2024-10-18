#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

#include "bullet.hpp"
#include "manager.hpp"
#include "bullet_type.hpp"
#include "axe_bullet.hpp"
#include "arrow_bullet.hpp"
#include "shell_bullet.hpp"

#include <vector>

class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	typedef std::vector<Bullet*> BulletList;

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	BulletList& get_bullet_list();

	void fire_bullet(BulletType type, const Vector2& position, const Vector2& velocity, double damage);

protected:
	BulletManager() = default;
	~BulletManager();

private:
	BulletList bullet_list;

};

#endif // BULLET_MANAGER_HPP