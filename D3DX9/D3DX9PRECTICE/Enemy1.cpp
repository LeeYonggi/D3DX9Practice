#include "DXUT.h"
#include "Enemy1.h"


Enemy1::Enemy1()
{
}


Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	name = "Enemy1";
	EnemyMeshInit(name);
	hp = 1000;
}

void Enemy1::Update()
{
	Enemy::Update();

}

void Enemy1::Render()
{
	Enemy::Render();
}

void Enemy1::Release()
{
}

void Enemy1::MoveSide()
{

}

