#include "../include/config_manager.hpp"

bool ConfigManager::load_level_config(const std::string &path)
{
    std::fstream file(path, std::ios::in);
    if (!file.is_open())
        return false;

    std::stringstream str_stream;
    str_stream << file.rdbuf();
    file.close();

    cJSON *json_root = cJSON_Parse(str_stream.str().c_str());
    if (!json_root)
        return false;

    if (json_root->type != cJSON_Array)
    {
        cJSON_Delete(json_root);
        return false;
    }

    cJSON *json_wave = nullptr;
    cJSON_ArrayForEach(json_wave, json_root)
    {
        if (json_wave->type != cJSON_Array)
            continue;

        wave_list.emplace_back();
        Wave &wave = wave_list.back();

        cJSON *json_wave_rewards = cJSON_GetObjectItem(json_wave, "rewards");
        if (json_wave_rewards && json_wave_rewards->type == cJSON_Number)
            wave.rewards = json_wave_rewards->valuedouble;

        cJSON *json_wave_interval = cJSON_GetObjectItem(json_wave, "interval");
        if (json_wave_interval && json_wave_interval->type == cJSON_Number)
            wave.interval = json_wave_interval->valuedouble;

        cJSON *json_wave_spawn_list = cJSON_GetObjectItem(json_wave, "spawn_list");
        if (json_wave_spawn_list && json_wave_spawn_list->type == cJSON_Array)
        {
            cJSON *json_spawn_event = nullptr;
            cJSON_ArrayForEach(json_spawn_event, json_wave_spawn_list)
            {
                if (json_spawn_event->type != cJSON_Object)
                    continue;

                wave.spawn_event_list.emplace_back();
                Wave::SpawnEvent &spawn_event = wave.spawn_event_list.back();

                cJSON *json_spawn_event_interval = cJSON_GetObjectItem(json_spawn_event, "interval");
                if (json_spawn_event_interval && json_spawn_event_interval->type == cJSON_Number)
                    spawn_event.interval = json_spawn_event_interval->valuedouble;

                cJSON *json_spawn_event_spawn_point = cJSON_GetObjectItem(json_spawn_event, "point");
                if (json_spawn_event_spawn_point && json_spawn_event_spawn_point->type == cJSON_Number)
                    spawn_event.spawn_point = json_spawn_event_spawn_point->valueint;

                cJSON *json_spawn_event_enemy_type = cJSON_GetObjectItem(json_spawn_event, "enemy");
                if (json_spawn_event_enemy_type && json_spawn_event_enemy_type->type == cJSON_String)
                {
                    const std::string str_enemy_type = json_spawn_event_enemy_type->valuestring;
                    if (str_enemy_type == "Slim")
                        spawn_event.enemy_type = EnemyType::Slim;
                    else if (str_enemy_type == "KingSlim")
                        spawn_event.enemy_type = EnemyType::KingSlim;
                    else if (str_enemy_type == "Skeleton")
                        spawn_event.enemy_type = EnemyType::Skeleton;
                    else if (str_enemy_type == "Goblin")
                        spawn_event.enemy_type = EnemyType::Goblin;
                    else if (str_enemy_type == "GoblinPriest")
                        spawn_event.enemy_type = EnemyType::GoblinPriest;
                }
            }

            if (wave.spawn_event_list.empty())
                wave_list.pop_back();
        }
    }
    cJSON_Delete(json_root);
    if (wave_list.empty())
        return false;
    
    return true;
}