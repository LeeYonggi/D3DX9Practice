#pragma once
#include "Singleton.h"

class SoundManager :
	public Singleton<SoundManager>
{
public:
	SoundManager();
	virtual ~SoundManager();

private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	map<string, int> mSound;

public:
	void AddSound(string str, wstring route, int volume);
	void Playbgm(string str, bool isbgm);
	void Stopbgm(string str);
	void Release();
};

#define SOUNDMANAGER SoundManager::GetInstance()