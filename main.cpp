#include "Game.h"

int main()
{
	Game* game = Game::GetInstance();
	game->init();
	game->update();
	game->clean();
	return 0;
}