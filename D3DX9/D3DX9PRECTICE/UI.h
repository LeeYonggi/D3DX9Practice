#pragma once
#include "Object.h"

#include <functional>
class Color;
class UI :
	public Object
{
public:
	UI(std::function<void()> _function, Texture *_tex, Color _color);
	UI();
	virtual ~UI();

protected:
	Texture *texture;
	std::function<void()> function;
	Color color;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void LerpColorAlpha();

public:
	void SetTexture(Texture *_tex) { texture = _tex; }
	void SetColor(Color _color) { color = _color; }
	void SetFunc(std::function<void()> func) { function = func; }
};

