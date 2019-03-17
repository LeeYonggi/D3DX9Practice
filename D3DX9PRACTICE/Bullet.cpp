#include "DXUT.h"
#include "Bullet.h"

#include "Ground.h"

Bullet::Bullet(Vector3 initPos, Vector3 _moveVector, float _speed, float _scale, float rotateZ, int _damage)
{
	pos = initPos;
	scale = { _scale, _scale, _scale };
	rotation.x = 90;
	rotation.z = rotateZ;
	moveVector = _moveVector;
	speed = _speed;
	objRadius = 0.1f;
	damage = _damage;
	bulletState = BULLET_PLAYER;
	frame = 0;
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("BulletPlan", L"./Resource/Effect/BulletFire.obj");
	tex = TEXMANAGER->AddTexture("PlayerBullet", "./Resource/Effect/PlayerBullet.png");
	firetex = TEXMANAGER->AddTexture("PlayerFireBullet", "./Resource/Effect/FireEffect/bomb_4.png");
	eBullet = MESHMANAGER->AddObjMesh("EnemyBullet", L"./Resource/Enemy/Bullet/EnemyBullet.obj");
	bulletEffect = TEXMANAGER->AddAnimeTexture("./Resource/Effect/BulletEffect/bullet_effect_%d.png", 1, 6);

	map = dynamic_cast<Ground*>(OBJECTMANAGER->GetObjectOfState(OBJ_GROUND));
}

void Bullet::Update()
{
	Vector2 distance;
	distance.x = CAMERAMANAGER->GetEye().x - pos.x;
	distance.y = CAMERAMANAGER->GetEye().z - pos.z;
	float random = 0;
	switch (bulletState)
	{
	case BULLET_ENEMY:
		rotation.x += 1;
		rotation.y += 1;
		break;
	case BULLET_PLAYER:
		rotation.y = GetVec2Angle(distance);
		break;
	case BULLET_FIRE:
		rotation.y = GetVec2Angle(distance);
		random = d3d::getRandomNumber(5, 30);
		scale.x += random * 0.0002;
		scale.y += random * 0.0002;
		scale.z += random * 0.0002;

		if (scale.x > 0.32)
			SetDestroy(true);
		break;
	case BULLET_EFFECT:
		damage = 0;
		objRadius = 0;
		rotation.y = GetVec2Angle(distance);
		rotation.x = 90;
		scale = {0.5, 0.5, 0.5};
		frame += ElTime * 10;
		if (frame > 5)
		{
			SetDestroy(true);
			frame = 4;
		}
		break;
	default:
		break;
	}
	if(bulletState != BULLET_EFFECT)
		pos += moveVector * speed * ElTime;

	if (CheckDestroy() || IsCollisionGround(pos, map))
		SetBulletState(BULLET_EFFECT);
}

void Bullet::Render()
{
	switch (bulletState)
	{
	case BULLET_ENEMY:
		MESHMANAGER->RenderAlphaMesh(eBullet, pos, rotation, scale);
		break;
	case BULLET_PLAYER:
		MESHMANAGER->RenderPlanEffect(meshLoader, tex, pos, rotation, scale);
		break;
	case BULLET_FIRE:
		MESHMANAGER->RenderPlanEffect(meshLoader, firetex, pos, rotation, scale);
		break;
	case BULLET_EFFECT:
		MESHMANAGER->RenderPlanEffect(meshLoader, bulletEffect[(int)frame], pos, rotation, scale);
		break;
	default:
		break;
	}
}

void Bullet::Release()
{
}

bool Bullet::CheckDestroy()
{
	if (pos.x < -(map->GetMap()->info.Width * 0.5f) ||
		pos.x > map->GetMap()->info.Width * 0.5f ||
		pos.z < -(map->GetMap()->info.Width * 0.5f) ||
		pos.z > map->GetMap()->info.Width * 0.5f)
		return true;
	return false;
}
