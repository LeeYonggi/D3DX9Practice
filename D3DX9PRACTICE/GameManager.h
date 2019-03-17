#pragma once
#include "Singleton.h"

enum STAGE_STATE
{
	STAGE1,
	STAGE2
};
class GameManager :
	public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

public:
	STAGE_STATE stage;

public:
	void GameObjInit();
	void Update();
};

#define GAMEMANAGER GameManager::GetInstance()