#include "../include/game_manager.hpp"

GameManager::GameManager()
{
    // 初始化
    init_assert(!TTF_Init(), u8"SDL2_ttf初始化失败!");
    init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2初始化失败!");
    init_assert(Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_MID), u8"SDL2_mixer初始化失败!");
    init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_JXL | IMG_INIT_TIF), u8"SDL2_image初始化失败!");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    ConfigManager *config = ConfigManager::instance();
    init_assert(config->map.load("../data/map.csv"), u8"游戏地图加载失败");
    init_assert(config->load_level_config("../data/level.json"), u8"关卡配置加载失败");
    init_assert(config->load_game_config("../data/config.json"), u8"游戏配置加载失败");

    window = SDL_CreateWindow(config->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              config->basic_template.window_width, config->basic_template.window_height, SDL_WINDOW_RESIZABLE);
    init_assert(window, u8"窗口创建失败!");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    init_assert(renderer, u8"渲染器创建失败!");

    init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"游戏资源加载失败");

    init_assert(generate_tile_map_texture(), u8"生成瓦片地图失败");
}

GameManager::~GameManager()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}

int GameManager::run(int argc, char **argv)
{
    // 动态延时实现
    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 quency_counter = SDL_GetPerformanceFrequency();

    while (running)
    {
        // 消息处理
        while (SDL_PollEvent(&event))
        {
            on_input();
        }

        // 数据更新
        Uint64 current_counter = SDL_GetPerformanceCounter();
        double delta = (current_counter - last_counter) / quency_counter;
        last_counter = current_counter;
        on_update(delta);

        // 渲染
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        on_renderer();
        SDL_RenderPresent(renderer);

        if (delta * 1000 < 1000 / FPS)
        {
            SDL_Delay((Uint32)(1000 / FPS - delta));
        }
    }

    return 0;
}

void GameManager::on_input()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }
    }
}

void GameManager::on_update(double delta)
{
}

void GameManager::on_renderer()
{
    static ConfigManager *instance = ConfigManager::instance();
    static SDL_Rect &rect_dst = instance->rect_tile_map;
    SDL_RenderCopy(renderer, tex_tile_map, nullptr, &rect_dst);
}

void GameManager::init_assert(bool flags, const char *error_msg)
{
    if (flags)
        return;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", error_msg, window);
    exit(-1);
}

bool GameManager::generate_tile_map_texture()
{
    const Map &map = ConfigManager::instance()->map;
    const TileMap &tile_map = map.get_tile_map();
    SDL_Rect &rect_tile_map = ConfigManager::instance()->rect_tile_map;
    SDL_Texture *tex_tile_set = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Tileset)->second;

    int width_tex_tile_set,
        height_tex_tile_set;
    SDL_QueryTexture(tex_tile_set, nullptr, nullptr, &width_tex_tile_set, &height_tex_tile_set);

    int num_tile_single_line = (int)std::ceil((double)width_tex_tile_set / TILE_SIZE);

    int width_tex_tile_map,
        height_tex_tile_map;
    width_tex_tile_map = (int)map.get_width() * TILE_SIZE;
    height_tex_tile_map = (int)map.get_height() * TILE_SIZE;

    tex_tile_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_TARGET, width_tex_tile_map, height_tex_tile_map);
    if (!tex_tile_map)
        return false;

    ConfigManager *config = ConfigManager::instance();
    rect_tile_map.x = (config->basic_template.window_width - width_tex_tile_map) / 2;
    rect_tile_map.y = (config->basic_template.window_height - height_tex_tile_map) / 2;
    rect_tile_map.w = width_tex_tile_map;
    rect_tile_map.h = height_tex_tile_map;

    SDL_SetTextureBlendMode(tex_tile_map, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, tex_tile_map);

    for (auto y = 0; y < map.get_height(); y++)
    {
        for (auto x = 0; x < map.get_width(); x++)
        {
            SDL_Rect rect_src;
            const Tile &tile = tile_map[y][x];

            const SDL_Rect &rect_dst = {
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE};

            rect_src = {
                (tile.terrian % num_tile_single_line) * TILE_SIZE,
                (tile.terrian / num_tile_single_line) * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE};

            SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);

            if (tile.decoration >= 0)
            {
                rect_src = {
                    (tile.decoration % num_tile_single_line) * TILE_SIZE,
                    (tile.decoration / num_tile_single_line) * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE};
                SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);
            }
        }
    }

    const SDL_Point &idx_home = map.get_idx_home();
    const SDL_Rect rect_dst = {
        idx_home.x * TILE_SIZE,
        idx_home.y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE};
    SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Home)->second, nullptr, &rect_dst);

    SDL_SetRenderTarget(renderer, nullptr);

    return true;
}