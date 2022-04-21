#include "CharacterSelectScene.h"
#include "SceneManager.h"
#include "Game.h"
#include <string>
CharacterSelectScene::CharacterSelectScene()
	: s_xpos(917), s_character(0), isTitle(false)
{
	texturePointer = new Texture();
	spritePointer = new Sprite();

	InitScene();
	SetSellectModelsPos();
}

CharacterSelectScene::~CharacterSelectScene()
{
	delete texturePointer;
	delete spritePointer;
}

void CharacterSelectScene::InitScene()
{
	for (int i = 0; i < CHARACTER_NUMBER; ++i)
	{
		dir[i] = "graphics/player0";
		dir[i] += to_string(i + 1);
		dir[i] += ".png";
		texturePaths[i] = dir[i].data();
		texturePlayerModels[i].loadFromFile(dir[i]);
		spritePlayerModels[i].setTexture(texturePlayerModels[i]);
		spritePlayerModels[i].setPosition(2000, 720);
	}

	texturePointer->loadFromFile("graphics/down.png");
	spritePointer->setTexture(*texturePointer);
	spritePointer->setPosition(s_xpos, 620);
}

void CharacterSelectScene::UpdateScene()
{
	if (isTitle)
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::MENU_SCENE);
}

void CharacterSelectScene::DrawScene(RenderWindow* window)
{
	for (int i = 0; i < CHARACTER_NUMBER; ++i)
	{
		window->draw(spritePlayerModels[i]);
	}
	window->draw(*spritePointer);
}

void CharacterSelectScene::KeyboardEvent(Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Left:
	{
		s_xpos -= 310;
		if (s_xpos < 607)
		{
			s_xpos = 1227;
		}
		spritePointer->setPosition(s_xpos, 620);
	}
		break;
	case Keyboard::Right:
	{
		s_xpos += 310;
		if (s_xpos > 1227)
		{
			s_xpos = 607;
		}
		spritePointer->setPosition(s_xpos, 620);
	}
		break;
	case Keyboard::Space:
	{
		if (s_xpos == 607)
		{
			s_character = 0;
		}
		else if (s_xpos == 917)
		{
			s_character = 1;
		}
		else if (s_xpos == 1227)
		{
			s_character = 2;
		}
		Game::GetInstance()->ChangePlayerModel(texturePaths[s_character]);
		isTitle = true;
	}
		break;
	default:
		break;
	}
}

void CharacterSelectScene::SetSellectModelsPos()
{
	spritePlayerModels[0].setPosition(580, 720);
	spritePlayerModels[1].setPosition(890, 720);
	spritePlayerModels[2].setPosition(1200, 720);
}
