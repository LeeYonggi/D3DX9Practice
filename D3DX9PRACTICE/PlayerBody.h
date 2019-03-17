#pragma once
#include "Object.h"
#include "Player.h"

class UI;
class PlayerBody :
	public Object
{
public:
	PlayerBody(Player *_parent);
	virtual ~PlayerBody();
private:
	vector<MeshLoader*> body_Running;
	vector<MeshLoader*> body_Idle;
	vector<MeshLoader*> body_Shooting;
	vector<MeshLoader*> body_Fire;
	Player *parent;
	PlayerState bodyState;
	PlayerState nextState;
	PlayerWeapon pWeapon;
	UI *weaponUI;
	int shootGunDamage;
	int fireGunDamage;
	float animeDelay;
	float stopFrame;
	bool isShoot;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;	
	virtual void Release()	override;

public:
	void BodyIdle();
	void BodyRun();
	void BodyShooting();
	void BodyFireAttack();
	void AddBullet();
	void AddBulletFire();
	void AddFireBullet();
};

