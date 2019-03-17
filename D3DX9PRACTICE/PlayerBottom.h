#pragma once
#include "Object.h"
#include "Player.h"

class Player;
class PlayerBottom :
	public Object
{
public:
	PlayerBottom(Player *_parent);
	virtual ~PlayerBottom();

private:
	vector<MeshLoader*> bottom_Running;
	vector<MeshLoader*> bottom_Idle;
	Player *parent;
	PlayerState bottomState;
	PlayerState nextState;
	Vector3 smoothDirection;
	float animeDelay;
	float stopFrame;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:

public:
	void SetBottomState(PlayerState state) { nextState = state; }
	PlayerState GetBottomState() { return bottomState; }
};

