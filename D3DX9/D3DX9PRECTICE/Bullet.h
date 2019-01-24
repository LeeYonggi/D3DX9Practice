#pragma once
#include "Object.h"

enum BulletState
{
	BULLET_ENEMY,
	BULLET_PLAYER,
	BULLET_EFFECT,
	BULLET_FIRE
};
class Ground;
class Bullet :
	public Object
{
public:
	Bullet(Vector3 initPos, Vector3 _moveVector, float _speed, float _scale, float rotateZ, int _damage);
	virtual ~Bullet();

private:
	Texture *tex;
	Texture *firetex;
	Vector3 moveVector;
	Ground *map;
	BulletState bulletState;
	MeshLoader *eBullet;
	vector<Texture*> bulletEffect;
	float speed;
	float frame;
	int damage;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	bool CheckDestroy();
	int GetDamage() { return damage; }
	void SetBulletState(BulletState _state) 
	{ 
		if(bulletState != BulletState::BULLET_FIRE)
			bulletState = _state; 
	}
};

