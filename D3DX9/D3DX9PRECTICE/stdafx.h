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

//custom

#include "Singleton.h"
#include "CameraManager.h"
#include "MeshManager.h"
#include "MainProc.h"
