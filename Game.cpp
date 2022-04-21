#include "Game.h"
#include "TextureList.h"
#include "EventHandler.h"
#include "UI.h"
#include "Timer.h"
#include "Player.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include <string>

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

	SceneManager::GetInstance()->LoadScene(SCENE_TYPE::MENU_SCENE);
}

void Game::update()
{
	while (window->isOpen())
	{
		eventHandler->InputKeyEvent();
		SceneManager::GetInstance()->UpdateScene();
		resetTimer();
		Render();
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

void Game::Render()
{
	window->clear();
	SceneManager::GetInstance()->DrawScene(window);
	window->display();
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
	UI::GetInstance()->init();
	UI::GetInstance()->initTimerBar();
}

void Game::SoundLoad()
{
	SoundManager::GetInstance()->init();
}

void Game::CreatePlayer()
{
	player = new Player();
	player->init("graphics/player.png", 580, 720);
	player->setDir(side::LEFT);
	player->SetWeapon();
}

void Game::ChangePlayerModel(const char* path)
{
	CreatePlayer();
	player->init(path, 580, 720);
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
	Timer::GetInstance()->setTime(&clock);
}

bool Game::GetPause()
{
	return isPause;
}

void Game::SetPause(bool is)
{
	isPause = is;
}