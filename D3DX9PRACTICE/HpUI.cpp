#include "DXUT.h"
#include "HpUI.h"

#include "Player.h"

HpUI::HpUI(Player *_player)
{
	player = _player;
}


HpUI::~HpUI()
{
}

void HpUI::Init()
{
	hp		= TEXMANAGER->AddTexture("Hp", "./Resource/UI/Hp.png");
	outLine	= TEXMANAGER->AddTexture("HpOutline", "./Resource/UI/HpOutline.png");
	blood	= TEXMANAGER->AddTexture("HpBlood", "./Resource/UI/HpBlood.png");
	color = { 255, 255, 255, 180 };
	SetPos(Vector3(SCREEN_X * 0.9f, SCREEN_Y * 0.8f, 0));
}

void HpUI::Update()
{
	hpRc = 1 - (float)player->GetHp() / (float)player->GetMaxHp();
}

void HpUI::Render()
{
	TEXMANAGER->RenderSprite(hp, { pos.x, pos.y }, { 1, 1 }, { scale.x, scale.y }, rotation.z, color);
	TEXMANAGER->RenderSprite(blood, { pos.x, pos.y }, { 1, hpRc }, { scale.x, scale.y }, rotation.z, color);
	TEXMANAGER->RenderSprite(outLine, { pos.x, pos.y }, { 1, 1 }, { scale.x, scale.y }, rotation.z, color);
}

void HpUI::Release()
{
}
