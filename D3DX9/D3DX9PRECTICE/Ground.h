#pragma once


class Ground
	: public Object
{
public:
	Ground();
	virtual ~Ground();

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

};

