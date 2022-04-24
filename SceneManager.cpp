#include "SceneManager.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "CharacterSelectScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
    if (nullptr == instance)
    {
        instance = new SceneManager();
    }
    return instance;
}

void SceneManager::InitScene()
{
    scene->InitScene();
}

void SceneManager::LoadScene(SCENE_TYPE type)
{
    sceneType = type;

    switch (sceneType)
    {
    case SCENE_TYPE::MENU_SCENE:
    {
        if (scene != nullptr)
        {
            delete scene;
        }
        scene = new MenuScene();
    }
        break;
    case SCENE_TYPE::SELECT_SCENE:
    {
        if (scene != nullptr)
        {
            delete scene;
        }
        scene = new CharacterSelectScene();
    }
        break;
    case SCENE_TYPE::GAME_SCENE:
    {
        if (scene != nullptr)
        {
            delete scene;
        }
        scene = new PlayScene();
    }
        break;
    default:
        break;
    }
}

void SceneManager::UpdateScene()
{
    scene->UpdateScene();
}

void SceneManager::DrawScene(RenderWindow* window)
{
    scene->DrawScene(window);
}

void SceneManager::KeyboardEvent(Keyboard::Key key)
{
    scene->KeyboardEvent(key);
}

void SceneManager::SetAcceptInput(bool is)
{
    scene->SetAcceptInput(is);
}

SCENE_TYPE SceneManager::getSceneType()
{
    return sceneType;
}
