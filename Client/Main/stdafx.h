#pragma once

typedef unsigned __int64 QWORD;

#define WIN32_LEAN_AND_MEAN
//
//#define _WIN32_WINNT _WIN32_WINNT_WINXP

// System Include
#include "targetver.h"
#define PI 3.14159265

#include <windows.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <string>
#include "detours.h"
#include "zzzmathlib.h"
#include <gl\GL.h>
#include <time.h>
#include <Shellapi.h>
#include <string.h>
#include <algorithm>
#include <winioctl.h>
#include <vector>
#include <atltime.h>
#include "..\\..\\Util\\lua\\include\\lua.hpp"
#pragma comment(lib, "..\\..\\Util\\lua\\lib\\lua52.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Opengl32.lib")
#pragma comment(lib,"detours.lib")

#pragma pack(push, 1)
struct MU3Float
{
	float X;
	float Y;
	float Z;
};
#pragma pack(pop)

#define DLL_VERSION "6.4"