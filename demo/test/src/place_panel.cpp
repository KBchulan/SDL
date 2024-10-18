#include "../include/place_panel.hpp"

PlacePanel::PlacePanel()
{
    const ResourcesManager::TexturePool &texture_pool = ResourcesManager::instance()->get_texture_pool();

    tex_idle = texture_pool.find(ResID::Tex_UIPlaceIdle)->second;
    tex_hovered_top = texture_pool.find(ResID::Tex_UIPlaceHoveredTop)->second;
    tex_hovered_left = texture_pool.find(ResID::Tex_UIPlaceHoveredLeft)->second;
    tex_hovered_right = texture_pool.find(ResID::Tex_UIPlaceHoveredRight)->second;
}

void PlacePanel::on_update(SDL_Renderer *renderer)
{
    static TowerManager *instance = TowerManager::instance();

    val_top = (int)instance->get_place_cost(TowerType::Axeman);
    val_left = (int)instance->get_place_cost(TowerType::Archer);
    val_right = (int)instance->get_place_cost(TowerType::Gunner);

    reg_top = (int)instance->get_damage_range(TowerType::Axeman) * TILE_SIZE;
    reg_left = (int)instance->get_damage_range(TowerType::Archer) * TILE_SIZE;
    reg_right = (int)instance->get_damage_range(TowerType::Gunner) * TILE_SIZE;

    Panel::on_update(renderer);
}

void PlacePanel::on_render(SDL_Renderer *renderer)
{
    if (!visible)
        return;

    int reg = 0;
    switch (hovered_target)
    {
    case Panel::HoveredTarget::Top:
        reg = reg_top;
        break;
    case Panel::HoveredTarget::Left:
        reg = reg_left;
        break;
    case Panel::HoveredTarget::Right:
        reg = reg_right;
        break;
    }

    if (reg > 0)
    {
        filledCircleRGBA(renderer, center_pos.x, center_pos.y, reg,
                         color_region_content.r, color_region_content.g, color_region_content.b, color_region_content.a);
        aacircleRGBA(renderer, center_pos.x, center_pos.y, reg,
                     color_region_frame.r, color_region_frame.g, color_region_frame.b, color_region_frame.a);
    }

    Panel::on_render(renderer);
}

void PlacePanel::on_click_top_area()
{
    CoinManager *instance = CoinManager::instance();

    if (val_top <= instance->get_current_coin_num())
    {
        TowerManager::instance()->place_tower(TowerType::Axeman, idx_tile_selected);
        instance->decrease_coin(val_top);
    }
}

void PlacePanel::on_click_left_area()
{
    CoinManager *instance = CoinManager::instance();

    if (val_left <= instance->get_current_coin_num())
    {
        TowerManager::instance()->place_tower(TowerType::Archer, idx_tile_selected);
        instance->decrease_coin(val_left);
    }
}

void PlacePanel::on_click_right_area()
{
    CoinManager *instance = CoinManager::instance();

    if (val_right <= instance->get_current_coin_num())
    {
        TowerManager::instance()->place_tower(TowerType::Gunner, idx_tile_selected);
        instance->decrease_coin(val_right);
    }
}