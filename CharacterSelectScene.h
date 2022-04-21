#pragma once
#include "Scene.h"

#define CHARACTER_NUMBER 3

class CharacterSelectScene : public Scene
{
private:
	Texture texturePlayerModels[CHARACTER_NUMBER];
	Sprite spritePlayerModels[CHARACTER_NUMBER];
	const char* texturePaths[CHARACTER_NUMBER];
	
	Texture* texturePointer;
	Sprite* spritePointer;

	int s_xpos;
	int s_character;
	bool isTitle;
	string dir[CHARACTER_NUMBER];
public:
	CharacterSelectScene();
	~CharacterSelectScene();
	virtual void InitScene();
	virtual void UpdateScene();
	virtual void DrawScene(RenderWindow* window);
	virtual void KeyboardEvent(Keyboard::Key key);
	void SetSellectModelsPos();
};

