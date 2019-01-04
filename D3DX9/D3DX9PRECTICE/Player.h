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
	float animeTime;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;
};

