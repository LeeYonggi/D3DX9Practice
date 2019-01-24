#pragma once
#include "Object.h"

class Player;
class HpUI :
	public Object
{
public:
	HpUI(Player *_player);
	virtual ~HpUI();

private:
	Texture *hp;
	Texture *outLine;
	Texture *blood;
	Color color;
	Player *player;
	float hpRc;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

