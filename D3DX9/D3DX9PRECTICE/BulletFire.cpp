#include "DXUT.h"
#include "BulletFire.h"


BulletFire::BulletFire(Vector3 initPos, Vector3 _playerPos)
{
	pos = initPos;
	playerPos = _playerPos;
	scale = {0.2, 0.2, 0.2};
	frame = 0;
	rotation.x = 90;
}


BulletFire::~BulletFire()
{
}

void BulletFire::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("BulletPlan", L"./Resource/Effect/BulletFire.obj");
	vFireAnime = TEXMANAGER->AddAnimeTexture("./Resource/Effect/BulletFire/effect%d.png", 1, 6);
}

void BulletFire::Update()
{
	Vector2 distance;
	distance.x = playerPos.x - pos.x;
	distance.y = playerPos.z - pos.z;
	rotation.y = GetVec2Angle(distance);

	frame += ElTime * 15;
	if (frame > 5)
	{
		frame = 4;
		SetDestroy(true);
	}
}

void BulletFire::Render()
{
	MESHMANAGER->RenderPlanEffect(meshLoader, vFireAnime[(int)frame], pos, rotation, scale);
}

void BulletFire::Release()
{
}
