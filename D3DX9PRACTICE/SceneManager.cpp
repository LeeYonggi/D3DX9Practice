#include "DXUT.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	nowScene = 0;
	pastScene = -1;
}


SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::AddScene(Scene *newScene)
{
	vScenes.push_back(newScene);
	nowScene = vScenes.size() - 1;
}

void SceneManager::Update()
{
	if (pastScene != nowScene)
	{
		if (pastScene != -1)
			vScenes[pastScene]->Release();

		pastScene = nowScene;
		vScenes[nowScene]->Init();
		vScenes[nowScene]->Update();
	}
	else
	{
		vScenes[pastScene]->Update();
	}
}

void SceneManager::Render()
{
	vScenes[pastScene]->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(vScenes[nowScene]);
	for (auto iter : vScenes)
	{
		SAFE_DELETE(iter);
	}
	vScenes.clear();
}
