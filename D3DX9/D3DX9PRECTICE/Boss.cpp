#include "DXUT.h"
#include "Boss.h"

#include "Bullet.h"
#include "Player.h"

Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::Init()
{
	name = "Boss";
	EnemyMeshInit(name);
	enemyState = BossState();
	enemyState.state = enemyState.ENEMY_IDLE;
	hp = 20000;
	scale = { 0.1, 0.1, 0.1 };
	objRadius = 10;
	pattern = BossPattern::PATTERN_ATTACK1;
	pos.y = 10;
	isShooting = false;
	animeDelay = 10;
	animeFrame = 0;
}

void Boss::Update()
{
	if (enemyState.state != enemyState.ENEMY_DIE)
	{
		HaveAttacked();
	}
	animeFrame += ElTime * animeDelay;

	distance.x = player->GetPos().x - pos.x;
	distance.y = player->GetPos().z - pos.z;
	D3DXVec2Normalize(&distance, &distance);

	switch (pattern)
	{
	case PATTERN_ATTACK1:
		if (isShooting == false)
		{
			BossAttack1();
			enemyState.state = enemyState.ENEMY_ATTACK;
			isShooting = true;
			animeFrame = 0;
		}
		else
		{
			if (animeFrame > enemyState.state)
			{
				isShooting = false;
				//pattern = (BossPattern)d3d::getRandomNumber(0, (int)PATTERN_MOVE);
				if ((int)animeFrame % 5 == 0)
					isShooting = true;
			}
		}
		break;
	case PATTERN_DASH:

		break;
	case PATTERN_MOVE:
		break;
	default:
		break;
	}
	rotation.y = GetVec2Angle(distance);
	if (hp < 1 && animeFrame > enemyState.state)
	{
		SetDestroy(true);
	}

	if (animeFrame > enemyState.state)
	{
		animeFrame = 0;
	}
}

void Boss::Render()
{
	Vector3 tempRotation = rotation;
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

void Boss::Release()
{
}

void Boss::BossAttack1()
{
	Vector3 initPos = pos;
	initPos.x += sin(D3DXToRadian(rotation.y - 60)) * 9;
	initPos.z += cos(D3DXToRadian(rotation.y - 60)) * 9;
	initPos.y += 4.0f;
	for (int i = rotation.y; i < rotation.y + 30; i += 10)
	{
		Vector3 moveVec3 = { 0, 0, 0 };
		Vector3 temp = player->GetPos() - initPos;
		moveVec3.x = sin(D3DXToRadian(i));
		moveVec3.z = cos(D3DXToRadian(i));
		D3DXVec3Normalize(&temp, &temp);
		moveVec3.y = temp.y;

		Bullet *bullet = OBJECTMANAGER->AddObject<Bullet>(OBJ_EBULLET, new Bullet(initPos, moveVec3, 10, 0.02f, 0, 10));
		bullet->SetBulletState(BulletState::BULLET_ENEMY);
	}

	initPos = pos;
	initPos.x += sin(D3DXToRadian(rotation.y + 50)) * 9;
	initPos.z += cos(D3DXToRadian(rotation.y + 50)) * 9;
	initPos.y += 4.0f;
	for (int i = rotation.y; i < rotation.y + 30; i += 10)
	{
		Vector3 moveVec3 = { 0, 0, 0 };
		Vector3 temp = player->GetPos() - initPos;
		moveVec3.x = sin(D3DXToRadian(i));
		moveVec3.z = cos(D3DXToRadian(i));
		D3DXVec3Normalize(&temp, &temp);
		moveVec3.y = temp.y;

		Bullet *bullet = OBJECTMANAGER->AddObject<Bullet>(OBJ_EBULLET, new Bullet(initPos, moveVec3, 10, 0.02f, 0, 10));
		bullet->SetBulletState(BulletState::BULLET_ENEMY);
	}
}
