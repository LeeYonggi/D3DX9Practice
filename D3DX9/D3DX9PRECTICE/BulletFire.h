#pragma once
#include "Object.h"
class BulletFire :
	public Object
{
public:
	BulletFire(Vector3 initPos, Vector3 _playerPos);
	virtual ~BulletFire();

private:
	vector<Texture*> vFireAnime;
	Vector3 playerPos;
	float frame;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
	
public:

};

