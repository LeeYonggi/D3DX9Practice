#pragma once
#include "Object.h"

class MapCollision :
	public Object
{
public:
	MapCollision();
	virtual ~MapCollision();
private:
	int mapArray[10][10];

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

};