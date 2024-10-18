#include "../include/home_manager.hpp"

HomeManager::HomeManager()
{
    num_hp = ConfigManager::instance()->num_initial_hp;
}

double HomeManager::get_current_hp_num()
{
    return num_hp;
}

void HomeManager::decrease_hp(double val)
{
    num_hp -= val;

    if (num_hp < 0)
        num_hp = 0;

    static const ResourcesManager::SoundPool &sound_pool = ResourcesManager::instance()->get_sound_pool();

    Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_HomeHurt)->second, 0);
    
}