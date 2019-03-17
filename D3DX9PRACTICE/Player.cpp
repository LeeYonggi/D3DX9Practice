#include "DXUT.h"
#include "Player.h"
#include "TpCamera.h"
#include "Ground.h"
#include "PlayerBottom.h"
#include "PlayerBody.h"
#include "Bullet.h"
#include <iostream>
#include "UI.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	CAMERAMANAGER->Init(new TpCamera(this));
	map = dynamic_cast<Ground*>(OBJECTMANAGER->GetObjectOfState(OBJ_GROUND));
	playerPixel = TEXMANAGER->AddTexture("PlayerPixel", "./Resource/UI/Player.png");
	
	pos = { 24, 0, 18 };
	rotation = { 0, 180, 0 };
	maxFrame = 1;
	speed = 5.0f;
	scale = { 0.013f, 0.013f, 0.013f };
	cDistance = { 0, 0, 0 };
	hp = 150;
	maxHp = 150;

	animeTime = 0.0f;
	isMove = false;
	objRadius = 1.5f;
	playerH = 1.8f;

	pBottom = OBJECTMANAGER->AddObject<PlayerBottom>(OBJ_CHARACTER, new PlayerBottom(this));
	pBody =	OBJECTMANAGER->AddObject<PlayerBody>(OBJ_CHARACTER, new PlayerBody(this));
}

void Player::Update()
{
	isMove = false;
	PlayerMove(speed);
	if (isMove)
	{
		
	}
	HaveAttacked();

	PlayerRotateMove({ CAMERAMANAGER->GetEye().x, CAMERAMANAGER->GetEye().z });
}

void Player::Render()
{
	Vector2 uiPos;
	uiPos.x = pos.x + map->GetMap()->info.Width * 0.5f;
	uiPos.y = pos.z + map->GetMap()->info.Width * 0.5f;
	uiPos *= 2;
	uiPos.x += SCREEN_X - 140;
	TEXMANAGER->RenderSprite(playerPixel, uiPos, {1, 1});
}

void Player::Release()
{
}

float Player::RotateToDirection()
{
	float tempRotate = 0;
	switch (GetMoveDirection())
	{
	case LEFT:
		tempRotate -= 30;
		break;
	case RIGHT:
		tempRotate += 30;
		break;
	default:
		break;
	}

	return tempRotate;
}

void Player::HaveAttacked()
{
	Vector3 cTempVec3 = pos;
	cTempVec3.y += playerH;
	int tempHp = hp;
	auto iter = OBJECTMANAGER->GetObjects(OBJ_EBULLET);
	for (int i = 0; i < iter->size(); ++i)
	{
		if (IsCollisionCircle(cTempVec3, (*iter)[i]->GetPos(), objRadius, (*iter)[i]->GetRadius()))
		{
			hp -= dynamic_cast<Bullet*>((*iter)[i])->GetDamage();
			dynamic_cast<Bullet*>((*iter)[i])->SetBulletState(BulletState::BULLET_EFFECT);
		}
	}

	if (tempHp > hp)
	{
		UI *temp = OBJECTMANAGER->AddObject<UI>(OBJ_UIEFFECT, new UI);
		temp->SetTexture(TEXMANAGER->AddTexture("PlayerBlood", "./Resource/Effect/damage_effect/damage_5.png"));
		temp->SetPos({SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0});
		temp->SetColor({ 255, 255, 255, 200 });
		temp->SetFunc([temp]() { temp->LerpColorAlpha(); });
	}
}

void Player::PlayerMove(float _speed)
{
	direction = PlayerHorizontal();
	if (!isMove) return;
	Vector3 nextPos = (pos + direction * _speed * ElTime);

	D3DLOCKED_RECT lockRect;
	auto mapTex = map->GetMap()->tex;
	mapTex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD *pColor = (DWORD*)lockRect.pBits;

	int x = (int)nextPos.x;
	int y = (int)nextPos.z;

	int texW = map->GetMap()->info.Width;
	cout << (x + texW * 0.5f) << ", " << (y + texW * 0.5f) << endl;
	D3DXCOLOR color = pColor[(int)((y + texW * 0.5f) * texW + (x + texW * 0.5f))];

	if (color != D3DXCOLOR(1.f, 0.f, 1.f, 1.f))
		pos = pos + direction * _speed * ElTime;

	mapTex->UnlockRect(0);
}

void Player::PlayerRotateMove(D3DXVECTOR2 vec2)
{
	TpCamera *tempCam = dynamic_cast<TpCamera*>(CAMERAMANAGER->GetCamera());
	distance.x = tempCam->GetAt().x - tempCam->GetEye().x;
	distance.y = tempCam->GetAt().z - tempCam->GetEye().z;

	rotation.y = (D3DXToDegree(-atan2f(distance.y, distance.x)) - 180) + 360;
	D3DXVec2Normalize(&distance, &distance);

	D3DXVec3Cross(&cDistance, &CAMERAMANAGER->GetUp(), &Vector3(distance.x, 0, distance.y));
	D3DXVec3Normalize(&cDistance, &cDistance);
}

D3DXVECTOR3 Player::PlayerHorizontal()
{
	Vector3 movement = { 0, 0, 0 };
	moveDirection = NONE;
	if (INPUTMANAGER->IsKeyPress('W'))
	{
		movement.x += distance.x;
		movement.z += distance.y;
		isMove = true;
	}
	if (INPUTMANAGER->IsKeyPress('A'))
	{
		movement.x -= cDistance.x;
		movement.z -= cDistance.z;
		isMove = true;
		moveDirection = LEFT;
	}
	if (INPUTMANAGER->IsKeyPress('S'))
	{
		movement.x -= distance.x;
		movement.z -= distance.y;
		isMove = true;
	}
	if (INPUTMANAGER->IsKeyPress('D'))
	{
		movement.x += cDistance.x;
		movement.z += cDistance.z;
		isMove = true;
		moveDirection = RIGHT;
	}

	return movement;
}

#pragma region SinToMove
	/*
	if (INPUTMANAGER->IsKeyPress('W')) 
	{
		movement.x -= sin(D3DXToRadian(rotation.y));
		movement.z -= cos(D3DXToRadian(rotation.y));
	}
	if (INPUTMANAGER->IsKeyPress('A'))
	{
		movement.x += sin(D3DXToRadian(rotation.y + 90));
		movement.z += cos(D3DXToRadian(rotation.y + 90));
	}
	if (INPUTMANAGER->IsKeyPress('S'))
	{
		movement.x += sin(D3DXToRadian(rotation.y));
		movement.z += cos(D3DXToRadian(rotation.y));
	}
	if (INPUTMANAGER->IsKeyPress('D'))
	{
		movement.x -= sin(D3DXToRadian(rotation.y + 90));
		movement.z -= cos(D3DXToRadian(rotation.y + 90));
	}
	*/
#pragma endregion
