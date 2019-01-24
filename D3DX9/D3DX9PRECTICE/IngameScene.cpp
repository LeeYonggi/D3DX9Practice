#include "DXUT.h"
#include "IngameScene.h"
#include "Ground.h"
#include "Player.h"
#include "SkyBox.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "UI.h"


IngameScene::IngameScene()
{
}


IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	GAMEMANAGER->GameObjInit();
}

void IngameScene::Update()
{
	OBJECTMANAGER->Update();
	//cout << DXUTGetFPS() << endl;
	GAMEMANAGER->Update();
}

void IngameScene::Render()
{
	OBJECTMANAGER->Render();
}

void IngameScene::Release()
{
	OBJECTMANAGER->Release();
	ObjectManager::ReleaseInstance();
	SOUNDMANAGER->Release();
}
