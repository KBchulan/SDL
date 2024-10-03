#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "tile.hpp"
#include "config.hpp"

class Route
{
public:
    typedef std::vector<SDL_Point> IdxLists;

public:
    Route();
    ~Route();

    // 给定初始位置生成路线
    Route(const TileMap &map, const SDL_Point &idx_origin);

    // 返回路线
    const IdxLists &get_idx_lists() const
    {
        return idx_lists;
    }

private:
    IdxLists idx_lists;

private:
    bool check_duplicate_idx(const SDL_Point &target_idx);
};

#endif // ROUTE_HPP