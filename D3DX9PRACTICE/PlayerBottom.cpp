#include "DXUT.h"
#include "PlayerBottom.h"

#include "Player.h"


PlayerBottom::PlayerBottom(Player * _parent)
{
	parent = _parent;
	animeDelay = 0.f;
	bottomState = PlayerState::PLAYER_RUN;
	nextState = PlayerState::PLAYER_RUN;

	pos = _parent->GetPos();
	rotation = _parent->GetRotation();
	scale = _parent->GetSize();

	smoothDirection = rotation;
	stopFrame = 0.0f;
}

PlayerBottom::~PlayerBottom()
{
}

void PlayerBottom::Init()
{
	bottom_Running = MESHMANAGER->AddObjAnime("Player_Bottom_running", L"./Resource/Character/Running/Bottom/Bottom_Running", 0, 41);
	bottom_Idle = MESHMANAGER->AddObjAnime("Player_Bottom_Idle", L"./Resource/Character/Idle/Bottom/Bottom_Idle", 0, PlayerState::PLAYER_IDLE);
}

void PlayerBottom::Update()
{
	pos = parent->GetPos();
	scale = parent->GetSize();
	rotation.x = parent->GetRotation().x;
	rotation.z = parent->GetRotation().z;

	animeDelay += ElTime * PLAYERANIMESPEED;
	if (animeDelay > bottomState)
		animeDelay = 0.0f;

	switch (bottomState)
	{
	case PlayerState::PLAYER_IDLE:
		if (parent->GetIsMove())
		{
			bottomState = PlayerState::PLAYER_RUN;
			animeDelay = 0.0f;
		}
		break;
	case PlayerState::PLAYER_RUN:
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
			bottomState = PlayerState::PLAYER_IDLE;
			animeDelay = 0;
			stopFrame = 0;
		}
		break;
	default:
		break;

	}
	float targetRotate;
	if (bottomState == PlayerState::PLAYER_RUN)
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

void PlayerBottom::Render()
{
	switch (bottomState)
	{
	case PLAYER_IDLE:
		MESHMANAGER->RenderMesh(bottom_Idle[(int)animeDelay], pos, rotation, scale);
		break;
	case PLAYER_RUN:
		MESHMANAGER->RenderMesh(bottom_Running[(int)animeDelay], pos, rotation, scale);
		break;
	case PLAYER_SHOOTING:
		break;
	default:
		break;
	}
}

void PlayerBottom::Release()
{
}

