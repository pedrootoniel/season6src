#include "stdafx.h"
#include "BotBuffer.h"
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

CBotBuffer gBotBuffer;

CBotBuffer::CBotBuffer()
{

}

CBotBuffer::~CBotBuffer()
{
	
}

void CBotBuffer::Load(char* path)
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTBUFFER;botNum++)
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
	for(int i=0;i<MAX_BOTBUFFER;i++)
	{
		this->bot[i].index = -1;
		this->bot[i].SkillCount = 0;
		this->bot[i].MaxLevel = 400;
		memset(&this->bot[i].skill,0,sizeof(this->bot[i].skill));
		this->bot[i].Enabled = false;
		for(int j=0;j<9;j++)
			this->bot[i].body[j].num =-1;
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

					if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
					{
						MsgBox("BotBuffer error: BotBuffer Index:%d out of range!", BotNum);
						return;
					}

					this->bot[BotNum].Class = lpMemScript->GetAsNumber();

					this->bot[BotNum].OnlyVip = lpMemScript->GetAsNumber();

					this->bot[BotNum].MaxLevel = lpMemScript->GetAsNumber();

					strncpy(this->bot[BotNum].Name,lpMemScript->GetAsString(),sizeof(this->bot[BotNum].Name));

					this->bot[BotNum].Map = lpMemScript->GetAsNumber();

					this->bot[BotNum].X = lpMemScript->GetAsNumber();

					this->bot[BotNum].Y = lpMemScript->GetAsNumber();

					this->bot[BotNum].Dir = lpMemScript->GetAsNumber();

					this->bot[BotNum].PriceType = lpMemScript->GetAsNumber();

					this->bot[BotNum].PriceCount = lpMemScript->GetAsNumber();

					this->bot[BotNum].Enabled = true;
				}
				else if (section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int BotNum = lpMemScript->GetNumber();
					if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
					{
						MsgBox("BotBuffer error: BotBuffer Index:%d doesnt exist[0]", BotNum);
						return;
					}
					if(this->bot[BotNum].Enabled == false)
					{	
						MsgBox("BotBuffer error: BotBuffer Index:%d doesnt exist[0.5]", BotNum);
						return;
					}

					int Slot = lpMemScript->GetAsNumber();
				
					if(Slot < 0 || Slot > 8)
					{	
						MsgBox("BotBuffer error: Min Slot 0 ; Max Slot 8");
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
					if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
					{
						MsgBox("BotBuffer error: BotBuffer Index:%d doesnt exist[1]", BotNum);
						return;
					}
					if(this->bot[BotNum].Enabled == false)
					{	
						MsgBox("BotBuffer error: BotBuffer Index:%d doesnt exist", BotNum);
						return;
					}
					if(this->bot[BotNum].SkillCount < 0 || this->bot[BotNum].SkillCount > MAX_BOTBUFFERSKILLS-1)
					{
						MsgBox("BotBuffer error: Skill Buff out of range (MAX BUFF PER BOT = %d)!", this->bot[BotNum].SkillCount);
						return;
					}

					this->bot[BotNum].skill[this->bot[BotNum].SkillCount].skill = lpMemScript->GetAsNumber();

					this->bot[BotNum].skill[this->bot[BotNum].SkillCount].time = lpMemScript->GetAsNumber();

					this->bot[BotNum].SkillCount++;
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

void CBotBuffer::MakeBot()
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTBUFFER;botNum++)
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
					lpObj->IsBot = 3;
					lpObj->Type = OBJECT_USER;
					//gObjSetMonsterTest(aIndex,this->bot[botNum].Class, "BotBuffer");
					gObjSetMonster(aIndex,this->bot[botNum].Class);

					lpObj->ChangeUp = this->bot[botNum].Class % 16;	// Set Second Type of Character
					lpObj->Class = this->bot[botNum].Class / 16;
					lpObj->Level = 400;
					lpObj->Life = 1;
					lpObj->MaxLife = 2;
					lpObj->Mana = 1;
					lpObj->MaxMana = 2;
					lpObj->Experience = 0;
					//lpObj->DBClass = this->bot[botNum].Class;

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
					//gObjMakePreviewCharSet(result);
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

int CBotBuffer::GetBotIndex(int aIndex)
{
	for(int i=0;i<MAX_BOTBUFFER;i++)
	{
		if(this->bot[i].Enabled == true)
		{
			if(this->bot[i].index == aIndex)
				return i;
		}
	}
	return -1;
}

bool CBotBuffer::TradeOpen(int aIndex,int bIndex)
{
	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return false;
	}

	if(gObjIsConnected(bIndex) == 0)
	{
		return false;
	}

	int number = this->GetBotIndex(bIndex);
	if(number == -1)
	{		
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpBot = &gObj[bIndex];

	//return 1;

	gCashShop.GDCashShopRecievePointSend(lpObj->Index,(DWORD)&CBotBuffer::CheckPriceCallback,(DWORD)number,(DWORD)lpBot);

	//for(int x=0;x<this->bot[number].SkillCount;x++)
	//{
	//	switch(this->bot[number].skill[x].skill)
	//	{
	//		case SKILL_MANA_SHIELD:
	//		{
	//			int value1 = gServerInfo.m_ManaShieldConstA+((lpObj->Dexterity+lpObj->AddDexterity)/gServerInfo.m_ManaShieldConstB)+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ManaShieldConstC);

	//			value1 = ((value1>gServerInfo.m_ManaShieldMaxRate)?gServerInfo.m_ManaShieldMaxRate:value1);

	//			value1 = (value1*((lpObj->Type==OBJECT_USER)?gServerInfo.m_ManaShieldRate[lpObj->Class]:100))/100;

	//			int value2 = gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_MANA_SHIELD_MASTERED);

	//			//int count = gServerInfo.m_ManaShieldTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ManaShieldTimeConstB);

	//			//count += gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_MANA_SHIELD_ENHANCED);

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_MANA_SHIELD,this->bot[number].skill[x].time,value1,value2,0,0);

	//			gSkillManager.GCSkillAttackSend(lpBot,SKILL_MANA_SHIELD,bIndex,1);
	//		}break;
	//		case SKILL_GREATER_DEFENSE:
	//		{
	//			int value = gServerInfo.m_GreaterDefenseConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterDefenseConstB);

	//			value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_IMPROVED))/100;

	//			value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_ENHANCED))/100;

	//			value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterDefenseRate[lpObj->Class]:100))/100;

	//			//int count = gServerInfo.m_GreaterDefenseTimeConstA;

	//			//count += gMasterSkillTree.GetMasterSkillLevel(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_ENHANCED);

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DEFENSE,this->bot[number].skill[x].time,(value*2),0,0,0);

	//			gSkillManager.GCSkillAttackSend(lpObj,SKILL_GREATER_DEFENSE,bIndex,1);
	//		}break;
	//		case SKILL_GREATER_DAMAGE:
	//		{
	//			int value = gServerInfo.m_GreaterDamageConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterDamageConstB);

	//			value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_IMPROVED))/100;

	//			value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_ENHANCED))/100;

	//			value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterDamageRate[lpObj->Class]:100))/100;

	//			//int count = gServerInfo.m_GreaterDamageTimeConstA;

	//			//count += gMasterSkillTree.GetMasterSkillLevel(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_ENHANCED);

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DAMAGE,this->bot[number].skill[x].time,value,0,0,0);

	//			gSkillManager.GCSkillAttackSend(lpObj,SKILL_GREATER_DAMAGE,bIndex,1);
	//		}break;
	//		case SKILL_GREATER_LIFE:
	//		{
	//			int value1 = gServerInfo.m_GreaterLifeConstA+((lpObj->Vitality+lpObj->AddVitality)/gServerInfo.m_GreaterLifeConstB)+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterLifeConstC);

	//			value1 = ((value1>gServerInfo.m_GreaterLifeMaxRate)?gServerInfo.m_GreaterLifeMaxRate:value1);

	//			int value2 = 0;

	//			int value3 = 0;

	//			//int count = gServerInfo.m_GreaterLifeTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterLifeTimeConstB);

	//			value1 = (value1*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterLifeRate[lpObj->Class]:100))/100;

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_LIFE,this->bot[number].skill[x].time,value1,value2,value3,0);

	//			gSkillManager.GCSkillAttackSend(lpBot,SKILL_GREATER_LIFE,aIndex,1);
	//			//gObjAddBuffEffect(lpObj, AT_SWELL_LIFE, 4, iaddlife, 0, 0, iLifeTime);
	//			//GCMagicAttackNumberSend(&gObj[this->bot[number].index],AT_SKILL_KNIGHTADDLIFE,index,1);
	//			//gObjCalCharacter(lpObj->m_Index);
	//		}break;
	//		case SKILL_GREATER_CRITICAL_DAMAGE:
	//		{
	//			int value1 = ((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterCriticalDamageConstA)+((lpObj->Leadership+lpObj->AddLeadership)/gServerInfo.m_GreaterCriticalDamageConstB);

	//			int value2 = 0;

	//			int value3 = 0;

	//			//int count = gServerInfo.m_GreaterCriticalDamageTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterCriticalDamageTimeConstB);

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_CRITICAL_DAMAGE,this->bot[number].skill[x].time,value1,value2,value3,0);

	//			gSkillManager.GCSkillAttackSend(lpBot,SKILL_GREATER_CRITICAL_DAMAGE,aIndex,1);	
	//		}break;
	//		case SKILL_DAMAGE_REFLECT:
	//		{
	//			int value = gServerInfo.m_ReflectDamageConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ReflectDamageConstB);

	//			value = ((value>gServerInfo.m_ReflectDamageMaxRate)?gServerInfo.m_ReflectDamageMaxRate:value);

	//			value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_ReflectDamageRate[lpObj->Class]:100))/100;

	//			//int count = gServerInfo.m_ReflectDamageTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ReflectDamageTimeConstB);

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_DAMAGE_REFLECT,this->bot[number].skill[x].time,value,0,0,0);

	//			gSkillManager.GCSkillAttackSend(lpBot,SKILL_DAMAGE_REFLECT,aIndex,1);
	//		}break;
	//		case SKILL_MAGIC_CIRCLE:
	//		{
	//			int value1 = (((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_DWMagicDamageMinConstA)*gServerInfo.m_MagicCircleConstA)/100;

	//			int value2 = 0;

	//			int value3 = 0;

	//			//int count = gServerInfo.m_MagicCircleTimeConstA;

	//			gEffectManager.AddEffect(lpObj,0,EFFECT_MAGIC_CIRCLE,this->bot[number].skill[x].time,value1,value2,value3,0);

	//			gSkillManager.GCSkillAttackSend(lpBot,SKILL_MAGIC_CIRCLE,aIndex,1);
	//		}break;
	//	}
	//}

	//GCChatTargetSend(lpBot, lpObj->Index, "Now you are blessed!");
	//return 1;
}

void CBotBuffer::CheckPrice(int aIndex, int bIndex)
{
	
}

void CBotBuffer::CheckPriceCallback(LPOBJ lpObj, int botindex, LPOBJ lpBot, DWORD WCoinC, DWORD WCoinP, DWORD GoblinPoint)
{
	char sbuf[512] = {0};
	if (lpObj->AccountLevel < gBotBuffer.bot[botindex].OnlyVip)
	{
		ChatSend(&gObj[gBotBuffer.bot[botindex].index],gMessage.GetMessage(517));
		return;
	}

	if (gBotBuffer.bot[botindex].PriceType == 0)
	{
		if (lpObj->Money < gBotBuffer.bot[botindex].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(518),gBotBuffer.bot[botindex].PriceCount);
			ChatSend(&gObj[gBotBuffer.bot[botindex].index],sbuf);
			return;
		}
	}
	else if (gBotBuffer.bot[botindex].PriceType == 1)
	{
		if (WCoinC < gBotBuffer.bot[botindex].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(519),gBotBuffer.bot[botindex].PriceCount);
			ChatSend(&gObj[gBotBuffer.bot[botindex].index],sbuf);
			return;
		}
	}
	else if (gBotBuffer.bot[botindex].PriceType == 2)
	{
		if (WCoinP < gBotBuffer.bot[botindex].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(520),gBotBuffer.bot[botindex].PriceCount);
			ChatSend(&gObj[gBotBuffer.bot[botindex].index],sbuf);
			return;
		}
	}
	else if (gBotBuffer.bot[botindex].PriceType == 3)
	{
		if (GoblinPoint < gBotBuffer.bot[botindex].PriceCount)
		{
			wsprintf(sbuf,gMessage.GetMessage(521),gBotBuffer.bot[botindex].PriceCount);
			ChatSend(&gObj[gBotBuffer.bot[botindex].index],sbuf);
			return;
		}
	}
	else
	{
		wsprintf(sbuf,"Wrong currency! Contact Admin check config!!!");
		ChatSend(&gObj[gBotBuffer.bot[botindex].index],sbuf);
		return;
	}

	if (gBotBuffer.bot[botindex].PriceType == 0)
	{
		lpObj->Money -= gBotBuffer.bot[botindex].PriceCount;
		GCMoneySend(lpObj->Index, lpObj->Money);
	}
	else if (gBotBuffer.bot[botindex].PriceType == 1)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,gBotBuffer.bot[botindex].PriceCount,0,0);
	}
	else if (gBotBuffer.bot[botindex].PriceType == 2)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,gBotBuffer.bot[botindex].PriceCount,0);
	}
	else if (gBotBuffer.bot[botindex].PriceType == 3)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,0,gBotBuffer.bot[botindex].PriceCount);
	}

	for(int x=0;x<gBotBuffer.bot[botindex].SkillCount;x++)
	{
		switch(gBotBuffer.bot[botindex].skill[x].skill)
		{
			case SKILL_MANA_SHIELD:
			{
				int value1 = gServerInfo.m_ManaShieldConstA+((lpObj->Dexterity+lpObj->AddDexterity)/gServerInfo.m_ManaShieldConstB)+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ManaShieldConstC);

				value1 = ((value1>gServerInfo.m_ManaShieldMaxRate)?gServerInfo.m_ManaShieldMaxRate:value1);

				value1 = (value1*((lpObj->Type==OBJECT_USER)?gServerInfo.m_ManaShieldRate[lpObj->Class]:100))/100;

				int value2 = gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_MANA_SHIELD_MASTERED);

				//int count = gServerInfo.m_ManaShieldTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ManaShieldTimeConstB);

				//count += gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_MANA_SHIELD_ENHANCED);

				gEffectManager.AddEffect(lpObj,0,EFFECT_MANA_SHIELD,gBotBuffer.bot[botindex].skill[x].time,value1,value2,0,0);

				gSkillManager.GCSkillAttackSend(lpBot,SKILL_MANA_SHIELD,lpBot->Index,1);
			}break;
			case SKILL_GREATER_DEFENSE:
			{
				int value = gServerInfo.m_GreaterDefenseConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterDefenseConstB);

				value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_IMPROVED))/100;

				value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_ENHANCED))/100;

				value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterDefenseRate[lpObj->Class]:100))/100;

				//int count = gServerInfo.m_GreaterDefenseTimeConstA;

				//count += gMasterSkillTree.GetMasterSkillLevel(lpObj,MASTER_SKILL_ADD_GREATER_DEFENSE_ENHANCED);

				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DEFENSE,gBotBuffer.bot[botindex].skill[x].time,(value*2),0,0,0);

				gSkillManager.GCSkillAttackSend(lpObj,SKILL_GREATER_DEFENSE,lpBot->Index,1);
			}break;
			case SKILL_GREATER_DAMAGE:
			{
				int value = gServerInfo.m_GreaterDamageConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterDamageConstB);

				value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_IMPROVED))/100;

				value += (value*gMasterSkillTree.GetMasterSkillValue(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_ENHANCED))/100;

				value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterDamageRate[lpObj->Class]:100))/100;

				//int count = gServerInfo.m_GreaterDamageTimeConstA;

				//count += gMasterSkillTree.GetMasterSkillLevel(lpObj,MASTER_SKILL_ADD_GREATER_DAMAGE_ENHANCED);

				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DAMAGE,gBotBuffer.bot[botindex].skill[x].time,value,0,0,0);

				gSkillManager.GCSkillAttackSend(lpObj,SKILL_GREATER_DAMAGE,lpBot->Index,1);
			}break;
			case SKILL_GREATER_LIFE:
			{
				int value1 = gServerInfo.m_GreaterLifeConstA+((lpObj->Vitality+lpObj->AddVitality)/gServerInfo.m_GreaterLifeConstB)+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterLifeConstC);

				value1 = ((value1>gServerInfo.m_GreaterLifeMaxRate)?gServerInfo.m_GreaterLifeMaxRate:value1);

				int value2 = 0;

				int value3 = 0;

				//int count = gServerInfo.m_GreaterLifeTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterLifeTimeConstB);

				value1 = (value1*((lpObj->Type==OBJECT_USER)?gServerInfo.m_GreaterLifeRate[lpObj->Class]:100))/100;

				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_LIFE,gBotBuffer.bot[botindex].skill[x].time,value1,value2,value3,0);

				gSkillManager.GCSkillAttackSend(lpBot,SKILL_GREATER_LIFE,lpObj->Index,1);
				//gObjAddBuffEffect(lpObj, AT_SWELL_LIFE, 4, iaddlife, 0, 0, iLifeTime);
				//GCMagicAttackNumberSend(&gObj[this->bot[number].index],AT_SKILL_KNIGHTADDLIFE,index,1);
				//gObjCalCharacter(lpObj->m_Index);
			}break;
			case SKILL_GREATER_CRITICAL_DAMAGE:
			{
				int value1 = ((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterCriticalDamageConstA)+((lpObj->Leadership+lpObj->AddLeadership)/gServerInfo.m_GreaterCriticalDamageConstB);

				int value2 = 0;

				int value3 = 0;

				//int count = gServerInfo.m_GreaterCriticalDamageTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_GreaterCriticalDamageTimeConstB);

				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_CRITICAL_DAMAGE,gBotBuffer.bot[botindex].skill[x].time,value1,value2,value3,0);

				gSkillManager.GCSkillAttackSend(lpBot,SKILL_GREATER_CRITICAL_DAMAGE,lpObj->Index,1);	
			}break;
			case SKILL_DAMAGE_REFLECT:
			{
				int value = gServerInfo.m_ReflectDamageConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ReflectDamageConstB);

				value = ((value>gServerInfo.m_ReflectDamageMaxRate)?gServerInfo.m_ReflectDamageMaxRate:value);

				value = (value*((lpObj->Type==OBJECT_USER)?gServerInfo.m_ReflectDamageRate[lpObj->Class]:100))/100;

				//int count = gServerInfo.m_ReflectDamageTimeConstA+((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_ReflectDamageTimeConstB);

				gEffectManager.AddEffect(lpObj,0,EFFECT_DAMAGE_REFLECT,gBotBuffer.bot[botindex].skill[x].time,value,0,0,0);

				gSkillManager.GCSkillAttackSend(lpBot,SKILL_DAMAGE_REFLECT,lpObj->Index,1);
			}break;
			case SKILL_MAGIC_CIRCLE:
			{
				int value1 = (((lpObj->Energy+lpObj->AddEnergy)/gServerInfo.m_DWMagicDamageMinConstA)*gServerInfo.m_MagicCircleConstA)/100;

				int value2 = 0;

				int value3 = 0;

				//int count = gServerInfo.m_MagicCircleTimeConstA;

				gEffectManager.AddEffect(lpObj,0,EFFECT_MAGIC_CIRCLE,gBotBuffer.bot[botindex].skill[x].time,value1,value2,value3,0);

				gSkillManager.GCSkillAttackSend(lpBot,SKILL_MAGIC_CIRCLE,lpObj->Index,1);
			}break;
		}
	}

	//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"[BOT]: Now you are blessed!");
	ChatSend(&gObj[gBotBuffer.bot[botindex].index],gMessage.GetMessage(535));

}

