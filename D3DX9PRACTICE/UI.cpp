#include "DXUT.h"
#include "UI.h"


UI::UI(std::function<void()> _function, Texture *_tex, Color _color)
{
	function = _function;
	texture = _tex;
	color = _color;
}

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init()
{
}

void UI::Update()
{
	if (function)
	{
		function();
	}
}

void UI::Render()
{
	TEXMANAGER->RenderSprite(texture, { pos.x, pos.y }, { 1, 1 }, {scale.x, scale.y}, rotation.z, color);
}

void UI::Release()
{
}

void UI::LerpColorAlpha()
{
	color.a -= 3;
	if (color.a < 100)
		SetDestroy(true);
}
