#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	Init();
}


InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

	cursor = { 0, 0 };
}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));

	for (int i = 0; i < KEY_SIZE; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;

	POINT point;
	ScreenToClient(DXUTGetHWND(), &point);
	GetCursorPos(&point);

	cursor = { (float)point.x, (float)point.y };
}
