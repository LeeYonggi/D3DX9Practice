#pragma once
#include "Singleton.h"

#define KEY_SIZE 256
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

private:
	bool nowKey[KEY_SIZE];
	bool pastKey[KEY_SIZE];
	D3DXVECTOR2 cursor;

public:
	void Init();
	void Update();

	D3DXVECTOR2 GetCusor() { return cursor; }
	bool IsKeyDown(int key) { return (pastKey[key] == false && nowKey[key] == true) ? true : false; }
	bool IsKeyPress(int key){ return (pastKey[key] == true && nowKey[key] == true) ? true : false; }
	bool IsKeyUp(int key)	{ return (pastKey[key] == true && nowKey[key] == false) ? true : false; }
};

#define INPUTMANAGER InputManager::GetInstance()