#pragma once
#include "Object.h"

const float PLAYERANIMESPEED = 25;
const float STOPMOVEFRAME = 15;
//33
//41
//17
//30
enum PlayerState
{
	PLAYER_IDLE = 33,
	PLAYER_RUN = 41,
	PLAYER_SHOOTING = 17,
	PLAYER_FIRE = 30
};

enum PlayerWeapon
{
	WEAPON_SHOTGUN,
	WEAPON_FIRE
};
enum DIRECTION
{
	NONE,
	LEFT,
	FRONT,
	RIGHT,
	BACK
};

class PlayerBottom;
class PlayerBody;
class Ground;
class Player :
	public Object
{
public:
	Player();
	virtual ~Player();

private:
	vector<MeshLoader*> m_AnimeMesh;

	D3DXVECTOR3 cDistance;
	Vector3 direction;
	DIRECTION moveDirection;
	D3DXVECTOR2 distance;
	Ground *map;
	Texture *playerPixel;

	PlayerBottom	*pBottom;
	PlayerBody		*pBody;

	int maxFrame;
	int hp;
	int maxHp;
	float animeTime;
	float speed;
	float playerH;
	bool isMove;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

public:
	float RotateToDirection();
	void HaveAttacked(); 

public:
	void PlayerMove(float _speed);
	void PlayerRotateMove(D3DXVECTOR2 vec2);
	Vector2 GetDistance() { return distance; }
	D3DXVECTOR3 PlayerHorizontal();
	Vector3 GetDirection() { return direction; }
	DIRECTION GetMoveDirection() { return moveDirection; }
	PlayerBottom *GetBottom() { return pBottom; }
	PlayerBody *GetBody() { return pBody; }
	bool GetIsMove() { return isMove; }
	int GetHp() { return hp; }
	int GetMaxHp() { return maxHp; }
};

