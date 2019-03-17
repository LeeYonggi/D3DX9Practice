#pragma once
#include "Scene.h"
class IngameScene :
	public Scene
{
public:
	IngameScene();
	virtual ~IngameScene();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

