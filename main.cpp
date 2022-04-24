#include "Game.h"

int main()
{
	Game::GetInstance()->init();
	Game::GetInstance()->update();
	Game::GetInstance()->clean();
	return 0;
}