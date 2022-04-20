#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene()
	: CursorY(0)
{
	textGameMode = new Text();
	textCharacterSelect = new Text();
	textPlay = new Text();
	textureCursor = new Texture();
	spriteCursor = new Sprite();
}

MenuScene::~MenuScene()
{
	delete textGameMode;
	delete textCharacterSelect;
	delete textPlay;
	delete textureCursor;
	delete spriteCursor;
}

void MenuScene::InitScene()
{
	SetFont(*UI::GetInstance()->getFont());
	SetString();
	SetCursor();
}

void MenuScene::UpdateScene()
{
	if (isPlay)
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::GAME_SCENE);
	else if (isSelect)
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::SELECT_SCENE);
}

void MenuScene::DrawScene(RenderWindow* window)
{
	window->draw(*spriteCursor);
	window->draw(*textGameMode);
	window->draw(*textCharacterSelect);
	window->draw(*textPlay);
}

void MenuScene::SetFont(Font font)
{
	textGameMode->setFont(font);
	textCharacterSelect->setFont(font);
	textPlay->setFont(font);
}

void MenuScene::SetString()
{
	textGameMode->setString("GAME MODE");
	textCharacterSelect->setString("CHARACTER SELECT");
	textPlay->setString("PLAY");

	textGameMode->setCharacterSize(75);
	textGameMode->setFillColor(Color::White);
	textGameMode->setPosition(1920 * 0.5f, 1080 * 0.5f - 100);

	textCharacterSelect->setCharacterSize(75);
	textCharacterSelect->setFillColor(Color::White);
	textCharacterSelect->setPosition(1920 * 0.5f, 1080 * 0.5f);
	
	textPlay->setCharacterSize(75);
	textPlay->setFillColor(Color::White);
	textPlay->setPosition(1920 * 0.5f, 1080 * 0.5f + 100);
}

void MenuScene::SetCursor()
{
	textureCursor->loadFromFile("graphics/cursor.png");
	spriteCursor->setTexture(*textureCursor);
	CursorY = 1080 * 0.5f;
	spriteCursor->setPosition(1920 * 0.5 - 150, CursorY);
}

void MenuScene::SetIsPlay(bool is)
{
	isPlay = is;
}

void MenuScene::KeyboardEvent(Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Down:
	{
		CursorY += 100;
		if (CursorY > 1080 * 0.5f + 101)
		{
			CursorY = 1080 * 0.5f - 100;
		}
		spriteCursor->setPosition(1920 * 0.5 - 150, CursorY);
	}
		break;
	case Keyboard::Up:
	{
		CursorY -= 100;
		if (CursorY < 1080 * 0.5f - 101)
		{
			CursorY = 1080 * 0.5f + 100;
		}
		spriteCursor->setPosition(1920 * 0.5 - 150, CursorY);
	}
		break;
	case Keyboard::Space:
	{
		if (CursorY == 1080 * 0.5f)
		{
			isPlay = false;
			isSelect = true;
		}
		else if (CursorY == 1080 * 0.5f + 100)
		{
			isPlay = true;
			isSelect = false;
		}
	}
		break;
	default:
		break;
	}
}