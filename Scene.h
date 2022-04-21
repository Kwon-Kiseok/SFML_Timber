#pragma once
#include "SFML_headers.h"

class Scene
{
protected:
	bool acceptInput;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void InitScene() = 0;
	virtual void UpdateScene() = 0;
	virtual void DrawScene(RenderWindow* window) = 0;
	virtual void KeyboardEvent(Keyboard::Key key) = 0;
	virtual void SetAcceptInput(bool is);
};

