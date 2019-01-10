#pragma once
#include "Object.h"
class Player :
	public Object
{
public:
	Player();
	virtual ~Player();

private:
	vector<MeshLoader*> m_AnimeMesh;
	D3DXVECTOR3 cDistance;
	D3DXVECTOR2 distance;
	int maxFrame;
	float animeTime;
	float speed;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

public:
	void PlayerMove(float _speed);
	void PlayerRotateMove(D3DXVECTOR2 vec2);
	D3DXVECTOR3 PlayerHorizontal();
};

