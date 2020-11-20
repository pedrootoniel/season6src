#pragma once
// ----------------------------------------------------------------------------------------------

#include "Object.h"
#include "Defines.h"
// ----------------------------------------------------------------------------------------------

#define MAX_LOOTOBJECT	1000

class CustomPet
{
public:
	CustomPet();
	virtual ~CustomPet();
	void Load();
	//static void _FC SearchTarget(LPVOID This, LPVOID EDX, int ObjectModel);
	static void		PreviewCharSet(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode);
	static void		PetsMovement(int a1, char a2);
	static char		PetHPBar(int a1, int a2);
	static void		RefreshViewPortItem(int a1);
	static void		PetFollowCharacter(int a1, float MaxPos);

	DWORD PetTickCount;
	//static void		MuunStyle(int a1, float MaxPos, float LootPosition);
	//BYTE CharSetView;
	//int ViewOnwer[3];
	//int ViewPet[3];
	//vec_t ViewAngle;
	//float ViewAngle2;
	//float ViewAngle3;

}; extern CustomPet gCustomPet;
