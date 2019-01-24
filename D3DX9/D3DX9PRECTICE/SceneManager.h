#pragma once
#include "Singleton.h"

#include "Scene.h"
class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	vector<Scene*> vScenes;
	int nowScene;
	int pastScene;

public:
	void AddScene(Scene *newScene);
	void Update();
	void Render();
	void Release();
};

#define SCENEMANAGER SceneManager::GetInstance()