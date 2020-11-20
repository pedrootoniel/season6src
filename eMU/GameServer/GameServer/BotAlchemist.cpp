#include "stdafx.h"
#include "BotAlchemist.h"
#include "Monster.h"
#include "ItemManager.h"
#include "ObjectManager.h"
#include "SkillManager.h"
#include "EffectManager.h"
#include "MasterSkillTree.h"
#include "ServerInfo.h"
#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "JewelsBank.h"
#include "Message.h"
#include "Notice.h"
#include "Trade.h"
#include "DSProtocol.h"

ObjBotAlchemist BotAlchemist;

void ObjBotAlchemist::Load(char* path)
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTALCHEMIST;botNum++)
		{
			if(this->bot[botNum].Enabled == true)
			{
				int bIndex = this->bot[botNum].index;
				if(gObjIsConnected(bIndex) == TRUE)
				{
					gObjDel(bIndex);
				}
			}
		}
	}

	this->Enabled = FALSE;

	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if (section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int BotNum = lpMemScript->GetNumber();

					if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
					{
						MsgBox("BotAlchemist error: BotPetIndex:%d out of range!", BotNum);
						return;
					}

					this->bot[BotNum].Class = lpMemScript->GetAsNumber();

					this->bot[BotNum].Rate = lpMemScript->GetAsNumber();

					strncpy(this->bot[BotNum].Name,lpMemScript->GetAsString(),sizeof(this->bot[BotNum].Name));

					this->bot[BotNum].Map = lpMemScript->GetAsNumber();

					this->bot[BotNum].X = lpMemScript->GetAsNumber();

					this->bot[BotNum].Y = lpMemScript->GetAsNumber();

					this->bot[BotNum].Dir = lpMemScript->GetAsNumber();

					this->bot[BotNum].Enabled = true;
				}
				else if (section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int BotNum = lpMemScript->GetNumber();
					if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
					{
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}
					if(this->bot[BotNum].Enabled == false)
					{	
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}

					int Slot = lpMemScript->GetAsNumber();
				
					if(Slot < 0 || Slot > 8)
					{	
						MsgBox("BotAlchemist error: Min Slot 0 ; Max Slot 8");
						return;
					}

					int iType = lpMemScript->GetAsNumber();

					int iIndex = lpMemScript->GetAsNumber();

					this->bot[BotNum].body[Slot].num = GET_ITEM(iType,iIndex);

					this->bot[BotNum].body[Slot].level = lpMemScript->GetAsNumber();

					this->bot[BotNum].body[Slot].opt = lpMemScript->GetAsNumber();

					this->bot[BotNum].body[Slot].Enabled = true;
				}
				else if (section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->Enabled = TRUE;

					int BotNum = lpMemScript->GetNumber();
					if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
					{
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}
					if(this->bot[BotNum].Enabled == false)
					{	
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}
					this->bot[BotNum].AllowLevel = lpMemScript->GetAsNumber();
					this->bot[BotNum].AllowOpt = lpMemScript->GetAsNumber();
					this->bot[BotNum].AllowLuck = lpMemScript->GetAsNumber();
					this->bot[BotNum].AllowSkill = lpMemScript->GetAsNumber();
					this->bot[BotNum].AllowExc = lpMemScript->GetAsNumber();
				}
				else if (section == 3)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->Enabled = TRUE;

					int BotNum = lpMemScript->GetNumber();
					if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
					{
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}
					if(this->bot[BotNum].Enabled == false)
					{	
						MsgBox("BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
						return;
					}
					this->bot[BotNum].OnlyVip = lpMemScript->GetAsNumber();
					this->bot[BotNum].PriceType = lpMemScript->GetAsNumber();
					this->bot[BotNum].PriceCount = lpMemScript->GetAsNumber();
					this->bot[BotNum].OnlySameType = lpMemScript->GetAsNumber();
					this->bot[BotNum].OnlyLowerIndex = lpMemScript->GetAsNumber();
					this->bot[BotNum].AcceptAncient = lpMemScript->GetAsNumber();
					this->bot[BotNum].MaxLevel = lpMemScript->GetAsNumber();
					this->bot[BotNum].MaxExc = lpMemScript->GetAsNumber();
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void ObjBotAlchemist::MakeBot()
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTALCHEMIST;botNum++)
		{
			if(this->bot[botNum].Enabled == true)
			{
				int aIndex = gObjAddMonster(bot[botNum].Map);

				if(aIndex >= 0)
				{
					LPOBJ lpObj = &gObj[aIndex];
					this->bot[botNum].index = aIndex;
					lpObj->PosNum = (WORD)-1;
					lpObj->X = this->bot[botNum].X;
					lpObj->Y = this->bot[botNum].Y;
					lpObj->OldX = this->bot[botNum].X;
					lpObj->OldY = this->bot[botNum].Y;
					lpObj->TX = this->bot[botNum].X;
					lpObj->TY = this->bot[botNum].Y;
					lpObj->MTX = this->bot[botNum].X;
					lpObj->MTY = this->bot[botNum].Y;
					lpObj->Dir = this->bot[botNum].Dir;
					lpObj->Map = this->bot[botNum].Map;
					lpObj->Live = TRUE;
					lpObj->PathCount = 0;
					lpObj->IsBot = 2;
					lpObj->Type = OBJECT_USER;
					gObjSetMonster(aIndex,this->bot[botNum].Class);

					lpObj->ChangeUp = this->bot[botNum].Class % 16;	// Set Second Type of Character
					lpObj->Class = this->bot[botNum].Class / 16;
					lpObj->Level = 400;
					lpObj->Life = 1;
					lpObj->MaxLife = 2;
					lpObj->Mana = 1;
					lpObj->MaxMana = 2;
					lpObj->Experience = 0;

					lpObj->Inventory = new CItem[INVENTORY_EXT4_SIZE];					
					lpObj->Inventory1 = new CItem[INVENTORY_EXT4_SIZE];
					lpObj->InventoryMap1 = new BYTE[INVENTORY_EXT4_SIZE];
					lpObj->InventoryMap = new BYTE[INVENTORY_EXT4_SIZE];

					for (int i=0;i<INVENTORY_EXT4_SIZE;i++)
					{
						lpObj->Inventory[i].Clear();
						lpObj->Inventory1[i].Clear();
					}

					memset(&lpObj->InventoryMap[0], (BYTE)-1, INVENTORY_EXT4_SIZE);
					memset(&lpObj->InventoryMap1[0], (BYTE)-1, INVENTORY_EXT4_SIZE);

					strncpy(lpObj->Name,this->bot[botNum].Name,sizeof(lpObj->Name));

					for(int i=0;i<9;i++)
					{
						if(this->bot[botNum].body[i].num >= 0 && this->bot[botNum].body[i].Enabled == true)
						{
							CItem lpItem;

							lpObj->Inventory[i].Clear();

							lpItem.Clear();

							lpItem.m_Index = this->bot[botNum].body[i].num;

							lpItem.m_Option1 = 0;

							lpItem.m_Option2 = 1;

							lpItem.m_Option3 = this->bot[botNum].body[i].opt;

							lpItem.m_Level = this->bot[botNum].body[i].level;

							lpItem.m_Durability = 255.0f;

							lpItem.m_Serial = 0;

							lpItem.m_NewOption = 0;

							lpItem.m_SetOption = 0;

							lpItem.m_ItemOptionEx = 0;

							lpItem.m_IsPeriodicItem = 0;

							lpItem.m_IsExpiredItem = 0;

							memset(lpItem.m_SocketOption,0xFF,MAX_SOCKET_OPTION);

							lpItem.m_JewelOfHarmonyOption = 0;

							lpItem.m_SocketOptionBonus = 0xFF;

							lpItem.Convert(lpItem.m_Index,lpItem.m_Option1,lpItem.m_Option2,lpItem.m_Option3,lpItem.m_NewOption,lpItem.m_SetOption,lpItem.m_JewelOfHarmonyOption,lpItem.m_ItemOptionEx,lpItem.m_SocketOption,lpItem.m_SocketOptionBonus);

							gItemManager.InventoryAddItem(aIndex,lpItem,i);
						}
					}

					lpObj->Inventory1 = lpObj->Inventory;
					lpObj->InventoryMap1 = lpObj->InventoryMap;
					gObjectManager.CharacterMakePreviewCharSet(aIndex);

					lpObj->AttackType = 0;
					lpObj->BotSkillAttack = 0;					

					lpObj->Attribute = 100;
					lpObj->TargetNumber = (WORD)-1;
					lpObj->ActionState.Emotion = 0;
					lpObj->ActionState.Attack = 0;
					lpObj->ActionState.EmotionCount = 0;
					lpObj->PathCount = 0;
					lpObj->BotPower = 0;
					lpObj->BotDefense = this->bot[botNum].OnlyVip;
					lpObj->BotLife = 1;
					lpObj->BotMaxLife = 1;
					
					lpObj->BotLvlUpDefense = 1;
					lpObj->BotLvlUpPower = 1;
					lpObj->BotLvlUpLife = 1;
					lpObj->BotLvlUpMana = 1;
					lpObj->BotLvlUpExp = 1;
					lpObj->BotLvlUpMaxLevel = 1;

					lpObj->MoveRange = 1;
					lpObj->BotFollowMe = 0;
					lpObj->NextExperience = gLevelExperience[lpObj->Level];
				}
			}
		}
	}
}
BOOL ObjBotAlchemist::IsInTrade(int aIndex)
{
	int number = this->GetBotIndex(gObj[aIndex].TargetNumber);
	if(number != -1)
		return 1;
	else
		return 0;
}

int ObjBotAlchemist::GetBotIndex(int aIndex)
{
	for(int i=0;i<MAX_BOTALCHEMIST;i++)
	{
		if(this->bot[i].Enabled == true)
		{
			if(this->bot[i].index == aIndex)
				return i;
		}
	}
	return -1;
}

bool ObjBotAlchemist::AllowExc(BYTE BotNum, BYTE ExcOpt)
{				
	int dwExOpCount = getNumberOfExcOptions(ExcOpt);

	if(dwExOpCount < this->bot[BotNum].MaxExc)
	{
		return true;
	}
	return false;
}

BYTE ObjBotAlchemist::Alchemy(int aIndex,int BotNum)
{
	char sbuf[512]={0};
	int fitem=-1;
	int sitem=-1;
	int count=0;

	if(gObjIsConnected(aIndex) == 0)
	{
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if (this->bot[BotNum].PriceType == 0)
	{
		if (lpObj->Money < this->bot[BotNum].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(518),this->bot[BotNum].PriceCount);
			ChatSend(&gObj[this->bot[BotNum].index],sbuf);
			goto Cancel;
		}
	}
	else if (this->bot[BotNum].PriceType == 1)
	{
		if (lpObj->WCoinCaRecv < this->bot[BotNum].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(519),this->bot[BotNum].PriceCount);
			ChatSend(&gObj[this->bot[BotNum].index],sbuf);
			goto Cancel;
		}
	}
	else if (this->bot[BotNum].PriceType == 2)
	{
		if (lpObj->WCoinPaRecv < this->bot[BotNum].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(520),this->bot[BotNum].PriceCount);
			ChatSend(&gObj[this->bot[BotNum].index],sbuf);
			goto Cancel;
		}
	}
	else if (this->bot[BotNum].PriceType == 3)
	{
		if (lpObj->GPointaRecv < this->bot[BotNum].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(521),this->bot[BotNum].PriceCount);
			ChatSend(&gObj[this->bot[BotNum].index],sbuf);
			goto Cancel;
		}
	}
	else
	{
		wsprintf(sbuf,"Wrong currency! Contact Admin check config!!!");
		ChatSend(&gObj[this->bot[BotNum].index],sbuf);
		goto Cancel;
	}

	for(int n = 0; n < TRADE_SIZE; n++)
	{
		if(lpObj->Trade[n].IsItem() != 0)
		{
			if((n >= 0 && n<=3) || (n >= 8 && n<=11) || (n >= 16 && n<=19) || (n >= 24 && n<=27))
			{
				fitem = n;
			}else
			{
				sitem = n;
			}

			count++;
		}
	}
	if(count != 2)
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(526));
		LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Items Count Error (%d)",lpObj->Account,lpObj->Name,count);
		goto Cancel;
	}
	if((lpObj->Trade[fitem].m_Index >= 6144) || (lpObj->Trade[sitem].m_Index >= 6144))
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(527));
		LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Items Error",lpObj->Account,lpObj->Name);
		goto Cancel;
	}
	
	if(fitem == -1 || sitem == -1)
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(528));
		LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Items Position Error",lpObj->Account,lpObj->Name);
		goto Cancel;
	}

	if(this->bot[BotNum].OnlySameType == 1)
	{
		int fType = lpObj->Trade[fitem].m_Index/512;
		int sType = lpObj->Trade[sitem].m_Index/512;
		if(fType != sType)
		{
			ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(529));
			LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Item Types Error",lpObj->Account,lpObj->Name);
			goto Cancel;
		}
	}

	if(this->bot[BotNum].OnlyLowerIndex == 1)
	{
		int fLevel = gItemManager.m_ItemInfo[lpObj->Trade[fitem].m_Index].Level;
		int sLevel = gItemManager.m_ItemInfo[lpObj->Trade[sitem].m_Index].Level;

		if(fLevel > sLevel)
		{
			if(fLevel > (sLevel + 10))
			{
				ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(530));
				LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Item Destiny Lower Index Error",lpObj->Account,lpObj->Name);
				goto Cancel;
			}
		}
	}

	if(this->bot[BotNum].AcceptAncient == 0 && lpObj->Trade[fitem].m_SetOption > 0)
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(531));
		LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Ancient Item Error",lpObj->Account,lpObj->Name);
		goto Cancel;
	}

	srand(static_cast<int>(time(NULL)));
	int random = rand()%100;
	bool failed = false;

	if(random > this->bot[BotNum].Rate )
	{
		failed = true;
	}

	if(this->bot[BotNum].AllowLuck == 1)
	{
		if(lpObj->Trade[fitem].m_Option2 == 0 && lpObj->Trade[sitem].m_Option2 == 1)
		{
			if(!failed)
				lpObj->Trade[fitem].m_Option2 = 1;
			lpObj->Trade[sitem].m_Option2 = 0;
		}
	}
	if(this->bot[BotNum].AllowLevel == 1)
	{
		int fLevel = lpObj->Trade[fitem].m_Level;
		if(fLevel < this->bot[BotNum].MaxLevel)
		{
			int sLevel = lpObj->Trade[sitem].m_Level;
			if ((fLevel + sLevel) > this->bot[BotNum].MaxLevel)
			{
				sLevel -= (this->bot[BotNum].MaxLevel - fLevel);
				if(!failed)
					fLevel = this->bot[BotNum].MaxLevel;
			}else
			{
				if(!failed)
					fLevel += sLevel;
				sLevel = 0;
			}
			lpObj->Trade[fitem].m_Level = fLevel;
			lpObj->Trade[sitem].m_Level = sLevel;
		}
	}
	if(this->bot[BotNum].AllowSkill == 1)
	{
		if(lpObj->Trade[fitem].m_Index < 3584)
		{
			if(lpObj->Trade[fitem].m_Option1 == 0 && lpObj->Trade[sitem].m_Option1 == 1)
			{
				if(!failed)
					lpObj->Trade[fitem].m_Option1 = 1;
				lpObj->Trade[sitem].m_Option1 = 0;
			}
		}
	}
	if(this->bot[BotNum].AllowOpt == 1)
	{
		int fOpt = lpObj->Trade[fitem].m_Option3;
		if(fOpt < 7)
		{
			int sOpt = lpObj->Trade[sitem].m_Option3;
			if ((fOpt + sOpt) > 7)
			{
				sOpt -= (7 - fOpt);
				if(!failed)
					fOpt = 7;
			}else
			{
				if(!failed)
					fOpt += sOpt;
				sOpt = 0;
			}
			lpObj->Trade[fitem].m_Option3 = fOpt;
			lpObj->Trade[sitem].m_Option3 = sOpt;
		}
	}
	if(this->bot[BotNum].AllowExc == 1)
	{
		if(lpObj->Trade[fitem].m_NewOption != 63)
		{
			if(lpObj->Trade[sitem].m_NewOption != 0)
			{		
				if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
				{
					BYTE fLife		= lpObj->Trade[fitem].IsExtLifeAdd();
					BYTE fMana		= lpObj->Trade[fitem].IsExtManaAdd();
					BYTE fDmg		= lpObj->Trade[fitem].IsExtDamageMinus();
					BYTE fReflect	= lpObj->Trade[fitem].IsExtDamageReflect();
					BYTE fDef		= lpObj->Trade[fitem].IsExtDefenseSuccessfull();
					BYTE fMoney		= lpObj->Trade[fitem].IsExtMonsterMoney();
					
					BYTE sLife		= lpObj->Trade[sitem].IsExtLifeAdd();
					BYTE sMana		= lpObj->Trade[sitem].IsExtManaAdd();
					BYTE sDmg		= lpObj->Trade[sitem].IsExtDamageMinus();
					BYTE sReflect	= lpObj->Trade[sitem].IsExtDamageReflect();
					BYTE sDef		= lpObj->Trade[sitem].IsExtDefenseSuccessfull();
					BYTE sMoney		= lpObj->Trade[sitem].IsExtMonsterMoney();

					
					if(fLife == 0 && sLife != 0)
					{
						if(!failed)
							lpObj->Trade[fitem].m_NewOption |= 0x20;
						lpObj->Trade[sitem].m_NewOption &= ~0x20;
					}
					if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
					{
						if(fMana == 0 && sMana != 0)
						{
							if(!failed)
								lpObj->Trade[fitem].m_NewOption |= 0x10;
							lpObj->Trade[sitem].m_NewOption &= ~0x10;
						}
					}
		
					if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
					{
						if(fDmg == 0 && sDmg != 0)
						{
							if(!failed)
								lpObj->Trade[fitem].m_NewOption |= 8;
							lpObj->Trade[sitem].m_NewOption &= ~8;
						}
					}
					
					if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
					{
						if(fReflect == 0 && sReflect != 0)
						{
							if(!failed)
								lpObj->Trade[fitem].m_NewOption |= 4;
							lpObj->Trade[sitem].m_NewOption &= ~4;
						}
					}
					
					if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
					{
						if(fDef == 0 && sDef != 0)
						{
							if(!failed)
								lpObj->Trade[fitem].m_NewOption |= 2;
							lpObj->Trade[sitem].m_NewOption &= ~2;
						}
					}
					
					if(this->AllowExc(BotNum,lpObj->Trade[fitem].m_NewOption) == true)
					{
						if(fMoney == 0 && sMoney != 0)
						{
							if(!failed)
								lpObj->Trade[fitem].m_NewOption |= 1;
							lpObj->Trade[sitem].m_NewOption &= ~1;
						}
					}
				}
			}
		}
	}

	int a = gItemManager.InventoryInsertItem(aIndex,lpObj->Trade[fitem]);
	int b = gItemManager.InventoryInsertItem(aIndex,lpObj->Trade[sitem]);
	if(a == 255 || b == 255)
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(532));
		LogAdd(LOG_RED,"[BotAlchemist](%s)(%s) Doesnt have space on inventory",lpObj->Account,lpObj->Name);
		goto Cancel;
	}

	if(failed)
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(533));
		LogAdd(LOG_RED,"[BotAlchemist][Bot:%d](%s)(%s) Alchemy Failed",BotNum,lpObj->Account,lpObj->Name);
	}
	else
	{
		ChatSend(&gObj[this->bot[BotNum].index],gMessage.GetMessage(534));
		LogAdd(LOG_RED,"[BotAlchemist][Bot:%d](%s)(%s) Alchemy Success",BotNum,lpObj->Account,lpObj->Name);
	}

	if (this->bot[BotNum].PriceType == 0)
	{
		lpObj->Money -= this->bot[BotNum].PriceCount;
		GCMoneySend(lpObj->Index, lpObj->Money);
	}
	else if (this->bot[BotNum].PriceType == 1)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,this->bot[BotNum].PriceCount,0,0);
	}
	else if (this->bot[BotNum].PriceType == 2)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,this->bot[BotNum].PriceCount,0);
	}
	else if (this->bot[BotNum].PriceType == 3)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,0,this->bot[BotNum].PriceCount);
	}

	gObjInventoryCommit(aIndex);
	gObjectManager.CharacterMakePreviewCharSet(aIndex);
	GDCharacterInfoSaveSend(aIndex);
	//gObjItemTextSave(&gObj[aIndex]);
	//gObjStatTextSave(&gObj[aIndex]);
	GDPetItemInfoSend(aIndex,0);
	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;
	gTrade.GCTradeResultSend(aIndex,1);
	gItemManager.GCItemListSend(aIndex);
	gTrade.ClearTrade(lpObj);
	//gObjNotifyUpdateUnionV1(&gObj[aIndex]);
	//gObjNotifyUpdateUnionV2(&gObj[aIndex]);
	return 1;

Cancel:
	this->TradeCancel(aIndex);
	return 0;
}


void ObjBotAlchemist::TradeOk(int aIndex)
{
	int MixNum=-1;
	int MixItem=-1;

	int number = this->GetBotIndex(gObj[aIndex].TargetNumber);

	if(number == -1)
	{			
		gObj[aIndex].Interface.state = 0;
		gObj[aIndex].Interface.type = 0;
		gObj[aIndex].TargetShopNumber = -1;
		gObj[aIndex].Transaction = 0;

		return;
	}
	this->Alchemy(aIndex,number);
}

BOOL ObjBotAlchemist::TradeOpen(int index, int nindex)
{
	if(gObjIsConnected(index) == 0)
	{
		return 0;
	}
	if(gObjIsConnected(nindex) == 0)
	{
		return 0;
	}

	int number = this->GetBotIndex(nindex);
	if(number == -1)
		return 0;
	char sbuf[512]={0};
	LPOBJ lpObj = &gObj[index];
	LPOBJ lpBot = &gObj[nindex];

	if (lpObj->AccountLevel < this->bot[number].OnlyVip)
	{
		ChatSend(&gObj[this->bot[number].index],gMessage.GetMessage(517));
		return 0;
	}

	if(this->Enabled == TRUE)
	{
		if ( lpObj->Interface.use > 0 )
		{
			return 0;
		}else
		{	
			for(int n = 0; n < TRADE_SIZE; n++)
			{
				lpObj->Trade[n].Clear();
			}
			memset(lpObj->TradeMap, (BYTE)-1, TRADE_SIZE );

			gObjInventoryTransaction(lpObj->Index);
			gTrade.GCTradeResponseSend(lpObj->Index,1,lpBot->Name, 400, 0);
			gTrade.GCTradeOkButtonSend(lpObj->Index, 1);
			lpObj->Interface.state = 1;
			lpObj->Interface.use = 1;
			lpObj->Interface.type = 1;
			lpObj->TradeMoney = 0;
			lpObj->TargetNumber =lpBot->Index;
			lpObj->Transaction = 1;

			char wbuf[1024]={0};
			wsprintf(wbuf,"[BotAlchemist] (%s)(%s) OPEN",gObj[index].Account,gObj[index].Name);
			LogAdd(LOG_RED,wbuf);
			ChatSend(&gObj[this->bot[number].index],gMessage.GetMessage(525));			
		}
	}
	return 1;
}

void ObjBotAlchemist::TradeCancel(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	gTrade.ResetTrade(aIndex);
	gTrade.GCTradeResultSend(aIndex,0);
}

