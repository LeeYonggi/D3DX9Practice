#include "DXUT.h"
#include "GameManager.h"

#include "Ground.h"
#include "Player.h"
#include "SkyBox.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "UI.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "HpUI.h"


GameManager::GameManager()
{
	stage = STAGE1;
}


GameManager::~GameManager()
{
}

void GameManager::GameObjInit()
{
	OBJECTMANAGER->AddObject(OBJ_STATE::OBJ_GROUND, new Ground);
	OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new SkyBox);
	Player *player = OBJECTMANAGER->AddObject<Player>(OBJ_CHARACTER, new Player);
	UI *temp, *hpUI;
	temp = OBJECTMANAGER->AddObject<UI>(OBJ_UI, new UI);
	temp->SetColor(Color(255, 255, 255, 200));
	temp->SetPos(Vector3(SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0));
	temp->SetTexture(TEXMANAGER->AddTexture("AimUI", "./Resource/UI/AimUI.png"));

	OBJECTMANAGER->AddObject<HpUI>(OBJ_UI, new HpUI(player));
	switch (stage)
	{
	case STAGE1:
		SOUNDMANAGER->AddSound("Stage1", L"./Resource/Sound/Stage1.mp3", 100);
		SOUNDMANAGER->Playbgm("Stage1", true);
		MakeEnemy<Enemy1>({ 10, 0, 7 }, player, { 0, 1 });
		MakeEnemy<Enemy1>({ 60 - 35, 0, 10 -35 }, player, { 0, 1 });
		MakeEnemy<Enemy1>({ 40 - 35, 0, 15 - 35 }, player, { -1, 0 });
		MakeEnemy<Enemy1>({ 25 - 35, 0, 20 - 35 }, player, { 0, 1 });
		MakeEnemy<Enemy1>({ 10 - 35, 0, 15 - 35 }, player, { 0, 1 });
		MakeEnemy<Enemy1>({ 10 - 35, 0, 60 - 35 }, player, { 1, 0 });
		MakeEnemy<Enemy2>({ 10 - 35, 0, 45 - 35 }, player, { 0, 1 });
		break;
	case STAGE2:
		SOUNDMANAGER->AddSound("Stage2", L"./Resource/Sound/Stage2.mp3", 100);
		SOUNDMANAGER->Playbgm("Stage2", true);
		MakeEnemy<Boss>({ 20 - 35, 0, 0 }, player, { 0, 1 });
		MakeEnemy<Enemy2>({ 10 - 35, 0, 45 - 35 }, player, { 0, 1 });
		MakeEnemy<Enemy2>({ 50 - 35, 0, 45 - 35 }, player, { 0, 1 });
		MakeEnemy<Enemy2>({ 50 - 35, 0, 10 - 35 }, player, { 0, 1 });
		break;
	default:
		break;
	}
}

void GameManager::Update()
{
	auto iter = OBJECTMANAGER->GetObjects(OBJ_ENEMY);
	switch (stage)
	{
	case STAGE1:
		if (iter->size() == 0)
		{
			stage = STAGE2;
			SCENEMANAGER->AddScene(new IngameScene);
		}
		break;
	case STAGE2:
		break;
	default:
		break;
	}
}
