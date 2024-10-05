#include "../include/upgrade_panel.hpp"

UpgradePanel::UpgradePanel()
{
    const ResourcesManager::TexturePool &texture_pool = ResourcesManager::instance()->get_texture_pool();

    tex_idle = texture_pool.find(ResID::Tex_UIUpgradeIdle)->second;
    tex_hovered_top = texture_pool.find(ResID::Tex_UIUpgradeHoveredTop)->second;
    tex_hovered_left = texture_pool.find(ResID::Tex_UIUpgradeHoveredLeft)->second;
    tex_hovered_right = texture_pool.find(ResID::Tex_UIUpgradeHoveredRight)->second;
}

void UpgradePanel::on_update(SDL_Renderer *renderer)
{
    static TowerManager *instance = TowerManager::instance();

    val_top = (int)instance->get_upgrade_cost(TowerType::Axeman);
    val_left = (int)instance->get_upgrade_cost(TowerType::Archer);
    val_right = (int)instance->get_upgrade_cost(TowerType::Gunner);

    Panel::on_update(renderer);
}

void UpgradePanel::on_click_top_area() override
{
    CoinManager *instance = CoinManager::instance();

    if (val_top > 0 && val_top <= instance->get_current_coin_num())
    {
        TowerManager::instance()->upgrade_tower(TowerType::Axeman);
        instance->decrease_coin(val_top);
    }
}

void UpgradePanel::on_click_left_area() override
{
    CoinManager *instance = CoinManager::instance();

    if (val_left > 0 && val_left <= instance->get_current_coin_num())
    {
        TowerManager::instance()->upgrade_tower(TowerType::Axeman);
        instance->decrease_coin(val_left);
    }
}

void UpgradePanel::on_click_right_area() override
{
    CoinManager *instance = CoinManager::instance();

    if (val_right > 0 && val_right <= instance->get_current_coin_num())
    {
        TowerManager::instance()->upgrade_tower(TowerType::Axeman);
        instance->decrease_coin(val_right);
    }
}