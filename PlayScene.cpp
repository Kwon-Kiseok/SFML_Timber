#include "PlayScene.h"
#include "TextureList.h"
#include "UI.h"
#include "SoundManager.h"
#include "Player.h"
#include "Timer.h"
#include "Game.h"


PlayScene::PlayScene()
{
	acceptInput = false;
	InitScene();
}

PlayScene::~PlayScene()
{
}

void PlayScene::InitScene()
{
	Game::GetInstance()->TextureLoad();
	Game::GetInstance()->UILoad();
	if(Game::GetInstance()->GetPlayer() == nullptr)
		Game::GetInstance()->CreatePlayer();
	Game::GetInstance()->SoundLoad();
	RestartEvent();
}

void PlayScene::UpdateScene()
{
	if (!Game::GetInstance()->GetPause())
	{
		Game::GetInstance()->GetTL()->update();
		UI::GetInstance()->update();
		DeathEvent(Game::GetInstance()->GetPlayer()->getDir());
	}
}

void PlayScene::DrawScene(RenderWindow* window)
{
	Game::GetInstance()->GetTL()->draw(window);
	Game::GetInstance()->GetPlayer()->draw(window);
	UI::GetInstance()->draw(window);
}

void PlayScene::KeyboardEvent(Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Return:
		RestartEvent();
		break;
	case Keyboard::Left:
		PlayerMoveEvent(side::LEFT);
		break;
	case Keyboard::Right:
		PlayerMoveEvent(side::RIGHT);
		break;
	default:
		break;
	}
}

void PlayScene::RestartEvent()
{
	Game::GetInstance()->SetPause(false);
	Game::GetInstance()->GetPlayer()->SetScore(0);
	Timer::GetInstance()->setRemaining(Timer::GetInstance()->getTimeMax());
	for (int i = 0; i < 6; ++i)
	{
		Game::GetInstance()->GetTL()->branch[i].setDir(side::NONE);
	}
	Game::GetInstance()->GetPlayer()->ResetPos(720, 720);
	Game::GetInstance()->GetTL()->tombstone->SetXY(2000, 2000);
	acceptInput = true;
}

void PlayScene::PlayerMoveEvent(side side)
{
	if (acceptInput && !Game::GetInstance()->GetPause())
	{
		random_device rd;   // non-deterministic generator
		mt19937 gen(rd());  // to seed mersenne twister.

		for (int i = 5; i > 0; --i)
		{
			Branch prevBranch = Game::GetInstance()->GetTL()->branch[i - 1];
			Game::GetInstance()->GetTL()->branch[i].downBranch(prevBranch);
		}
		Game::GetInstance()->GetTL()->branch[0].setNewBranch(&gen);
		Game::GetInstance()->GetTL()->treeLog->SetLog(side);
		Game::GetInstance()->GetPlayer()->setDir(side);
		Game::GetInstance()->GetPlayer()->AddScore(1);
		Game::GetInstance()->GetPlayer()->move();
		Timer::GetInstance()->setRemaining((2.f / Game::GetInstance()->GetPlayer()->GetScore()) + 0.15f);
		acceptInput = false;
		SoundManager::GetInstance()->chopSound->play();
		Game::GetInstance()->GetPlayer()->SetWeaponPos(side);

	}
}

void PlayScene::DeathEvent(side playerSide)
{
	if (Game::GetInstance()->GetTL()->branch[5].getDir() == playerSide)
	{
		if (playerSide == side::LEFT)
		{
			Game::GetInstance()->GetTL()->tombstone->SetXY(580, 760);
		}
		else
		{
			Game::GetInstance()->GetTL()->tombstone->
				SetXY(Game::GetInstance()->GetPlayer()->getSprite().getPosition().x,
					Game::GetInstance()->GetPlayer()->getSprite().getPosition().y);
		}
		Game::GetInstance()->GetPlayer()->ResetPos(3000, 3000);

		Game::GetInstance()->SetPause(true);
		acceptInput = false;

		UI::GetInstance()->getTextMessage()->setString("SQUISHED!");
		UI::GetInstance()->setTextRect();
		SoundManager::GetInstance()->deathSound->play();
	}
}
