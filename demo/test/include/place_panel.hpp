#ifndef PLACE_PANEL_HPP
#define PLACE_PANEL_HPP

#include "panel.hpp"
#include "coin_manager.hpp"
#include "tower_manager.hpp"
#include "resources_manager.hpp"

class PlacePanel : public Panel
{
public:
	PlacePanel();
	~PlacePanel() = default;

	void on_update(SDL_Renderer* renderer) override;

	void on_render(SDL_Renderer* renderer) override;

protected:
	void on_click_top_area() override;

	void on_click_left_area() override;

	void on_click_right_area() override;

private:
	const SDL_Color color_region_frame = { 30, 80, 162, 175 };
	const SDL_Color color_region_content = { 0, 149, 217, 75 };

private:
	int reg_top = 0, reg_left = 0, reg_right = 0;

};

#endif // PLACE_PANEL_HPP