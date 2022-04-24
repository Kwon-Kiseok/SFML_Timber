#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
private:
	Text* textGameMode;
	Text* textCharacterSelect;
	Text* textPlay;
	
	Texture* textureCursor;
	Sprite* spriteCursor;

	float CursorY;
	bool isPlay = false;
	bool isSelect = false;
public:
	MenuScene();
	~MenuScene();

	virtual void InitScene();
	virtual void UpdateScene();
	virtual void DrawScene(RenderWindow* window);
	virtual void KeyboardEvent(Keyboard::Key key);

	void SetFont(Font& font);
	void SetString();
	void SetCursor();
	void SetIsPlay(bool is);
};

