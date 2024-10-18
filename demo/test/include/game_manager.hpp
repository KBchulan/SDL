#ifndef GAME_MANAGER_HPP
#define GANE_MANAGER_HPP

#include "panel.hpp"
#include "banner.hpp"
#include "config.hpp"
#include "manager.hpp"
#include "status_bar.hpp"
#include "place_panel.hpp"
#include "wave_manager.hpp"
#include "upgrade_panel.hpp"
#include "tower_manager.hpp"
#include "enemy_manager.hpp"
#include "player_manager.hpp"
#include "config_manager.hpp"
#include "bullet_manager.hpp"
#include "resources_manager.hpp"

#include <cmath>

class GameManager : public Manager<GameManager>
{
    friend class Manager<GameManager>;

public:
    // 游戏主循环
    int run(int argc, char **argv);

protected:
    GameManager();
    ~GameManager();

private:
    SDL_Event event;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    StatusBar status_bar;

    SDL_Texture *tex_tile_map = nullptr;

    Banner *banner = nullptr;
    Panel *place_panel = nullptr;
    Panel *upgrade_panel = nullptr;

private:
    // 初始化断言
    void init_assert(bool flags, const char *error_msg);

    // 处理输入
    void on_input();

    // 数据更新
    void on_update(double delta);

    // 渲染
    void on_renderer();

    // 生成地图
    bool generate_tile_map_texture();

    bool check_home(const SDL_Point &idx_tile_selected);

    bool get_cursor_idx_tile(SDL_Point &idx_tile_selected, int screen_x, int screen_y) const;

    bool can_place_tower(const SDL_Point &idx_tile_selected) const;

    void get_selected_tile_center_pos(SDL_Point &pos, const SDL_Point &idx_tile_selected) const;
};

#endif // GAME_MANAGER_HPP