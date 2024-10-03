#include "../include/map.hpp"

Map::Map() = default;
Map::~Map() = default;

bool Map::load(const std::string &path)
{
    std::fstream file(path, std::ios::in);
    if (!file.is_open())
    {
        return false;
    }

    TileMap temp_tile_map;
    int idx_x = -1,
        idx_y = -1;

    std::string str_line;
    while (std::getline(file, str_line))
    {
        str_line = trim_str(str_line);
        if (str_line.empty())
            continue;

        idx_x = -1, idx_y++;
        temp_tile_map.emplace_back();

        std::string str_tile;
        std::stringstream str_stream(str_line);
        while (std::getline(str_stream, str_tile, ','))
        {
            idx_x++;
            temp_tile_map[idx_y].emplace_back();
            Tile &tile = temp_tile_map[idx_y].back();
            load_tile_from_string(tile, str_tile);
        }
    }
    file.close();

    if (temp_tile_map.empty() || temp_tile_map[0].empty())
    {
        return false;
    }

    tile_map = temp_tile_map;
    return true;
}

size_t Map::get_width() const
{
    if (tile_map.empty())
        return 0;
    return tile_map[0].size();
}

size_t Map::get_height() const
{
    if (tile_map.empty())
        return 0;
    return tile_map.size();
}

std::string Map::trim_str(const std::string &str)
{
    size_t idx_begin = str.find_first_not_of(" \t");
    if (idx_begin == std::string::npos)
    {
        return "";
    }
    size_t idx_last = str.find_last_not_of(" \t");
    size_t idx_range = idx_last - idx_begin + 1;
    return str.substr(idx_begin, idx_range);
}

void Map::load_tile_from_string(Tile &tile, const std::string &str)
{
    std::string str_tidy = trim_str(str);

    std::string str_value;
    std::vector<int> values;
    std::stringstream str_stream(str_tidy);

    while (std::getline(str_stream, str_value, '\\'))
    {
        int value;
        try
        {
            value = std::stoi(str_value);
        }
        catch (const std::invalid_argument &)
        {
            value = -1;
        }
        values.push_back(value);
    }

    tile.terrian = (values.size() < 1 || values[0] < 0)
                       ? 0
                       : values[0];
    tile.decoration = (values.size() < 2)
                          ? -1
                          : values[1];
    tile.direction = (Tile::Direction)(values.size() < 3 || values[3] < 0
                                           ? 0
                                           : values[2]);
    tile.special_flag = (values.size() < 4)
                            ? -1
                            : values[3];
}

void Map::generate_map_cache()
{
    for (auto y = 0; y < get_height(); y++)
    {
        for (auto x = 0; x < get_width(); x++)
        {
            const Tile &tile = tile_map[y][x];
            if (tile.special_flag < 0)
                continue;

            if (tile.special_flag == 0)
            {
                idx_home.x = x;
                idx_home.y = y;
            }
            else
            {
                spawner_route_pool[tile.special_flag] = Route(tile_map, {x, y});
            }
        }
    }
}