#pragma once

#include "User.h"
// -------------------------------------------------------------------------------

#define CB_ERROR					0
#define CB_SUCCESS					1
#define CB_NOT_ENOUGH_ZEN			2
#define CB_TOO_MANY_ITEMS			3
#define CB_LOW_LEVEL_USER			4
#define CB_LACKING_MIX_ITEMS		6
#define CB_INCORRECT_MIX_ITEMS		7
#define CB_INVALID_ITEM_LEVEL		8
#define CB_USER_CLASS_LOW_LEVEL		9
#define CB_NO_BC_CORRECT_ITEMS		10
#define CB_BC_NOT_ENOUGH_ZEN		11
#define CB_IMPROPER_MATERIALS		251
#define CB_PSHOP_OPEN				253
#define CB_ALREADY_OPEN				254
#define FILE_CHAOSMACHINE				"ChaosMachine.xml"
#define PATH_CHAOSMACHINE				"ChaosMachine\\"
// -------------------------------------------------------------------------------

struct ChaosProduce
{
	BYTE	Type;
	short	Index;
	BYTE	LevelMin;
	BYTE	LevelMax;
	BYTE	OptionMin;
	BYTE	OptionMax;
	BYTE	Skill;
	BYTE	Luck;
	BYTE	ExcellentMin;
	BYTE	ExcellentMax;
	BYTE	Ancient;
	BYTE	SocketMin;
	BYTE	SocketMax;
	BYTE	Durability;
};
// -------------------------------------------------------------------------------

struct ChaosIngredient
{
	BYTE	TypeStart;
	short	IndexStart;
	BYTE	TypeEnd;
	short	IndexEnd;
	BYTE	LevelMin;
	BYTE	LevelMax;
	BYTE	OptionMin;
	BYTE	OptionMax;
	BYTE	DurabilityMin;
	BYTE	DurabilityMax;
	BYTE	CountMin;
	BYTE	CountMax;
	char	Tag[50];
};
// -------------------------------------------------------------------------------

struct ChaosTalisman
{
	BYTE	TypeStart;
	short	IndexStart;
	BYTE	TypeEnd;
	short	IndexEnd;
	BYTE	LevelMin;
	BYTE	LevelMax;
	BYTE	OptionMin;
	BYTE	OptionMax;
	BYTE	DurabilityMin;
	BYTE	DurabilityMax;
	BYTE	AdditionalRate; //-1: by durability, 0+: value
	BYTE	CountMax; //-1: none, 0+: value
};
// -------------------------------------------------------------------------------

struct ChaosCombination
{
	char Name[255];
	BYTE SuccessRate;
	int Money;
	std::vector<ChaosIngredient> Ingredients;
	std::vector<ChaosProduce> Produces;
	std::vector<ChaosTalisman> Talismans;
};
// -------------------------------------------------------------------------------

class cChaosRecipe
{
public:
			cChaosRecipe(short RecipeIndex);
	virtual ~cChaosRecipe();
 
	void Init();
	bool Read(LPSTR File);
 
	static void	ActStart(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination);
	static bool	ActCheck(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination);
	static void ActFail(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination);
	static void ActFail(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, BYTE ErrorCode);
	static void	ActSuccess(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, ChaosProduce* lpProduce);
 
	static bool	CheckIngredient(LPOBJ lpUser, short ChaosPos, ChaosIngredient* lpIngredient);
	static bool	CheckTalisman(LPOBJ lpUser, short ChaosPos, ChaosTalisman* lpTalisman);
	static bool	ApplyTalisman(LPOBJ lpUser, short ChaosPos, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, ChaosTalisman* lpTalisman);
public:
	char Name[255];
	short RecipeIndex;
	std::vector<ChaosCombination> Combinations;
};
// -------------------------------------------------------------------------------

class cChaosBoxManager
{
public:
	cChaosBoxManager();
	virtual ~cChaosBoxManager();

	//void	Init();
	//void	Load();
	void	Read(char* File);
 
	bool	StartMix(LPOBJ lpUser, short RecipeIndex);
private:
	std::vector<cChaosRecipe*> Recipes;
}; extern cChaosBoxManager gChaosBoxManager;