#include "stdafx.h"
#include "ChaosBoxManager.h"
#include "Util.h"
#include "ItemManager.h"
#include "DSProtocol.h"
#include "SetItemOption.h"
#include "SocketItemType.h"
#include "ChaosBox.h"
#include "RandomManager.h"
#include "Path.h"
#include "Log.h"
// -------------------------------------------------------------------------------
cChaosBoxManager gChaosBoxManager;
CRandomManager RandomManager;
// -------------------------------------------------------------------------------

cChaosRecipe::cChaosRecipe(short RecipeIndex)
{
	this->RecipeIndex = RecipeIndex;
}
// -------------------------------------------------------------------------------

cChaosRecipe::~cChaosRecipe()
{
	this->Init();
}
// -------------------------------------------------------------------------------

void cChaosRecipe::Init()
{
	this->Combinations.clear();

	if (this->Combinations.capacity() > 0)
	{
		std::vector<ChaosCombination>().swap(this->Combinations);
	}

	this->RecipeIndex = -1;
}
// -------------------------------------------------------------------------------

bool cChaosRecipe::Read(LPSTR File)
{
	pugi::xml_document Document;
	pugi::xml_parse_result Result = Document.load_file(File);

	if (Result.status != pugi::status_ok)
	{
		MsgBox("[ChaosRecipe] File %s not found!", File);
		return false;
	}

	pugi::xml_node Recipe	= Document.child("recipe");
	strncpy(this->Name, Recipe.attribute("name").as_string(), sizeof(this->Name));

	for (pugi::xml_node CombinationNode = Recipe.child("combination"); CombinationNode; CombinationNode = CombinationNode.next_sibling())
	{
		ChaosCombination lpCombination;
		strncpy(lpCombination.Name, CombinationNode.attribute("name").as_string(), sizeof(lpCombination.Name));
		lpCombination.Money = CombinationNode.child("money").text().as_int(0);
		lpCombination.SuccessRate = CombinationNode.child("successrate").text().as_int(0);
		// ----
		int Op1Rate		= CombinationNode.child("excoption").attribute("op1").as_int();
		int Op2Rate		= CombinationNode.child("excoption").attribute("op2").as_int();
		int Op4Rate		= CombinationNode.child("excoption").attribute("op4").as_int();
		int Op8Rate		= CombinationNode.child("excoption").attribute("op8").as_int();
		int Op16Rate	= CombinationNode.child("excoption").attribute("op16").as_int();
		int Op32Rate	= CombinationNode.child("excoption").attribute("op32").as_int();
		// ----
		//m_ExcellentPool.InitPool();
		RandomManager.AddElement(1, Op1Rate);
		RandomManager.AddElement(2, Op2Rate);
		RandomManager.AddElement(4, Op4Rate);
		RandomManager.AddElement(8, Op8Rate);
		RandomManager.AddElement(16, Op16Rate);
		RandomManager.AddElement(32, Op32Rate);
		// ----
				
		for (pugi::xml_node IngredientNode = CombinationNode.child("ingredients").child("item"); IngredientNode; IngredientNode = IngredientNode.next_sibling())
		{
			ChaosIngredient lpIngredient = { 0 };
			lpIngredient.TypeStart = IngredientNode.attribute("starttype").as_int(0);
			lpIngredient.IndexStart = IngredientNode.attribute("startindex").as_int(0);
			lpIngredient.TypeEnd = IngredientNode.attribute("endtype").as_int(0);
			lpIngredient.IndexEnd = IngredientNode.attribute("endindex").as_int(0);
			lpIngredient.LevelMin = (BYTE)IngredientNode.attribute("minlevel").as_int(0);
			lpIngredient.LevelMax = (BYTE)IngredientNode.attribute("maxlevel").as_int(0);
			lpIngredient.OptionMin = IngredientNode.attribute("minoption").as_int(0);
			lpIngredient.OptionMax = IngredientNode.attribute("maxoption").as_int(0);
			lpIngredient.DurabilityMin = IngredientNode.attribute("mindur").as_int(0);
			lpIngredient.DurabilityMax = IngredientNode.attribute("maxdur").as_int(0);
			lpIngredient.CountMin = IngredientNode.attribute("mincount").as_int(0);
			lpIngredient.CountMax = IngredientNode.attribute("maxcount").as_int(0);
			strncpy(lpIngredient.Tag, CombinationNode.attribute("tag").as_string(), sizeof(lpIngredient.Tag));
			lpCombination.Ingredients.push_back(lpIngredient);
		}

		for (pugi::xml_node TalismanNode = CombinationNode.child("talismans").child("item"); TalismanNode; TalismanNode = TalismanNode.next_sibling())
		{
			ChaosTalisman lpTalisman = { 0 };
			lpTalisman.TypeStart = TalismanNode.attribute("starttype").as_int(0);
			lpTalisman.IndexStart = TalismanNode.attribute("startindex").as_int(0);
			lpTalisman.TypeEnd = TalismanNode.attribute("endtype").as_int(0);
			lpTalisman.IndexEnd = TalismanNode.attribute("endindex").as_int(0);
			lpTalisman.LevelMin = (BYTE)TalismanNode.attribute("minlevel").as_int(0);
			lpTalisman.LevelMax = (BYTE)TalismanNode.attribute("maxlevel").as_int(0);
			lpTalisman.OptionMin = TalismanNode.attribute("minoption").as_int(0);
			lpTalisman.OptionMax = TalismanNode.attribute("maxoption").as_int(0);
			lpTalisman.DurabilityMin = TalismanNode.attribute("mindur").as_int(0);
			lpTalisman.DurabilityMax = TalismanNode.attribute("maxdur").as_int(0);
			lpTalisman.AdditionalRate = TalismanNode.attribute("addrate").as_int(0);
			lpTalisman.CountMax = TalismanNode.attribute("countmax").as_int(0);
			lpCombination.Talismans.push_back(lpTalisman);
		}

		for (pugi::xml_node ProduceNode = CombinationNode.child("produces").child("item"); ProduceNode; ProduceNode = ProduceNode.next_sibling())
		{
			ChaosProduce lpProduce = { 0 };
			lpProduce.Type = ProduceNode.attribute("type").as_int(0);
			lpProduce.Index = ProduceNode.attribute("index").as_int(0);
			lpProduce.LevelMin = ProduceNode.attribute("minlevel").as_int(0);
			lpProduce.LevelMax = ProduceNode.attribute("maxlevel").as_int(0);
			lpProduce.OptionMin = ProduceNode.attribute("minoption").as_int(0);
			lpProduce.OptionMax = ProduceNode.attribute("maxoption").as_int(0);
			lpProduce.Skill = ProduceNode.attribute("skill").as_int(0);
			lpProduce.Luck = ProduceNode.attribute("luck").as_int(0);
			lpProduce.ExcellentMin = ProduceNode.attribute("excmin").as_int(0);
			lpProduce.ExcellentMax = ProduceNode.attribute("excmax").as_int(0);
			lpProduce.Ancient = ProduceNode.attribute("ancient").as_int(0);
			lpProduce.SocketMin = ProduceNode.attribute("sockmin").as_int(0);
			lpProduce.SocketMax = ProduceNode.attribute("sockmax").as_int(0);
			lpProduce.Durability = ProduceNode.attribute("dur").as_int(0);
			lpCombination.Produces.push_back(lpProduce);
		}

		this->Combinations.push_back(lpCombination);
	}

	return true;
}
// -------------------------------------------------------------------------------

void cChaosRecipe::ActStart(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination)
{
	lpUser->ChaosSuccessRate += lpCombination->SuccessRate;

	int ProduceIndex = GetLargeRand() % lpCombination->Produces.size();
	ChaosProduce* lpProduce = &lpCombination->Produces[ProduceIndex];

	if (lpProduce == NULL)
	{
		//LogAddC(2, "[DEBUG] Produce not found");
		return;
	}
	
	if (lpUser->Money < lpCombination->Money)
	{
		cChaosRecipe::ActFail(lpUser, lpRecipe, lpCombination, CB_NOT_ENOUGH_ZEN);
		return;
	}

	DWORD Random = GetLargeRand() % 100;
	lpUser->ChaosLock = true;
	lpUser->Money -= lpCombination->Money;
	GCMoneySend(lpUser->Index, lpUser->Money);

	if (Random > lpUser->ChaosSuccessRate)
	{
		cChaosRecipe::ActFail(lpUser, lpRecipe, lpCombination);
	}
	else
	{
		cChaosRecipe::ActSuccess(lpUser, lpRecipe, lpCombination, lpProduce);
	}	
}
// -------------------------------------------------------------------------------

bool cChaosRecipe::ActCheck(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination)
{
	return false;
}
// -------------------------------------------------------------------------------

void cChaosRecipe::ActFail(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, BYTE ErrorCode)
{
	PMSG_CHAOS_MIX_SEND pMsg;
	pMsg.header.set(0x86,sizeof(pMsg));
	pMsg.result = ErrorCode;
	
//	ChaosBoxWingMixItemDown(lpObj);
	gChaosBox.ChaosBoxInit(lpUser);
	gChaosBox.GCChaosBoxSend(lpUser, 0);
	DataSend(lpUser->Index,(BYTE*)&pMsg,pMsg.header.size);

	lpUser->ChaosLock = false;
	gLog.Output(LOG_CHAOS_MIX,"[ChaosRecipe] [%s] [%s] Combination has failed (Recipe: %s, Combination: %s, Rate: %d)",
		lpUser->Account, lpUser->Name, lpRecipe->Name, lpCombination->Name, 
		lpUser->ChaosSuccessRate);
}
// -------------------------------------------------------------------------------

void cChaosRecipe::ActFail(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination)
{
	cChaosRecipe::ActFail(lpUser, lpRecipe, lpCombination, CB_ERROR);
}
// -------------------------------------------------------------------------------

void cChaosRecipe::ActSuccess(LPOBJ lpUser, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, ChaosProduce* lpProduce)
{
	BYTE Level = 0;
	BYTE Luck = 0;
	BYTE Option = 0;
	int	ExcOption = 0;
	int SetOption		= 0;
	int SocketCount		= 0;
	BYTE SocketBonus	= (BYTE)-1;
	BYTE SocketOption[5] = {0xFF,0xFF,0xFF,0xFF,0xFF};
	int ItemNumber = GET_ITEM(lpProduce->Type, lpProduce->Index);

	if (lpProduce->LevelMax == lpProduce->LevelMin)
	{
		Level = lpProduce->LevelMax;
	}
	else if (lpProduce->LevelMin < lpProduce->LevelMax)
	{
		int Sub = (lpProduce->LevelMax - lpProduce->LevelMin) + 1;
		Level = lpProduce->LevelMin + (GetLargeRand() % Sub);
	}
	else
	{
		Level = lpProduce->LevelMin;
		gLog.Output(LOG_CHAOS_MIX,"[ChaosRecipe] [%s] [%s] (Warning) Produce have wrong level (Recipe: %s, Combination: %s)",
			lpUser->Account, lpUser->Name, lpRecipe->Name, lpCombination->Name);
	}

	if (Level > 15)
	{
		Level = 15;
	}

	if (lpProduce->OptionMax == lpProduce->OptionMin )
	{
		Option = lpProduce->OptionMax;
	}
	else if (lpProduce->OptionMin < lpProduce->OptionMax )
	{
		int Sub = (lpProduce->OptionMax - lpProduce->OptionMin) + 1;
		Option = lpProduce->OptionMin + (GetLargeRand() % Sub);
	}
	else
	{
		Option = lpProduce->OptionMin;
		gLog.Output(LOG_CHAOS_MIX,"[ChaosRecipe] [%s] [%s] (Warning) Produce have wrong option (Recipe: %s, Combination: %s)",
		lpUser->Account, lpUser->Name, lpRecipe->Name, lpCombination->Name);
	}

	if (Option > 7)
	{
		Option = 7;
	}
	// ----
	if( lpProduce->Luck )
	{
		Luck = 0;
		// ----
		if( GetLargeRand() % 2 == 0 )
		{
			Luck = 1;
		}
	}
	// ----
	if( lpProduce->ExcellentMin )
	{
		int ExcOptionCount = lpProduce->ExcellentMin;
		// ----
		if( ExcOptionCount != lpProduce->ExcellentMax )
		{
			ExcOptionCount += GetLargeRand() % (1 + (lpProduce->ExcellentMax - ExcOptionCount));
		}
		// ----
		while(ExcOptionCount != 0)
		{
			
			BYTE ExcValue;
			RandomManager.GetRandomElement(&ExcValue);
		//	LogAddC(2, "Count %d Value %d", ExcOptionCount, ExcValue);
			// ----
			if( (ExcOption & ExcValue) == 0 )
			{
				ExcOption |= ExcValue;
				ExcOptionCount--;
			}
		}
	}
	// ----
	if( lpProduce->Ancient )
	{
		SetOption = gSetItemType.GetSetOption(ItemNumber);
	}
	// ----
	if( gSocketItemType.CheckSocketItemType(ItemNumber) )
	{
		if( lpProduce->SocketMin < 1 )
		{
			lpProduce->SocketMin = 1;
		}
		// ----
		if( lpProduce->SocketMax < lpProduce->SocketMin )
		{
			lpProduce->SocketMax = lpProduce->SocketMin;
		}
		// ----
		SocketCount = lpProduce->SocketMin;
		// ----
		if( lpProduce->SocketMin != lpProduce->SocketMax )
		{
			SocketCount += GetLargeRand() % (1 + (lpProduce->SocketMax - lpProduce->SocketMin));
		}
		// ----
		for( int i = 0; i < 5; i++ )
		{
			if( i < SocketCount )
			{
				SocketOption[i] = (BYTE)-2;
			}
			else
			{
				SocketOption[i] = (BYTE)-1;
			}
		}
	}
	// ----
	GDCreateItemSend(lpUser->Index,-1,0,0,ItemNumber,Level,lpProduce->Durability,lpProduce->Skill,Luck,Option,-1,ExcOption,SetOption,0,0,SocketOption,SocketBonus,0);
	//ItemSerialCreateSend(lpUser->m_Index, -1, 0, 0, ItemNumber, Level, 
	//	lpProduce->Durability, lpProduce->Skill, Luck, Option, -1, ExcOption, SetOption, SocketBonus, SocketOption);
	gObjInventoryCommit(lpUser->Index);
	gLog.Output(LOG_CHAOS_MIX,"[ChaosRecipe] [%s] [%s] Combination success (Recipe: %s, Combination: %s, Rate: %d)",
		lpUser->Account, lpUser->Name, lpRecipe->Name, lpCombination->Name, 
		lpUser->ChaosSuccessRate);
}
// -------------------------------------------------------------------------------

bool cChaosRecipe::CheckIngredient(LPOBJ lpUser, short ChaosPos, ChaosIngredient* Ingredient)
{
	if (!lpUser->ChaosBox[ChaosPos].IsItem())
	{
		return false;
	}
	
	if (lpUser->ChaosBox[ChaosPos].m_Index < GET_ITEM(Ingredient->TypeStart, Ingredient->IndexStart)
		|| lpUser->ChaosBox[ChaosPos].m_Index > GET_ITEM(Ingredient->TypeEnd, Ingredient->IndexEnd))
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Level < Ingredient->LevelMin && Ingredient->LevelMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Level > Ingredient->LevelMax && Ingredient->LevelMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Option3 < Ingredient->OptionMin && Ingredient->OptionMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Option3 > Ingredient->OptionMax && Ingredient->OptionMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Durability < Ingredient->DurabilityMin && Ingredient->DurabilityMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Durability > Ingredient->DurabilityMax && Ingredient->DurabilityMax != (BYTE)-1)
	{
		return false;
	}
		
	return true;
}
// -------------------------------------------------------------------------------

bool cChaosRecipe::CheckTalisman(LPOBJ lpUser, short ChaosPos, ChaosTalisman* lpTalisman)
{
	if (!lpUser->ChaosBox[ChaosPos].IsItem())
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Index < GET_ITEM(lpTalisman->TypeStart, lpTalisman->IndexStart)
		|| lpUser->ChaosBox[ChaosPos].m_Index > GET_ITEM(lpTalisman->TypeEnd, lpTalisman->IndexEnd))
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Level < lpTalisman->LevelMin && lpTalisman->LevelMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Level > lpTalisman->LevelMax && lpTalisman->LevelMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Option3 < lpTalisman->OptionMin && lpTalisman->OptionMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Option3 > lpTalisman->OptionMax && lpTalisman->OptionMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Durability < lpTalisman->DurabilityMin && lpTalisman->DurabilityMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Durability > lpTalisman->DurabilityMax && lpTalisman->DurabilityMax != (BYTE)-1)
	{
		return false;
	}

	return true;
}
// -------------------------------------------------------------------------------

bool cChaosRecipe::ApplyTalisman(LPOBJ lpUser, short ChaosPos, cChaosRecipe* lpRecipe, ChaosCombination* lpCombination, ChaosTalisman* lpTalisman)
{
	if (!lpUser->ChaosBox[ChaosPos].IsItem())
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Index < GET_ITEM(lpTalisman->TypeStart, lpTalisman->IndexStart)
		|| lpUser->ChaosBox[ChaosPos].m_Index > GET_ITEM(lpTalisman->TypeEnd, lpTalisman->IndexEnd))
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Level < lpTalisman->LevelMin && lpTalisman->LevelMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Level > lpTalisman->LevelMax && lpTalisman->LevelMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Option3 < lpTalisman->OptionMin && lpTalisman->OptionMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Option3 > lpTalisman->OptionMax && lpTalisman->OptionMax != (BYTE)-1)
	{
		return false;
	}

	if (lpUser->ChaosBox[ChaosPos].m_Durability < lpTalisman->DurabilityMin && lpTalisman->DurabilityMin != (BYTE)-1
		|| lpUser->ChaosBox[ChaosPos].m_Durability > lpTalisman->DurabilityMax && lpTalisman->DurabilityMax != (BYTE)-1)
	{
		return false;
	}

	BYTE RateIncrease = 0;
	
	if (lpTalisman->AdditionalRate == (BYTE)-1)
	{
		RateIncrease += lpUser->ChaosBox[ChaosPos].m_Durability;
	}
	else
	{
		RateIncrease += lpTalisman->AdditionalRate;
	}

	lpUser->ChaosSuccessRate += RateIncrease;
	gLog.Output(LOG_CHAOS_MIX,"[ChaosRecipe] [%s] [%s] Talisman has been applied (Recipe: %s, Combination: %s, Talisman: %d-%d, Increase: %d)",
		lpUser->Account, lpUser->Name, lpRecipe->Name, lpCombination->Name, 
		lpUser->ChaosBox[ChaosPos].m_Index / 512, lpUser->ChaosBox[ChaosPos].m_Index % 512, RateIncrease);
	return true;
}
// -------------------------------------------------------------------------------

cChaosBoxManager::cChaosBoxManager()
{
	this->Recipes.clear();

	if (this->Recipes.capacity() > 0)
	{
		std::vector<cChaosRecipe*>().swap(this->Recipes);
	}
}
// -------------------------------------------------------------------------------

cChaosBoxManager::~cChaosBoxManager()
{
	
}
// -------------------------------------------------------------------------------

void cChaosBoxManager::Read(char* File)
{
	pugi::xml_document Document;
	pugi::xml_parse_result Result = Document.load_file(File);

	if (Result.status != pugi::status_ok)
	{
		MsgBox("[ChaosMachineManager] File %s not found!", File);
		return;
	}

	pugi::xml_node Recipe	= Document.child("chaosmachine");

	for (pugi::xml_node CombinationNode = Recipe.child("mixlist").child("recipe"); CombinationNode; CombinationNode = CombinationNode.next_sibling())
	{
		char FileName[MAX_PATH] = { 0 };
		sprintf(FileName, "%s%s", gPath.GetFullPath("Custom\\ChaosMachine\\"), CombinationNode.text().as_string());
		//MessageBoxA(0, FileName,FileName, 0);

		cChaosRecipe* lpRecipe = new cChaosRecipe(CombinationNode.attribute("index").as_int(0));
		
		if (!lpRecipe->Read(FileName))
		{
			continue;
		}
		//MsgBox("Index [%d] Text [%s]", lpRecipe->RecipeIndex, FileName);

		this->Recipes.push_back(lpRecipe);
	}
}
// -------------------------------------------------------------------------------

bool cChaosBoxManager::StartMix(LPOBJ lpUser, short RecipeIndex)
{
	lpUser->ChaosSuccessRate = 0;

	for (int Recipe = 0; Recipe < this->Recipes.size(); Recipe++)
	{
		if (this->Recipes[Recipe]->RecipeIndex == RecipeIndex)
		{
			int ActiveCombination = -1;

			//Select active combination
			for (int Combination = 0; Combination < this->Recipes[Recipe]->Combinations.size(); Combination++)
			{
				BYTE ItemCounter[CHAOS_BOX_SIZE] = { 0 };
				BYTE TalismanCounter[CHAOS_BOX_SIZE] = { 0 };

				for (int Pos = 0; Pos < CHAOS_BOX_SIZE; Pos++)
				{
					if (!lpUser->ChaosBox[Pos].IsItem())
					{
						continue;
					}

					for (int n = 0; n < this->Recipes[Recipe]->Combinations[Combination].Ingredients.size(); n++)
					{
						if (n >= CHAOS_BOX_SIZE-1)
						{
							break;
						}

						ChaosIngredient* lpIngredient = &this->Recipes[Recipe]->Combinations[Combination].Ingredients[n];

						if (cChaosRecipe::CheckIngredient(lpUser, Pos, lpIngredient))
						{
							ItemCounter[n]++;
						}
					}
				}

				bool CountRange = true;

				for (int n = 0; n < this->Recipes[Recipe]->Combinations[Combination].Ingredients.size(); n++)
				{
					if (ItemCounter[n] < this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].CountMin
						|| ItemCounter[n] > this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].CountMax)
					{
						/*
						gLog.Output(LOG_CHAOS_MIX,"[DEBUG] Wrong range (%d:%d, %d/%d:%d)",
							this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].TypeStart,
							this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].IndexStart,
							ItemCounter[n],
							this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].CountMin,
							this->Recipes[Recipe]->Combinations[Combination].Ingredients[n].CountMax);*/
						CountRange = false;
						break;
					}
				}
				
				if (CountRange)
				{
					ActiveCombination = Combination;
					break;
				}
			}

			if (ActiveCombination == -1)
			{
				//LogAddC(2, "[DEBUG] Combination not found");
				return false;
			}

			ChaosCombination* lpCombination = &this->Recipes[Recipe]->Combinations[ActiveCombination];

			if (lpCombination->Produces.size() <= 0)
			{
				//LogAddC(2, "[DEBUG] Produces list not filled");
				return false;
			}

			//Talisman effect apply
			BYTE TalismanCounter[CHAOS_BOX_SIZE] = { 0 };

			for (int Pos = 0; Pos < CHAOS_BOX_SIZE; Pos++)
			{
				if (!lpUser->ChaosBox[Pos].IsItem())
				{
					continue;
				}

				for (int n = 0; n < this->Recipes[Recipe]->Combinations[ActiveCombination].Talismans.size(); n++)
				{
					if (n >= CHAOS_BOX_SIZE-1)
					{
						break;
					}

					ChaosTalisman* lpTalisman = &this->Recipes[Recipe]->Combinations[ActiveCombination].Talismans[n];

					if (cChaosRecipe::CheckTalisman(lpUser, Pos, lpTalisman))
					{
						if (TalismanCounter[n] < lpTalisman->CountMax)
						{
							cChaosRecipe::ApplyTalisman(lpUser, Pos, this->Recipes[Recipe], 
								&this->Recipes[Recipe]->Combinations[ActiveCombination], lpTalisman);
							TalismanCounter[n]++;
						}
						else
						{
							cChaosRecipe::ActFail(lpUser, this->Recipes[Recipe], &this->Recipes[Recipe]->Combinations[ActiveCombination], 0xF0);
							return 0;
						}
					}
				}
			}

			cChaosRecipe::ActStart(lpUser, this->Recipes[Recipe], lpCombination);
			return true;
		}
	}
	return false;
}

