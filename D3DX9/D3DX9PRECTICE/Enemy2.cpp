#include "DXUT.h"
#include "Enemy2.h"


Enemy2::Enemy2()
{
}


Enemy2::~Enemy2()
{
}

void Enemy2::Init()
{
	name = "Enemy2";
	EnemyMeshInit(name);
	enemyState = Enemy2State();
	enemyState.state = enemyState.ENEMY_IDLE;
	hp = 1500;
	scale = { 0.03, 0.03, 0.03 };
	centerH = 2.0f;
}

void Enemy2::Update()
{
	Enemy::Update();
}

void Enemy2::Render()
{
	//Enemy::Render();
	Vector3 tempRotation = rotation;
	tempRotation.y += 270;
	if (enemyState.state == enemyState.ENEMY_IDLE)
	{
		MESHMANAGER->RenderMesh(vAnimeIdle[(int)animeFrame], pos, tempRotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_MOVE)
	{
		MESHMANAGER->RenderMesh(vAnimeMove[(int)animeFrame], pos, tempRotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_ATTACK)
	{
		MESHMANAGER->RenderMesh(vAnimeAttack[(int)animeFrame], pos, tempRotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_DIE)
	{
		MESHMANAGER->RenderMesh(vAnimeDie[(int)animeFrame], pos, tempRotation, scale);
	}
}

void Enemy2::Release()
{
}
