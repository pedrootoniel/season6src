#pragma once
#include "Defines.h"
#include "Object.h"


class Other
{
public:
	void Load();
	static void RamFix(LPVOID lpThreadParameter);
	void UnlockCastleSkills();
	void InitOGLHook();
	static bool	IsExpensiveItem(ObjectItem * lpItem);
	//static BOOL DrawItemNumber(int pObj);
	static void _FC MoveListInit(LPVOID This, LPVOID EDX, int Arg1, int Arg2);
	static void _FC CalculateAttackSpeed(lpCharObj lpUser, LPVOID EDX);
}; extern Other gOther;

static bool IsHoldMouse = false;
