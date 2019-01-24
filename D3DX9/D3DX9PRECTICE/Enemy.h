#pragma once
#include "Object.h"

#include <functional>
//16
//35
//28
//20
struct EnemyState
{
	int ENEMY_IDLE = 16;
	int ENEMY_MOVE = 35;
	int ENEMY_ATTACK = 28;
	int ENEMY_DIE = 20;
	int state;
};

class Player;
class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();

protected:
	vector<std::function<void()>> vFuncAction;
	vector<MeshLoader*> vAnimeIdle;
	vector<MeshLoader*> vAnimeAttack;
	vector<MeshLoader*> vAnimeMove;
	vector<MeshLoader*> vAnimeDie;
	EnemyState enemyState;
	Player *player;
	string name;
	Vector2 distance;
	Vector2 fTimePos;
	bool isSensing;
	float centerH;
	float animeFrame;
	float animeDelay;
	float laderRadius;
	float speed;
	float bulletSpeed;
	int damage;
	int hp;

protected:
	void EnemyMeshInit(string str);
	void Idle();
	void Attack();
	void Die();
	void Move();
	void HaveAttacked();
	void ChangeFunc(int index, function<void()> func);
	void ChangeState(int _state);

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	string SetStrName(string str) { name = str; }
	vector<std::function<void()>> GetAction() { return vFuncAction; }
	void SetPlayer(Player *_player) { player = _player; }
	void SetDistance(Vector2 vec2) { distance = vec2; }
};

template<class T>
Enemy *MakeEnemy(Vector3 pos, Player *player, Vector2 distance)
{
	Enemy *temp = new T;
	temp->SetPos(pos);
	temp->SetPlayer(player);
	temp->SetDistance(distance);
	OBJECTMANAGER->AddObject<Enemy>(OBJ_ENEMY, temp);

	return temp;
}