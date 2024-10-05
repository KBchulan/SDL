#include "../include/wave_manager.hpp"

void WaveManager::on_update(double delta)
{
    static ConfigManager *instance = ConfigManager::instance();

    if (instance->is_game_over)
        return;

    if (!is_wave_started)
        timer_start_wave.on_update(delta);
    else
        timer_spawn_enemy.on_update(delta);

    if (is_spawned_last_enemy && EnemyManager::instance()->check_cleared())
    {
        CoinManager::instance()->increase_coin(instance->wave_list[idx_wave].rewards);

        idx_wave++;

        if (idx_wave >= instance->wave_list.size())
        {
            instance->is_game_win = true;
            instance->is_game_over = true;
        }
        else
        {
            idx_spawn_event = 0;
            is_wave_started = false;
            is_spawned_last_enemy = false;

            const Wave &wave = instance->wave_list[idx_wave];
            timer_start_wave.set_wait_time(wave.interval);
            timer_start_wave.restart();
        }
    }
}

WaveManager::WaveManager()
{
    static const std::vector<Wave> &wave_list = ConfigManager::instance()->wave_list;

    timer_start_wave.set_one_shot(true);
    timer_start_wave.set_wait_time(wave_list[0].interval);
    timer_start_wave.set_on_timeout(
        [&]()
        {
            is_wave_started = true;
            timer_spawn_enemy.set_wait_time(wave_list[idx_wave].spawn_event_list[0].interval);
            timer_spawn_enemy.restart();
        });

    timer_spawn_enemy.set_one_shot(true);
    timer_spawn_enemy.set_on_timeout(
        [&]()
        {
            const std::vector<Wave::SpawnEvent> &spawn_event_list = wave_list[idx_wave].spawn_event_list;
            const Wave::SpawnEvent &spawn_event = spawn_event_list[idx_spawn_event];
            EnemyManager::instance()->spawn_enemy(spawn_event.enemy_type, spawn_event.spawn_point);

            idx_spawn_event++;

            if (idx_spawn_event >= spawn_event_list.size())
            {
                is_spawned_last_enemy = true;
                return;
            }

            timer_spawn_enemy.set_wait_time(spawn_event_list[idx_spawn_event].interval);
            timer_spawn_enemy.restart();
        });
}

WaveManager::~WaveManager() = default;