#include "../include/route.hpp"

Route::Route(const TileMap &map, const SDL_Point &idx_origin)
{
    size_t width_map = map[0].size();
    size_t height_map = map.size();
    SDL_Point idx_next = idx_origin;

    while (true)
    {
        if (idx_next.x >= width_map || idx_next.y >= height_map)
            break;

        if (check_duplicate_idx(idx_next))
            break;
        else
            idx_list.push_back(idx_next);

        bool is_next_dir_exist = true;
        const Tile &tile = map[idx_next.y][idx_next.x];

        if (tile.special_flag == 0)
            break;
        switch (tile.direction)
        {
        case Tile::Direction::UP:
            idx_next.y--;
            break;
        case Tile::Direction::DOWN:
            idx_next.y++;
            break;
        case Tile::Direction::LEFT:
            idx_next.x--;
            break;
        case Tile::Direction::RIGHT:
            idx_next.x++;
            break;
        default:
            is_next_dir_exist = false;
            break;
        }

        if (!is_next_dir_exist)
            break;
    }
}

const Route::IdxLists &Route::get_idx_lists() const
{
    return idx_list;
}

bool Route::check_duplicate_idx(const SDL_Point &target_idx)
{
    for (const auto &idx : idx_list)
    {
        if (idx.x == target_idx.x && idx.y == target_idx.y)
            return true;
    }
    return false;
}
