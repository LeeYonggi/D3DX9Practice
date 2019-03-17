#pragma once
#include "Scene.h"


class LoadScene :
	public Scene
{
public:
	LoadScene();
	virtual ~LoadScene();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

