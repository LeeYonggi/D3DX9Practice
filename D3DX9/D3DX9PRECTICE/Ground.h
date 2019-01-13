#pragma once

#define MAPARRAYSIZE 10
class Ground
	: public Object
{
public:
	Ground();
	virtual ~Ground();
private:
	int mapArray[MAPARRAYSIZE][MAPARRAYSIZE];

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

	D3DXVECTOR2 CollisionToArray(D3DXVECTOR2 target);
};

