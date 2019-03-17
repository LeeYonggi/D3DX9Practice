#include "DXUT.h"
#include "LoadScene.h"

#include "IngameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	MESHMANAGER->AddObjMesh("Ground", L"./Resource/Map/Stage1/stage1.obj");
	MESHMANAGER->AddObjMesh("Ground2", L"./Resource/Map/Stage2/Stage2.obj");
	
	//Player
	MESHMANAGER->AddObjAnime("Player_Bottom_Idle", L"./Resource/Character/Idle/Bottom/Bottom_Idle", 0, PlayerState::PLAYER_IDLE);
	MESHMANAGER->AddObjAnime("Player_Body_Idle", L"./Resource/Character/Idle/Body/Body_Idle", 0, PlayerState::PLAYER_IDLE);
	MESHMANAGER->AddObjAnime("Player_Body_running", L"./Resource/Character/Running/Body/Body_Running", 0, PlayerState::PLAYER_RUN);
	MESHMANAGER->AddObjAnime("Player_Bottom_running", L"./Resource/Character/Running/Bottom/Bottom_Running", 0, PlayerState::PLAYER_RUN);
	MESHMANAGER->AddObjAnime("Player_Body_Shooting", L"./Resource/Character/Shooting/Body/body_shooing", 0, PlayerState::PLAYER_SHOOTING);
	MESHMANAGER->AddObjAnime("Player_Body_FireAttack",
		L"./Resource/Character/FireAttack/Player_FireAttack", 0, PlayerState::PLAYER_FIRE);
	//Enemy
	EnemyState state = EnemyState();
	MESHMANAGER->AddObjAnime("Enemy1_Idle", L"./Resource/Enemy/Enemy1/Idle/Monster1_Idle", 0, state.ENEMY_IDLE);
	MESHMANAGER->AddObjAnime("Enemy1_Move", L"./Resource/Enemy/Enemy1/Move/Monster1_Move", 0, state.ENEMY_MOVE);
	MESHMANAGER->AddObjAnime("Enemy1_Die", L"./Resource/Enemy/Enemy1/Die/Monster1_Die", 0, state.ENEMY_DIE);
	MESHMANAGER->AddObjAnime("Enemy1_Attack", L"./Resource/Enemy/Enemy1/Attack/Monster1_Attack", 0, state.ENEMY_ATTACK);
	
	EnemyState state2 = Enemy2State();
	MESHMANAGER->AddObjAnime("Enemy2_Idle", L"./Resource/Enemy/Enemy2/Idle/Enemy2_Idle", 0, state2.ENEMY_IDLE);
	MESHMANAGER->AddObjAnime("Enemy2_Move", L"./Resource/Enemy/Enemy2/Move/Enemy2_Move", 0, state2.ENEMY_MOVE);
	MESHMANAGER->AddObjAnime("Enemy2_Die", L"./Resource/Enemy/Enemy2/Die/Enemy2_Die", 0, state2.ENEMY_DIE);
	MESHMANAGER->AddObjAnime("Enemy2_Attack", L"./Resource/Enemy/Enemy2/Attack/Enemy2_Attack", 0, state2.ENEMY_ATTACK);

	EnemyState state3 = BossState();
	MESHMANAGER->AddObjAnime("Boss_Idle", L"./Resource/Enemy/Boss/Idle/Boss_Idle", 0, state3.ENEMY_IDLE);
	MESHMANAGER->AddObjAnime("Boss_Move", L"./Resource/Enemy/Boss/Move/Boss_Move", 0, state3.ENEMY_MOVE);
	MESHMANAGER->AddObjAnime("Boss_Die", L"./Resource/Enemy/Boss/Die/Boss_Die", 0, state3.ENEMY_DIE);
	MESHMANAGER->AddObjAnime("Boss_Attack", L"./Resource/Enemy/Boss/Attack/Boss_Attack", 0, state3.ENEMY_ATTACK);
	//Effect
	MESHMANAGER->AddObjMesh("EnemyBullet", L"./Resource/Enemy/Bullet/EnemyBullet.obj");
	MESHMANAGER->AddObjMesh("BulletPlan", L"./Resource/Effect/BulletFire.obj");
	TEXMANAGER->AddAnimeTexture("./Resource/Effect/FireEffect/bomb_%d.png", 2, 8);
	TEXMANAGER->AddAnimeTexture("./Resource/Effect/BulletEffect/bullet_effect_%d.png", 1, 6);
	TEXMANAGER->AddAnimeTexture("./Resource/Effect/BulletFire/effect%d.png", 1, 6);
	//UI
	TEXMANAGER->AddTexture("Stage1_Map", "./Resource/UI/Stage1_Map.png");
	TEXMANAGER->AddTexture("PlayerPixel", "./Resource/UI/Player.png");
	TEXMANAGER->AddTexture("Hp", "./Resource/UI/Hp.png");
	TEXMANAGER->AddTexture("HpOutline", "./Resource/UI/HpOutline.png");
	TEXMANAGER->AddTexture("HpBlood", "./Resource/UI/HpBlood.png");
	TEXMANAGER->AddTexture("PlayerBlood", "./Resource/Effect/damage_effect/damage_5.png");
}

void LoadScene::Update()
{
	SCENEMANAGER->AddScene(new IngameScene);
}

void LoadScene::Render()
{
}

void LoadScene::Release()
{
}
