#include "DXUT.h"
#include "Object.h"

#include "Ground.h"

Object::Object()
{
	destroy = false;
	active = true;
	rotation = { 0, 0, 0 };
	pos = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	objRadius = 1.0f;
}


Object::~Object()
{
}

bool Object::IsCollisionGround(Vector3 vec3, Ground *map)
{
	bool isCollision;
	D3DLOCKED_RECT lockRect;

	auto mapTex = map->GetMap()->tex;
	mapTex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD *pColor = (DWORD*)lockRect.pBits;

	int x = (int)vec3.x;
	int y = (int)vec3.z;

	int texW = map->GetMap()->info.Width;
	//cout << (x + texW * 0.5f) << ", " << (y + texW * 0.5f) << endl;
	D3DXCOLOR color = pColor[(int)((y + texW * 0.5f) * texW + (x + texW * 0.5f))];

	if (color == D3DXCOLOR(1.f, 0.f, 1.f, 1.f))
		isCollision = true;
	else
		isCollision = false;

	mapTex->UnlockRect(0);
	return isCollision;
}

bool Object::IsCollisionCircle(Vector3 p1, Vector3 p2, float r1, float r2)
{
	float tempX = p2.x - p1.x;
	float tempY = p2.y - p1.y;
	float tempZ = p2.z - p1.z;
	float length = (tempX * tempX) + (tempZ * tempZ);
	length = length + (tempY * tempY);
	length = sqrt(length);

	return (r1 + r2 > length);
}

float Object::GetVec2Angle(Vector2 distance)
{
	return D3DXToDegree(-atan2f(distance.y, distance.x)) + 90;
}

Vector2 Object::GetVec2TrackingPos(Vector3 p1)
{
	Vector2 temp;
	temp.x = p1.x - pos.x;
	temp.y = p1.z - pos.z;
	D3DXVec2Normalize(&temp, &temp);
	return temp;
}

float Object::GetDotRotationLerp(const float & p1, const float & p2)
{
	D3DXVECTOR2 dot1;
	dot1.x = sin(D3DXToRadian(p1));
	dot1.y = cos(D3DXToRadian(p1));
	D3DXVec2Normalize(&dot1, &dot1);
	D3DXVECTOR2 dot2;
	dot2.x = sin(D3DXToRadian(p2 - 90));
	dot2.y = cos(D3DXToRadian(p2 - 90));
	D3DXVec2Normalize(&dot2, &dot2);
	float s = D3DXToDegree(D3DXVec2Dot(&dot1, &dot2));

	return d3d::Lerp<float>(0.f, s, 0.1f);
}