#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

#define SIZE_TILE 48

struct Tile
{
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;
	int decoration = -1;
	int special_flag = -1;
	bool has_tower = false;
	Direction direction = Direction::None;
};

typedef std::vector<std::vector<Tile>> TileMap;

#endif // !TILE_HPP
