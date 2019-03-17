#include "DXUT.h"
#include "SoundManager.h"

#include "mmsystem.h"
#include "Digitalv.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::AddSound(string str, wstring route, int volume)
{
	auto iter = mSound.find(str);
	if (iter != mSound.end()) return;
	mciOpen.lpstrElementName = route.c_str();
	mciOpen.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	int dwID = mciOpen.wDeviceID;

	MCI_DGV_SETAUDIO_PARMS audioParam;
	audioParam.dwCallback = 0;
	audioParam.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	audioParam.dwValue = volume;
	audioParam.dwOver = 0;
	audioParam.lpstrAlgorithm = 0;
	audioParam.lpstrQuality = 0;
	mciSendCommand(dwID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM,
		(DWORD)(LPVOID)&audioParam);

	mSound.insert(make_pair(str, dwID));
}

void SoundManager::Playbgm(string str, bool isbgm)
{
	auto iter = mSound.find(str);
	if (iter == mSound.end()) return;

	if (isbgm)
	{
		mciSendCommand(iter->second, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
			(DWORD)(LPVOID)&mciPlay);
	}
	else
	{
		mciSendCommand(iter->second, MCI_PLAY, MCI_NOTIFY,
			(DWORD)(LPVOID)&mciPlay);
	}
}

void SoundManager::Stopbgm(string str)
{
	auto iter = mSound.find(str);
	if (iter == mSound.end()) return;

	mciSendCommand(iter->second, MCI_CLOSE, 0, NULL);
	mSound.erase(iter);
}

void SoundManager::Release()
{
	for (auto iter : mSound)
	{
		if (iter.second > 0)
		{
			mciSendCommand(iter.second, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		}
	}
	mSound.clear();
}
