#pragma once

//C, C++

#include <vector>
#include <map>
#include <string>

using namespace std;

//define

#define SCREEN_X 1280.0f
#define SCREEN_Y 720.0f
#define DEVICE DXUTGetD3D9Device()
#define M_HWND DXUTGetHWND()
#define ElTime DXUTGetElapsedTime() * timeScale

typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
extern float timeScale;

//custom

#include "d3dUtility.h"
#include "MeshLoader.h"

#include "Singleton.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TexManager.h"
#include "Object.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "CameraManager.h"
#include "MeshManager.h"
#include "GameManager.h"
#include "IngameScene.h"
#include "MainProc.h"
