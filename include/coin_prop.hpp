#ifndef COIN_PROP_HPP
#define COIN_PROP_HPP

#include "tile.hpp"
#include "timer.hpp"
#include "vector2.hpp"
#include "resources_manager.hpp"

class CoinProp
{
public:
	CoinProp();
	~CoinProp() = default;

	void set_position(const Vector2& position);

	const Vector2& get_position() const;

	const Vector2& get_size() const;

	void make_invalid();

	bool can_remove();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;
	Vector2 velocity;

	Timer timer_jump;
	Timer timer_disappear;

	bool is_valid = true;
	bool is_jumping = true;

	double gravity = 490;
	double interval_jump = 0.75;
	Vector2 size = { 16, 16 };
	double interval_disappear = 10;

};

#endif // COIN_PROP_HPP