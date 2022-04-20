#include "Game.h"
#include "TextureList.h"
#include "EventHandler.h"
#include "UI.h"
#include "Timer.h"
#include "Player.h"
#include "SoundManager.h"

Game* Game::instance = nullptr;

Game* Game::GetInstance()
{
	if (nullptr == instance)
	{
		instance = new Game();
	}
	return instance;
}


void Game::init()
{
	setWindow();
	TextureLoad();
	UILoad();
	CreatePlayer();
	SoundLoad();
}

void Game::update()
{
	while (window->isOpen())
	{
		eventHandler->InputKeyEvent();

		// 업데이트
		resetTimer();

		if (!isPause)
		{
			tl->update(gen, timer->GetInstance()->getTime());
			ui->GetInstance()->update();
			eventHandler->DeathEvent(player->getDir());
		}

		// 렌더
		window->clear();
		tl->draw(window);
		player->draw(window);
		ui->GetInstance()->draw(window);
		// 윈도우 출력
		window->display();
	}
}

void Game::clean()
{
	delete vm;
	delete window;
	delete gen;
	delete rd;
	delete tl;
	delete eventHandler;

	vm = nullptr;
	window = nullptr;
	gen = nullptr;
	rd = nullptr;
	tl = nullptr;
	eventHandler = nullptr;
}

void Game::setWindow()
{
	vm = new VideoMode(1920, 1080);
	window = new RenderWindow(*vm, "Timber", Style::Default);
	rd = new random_device();
	gen = new mt19937((*rd)());
	eventHandler = new EventHandler(window);
}

void Game::TextureLoad()
{
	tl = new TextureList();
	tl->init();
}

void Game::UILoad()
{
	ui->GetInstance()->init();
	ui->GetInstance()->initTimerBar();
}

void Game::SoundLoad()
{
	soundManager->GetInstance()->init();
}

void Game::CreatePlayer()
{
	player = new Player();
	player->init("graphics/player.png", 580, 720);
	player->setDir(side::LEFT);
	player->SetWeapon();
}

Player* Game::GetPlayer()
{
	return player;
}

TextureList* Game::GetTL()
{
	return tl;
}

void Game::resetTimer()
{
	timer->GetInstance()->setTime(&clock);
}

bool Game::GetPause()
{
	return isPause;
}

void Game::SetPause(bool is)
{
	isPause = is;
}