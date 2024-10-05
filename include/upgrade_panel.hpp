#ifndef UPGRADE_PANEL_HPP
#define UPGRADE_PANEL_HPP

#include "panel.hpp"
#include "tower_manager.hpp"
#include "resources_manager.hpp"

class UpgradePanel : public Panel
{
public:
    UpgradePanel();
    ~UpgradePanel() = default;

    void on_update(SDL_Renderer *renderer);

protected:
    void on_click_top_area() override;

    void on_click_left_area() override;

    void on_click_right_area() override;
};

#endif // UPGRADE_PANEL_HPP