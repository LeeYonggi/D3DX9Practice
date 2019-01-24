#pragma once
#include "Object.h"
class FireEffect :
	public Object
{
public:
	FireEffect(Vector3 initPos);
	virtual ~FireEffect();

private:
	vector<Texture*> vFireAnime;
	Vector3 playerPos;
	float frame;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

