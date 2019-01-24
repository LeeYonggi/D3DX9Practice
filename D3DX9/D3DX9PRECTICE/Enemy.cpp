#include "DXUT.h"
#include "Enemy.h"

#include "Player.h"
#include "Bullet.h"
#include "BulletFire.h"
#include "FireEffect.h"
#include "Ground.h"

Enemy::Enemy()
{
	animeFrame = 0;
	animeDelay = 10;
	name = "NONE";
	enemyState.state = enemyState.ENEMY_IDLE;
	scale = { 0.013f, 0.013f, 0.013f };
	laderRadius = 10.f;
	hp = 1000;
	centerH = 1.0f;
	rotation = { 0, 0, 0 };
	distance = { 0, 0 };
	isSensing = true;
	speed = 5;
	fTimePos = { 0, 0 };
	bulletSpeed = 5;
	damage = 10;

	vFuncAction.push_back([&]() { Idle(); });
	vFuncAction.push_back([&]() { Move(); });
	vFuncAction.push_back([&]() { Attack(); });
	vFuncAction.push_back([&]() { Die(); });
}


Enemy::~Enemy()
{
}

void Enemy::EnemyMeshInit(string str)
{
	string action = "_Idle";
	vAnimeIdle = MESHMANAGER->AddObjAnime(str + action, L"", 0, enemyState.ENEMY_IDLE);
	action = "_Move";
	vAnimeMove = MESHMANAGER->AddObjAnime(str + action, L"", 0, enemyState.ENEMY_MOVE);
	action = "_Attack";
	vAnimeAttack = MESHMANAGER->AddObjAnime(str + action, L"", 0, enemyState.ENEMY_ATTACK);
	action = "_Die";
	vAnimeDie = MESHMANAGER->AddObjAnime(str + action, L"", 0, enemyState.ENEMY_DIE);
}

void Enemy::Init()
{

}

void Enemy::Idle()
{
	if (animeFrame > enemyState.state)
	{
		isSensing = true;
		ChangeState(enemyState.ENEMY_MOVE);
		fTimePos.x = pos.x;
		fTimePos.y = pos.z;
	}
}

void Enemy::Attack()
{
	if (animeFrame > enemyState.state)
	{
		ChangeState(enemyState.ENEMY_MOVE);
	}
}

void Enemy::Die()
{
	if (animeFrame > enemyState.state)
	{
		SetDestroy(true);
	}
}

void Enemy::Move()
{
	auto iter = OBJECTMANAGER->GetObjectOfState(OBJ_GROUND);
	if (isSensing)
	{
		pos.x += distance.x * ElTime * speed;
		pos.z += distance.y * ElTime * speed;

		Vector2 temp;
		temp.x = fTimePos.x - pos.x;
		temp.y = fTimePos.y - pos.z;
		float length = sqrt((temp.x * temp.x) + (temp.y * temp.y));

		if (length > 10 || IsCollisionGround(pos, dynamic_cast<Ground*>(iter)))
		{
			distance = -distance;
			ChangeState(enemyState.ENEMY_IDLE);
		}
		if (IsCollisionCircle(pos, player->GetPos(), laderRadius, player->GetRadius()))
		{
			ChangeState(enemyState.ENEMY_MOVE);
			isSensing = false;
		}
	}
	else
	{
		distance = GetVec2TrackingPos(player->GetPos());
		pos.x += distance.x * speed * ElTime;
		pos.z += distance.y * speed * ElTime;
		if (IsCollisionGround(pos, dynamic_cast<Ground*>(iter)))
		{
			pos.x -= distance.x * speed * ElTime;
			pos.z -= distance.y * speed * ElTime;
		}
		if (IsCollisionCircle(pos, player->GetPos(), laderRadius, player->GetRadius()))
		{
			Vector3 collisionPos = pos;
			collisionPos.y += centerH;
			Vector3 tempVec3;
			tempVec3.x = distance.x;
			tempVec3.y = 0;
			tempVec3.z = distance.y;
			Bullet *obj = OBJECTMANAGER->AddObject<Bullet>(OBJ_EBULLET, new Bullet(collisionPos, tempVec3, bulletSpeed, 0.02f, 0, damage));
			obj->SetBulletState(BulletState::BULLET_ENEMY);
			ChangeState(enemyState.ENEMY_ATTACK);
		}
	}
}

void Enemy::HaveAttacked()
{
	auto iter = OBJECTMANAGER->GetObjects(OBJ_STATE::OBJ_BULLET);
	Vector3 collisionPos = pos;
	collisionPos.y += centerH;
	for (int i = 0; i < iter->size(); ++i)
	{
		if (IsCollisionCircle(collisionPos, (*iter)[i]->GetPos(), objRadius, (*iter)[i]->GetRadius()))
		{
			Bullet *temp = dynamic_cast<Bullet*>((*iter)[i]);
			hp -= temp->GetDamage();
			temp->SetBulletState(BulletState::BULLET_EFFECT);
			cout << hp << endl;
		}
	}
	if (hp < 1)
	{
		ChangeState(enemyState.ENEMY_DIE);
		int tempY = 1;
		for (int i = -1; i < 2; ++i)
		{
			Vector3 collisionPos = pos;
			collisionPos.x += i;
			collisionPos.y += centerH - tempY;
			if (i == -1)
				tempY = 0;
			else
				tempY = 1;
			collisionPos.z += i;

			OBJECTMANAGER->AddObject<FireEffect>(OBJ_EFFECT, new FireEffect(collisionPos));
		}
	}
}

void Enemy::ChangeFunc(int index, function<void()> func)
{
	auto iter = vFuncAction.begin();
	for (int i = 0; i < index; ++i)
		++iter;
	vFuncAction.erase(iter);
	vFuncAction[index] = [&]() { func(); };
}

void Enemy::ChangeState(int _state)
{
	enemyState.state = _state;
	animeFrame = 0;
}

void Enemy::Update()
{
	if (enemyState.state != enemyState.ENEMY_DIE)
	{
		HaveAttacked();
	}
	animeFrame += ElTime * animeDelay;
	if (enemyState.state == enemyState.ENEMY_IDLE)
	{
		vFuncAction[0]();
		if (IsCollisionCircle(pos, player->GetPos(), laderRadius, player->GetRadius()))
		{
			ChangeState(enemyState.ENEMY_MOVE);
			isSensing = false;
		}
		animeDelay = 10;
		rotation.y = d3d::Lerp<float>(rotation.y, GetVec2Angle(distance) - 180, 0.1f);
	}
	else if (enemyState.state == enemyState.ENEMY_MOVE)
	{
		vFuncAction[1]();
		rotation.y = GetVec2Angle(distance) - 180;
		animeDelay = 10;
	}
	else if (enemyState.state == enemyState.ENEMY_ATTACK)
	{
		vFuncAction[2]();
		rotation.y = GetVec2Angle(distance) - 180;
		animeDelay = 20;
	}
	else if (enemyState.state == enemyState.ENEMY_DIE)
	{
		vFuncAction[3]();
	}

	if (animeFrame > enemyState.state)
	{
		animeFrame = 0;
	}
}

void Enemy::Render()
{
	if (enemyState.state == enemyState.ENEMY_IDLE)
	{
		MESHMANAGER->RenderMesh(vAnimeIdle[(int)animeFrame], pos, rotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_MOVE)
	{
		MESHMANAGER->RenderMesh(vAnimeMove[(int)animeFrame], pos, rotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_ATTACK)
	{
		MESHMANAGER->RenderMesh(vAnimeAttack[(int)animeFrame], pos, rotation, scale);
	}
	else if (enemyState.state == enemyState.ENEMY_DIE)
	{
		MESHMANAGER->RenderMesh(vAnimeDie[(int)animeFrame], pos, rotation, scale);
	}
}

void Enemy::Release()
{
}