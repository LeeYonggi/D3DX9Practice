#include "DXUT.h"
#include "Player.h"
#include "TpCamera.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	pos = { -60, 0, 0 };
	rotation = { 0, 180, 0 };
	maxFrame = 1;
	speed = 5.0f;
	scale = { 0.013f, 0.013f, 0.013f };
	cDistance = { 0, 0, 0 };
	for (int i = 0; i < maxFrame; i++)
	{
		string str;
		wstring wstr = L"./Resource/Character/Walk/Walk";
		char ctr[8];
		WCHAR wnumber[8];
	
		wsprintf(wnumber, L"%d", i);
		wstr = wstr + wnumber + L".obj";
		sprintf(ctr, "%d", i);
		str = ctr;
		m_AnimeMesh.push_back(MESHMANAGER->AddObjMesh("Character" + str, wstr.c_str()));
	}
	CAMERAMANAGER->Init(new TpCamera(this));
	animeTime = 0.0f;
}

void Player::Update()
{
	animeTime += ElTime * 25;
	if (animeTime > maxFrame)
		animeTime = 0.0f;

	PlayerRotateMove({ CAMERAMANAGER->GetEye().x, CAMERAMANAGER->GetEye().z });
	PlayerMove(speed);
}

void Player::Render()
{
	MESHMANAGER->RenderMesh(m_AnimeMesh[(int)animeTime], pos, rotation, scale);
}

void Player::Release()
{
}

void Player::PlayerMove(float _speed)
{
	pos += PlayerHorizontal() * _speed * ElTime;
}

void Player::PlayerRotateMove(D3DXVECTOR2 vec2)
{
	TpCamera *tempCam = dynamic_cast<TpCamera*>(CAMERAMANAGER->GetCamera());
	distance.x = tempCam->GetTargetPos().x - vec2.x;
	distance.y = tempCam->GetTargetPos().z - vec2.y;

	rotation.y = D3DXToDegree(-atan2f(distance.y, distance.x)) - 180;
	D3DXVec2Normalize(&distance, &distance);

	D3DXVec3Cross(&cDistance, &CAMERAMANAGER->GetUp(), &Vector3(distance.x, 0, distance.y));
	D3DXVec3Normalize(&cDistance, &cDistance);
}

D3DXVECTOR3 Player::PlayerHorizontal()
{
	Vector3 movement = { 0, 0, 0 };

	if (INPUTMANAGER->IsKeyPress('W'))
	{
		movement.x += distance.x;
		movement.z += distance.y;
	}
	if (INPUTMANAGER->IsKeyPress('A'))
	{
		movement.x -= cDistance.x;
		movement.z -= cDistance.z;
	}
	if (INPUTMANAGER->IsKeyPress('S'))
	{
		movement.x -= distance.x;
		movement.z -= distance.y;
	}
	if (INPUTMANAGER->IsKeyPress('D'))
	{
		movement.x += cDistance.x;
		movement.z += cDistance.z;
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
