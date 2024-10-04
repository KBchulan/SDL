#ifndef GAME_MANAGER_HPP
#define GANE_MANAGER_HPP

#include "config.hpp"
#include "manager.hpp"
#include "wave_manager.hpp"
#include "enemy_manager.hpp"
#include "config_manager.hpp"
#include "resources_manager.hpp"

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

    SDL_Texture *tex_tile_map = nullptr;

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
};

#endif // GAME_MANAGER_HPP