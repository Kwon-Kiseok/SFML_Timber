#include "EventHandler.h"
#include "Game.h"
#include "UI.h"
#include "Timer.h"
#include "Player.h"
#include "TextureList.h"
#include "SoundManager.h"
#include "SceneManager.h"

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
				SceneManager::GetInstance()->SetAcceptInput(true);
				if(Game::GetInstance()->GetPlayer() != nullptr)
					Game::GetInstance()->GetPlayer()->WeaponInvisible();
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
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Return);
			}
				break;
			case Keyboard::Left:
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Left);
				break;
			case Keyboard::Right:
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Right);
				break;
			case Keyboard::Down:
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Down);
				break;
			case Keyboard::Up:
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Up);
				break;
			case Keyboard::Space:
				SceneManager::GetInstance()->KeyboardEvent(Keyboard::Space);
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