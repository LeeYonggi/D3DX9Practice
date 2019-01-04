#include "DXUT.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	Init();
}


ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	for (int i = 0; i < OBJSIZE; i++)
		mObj.insert(make_pair((OBJ_STATE)i, new vector<Object*>));
}

void ObjectManager::Update()
{
	for (auto iter : mObj)
	{
		for (auto _iter = iter.second->begin(); _iter != iter.second->end(); )
		{
			if ((*_iter)->GetDestroy() == true)
			{
				(*_iter)->Release();
				SAFE_DELETE((*_iter));
				_iter = iter.second->erase(_iter);
			}
			else
			{
				if((*_iter)->GetActive())
					(*_iter)->Update();
				++_iter;
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : mObj)
	{
		for (auto _iter = iter.second->begin(); _iter != iter.second->end(); )
		{
			if ((*_iter)->GetActive())
				(*_iter)->Render();
			++_iter;
		}
	}
}

void ObjectManager::Release()
{
	for (auto iter : mObj)
	{
		for (auto _iter : *iter.second)
		{
			SAFE_RELEASE(_iter);
			SAFE_DELETE(_iter);
		}
		iter.second->clear();
		SAFE_DELETE(iter.second);
	}
	mObj.clear();
	
}

Object * ObjectManager::AddObject(OBJ_STATE objState, Object * obj)
{
	auto iter = mObj.find(objState);
	if (iter == mObj.end()) return nullptr;

	obj->Init();
	iter->second->push_back(obj);
	
	return obj;
}

vector<Object*>* ObjectManager::GetObjects(OBJ_STATE objState)
{
	auto iter = mObj.find(objState);
	if (iter == mObj.end()) return nullptr;

	return iter->second;
}
