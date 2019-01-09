#include "DXUT.h"
#include "Object.h"


Object::Object()
{
	destroy = false;
	active = true;
	rotation = { 0, 0, 0 };
	pos = { 0, 0, 0 };
	scale = { 1, 1, 1 };
}


Object::~Object()
{
}
