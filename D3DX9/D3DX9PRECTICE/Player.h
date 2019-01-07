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
	int maxFrame;
	float animeTime;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;
};

