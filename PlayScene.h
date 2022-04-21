#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
private:
	bool acceptInput;
public:
	PlayScene();
	~PlayScene();
	virtual void InitScene();
	virtual void UpdateScene();
	virtual void DrawScene(RenderWindow* window);
	virtual void KeyboardEvent(Keyboard::Key key);
	
	void RestartEvent();
	void PlayerMoveEvent(side side);
	void DeathEvent(side playerSide);
};

