#pragma once
#include "Object.h"


class SkyBox :
	public Object
{
public:
	SkyBox();
	virtual ~SkyBox();

private:

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

