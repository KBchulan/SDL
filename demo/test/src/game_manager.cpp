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

    status_bar.set_position(15, 15);

    banner = new Banner();
    place_panel = new PlacePanel();
    upgrade_panel = new UpgradePanel();
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
    Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BGM)->second, -1, 1500);

    // 动态延时实现
    Uint64 last_counter = SDL_GetPerformanceCounter();
    const Uint64 quency_counter = SDL_GetPerformanceFrequency();

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
    static SDL_Point pos_center;
    static SDL_Point idx_tile_selected;
    static ConfigManager *instance = ConfigManager::instance();

    switch (event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (instance->is_game_over)
            break;
        if (get_cursor_idx_tile(idx_tile_selected, event.motion.x, event.motion.y))
        {
            get_selected_tile_center_pos(pos_center, idx_tile_selected);

            if (check_home(idx_tile_selected))
            {
                upgrade_panel->set_idx_tile(idx_tile_selected);
                upgrade_panel->set_center_pos(pos_center);
                upgrade_panel->show();
            }
            else if (can_place_tower(idx_tile_selected))
            {
                place_panel->set_idx_tile(idx_tile_selected);
                place_panel->set_center_pos(pos_center);
                place_panel->show();
            }
        }
        break;
    default:
        break;
    }

    if (!instance->is_game_over)
    {
        place_panel->on_input(event);
        upgrade_panel->on_input(event);
        PlayerManager::instance()->on_input(event);
    }
}

void GameManager::on_update(double delta)
{
    static bool is_game_over_last_tick = false;
    static ConfigManager *instance = ConfigManager::instance();

    if (!instance->is_game_over)
    {
        status_bar.on_update(renderer);
        place_panel->on_update(renderer);
        upgrade_panel->on_update(renderer);
        WaveManager::instance()->on_update(delta);
        EnemyManager::instance()->on_update(delta);
        CoinManager::instance()->on_update(delta);
        BulletManager::instance()->on_update(delta);
        TowerManager::instance()->on_update(delta);
        PlayerManager::instance()->on_update(delta);

        return;
    }

    if (!is_game_over_last_tick && instance->is_game_over)
    {
        static const ResourcesManager::SoundPool &sound_pool = ResourcesManager::instance()->get_sound_pool();

        Mix_FadeOutMusic(1500);
        Mix_PlayChannel(-1, sound_pool.find(instance->is_game_win ? ResID::Sound_Win : ResID::Sound_Loss)->second, 0);
    }

    is_game_over_last_tick = instance->is_game_over;

    banner->on_update(delta);
    if (banner->check_end_dispaly())
        running = false;
}

void GameManager::on_renderer()
{
    static ConfigManager *instance = ConfigManager::instance();
    static SDL_Rect &rect_dst = instance->rect_tile_map;
    SDL_RenderCopy(renderer, tex_tile_map, nullptr, &rect_dst);

    EnemyManager::instance()->on_render(renderer);
    CoinManager::instance()->on_render(renderer);
    BulletManager::instance()->on_render(renderer);
    TowerManager::instance()->on_render(renderer);
    PlayerManager::instance()->on_render(renderer);

    if (!instance->is_game_over)
    {
        place_panel->on_render(renderer);
        upgrade_panel->on_render(renderer);
        status_bar.on_render(renderer);

        return;
    }

    int width_screen, height_screen;
    SDL_GetWindowSizeInPixels(window, &width_screen, &height_screen);
    banner->set_center_position({(double)width_screen / 2, (double)height_screen / 2});
    banner->on_render(renderer);
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

bool GameManager::check_home(const SDL_Point &idx_tile_selected)
{
    static const Map &map = ConfigManager::instance()->map;
    static const SDL_Point &idx_home = map.get_idx_home();

    return (idx_home.x == idx_tile_selected.x && idx_home.y == idx_tile_selected.y);
}

bool GameManager::get_cursor_idx_tile(SDL_Point &idx_tile_selected, int screen_x, int screen_y) const
{
    static const Map &map = ConfigManager::instance()->map;
    static const SDL_Rect &rect_tile_map = ConfigManager::instance()->rect_tile_map;

    if (screen_x < rect_tile_map.x || screen_x > rect_tile_map.x + rect_tile_map.w || screen_y < rect_tile_map.y || screen_y > rect_tile_map.x + rect_tile_map.h)
        return false;

    idx_tile_selected.x = std::min((screen_x - rect_tile_map.x) / TILE_SIZE, (int)map.get_width() - 1);
    idx_tile_selected.y = std::min((screen_y - rect_tile_map.y) / TILE_SIZE, (int)map.get_height() - 1);

    return true;
}

bool GameManager::can_place_tower(const SDL_Point &idx_tile_selected) const
{
    static const Map &map = ConfigManager::instance()->map;
    const Tile &tile = map.get_tile_map()[idx_tile_selected.y][idx_tile_selected.x];

    return (tile.decoration < 0 && tile.direction == Tile::Direction::NONE && !tile.has_tower);
}

void GameManager::get_selected_tile_center_pos(SDL_Point &pos, const SDL_Point &idx_tile_selected) const
{
    static const SDL_Rect &rect_tile_map = ConfigManager::instance()->rect_tile_map;

    pos.x = rect_tile_map.x + idx_tile_selected.x * TILE_SIZE + TILE_SIZE / 2;
    pos.y = rect_tile_map.y + idx_tile_selected.y * TILE_SIZE + TILE_SIZE / 2;
}