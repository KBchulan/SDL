#define SDL_MAIN_HANDLED

#include "../include/game_state.hpp"
#include "../include/game_manager.hpp"
#include "../include/button_manager.hpp"

inline GameState current_state = GameState::Game;

int main(int argc, char **argv)
{
	switch (current_state)
	{
	case GameState::Menu:
		break;
	case GameState::Game:
		GameManager::instance()->run(argc, argv);
		break;
	case GameState::Quit:
		break;
	}
	return 0;
}