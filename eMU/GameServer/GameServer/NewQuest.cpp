#include "stdafx.h"
#include "NewQuest.h"
#include "GameServer.h"
#include "GameMain.h"
#include "CashShop.h"
#include "DSProtocol.h"
#include "MonsterManager.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Path.h"
#include "Util.h"
#include "Message.h"
#include "CommandManager.h"
// -------------------------------------------------------------------------

CQuestSystem gCustomQuest;
// -------------------------------------------------------------------------

CQuestSystem::CQuestSystem()
{
	this->Init();
}

CQuestSystem::~CQuestSystem()
{
	
}

void CQuestSystem::Init()
{
	for (int i = 0; i<MAX_QUESTS; i++)
	{
		this->m_Quest[i].q_Index	= -1;
		this->m_Quest[i].q_MobID	= -1;
		this->m_Quest[i].q_MobCnt	= -1;
		this->m_Quest[i].q_Type		= -1;
		this->m_Quest[i].q_ItemID	= -1;
		this->m_Quest[i].q_ItemLvl	= -1;
		strcpy(this->m_Quest[i].szHint, "");
	}
}
// -------------------------------------------------------------------------

void CQuestSystem::Load(char* path)
{
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

	this->Init();

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
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->Enable = lpMemScript->GetNumber();
					this->ID = lpMemScript->GetAsNumber();
					this->Map = lpMemScript->GetAsNumber();
					this->X = lpMemScript->GetAsNumber();
					this->Y = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					QUESTDATA info;
					memset(&info,0,sizeof(info));
					info.q_Index	= lpMemScript->GetNumber();
					info.q_MobID	= lpMemScript->GetAsNumber();
					info.q_MobCnt	= lpMemScript->GetAsNumber();
					info.q_Type		= lpMemScript->GetAsNumber();
					info.q_ItemID	= lpMemScript->GetAsNumber();
					info.q_ItemLvl	= lpMemScript->GetAsNumber();
					strcpy_s(info.szHint,lpMemScript->GetAsString());
					this->SetInfo(info);
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

void CQuestSystem::SetInfo(QUESTDATA info) // OK
{
	if(info.q_Index < 0 || info.q_Index >= MAX_QUESTS)
	{
		return;
	}

	this->m_Quest[info.q_Index] = info;
}

bool CQuestSystem::GetQuest(int index)
{
	// ----
	if (this->m_Quest[index].q_Index == -1)
		return false;
	// ----
	return true;
}
// -------------------------------------------------------------------------

bool CQuestSystem::Dialog(LPOBJ lpUser, LPOBJ lpNpc)
{

	if (	lpNpc->Class		== this->ID
		&&	lpNpc->Map			== this->Map
		&&	lpNpc->X			== this->X
		&&	lpNpc->Y			== this->Y )
		{
			this->TalkToNpc(lpUser->Index);
			return true;
		}
	return false;
}
// -------------------------------------------------------------------------

void CQuestSystem::TalkToNpc(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	// ----
	if (lpObj->Connected == OBJECT_ONLINE)
	{
		if (lpObj->iQuestIndex == 0)
		{
			if (lpObj->iQuestState == 0)
			{
				if (this->GetQuest(lpObj->iQuestIndex + 1))
				{
					MONSTER_INFO* lpMA = gMonsterManager.GetInfo(this->m_Quest[lpObj->iQuestIndex + 1].q_MobID);
					// ----
					if (lpMA == NULL)
						return;
					// ----
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(654),lpObj->iQuestIndex + 1);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(658), this->m_Quest[lpObj->iQuestIndex + 1].szHint);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(655), this->m_Quest[lpObj->iQuestIndex + 1].q_MobCnt, lpMA->Name);
					// ----
					// ----
					lpObj->iQuestIndex += 1;
					lpObj->iQuestState	= 1;
					lpObj->iQuestVar	= 0;
				}
				else
				{
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(656));
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(657));
				}
				// ----
				return;
			}
			else if (lpObj->iQuestState == 1)
			{
				if (this->GetQuest(lpObj->iQuestIndex))
				{
					MONSTER_INFO* lpMA = gMonsterManager.GetInfo(this->m_Quest[lpObj->iQuestIndex].q_MobID);
					// ----
					if (lpMA == NULL)
						return;
					// ----
					if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
					{
						if (this->m_Quest[lpObj->iQuestIndex].q_Type == 1)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(659), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							// ----
							unsigned long addZen = lpObj->Money + this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							// ----
							if (addZen > 2000000000)
							{
								addZen = 2000000000;
								this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(660));
							}
							// ----
							lpObj->Money = addZen;
							GCMoneySend(lpObj->Index, lpObj->Money);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 2)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(661), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//GDAddQuestStat(lpObj->m_Index, this->m_Quest[lpObj->iQuestIndex].q_wStat);
							lpObj->iQuestStat += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							lpObj->LevelUpPoint += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							//this->Effect(lpObj);
							GCFireworksSend(lpObj, lpObj->X, lpObj->Y);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 3)
						{
							this->MakeItem(lpObj, lpObj->iQuestIndex);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 4)
						{
							lpObj->Hornor.RankSlot1  = this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							SETTITLE_GD_SAVE_DATA pMsg;
							pMsg.header.set(0x0F,0x07,sizeof(pMsg));
							pMsg.index = lpObj->Index;
							memcpy(pMsg.Name,lpObj->Name,sizeof(pMsg.Name));
							pMsg.RankSlot1 = lpObj->Hornor.RankSlot1;
							gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 5)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(662), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinC += this->m_Quest[lpObj->iQuestIndex].q_wcoinc;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 6)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(663), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinP += this->m_Quest[lpObj->iQuestIndex].q_wcoinp;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 7)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(664), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.GoblinPoint += this->m_Quest[lpObj->iQuestIndex].q_goblin;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID);							
						}
						//
						GCNewCharacterInfoSend(lpObj);
						GDCharacterInfoSaveSend(lpObj->Index);
						// ----
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(665));					
						// ----
						lpObj->iQuestIndex++;
						lpObj->iQuestState  = 0;
						lpObj->iQuestVar	= 0;
						// ----
						//GDSaveQuestInfo(lpObj->Index); //Сохранение инфы
						return;
					}
					// ----
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(666), lpObj->iQuestIndex);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(658), this->m_Quest[lpObj->iQuestIndex].szHint);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(667), lpMA->Name, lpObj->iQuestVar, this->m_Quest[lpObj->iQuestIndex].q_MobCnt);
					// ----
				}
				else
				{
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(668));
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(657));
				}
				// ----
				return;
			}
			else if (lpObj->iQuestState == 2)
			{
				if (this->GetQuest(lpObj->iQuestIndex))
				{
					if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
					{
						if (this->m_Quest[lpObj->iQuestIndex].q_Type == 1)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(659), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							// ----
							unsigned long addZen = lpObj->Money + this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							// ----
							if (addZen > 2000000000)
							{
								addZen = 2000000000;
								this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(660));
							}
							// ----
							lpObj->Money = addZen;
							GCMoneySend(lpObj->Index, lpObj->Money);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 2)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(661), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//GDAddQuestStat(lpObj->m_Index, this->m_Quest[lpObj->iQuestIndex].q_wStat);
							lpObj->iQuestStat += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							lpObj->LevelUpPoint += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							//this->Effect(lpObj);
							GCFireworksSend(lpObj, lpObj->X, lpObj->Y);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 3)
						{
							this->MakeItem(lpObj, lpObj->iQuestIndex);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 4)
						{
							lpObj->Hornor.RankSlot1  = this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							SETTITLE_GD_SAVE_DATA pMsg;
							pMsg.header.set(0x0F,0x07,sizeof(pMsg));
							pMsg.index = lpObj->Index;
							memcpy(pMsg.Name,lpObj->Name,sizeof(pMsg.Name));
							pMsg.RankSlot1 = lpObj->Hornor.RankSlot1;
							gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 5)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(662), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinC += this->m_Quest[lpObj->iQuestIndex].q_wcoinc;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 6)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(663), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinP += this->m_Quest[lpObj->iQuestIndex].q_wcoinp;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 7)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(664), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.GoblinPoint += this->m_Quest[lpObj->iQuestIndex].q_goblin;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID);							
						}
						//
						GCNewCharacterInfoSend(lpObj);
						GDCharacterInfoSaveSend(lpObj->Index);
						// ----
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(665));					
						// ----
						lpObj->iQuestIndex++;
						lpObj->iQuestState  = 0;
						lpObj->iQuestVar	= 0;
						// ----
						//GDSaveQuestInfo(lpObj->Index); //Сохранение инфы
					}
				}
				// ----
				return;
			}
		}
		else
		{
			if (lpObj->iQuestState == 0)
			{
				if (this->GetQuest(lpObj->iQuestIndex))
				{
					MONSTER_INFO* lpMA = gMonsterManager.GetInfo(this->m_Quest[lpObj->iQuestIndex].q_MobID);
					// ----
					if (lpMA == NULL)
						return;
					// ----
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(654), lpObj->iQuestIndex);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(658), this->m_Quest[lpObj->iQuestIndex].szHint);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(655), this->m_Quest[lpObj->iQuestIndex].q_MobCnt, lpMA->Name);
					// ----
					lpObj->iQuestState = 1;
					lpObj->iQuestVar = 0;
				}
				else
				{
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(656));
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(657));
				}
				// ----
				return;
			}
			else if (lpObj->iQuestState == 1)
			{
				if (this->GetQuest(lpObj->iQuestIndex))
				{
					//LPMONSTER_ATTRIBUTE lpMA = gMAttr.GetAttr(this->m_Quest[lpObj->iQuestIndex].q_MobID);
					MONSTER_INFO* lpMA = gMonsterManager.GetInfo(this->m_Quest[lpObj->iQuestIndex].q_MobID);
					// ----
					if (lpMA == NULL)
						return;
					// ----
					if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
					{
						if (this->m_Quest[lpObj->iQuestIndex].q_Type == 1)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(659), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							// ----
							unsigned long addZen = lpObj->Money + this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							// ----
							if (addZen > 2000000000)
							{
								addZen = 2000000000;
								this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(660));
							}
							// ----
							lpObj->Money = addZen;
							GCMoneySend(lpObj->Index, lpObj->Money);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 2)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(661), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//GDAddQuestStat(lpObj->m_Index, this->m_Quest[lpObj->iQuestIndex].q_wStat);
							lpObj->iQuestStat += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							lpObj->LevelUpPoint += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							//this->Effect(lpObj);
							GCFireworksSend(lpObj, lpObj->X, lpObj->Y);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 3)
						{
							this->MakeItem(lpObj, lpObj->iQuestIndex);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 4)
						{
							lpObj->Hornor.RankSlot1  = this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							SETTITLE_GD_SAVE_DATA pMsg;
							pMsg.header.set(0x0F,0x07,sizeof(pMsg));
							pMsg.index = lpObj->Index;
							memcpy(pMsg.Name,lpObj->Name,sizeof(pMsg.Name));
							pMsg.RankSlot1 = lpObj->Hornor.RankSlot1;
							gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 5)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(662), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinC += this->m_Quest[lpObj->iQuestIndex].q_wcoinc;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 6)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(663), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinP += this->m_Quest[lpObj->iQuestIndex].q_wcoinp;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 7)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(664), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.GoblinPoint += this->m_Quest[lpObj->iQuestIndex].q_goblin;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID);							
						}
						
						GCNewCharacterInfoSend(lpObj);
						GDCharacterInfoSaveSend(lpObj->Index);
						// ----
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(665));
						// ----
						lpObj->iQuestIndex++;
						lpObj->iQuestState = 0;
						lpObj->iQuestVar = 0;
						// ----
						//GDSaveQuestInfo(lpObj->Index); //Сохранение инфы
						return;
					}
					// ----
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(666), lpObj->iQuestIndex);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(658), this->m_Quest[lpObj->iQuestIndex].szHint);
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(667), lpMA->Name, lpObj->iQuestVar, this->m_Quest[lpObj->iQuestIndex].q_MobCnt);
					// ----
				}
				else
				{
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(668));
					this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(657));
				}
				// ----
				return;
			}
			else if (lpObj->iQuestState == 2)
			{
				if (this->GetQuest(lpObj->iQuestIndex))
				{
					if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
					{
						if (this->m_Quest[lpObj->iQuestIndex].q_Type == 1)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(659), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							// ----
							unsigned long addZen = lpObj->Money + this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							// ----
							if (addZen > 2000000000)
							{
								addZen = 2000000000;
								this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(660));
							}
							// ----
							lpObj->Money = addZen;
							GCMoneySend(lpObj->Index, lpObj->Money);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 2)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(661), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//GDAddQuestStat(lpObj->m_Index, this->m_Quest[lpObj->iQuestIndex].q_wStat);
							lpObj->iQuestStat += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							lpObj->LevelUpPoint += this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							//this->Effect(lpObj);
							GCFireworksSend(lpObj, lpObj->X, lpObj->Y);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 3)
						{
							this->MakeItem(lpObj, lpObj->iQuestIndex);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 4)
						{
							lpObj->Hornor.RankSlot1  = this->m_Quest[lpObj->iQuestIndex].q_ItemID;
							SETTITLE_GD_SAVE_DATA pMsg;
							pMsg.header.set(0x0F,0x07,sizeof(pMsg));
							pMsg.index = lpObj->Index;
							memcpy(pMsg.Name,lpObj->Name,sizeof(pMsg.Name));
							pMsg.RankSlot1 = lpObj->Hornor.RankSlot1;
							gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 5)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(662), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinC += this->m_Quest[lpObj->iQuestIndex].q_wcoinc;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 6)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(663), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.WCoinP += this->m_Quest[lpObj->iQuestIndex].q_wcoinp;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID,0);							
						}
						else if (this->m_Quest[lpObj->iQuestIndex].q_Type == 7)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(664), this->m_Quest[lpObj->iQuestIndex].q_ItemID);
							//lpObj->GameShop.GoblinPoint += this->m_Quest[lpObj->iQuestIndex].q_goblin;
							//gGameShop.GDSavePoint(lpObj->m_Index);
							gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,0,0,this->m_Quest[lpObj->iQuestIndex].q_ItemID);							
						}
							
						GCNewCharacterInfoSend(lpObj);
						GDCharacterInfoSaveSend(lpObj->Index);
						// ----
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(665));
						// ----
						lpObj->iQuestIndex++;
						lpObj->iQuestState = 0;
						lpObj->iQuestVar = 0;
						// ----
						//GDSaveQuestInfo(lpObj->Index); //Сохранение инфы
					}
				}
				// ----
				return;
			}
		}
	}
}
// -------------------------------------------------------------------------

void CQuestSystem::MonsterKill(LPOBJ lpObj, LPOBJ lpTarget)
{

	if (this->Enable)
	{
		if (lpObj->iQuestState == 1 || lpObj->iQuestState == 2)
		{
			if (this->GetQuest(lpObj->iQuestIndex))
			{
				if (lpTarget->Class == this->m_Quest[lpObj->iQuestIndex].q_MobID)
				{
					if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
					{
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(670), lpObj->iQuestIndex);
						this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(671));

						lpObj->iQuestState = 2;
					}
					else
					{
						lpObj->iQuestVar++;

						//LPMONSTER_ATTRIBUTE lpMA = gMAttr.GetAttr(this->m_Quest[lpObj->iQuestIndex].q_MobID);
						MONSTER_INFO* lpMA = gMonsterManager.GetInfo(this->m_Quest[lpObj->iQuestIndex].q_MobID);

						if (lpMA != NULL)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(667), lpMA->Name, lpObj->iQuestVar, this->m_Quest[lpObj->iQuestIndex].q_MobCnt);
						}

						if (lpObj->iQuestVar >= this->m_Quest[lpObj->iQuestIndex].q_MobCnt)
						{
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(670), lpObj->iQuestIndex);
							this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(671));
							lpObj->iQuestState = 2;
						}
					}
				}
			}
		}
	}
}
// -------------------------------------------------------------------------

void CQuestSystem::SendMsg(int aIndex, int type, char* szMsg, ...)
{
	char szTemp[89];
	// ----
	va_list pArguments;
	va_start(pArguments, szMsg);
	vsprintf(szTemp, szMsg, pArguments); 
	va_end(pArguments);
	// ----
	PMSG_CHAT_WHISPER_RECV pWhisper;
	// ----
	if (type == 0)
	{
		pWhisper.header.type = 0xC1;
		pWhisper.header.size = sizeof(pWhisper);
		pWhisper.header.head = 0x00;
	}
	/*else if (type == 1)
	{
		GCServerMsgStringSend(szTemp, aIndex, 0x01);
		return;
	}*/
	else
	{
		pWhisper.header.type = 0xC1;
		pWhisper.header.size = sizeof(pWhisper);
		pWhisper.header.head = 0x02;
	}
	// ----
	strcpy(pWhisper.name, "");
	memcpy(pWhisper.message, szTemp, sizeof(szTemp));
	int len = strlen(pWhisper.message);
	// ----
	if (len > 0)
	{
		pWhisper.header.size -= sizeof(pWhisper.message);
		pWhisper.header.size += len + 1;
		// ----
		DataSend(aIndex, (LPBYTE)&pWhisper, pWhisper.header.size);
	}
}
// -------------------------------------------------------------------------

void CQuestSystem::MakeItem(LPOBJ lpObj, int QuestIndex)
{
	//int item_num = this->m_Quest[QuestIndex].q_ItemCat * 512 + this->m_Quest[QuestIndex].q_ItemID;
	// ----

	int type = this->m_Quest[QuestIndex].q_ItemID;
	int level = this->m_Quest[QuestIndex].q_ItemLvl;

	this->SendMsg(lpObj->Index, 0, gMessage.GetMessage(672));

	GDCreateItemSend(lpObj->Index,lpObj->Map,lpObj->X,lpObj->Y,type,level,0,0,0,0,lpObj->Index,0,0,0,0,0,0xFF,0);
	//GDCreateItemSend(lpObj->Index,lpObj->Map,(BYTE)lpObj->X,(BYTE)lpObj->Y,GET_ITEM(this->m_Quest[QuestIndex].q_ItemCat, this->m_Quest[QuestIndex].q_ItemID),this->m_Quest[QuestIndex].q_ItemLvl,0,0,0,0,lpObj->Index,0,0,0,0,0,0xFF,0);
	//this->Effect(lpObj);
	GCFireworksSend(lpObj, lpObj->X, lpObj->Y);
}