#include "DXUT.h"
#include "PlayerBody.h"

#include "Player.h"
#include "Bullet.h"
#include "BulletFire.h"
#include "UI.h"


PlayerBody::PlayerBody(Player * _parent)
{
	parent = _parent;
	animeDelay = 0.f;
	pos = _parent->GetPos();
	rotation = _parent->GetRotation();
	scale = _parent->GetSize();
	bodyState = PlayerState::PLAYER_IDLE;
	nextState = PlayerState::PLAYER_RUN;
	isShoot = false;
	stopFrame = 0;
	shootGunDamage = 70;
	fireGunDamage = 3;
	pWeapon = PlayerWeapon::WEAPON_SHOTGUN;
}

PlayerBody::~PlayerBody()
{
}

void PlayerBody::Init()
{
	body_Running = MESHMANAGER->AddObjAnime("Player_Body_running", L"./Resource/Character/Running/Body/Body_Running", 0, 41);
	body_Shooting = MESHMANAGER->AddObjAnime("Player_Body_Shooting", 
		L"./Resource/Character/Shooting/Body/Body_Shooting", 0, PlayerState::PLAYER_SHOOTING);
	body_Idle = MESHMANAGER->AddObjAnime("Player_Body_Idle", L"./Resource/Character/Idle/Body/Body_Idle", 0, PlayerState::PLAYER_IDLE);
	body_Fire = MESHMANAGER->AddObjAnime("Player_Body_FireAttack", 
		L"./Resource/Character/FireAttack/Player_FireAttack", 0, PlayerState::PLAYER_FIRE);

	UI *tempUI = OBJECTMANAGER->AddObject<UI>(OBJ_UI, new UI);
	tempUI->SetTexture(TEXMANAGER->AddTexture("bullet_cartridge_case", "./Resource/UI/bullet_cartridge_case.png"));
	tempUI->SetPos({ SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0 });
	tempUI->SetColor({ 255, 255, 255, 200 });

	weaponUI = OBJECTMANAGER->AddObject<UI>(OBJ_UI, new UI);
	weaponUI->SetTexture(TEXMANAGER->AddTexture("wShotgunUI", "./Resource/UI/shotgun.png"));
	weaponUI->SetPos({ SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0 });
	weaponUI->SetColor({ 255, 255, 255, 200 });
}

void PlayerBody::Update()
{
	pos = parent->GetPos();
	scale = parent->GetSize();
	rotation.x = parent->GetRotation().x;
	rotation.z = parent->GetRotation().z;

	float targetRotate;
	if (INPUTMANAGER->IsKeyDown('1'))
	{
		pWeapon = WEAPON_SHOTGUN;
		weaponUI->SetTexture(TEXMANAGER->AddTexture("wShotgunUI", "./Resource/UI/shotgun.png"));
	}
	if (INPUTMANAGER->IsKeyDown('2'))
	{
		pWeapon = WEAPON_FIRE;
		weaponUI->SetTexture(TEXMANAGER->AddTexture("wFireUI", "./Resource/UI/fire.png"));
	}
	if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
	{
		if (isShoot == false)
		{
			switch (pWeapon)
			{
			case WEAPON_SHOTGUN:
				bodyState = PlayerState::PLAYER_SHOOTING;
				AddBulletFire();
				AddBullet();
				break;
			case WEAPON_FIRE:
				SOUNDMANAGER->AddSound("Fire", L"./Resource/Sound/Fire2.mp3", 400);
				SOUNDMANAGER->Playbgm("Fire", true);
				bodyState = PlayerState::PLAYER_FIRE;
				AddFireBullet();
				break;
			default:
				break;
			}
			isShoot = true;
		}
	}
	switch (bodyState)
	{
	case PlayerState::PLAYER_IDLE:
		BodyIdle();
		break;
	case PlayerState::PLAYER_RUN:
		BodyRun();
		
		break;
	case PlayerState::PLAYER_SHOOTING:
		BodyShooting();
		
		break;
	case PlayerState::PLAYER_FIRE:
		BodyFireAttack();
		break;
	}

	if (bodyState == PlayerState::PLAYER_RUN)
	{
		targetRotate = parent->RotateToDirection() + parent->GetRotation().y;
		rotation.y += parent->GetDotRotationLerp(rotation.y, targetRotate);
	}
	else
	{
		targetRotate = parent->GetRotation().y;
		rotation.y += parent->GetDotRotationLerp(rotation.y, targetRotate);
	}
}

void PlayerBody::Render()
{
	Vector3 tempPos = pos;
	switch (bodyState)
	{
	case PlayerState::PLAYER_IDLE:
		tempPos.y += 0.1f;
		MESHMANAGER->RenderMesh(body_Idle[(int)animeDelay], tempPos, rotation, scale);
			break;
	case PlayerState::PLAYER_RUN:
		tempPos.y -= 0.06f;
		MESHMANAGER->RenderMesh(body_Running[(int)animeDelay], tempPos, rotation, scale);
		break;
	case PlayerState::PLAYER_SHOOTING:
		tempPos.y += 0.1f;
		MESHMANAGER->RenderMesh(body_Shooting[(int)animeDelay], tempPos, rotation, scale);
		break;
	case PlayerState::PLAYER_FIRE:
		tempPos.y += 0.1f;
		MESHMANAGER->RenderMesh(body_Fire[(int)animeDelay], tempPos, rotation, scale);
		break;
	}
}

void PlayerBody::Release()
{
}

void PlayerBody::BodyIdle()
{
	animeDelay += ElTime * PLAYERANIMESPEED;
	if (animeDelay > bodyState)
		animeDelay = 0.0f;


	if (parent->GetIsMove())
	{
		bodyState = PlayerState::PLAYER_RUN;
		animeDelay = 0.0f;
	}
}

void PlayerBody::BodyRun()
{
	animeDelay += ElTime * PLAYERANIMESPEED;
	if (animeDelay > bodyState)
		animeDelay = 0.0f;


	if (!parent->GetIsMove())
	{
		stopFrame += ElTime * PLAYERANIMESPEED;
	}
	else
	{
		stopFrame = 0;
	}

	if (stopFrame > STOPMOVEFRAME)
	{
		bodyState = PlayerState::PLAYER_IDLE;
		animeDelay = 0;
		stopFrame = 0;
	}
}

void PlayerBody::BodyShooting()
{
	animeDelay += ElTime * PLAYERANIMESPEED;
	if (animeDelay > bodyState)
	{
		if (parent->GetIsMove())
			bodyState = PlayerState::PLAYER_RUN;
		else
			bodyState = PlayerState::PLAYER_IDLE;

		isShoot = false;
		animeDelay = 0.0f;
	}

}

void PlayerBody::BodyFireAttack()
{
	animeDelay += ElTime * PLAYERANIMESPEED;
	if (animeDelay > bodyState)
	{
		animeDelay = 0.0f;
	}

	if (INPUTMANAGER->IsKeyUp(VK_LBUTTON))
	{
		if (parent->GetIsMove())
			bodyState = PlayerState::PLAYER_RUN;
		else
			bodyState = PlayerState::PLAYER_IDLE;
		isShoot = false;
		animeDelay = 0.0f;
		SOUNDMANAGER->Stopbgm("Fire");
	}
	else
	{
		AddFireBullet();
	}
}

void PlayerBody::AddBulletFire()
{
	Vector3 front = { 0, 0, 0 };
	front.x = sin(D3DXToRadian(rotation.y - 50));
	front.z = cos(D3DXToRadian(rotation.y - 50));
	front *= 1.6;
	front.y = 1.7f;
	front += pos;
	OBJECTMANAGER->AddObject<BulletFire>(OBJ_EFFECT, new BulletFire(front, pos));
}

void PlayerBody::AddFireBullet()
{
	Vector3 moveVector = CAMERAMANAGER->GetAt() - CAMERAMANAGER->GetEye();
	moveVector.x += d3d::getRandomNumber(-3, 3) * 0.1f;
	moveVector.y += d3d::getRandomNumber(-3, 3) * 0.1f;
	moveVector.z += d3d::getRandomNumber(-3, 3) * 0.1f;
	D3DXVec3Normalize(&moveVector, &moveVector);
	Vector3 distanceToShoot = { 0, 0, 0 };
	distanceToShoot.x = sin(D3DXToRadian(rotation.y - 55));
	distanceToShoot.z = cos(D3DXToRadian(rotation.y - 55));
	D3DXVec3Normalize(&distanceToShoot, &distanceToShoot);
	distanceToShoot = distanceToShoot * 1.8f + pos;
	distanceToShoot.y += 1.8f;

	int speed = d3d::getRandomNumber(10, 20);
	Bullet *tempBullet = OBJECTMANAGER->AddObject<Bullet>(OBJ_BULLET,
		new Bullet(distanceToShoot, moveVector, speed, 0.1, 0, fireGunDamage));
	tempBullet->SetBulletState(BulletState::BULLET_FIRE);
}

void PlayerBody::AddBullet()
{
	SOUNDMANAGER->Stopbgm("Shotgun");
	SOUNDMANAGER->AddSound("Shotgun", L"./Resource/Sound/ShotGun.mp3", 100);
	SOUNDMANAGER->Playbgm("Shotgun", false);
	for (int i = 0; i < 10; ++i)
	{
		Vector3 moveVector = CAMERAMANAGER->GetAt() - CAMERAMANAGER->GetEye();
		moveVector.x += d3d::getRandomNumber(-3, 3) * 0.1f;
		moveVector.y += d3d::getRandomNumber(-3, 3) * 0.1f;
		moveVector.z += d3d::getRandomNumber(-3, 3) * 0.1f;
		D3DXVec3Normalize(&moveVector, &moveVector);

		Vector3 distanceToShoot = { 0, 0, 0 };
		distanceToShoot.x = sin(D3DXToRadian(rotation.y - 10));
		distanceToShoot.z = cos(D3DXToRadian(rotation.y - 10));
		D3DXVec3Normalize(&distanceToShoot, &distanceToShoot);
		distanceToShoot = distanceToShoot * 1.5f + pos;
		distanceToShoot.y += 1.5f;

		int bRandom = d3d::getRandomNumber(1, 3);
		int bRotate = d3d::getRandomNumber(0, 90);
		int speed = d3d::getRandomNumber(40, 60);
		OBJECTMANAGER->AddObject<Bullet>(OBJ_BULLET, new Bullet(distanceToShoot, moveVector, speed, bRandom * 0.03f, 0, shootGunDamage));
		animeDelay = 0.0f;
	}
}
