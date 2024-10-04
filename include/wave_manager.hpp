#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include "timer.hpp"
#include "coin_manager.hpp"
#include "enemy_manager.hpp"
#include "config_manager.hpp"

class WaveManager : public Manager<WaveManager>
{
    friend class Manager<WaveManager>;

public:
    void on_update(double delta);

protected:
    WaveManager();
    ~WaveManager();
    
private:
    int idx_wave = 0;
    int idx_spawn_event = 0;
    Timer timer_start_wave;
    Timer timer_spawn_enemy;
    bool is_wave_started = false;
	bool is_spawned_last_enemy = false;
};

#endif // WAVE_MANAGER_HPP