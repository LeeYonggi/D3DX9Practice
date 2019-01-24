#pragma once
#include "Singleton.h"

#define OBJSIZE 9

enum OBJ_STATE
{
	OBJ_BACKGROUND,
	OBJ_GROUND,
	OBJ_ENEMY,
	OBJ_CHARACTER,
	OBJ_EBULLET,
	OBJ_BULLET,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_UIEFFECT
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

	template<class T>
	T *AddObject(OBJ_STATE objState, T *obj)
	{
		auto iter = mObj.find(objState);
		if (iter == mObj.end()) return nullptr;

		obj->Init();
		iter->second->push_back(obj);

		return obj;
	}
	vector<Object*>* GetObjects(OBJ_STATE objState);
	Object* GetObjectOfState(OBJ_STATE objState);
};


#define OBJECTMANAGER ObjectManager::GetInstance()