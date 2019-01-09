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

	D3DXVECTOR2 distance;
	distance.x = CAMERAMANAGER->GetAt().x - CAMERAMANAGER->GetEye().x;
	distance.y = CAMERAMANAGER->GetAt().z - CAMERAMANAGER->GetEye().z;

	rotation.y = D3DXToDegree(-atan2f(distance.y, distance.x)) -  90;

	if (INPUTMANAGER->IsKeyPress('W'))
	{
		pos.x++;
	}
}

void Player::Render()
{
	MESHMANAGER->RenderMesh(m_AnimeMesh[(int)animeTime], pos, rotation);
}

void Player::Release()
{
}
