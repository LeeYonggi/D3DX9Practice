#pragma once
#include "Enemy.h"

//20
//20
//20
//40
struct Enemy2State :
	public EnemyState
{
	Enemy2State()
	{
		ENEMY_IDLE = 20;
		ENEMY_MOVE = 19;
		ENEMY_ATTACK = 21;
		ENEMY_DIE = 40;
	}
};

class Enemy2 :
	public Enemy
{
public:
	Enemy2();
	virtual ~Enemy2();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

};

