#pragma once
#include "Enemy.h"

//21
//31
//20
//30
struct BossState :
	public EnemyState
{
	BossState()
	{
		ENEMY_IDLE = 21;
		ENEMY_MOVE = 31;
		ENEMY_ATTACK = 4;
		ENEMY_DIE = 30;
	}
};

enum BossPattern
{
	PATTERN_ATTACK1,
	PATTERN_DASH,
	PATTERN_MOVE
};

class Boss :
	public Enemy
{
public:
	Boss();
	virtual ~Boss();

private:
	BossPattern pattern;
	bool isShooting;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void BossAttack1();
};

