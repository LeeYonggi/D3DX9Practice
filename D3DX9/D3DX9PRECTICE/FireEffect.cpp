#include "DXUT.h"
#include "FireEffect.h"



FireEffect::FireEffect(Vector3 initPos)
{
	pos = initPos;
	scale = { 0.8, 0.8, 0.8 };
	rotation.x = 90;
	frame = 0;
}

FireEffect::~FireEffect()
{
}

void FireEffect::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("BulletPlan", L"./Resource/Effect/BulletFire.obj");
	vFireAnime = TEXMANAGER->AddAnimeTexture("./Resource/Effect/FireEffect/bomb_%d.png", 2, 8);
}

void FireEffect::Update()
{
	Vector2 distance;
	distance.x = CAMERAMANAGER->GetEye().x - pos.x;
	distance.y = CAMERAMANAGER->GetEye().z - pos.z;
	rotation.y = GetVec2Angle(distance);

	frame += ElTime * 8;
	if (frame > 6)
	{
		frame = 5;
		SetDestroy(true);
	}
}

void FireEffect::Render()
{
	MESHMANAGER->RenderPlanEffect(meshLoader, vFireAnime[(int)frame], pos, rotation, scale);
}

void FireEffect::Release()
{
}
