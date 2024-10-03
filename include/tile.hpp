/*
对应map.csv中，每个方格依次是
    1. 地形瓦片层 （0,+oo)
    2. 装饰瓦片    -1为没有装饰
    3. 行进路线    0不是行进路线
    4. 特殊标志    0为房子，（1,+oo）为刷怪点
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

struct Tile
{
    enum class Direction
    {
        NONE = 0,
        UP,
        DOWM,
        LEFT,
        RIGHT
    };

    Direction direction = Direction::NONE;

    int terrian = 0;            // 地形层
    int decoration = -1;        // 装饰
    int special_flag = -1;      // 特殊标志
    bool has_tower = false;     // 是否有防御塔
    
};

typedef std::vector<std::vector<Tile>> TileMap;

#endif // TILE_HPP