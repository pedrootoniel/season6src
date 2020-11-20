#pragma once
// ----------------------------------------------------------------------------------------------

#include "Object.h"
// ----------------------------------------------------------------------------------------------

class Jewel
{
public:
	void			Load();
	// ----
	static bool		IsCustomWings(WORD ItemID, bool Preview);
	static bool		IsCustomJewels(WORD ItemID, bool Preview);
	// ----
	static bool		IsExpensiveItem(ObjectItem * lpItem);
	static bool	_FC	GetUpgradeFlag(LPVOID This, LPVOID EDX, ObjectItem * lpSource, ObjectItem * lpTarget);
	// ----
}; extern Jewel gJewel;
// ----------------------------------------------------------------------------------------------