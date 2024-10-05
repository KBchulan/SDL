#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "tile.hpp"
#include "config.hpp"

class Route
{
public:
    typedef std::vector<SDL_Point> IdxList;

public:
    Route() = default;
    ~Route() = default;

    // 给定初始位置生成路线
    Route(const TileMap &map, const SDL_Point &idx_origin);

    // 返回路线
    const IdxList &get_idx_list() const;

private:
    IdxList idx_list;

private:
    bool check_duplicate_idx(const SDL_Point &target_idx);
};

#endif // ROUTE_HPP