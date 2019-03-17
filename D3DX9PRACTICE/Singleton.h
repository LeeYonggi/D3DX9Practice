#pragma once


template <class T>
class Singleton
{
public:
	Singleton() { }
	~Singleton() { }

private:
	static T *p;

public:
	static T *GetInstance()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void ReleaseInstance()
	{
		SAFE_DELETE(p);
	}
};

template <typename T>
T *Singleton<T>::p = nullptr;