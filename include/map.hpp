#ifndef MAP_HPP
#define MAP_HPP

#include "tile.hpp"
#include "config.hpp"

class Map
{
public:
    Map();
    ~Map();

    // 从.csv中加载瓦片信息
    bool load(const std::string &path);

private:
    TileMap tile_map;
    SDL_Point idx_home = {0, 0};

private:
    // 格式化字符串
    std::string trim_str(const std::string& str);

    // 从字符串中获取瓦片信息
    void load_tile_from_string(Tile& tile,const std::string& str);
};

#endif // MAP_HPP