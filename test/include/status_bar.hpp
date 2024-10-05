#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#include "coin_manager.hpp"
#include "home_manager.hpp"
#include "player_manager.hpp"
#include "resources_manager.hpp"

class StatusBar
{
public:
	StatusBar() = default;
	~StatusBar() = default;

	void set_position(int x, int y);

	void on_update(SDL_Renderer* renderer);

	void on_render(SDL_Renderer* renderer);

private:
	const int size_heart = 32;
	const int width_mp_bar = 200;
	const int height_mp_bar = 20;
	const int width_border_mp_bar = 4;
	const SDL_Point offset_shadow = { 2, 2 };
	const SDL_Color color_text_background = { 175, 175, 175, 255 };
	const SDL_Color color_text_foreground = { 255, 255, 255, 255 };
	const SDL_Color color_mp_bar_background = { 48, 40, 51, 255 };
	const SDL_Color color_mp_bar_foredground = { 144, 121, 173, 255 };

private:
	SDL_Point position = { 0 };
	int width_text = 0, height_text = 0;
	SDL_Texture* tex_text_background = nullptr;
	SDL_Texture* tex_text_foreground = nullptr;

};


#endif // STATUS_BAR_HPP