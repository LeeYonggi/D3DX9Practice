#pragma once

#define MAPARRAYSIZE 10
class Ground
	: public Object
{
public:
	Ground();
	virtual ~Ground();
private:
	Texture *map;
	Texture *miniMap;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

public:
	Texture *GetMap() { return map; }
};
