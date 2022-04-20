#include "EventHandler.h"
#include "Game.h"
#include "UI.h"
#include "Timer.h"
#include "Player.h"
#include "TextureList.h"
#include "SoundManager.h"

void EventHandler::InputKeyEvent()
{
	Event event;
	while (window->pollEvent(event))
	{
		// 이벤트 및 입력
		switch (event.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::KeyReleased:
			if (event.key.code == Keyboard::Left ||
				event.key.code == Keyboard::Right)
			{
				acceptInput = true;
			}
			break;
		case Event::KeyPressed:
			switch (event.key.code)
			{
			case Keyboard::Escape:
				window->close();
				break;
			case Keyboard::Return:
			{
				RestartEvent();
			}
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
			break;
		default:
			break;
		}
	}
}

void EventHandler::DeathEvent(side playerSide)
{
	if (game->GetInstance()->GetTL()->branch[5].getDir() == playerSide)
	{
		if (playerSide == side::LEFT)
		{
			game->GetInstance()->GetTL()->tombstone->SetXY(580, 760);
		}
		else
		{
			game->GetInstance()->GetTL()->tombstone->
				SetXY(game->GetInstance()->GetPlayer()->getSprite().getPosition().x,
					game->GetInstance()->GetPlayer()->getSprite().getPosition().y);
		}
		game->GetInstance()->GetPlayer()->ResetPos(3000, 3000);
		
		game->GetInstance()->SetPause(true);
		acceptInput = false;
	
		ui->GetInstance()->getTextMessage()->setString("SQUISHED!");
		ui->GetInstance()->setTextRect();
		soundManager->GetInstance()->deathSound->play();
	}
}

void EventHandler::PlayerMoveEvent(side side)
{
	if (acceptInput && !game->GetInstance()->GetPause())
	{
		random_device rd;   // non-deterministic generator
		mt19937 gen(rd());  // to seed mersenne twister.

		for (int i = 5; i > 0; --i)
		{
			Branch prevBranch = game->GetInstance()->GetTL()->branch[i - 1];
			game->GetInstance()->GetTL()->branch[i].downBranch(prevBranch);
		}
		game->GetInstance()->GetTL()->branch[0].setNewBranch(&gen);
		game->GetInstance()->GetTL()->treeLog->SetLog(side);
		game->GetInstance()->GetPlayer()->setDir(side);
		game->GetInstance()->GetPlayer()->AddScore(1);
		game->GetInstance()->GetPlayer()->move();
		timer->GetInstance()->setRemaining((2.f / game->GetInstance()->GetPlayer()->GetScore()) + 0.15f);
		acceptInput = false;
		soundManager->GetInstance()->chopSound->play();
		game->GetInstance()->GetPlayer()->SetWeaponPos(side);

	}
}

void EventHandler::RestartEvent()
{
	game->GetInstance()->SetPause(false);
	game->GetInstance()->GetPlayer()->SetScore(0);
	timer->GetInstance()->setRemaining(timer->GetInstance()->getTimeMax());
	for (int i = 0; i < 6; ++i)
	{
		game->GetInstance()->GetTL()->branch[i].setDir(side::NONE);
	}
	game->GetInstance()->GetPlayer()->ResetPos(720, 720);
	game->GetInstance()->GetTL()->tombstone->SetXY(2000, 2000);
	acceptInput = true;
}