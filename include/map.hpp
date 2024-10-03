#ifndef MAP_HPP
#define MAP_HPP

#include "tile.hpp"
#include "route.hpp"
#include "config.hpp"

class Map
{
public:
    typedef std::unordered_map<int, Route> SpawnerRoutePool;

public:
    Map();
    ~Map();

    // 从.csv中加载瓦片信息
    bool load(const std::string &path);

    // 获取地图的宽度（索引）
    size_t get_width() const;

    // 获取地图的高度（索引）
    size_t get_height() const;

    // 提供对外接口返回地图
    const TileMap &get_tile_map() const;

    // 提供对外接口返回房屋
    const SDL_Point &get_idx_home() const;

    // 提供对外接口返回路线池
    const SpawnerRoutePool &get_idx_spawner_pool() const;

    // 放置防御塔
    void place_tower(const SDL_Point &idx_tile);

private:
    TileMap tile_map;
    SDL_Point idx_home = {0, 0};
    SpawnerRoutePool spawner_route_pool;

private:
    // 格式化字符串
    std::string trim_str(const std::string &str);

    // 从字符串中获取瓦片信息（10\-1\0\-1）
    void load_tile_from_string(Tile &tile, const std::string &str);

    // 生成地图缓存
    void generate_map_cache();
};

#endif // MAP_HPP