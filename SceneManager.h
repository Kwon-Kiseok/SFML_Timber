#pragma once
#include "SFML_headers.h"

enum class SCENE_TYPE
{
	MENU_SCENE = 0,
	SELECT_SCENE,
	GAME_SCENE,
	NONE
};


class Scene;
class SceneManager
{
private:
	SceneManager() : sceneType(SCENE_TYPE::NONE), scene(nullptr) {}
	~SceneManager() {}

	static SceneManager* instance;
	SCENE_TYPE sceneType;

public:
	Scene* scene;

	static SceneManager* GetInstance();

	void InitScene();
	void LoadScene(SCENE_TYPE type);
	void UpdateScene();
	void DrawScene(RenderWindow* window);
	void KeyboardEvent(Keyboard::Key key);
	void SetAcceptInput(bool is);
	SCENE_TYPE getSceneType();
};

