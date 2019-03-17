#include "DXUT.h"
#include "Ground.h"


Ground::Ground()
{
	scale = { 1, 1, 1 };

}


Ground::~Ground()
{
}

void Ground::Init()
{
	switch (GAMEMANAGER->stage)
	{
	case STAGE_STATE::STAGE1:
		map = TEXMANAGER->AddTexture("MiniMap", "./Resource/Map/Stage1/Minimap.png");
		meshLoader = MESHMANAGER->AddObjMesh("Ground", L"./Resource/Map/Stage1/Background.obj");
		miniMap = TEXMANAGER->AddTexture("Stage1_Map", "./Resource/UI/Stage1_Map.png");

		break;
	case STAGE_STATE::STAGE2:
		map = TEXMANAGER->AddTexture("MiniMap2", "./Resource/Map/Stage2/Minimap.png");
		meshLoader = MESHMANAGER->AddObjMesh("Ground2", L"./Resource/Map/Stage2/Stage2.obj");
		miniMap = TEXMANAGER->AddTexture("Stage2_Map", "./Resource/UI/Stage2_Map.png");
		break;
	default:
		break;
	}
}

void Ground::Update()
{
}

void Ground::Render()
{
	switch (GAMEMANAGER->stage)
	{
	case STAGE_STATE::STAGE1:
		MESHMANAGER->RenderMesh(meshLoader, { 0, -0.1f, 0 }, { 0, 0, 0 }, scale);
		break;
	case STAGE_STATE::STAGE2:
		MESHMANAGER->RenderMesh(meshLoader, { 0, -0.8f, 0 }, { 0, 0, 0 }, scale);
		break;
	default:
		break;
	}
	TEXMANAGER->RenderSprite(miniMap, { SCREEN_X - 70, 70 }, { 1, 1 }, {1, 1}, 0, Color(255, 255, 255, 180));
}

void Ground::Release()
{
}

