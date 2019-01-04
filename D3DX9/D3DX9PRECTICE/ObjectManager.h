#pragma once
#include "Singleton.h"

#define OBJSIZE 6

enum OBJ_STATE
{
	OBJ_BACKGROUND,
	OBJ_ENEMY,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_EFFECT,
	OBJ_UI
};


class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();
	
private:
	map<OBJ_STATE, vector<Object*>*> mObj;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	Object *AddObject(OBJ_STATE objState, Object *obj);
	vector<Object*>* GetObjects(OBJ_STATE objState);
};

#define OBJECTMANAGER ObjectManager::GetInstance()