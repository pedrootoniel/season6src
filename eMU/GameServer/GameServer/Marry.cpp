#include "stdafx.h"
#include "Marry.h"
#include "protocol.h"
#include "user.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "Util.h"
#include "ItemManager.h"
#include "Notice.h"
#include "Message.h"
CMarry Marry;

CMarry::CMarry()
{
	InitializeCriticalSection(&this->m_criti);
}

CMarry::~CMarry()
{
	DeleteCriticalSection(&this->m_criti);
}

void CMarry::LoadFile(char * filename)
{
	EnterCriticalSection(&this->m_criti);

	this->m_bFileLoad = false;

	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(filename);

	if (res.status != pugi::status_ok)
	{
		ErrorMessageBox("Error loading %s file (%s)", filename, res.description());

		LeaveCriticalSection(&this->m_criti);
		return;
	}

	pugi::xml_node main = file.child("MarrySystem");

	this->m_bMarryEnable = main.attribute("Enable").as_bool();
	this->m_iMarryMinUserLevel = main.attribute("ReqLevel").as_int();
	this->m_iMarryNeedMoney = main.attribute("ReqMoney").as_int();

	pugi::xml_node location = main.child("Location");

	this->m_wMarryMapNumber = location.attribute("MapNumber").as_int();
	this->m_btMarryStartX = location.attribute("StartX").as_int();
	this->m_btMarryStartY = location.attribute("StartY").as_int();
	this->m_btMarryEndX = location.attribute("EndX").as_int();
	this->m_btMarryEndY = location.attribute("EndY").as_int();

	pugi::xml_node wedding = main.child("WeddingSettings");

	this->m_bHomoSexualAllow = wedding.attribute("Homosexual").as_bool();
	this->m_bNeedSpecialItemForMarry = wedding.attribute("ReqSpecialItem").as_bool();

	this->m_vtMarryItem.clear();
	
	for (pugi::xml_node item = wedding.child("Item"); item; item = item.next_sibling())
	{
		MARRY_ITEM m_Item;

		m_Item.m_iSide = item.attribute("Side").as_int();
		int iItemID = GET_ITEM(item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());//ItemGetNumberMake(item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());

		/*if (iItemID == -1)
		{
			g_Log.MsgBox("ERROR - Wrong item in %s file (%d %d)", filename, item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());
			continue;
		}*/

		m_Item.m_wItemID = iItemID;
		m_Item.m_iItemCount = item.attribute("ItemCount").as_int();

		this->m_vtMarryItem.push_back(m_Item);
	}

	pugi::xml_node gift = main.child("WeddingGift");

	this->m_bGiftEnable = gift.attribute("Enable").as_bool();

	this->m_vtGiftItem.clear();

	for (pugi::xml_node item = gift.child("Item"); item; item = item.next_sibling())
	{
		MARRY_ITEM m_Item;

		m_Item.m_iSide = item.attribute("Side").as_int();
		int iItemID = GET_ITEM(item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());

		/*if (iItemID == -1)
		{
			g_Log.MsgBox("ERROR - Wrong item in %s file (%d %d)", filename, item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());
			continue;
		}*/

		m_Item.m_wItemID = iItemID;
		m_Item.m_iItemCount = item.attribute("ItemCount").as_int();

		this->m_vtGiftItem.push_back(m_Item);
	}

	pugi::xml_node divorce = main.child("DivorceSettings");

	this->m_bDivorceAllow = divorce.attribute("Allow").as_bool();
	this->m_bNeedSpecialItemForDivorce = divorce.attribute("ReqSpecialItem").as_bool();

	this->m_vtDivorceItem.clear();

	for (pugi::xml_node item = divorce.child("Item"); item; item = item.next_sibling())
	{
		MARRY_ITEM m_Item;

		m_Item.m_iSide = 0;
		int iItemID = GET_ITEM(item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());

		/*if (iItemID == -1)
		{
			g_Log.MsgBox("ERROR - Wrong item in %s file (%d %d)", filename, item.attribute("ItemCat").as_int(), item.attribute("ItemIndex").as_int());
			continue;
		}*/

		m_Item.m_wItemID = iItemID;
		m_Item.m_iItemCount = item.attribute("ItemCount").as_int();

		this->m_vtDivorceItem.push_back(m_Item);
	}

	this->m_bFileLoad = true;
	LeaveCriticalSection(&this->m_criti);
}

void CMarry::Propose(int aIndex, int uIndex)
{
	if (OBJECT_RANGE(aIndex) == 0 || OBJECT_RANGE(uIndex) == 0)
	{
		return;
	}

	if (gObj[uIndex].Type != OBJECT_USER)
	{
		return;
	}

	if (gObj[aIndex].Name == gObj[uIndex].Name)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,393), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(584));
		return;
	}

	if (!this->m_bMarryEnable)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(585));
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,373), aIndex, 1);
		return;
	}

	if (gObj[aIndex].IsMarried != 0 || gObj[uIndex].IsMarried != 0)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,374), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(586));
		return;
	}

	if (isFemale(aIndex) == isFemale(uIndex) && !this->m_bHomoSexualAllow)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,375), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(587));
		return;
	}

	if (isMale(aIndex) == isMale(uIndex) && !this->m_bHomoSexualAllow)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(587));
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,375), aIndex, 1);
		return;
	}

	if (this->m_iMarryNeedMoney > gObj[aIndex].Money || this->m_iMarryNeedMoney > gObj[uIndex].Money)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,376), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(588));
		return;
	}

	if (this->m_iMarryMinUserLevel > gObj[aIndex].Level || this->m_iMarryMinUserLevel > gObj[uIndex].Level)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,377), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(589));
		return;
	}

	if (!this->CheckPosition(aIndex, uIndex))
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,378), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(590));
		return;
	}

	bool bCheck1 = this->CheckRequiredItem(aIndex, 1);
	bool bCheck2 = this->CheckRequiredItem(uIndex, 2);

	if (bCheck1 == false || bCheck2 == false)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,379), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(591));
		return;
	}

	gObj[uIndex].MarryRequested = 1;
	gObj[uIndex].MarryRequestIndex = aIndex;
	gObj[uIndex].MarryRequestTime = GetTickCount();

	//char msg[128];
	//wsprintf(msg, Lang.GetText(0,380), gObj[aIndex].Name);
	//GSProtocol.GCServerMsgStringSend(msg, uIndex, 1);
	gNotice.GCNoticeSend(uIndex,1,0,0,0,0,0,gMessage.GetMessage(592),gObj[aIndex].Name);
	//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,381), aIndex, 1);
	gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(593));

	//g_Log.Add("[Marry][%s][%s] Request to marry with [%s][%s]", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[uIndex].AccountID, gObj[uIndex].Name);
	LogAdd(LOG_BLUE, "[Marry][%s][%s] Request to marry with [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name, gObj[uIndex].Account, gObj[uIndex].Name);
}

bool CMarry::Accept(int aIndex)
{
	if (OBJECT_RANGE(aIndex) == 0)
	{
		return false;
	}

	char info[255];
	int uIndex = gObj[aIndex].MarryRequestIndex;

	if (gObj[aIndex].MarryRequested != 1)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,382), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(594));
		return false;
	}

	if (GetTickCount() - gObj[aIndex].MarryRequestTime > 60000)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,383), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(595));
		gObj[aIndex].MarryRequested = 0;
		return false;
	}

	if (!this->CheckPosition(aIndex, uIndex))
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,384), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(590));
		return false;
	}

	if (gObj[uIndex].Money < gObj[uIndex].Money - this->m_iMarryNeedMoney || gObj[aIndex].Money < gObj[aIndex].Money - this->m_iMarryNeedMoney)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,385), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(596));
		return false;
	}

	bool bCheck1 = this->CheckRequiredItem(aIndex, 1);
	bool bCheck2 = this->CheckRequiredItem(uIndex, 2);

	if (bCheck1 == false || bCheck2 == false)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,386), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(591));
		return false;
	}

	this->DeleteRequiredItem(aIndex, 1);
	this->DeleteRequiredItem(uIndex, 2);

	gObj[aIndex].IsMarried = 1;
	gObj[aIndex].MarryRequestIndex = 0;
	gObj[aIndex].MarryRequestTime = 0;
	strcpy(gObj[aIndex].MarryName, gObj[uIndex].Name);

	gObj[aIndex].Money -= this->m_iMarryNeedMoney;
	GCMoneySend(aIndex, gObj[aIndex].Money);

	//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,387), aIndex, 1);
	gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(597));

	gObj[uIndex].IsMarried = 1;
	gObj[uIndex].MarryRequestIndex = 0;
	gObj[uIndex].MarryRequestTime = 0;
	strcpy(gObj[uIndex].MarryName, gObj[aIndex].Name);

	gObj[uIndex].Money -= this->m_iMarryNeedMoney;
	GCMoneySend(uIndex, gObj[uIndex].Money);

	//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,388), uIndex, 1);
	gNotice.GCNoticeSend(uIndex,0,0,0,0,0,0,gMessage.GetMessage(597));
		
	PMSG_FIREWORKS_SEND pMsg;

	pMsg.header.set(0xF3,0x40,sizeof(pMsg));
	pMsg.type = 0;
	pMsg.x = gObj[uIndex].X;
	pMsg.y = gObj[uIndex].Y;

	DataSend(uIndex,(BYTE*)&pMsg,pMsg.header.size);
	MsgSendV2(&gObj[uIndex],(BYTE*)&pMsg,pMsg.header.size);

	pMsg.x = gObj[aIndex].X;
	pMsg.y = gObj[aIndex].Y;

	//GSProtocol.MsgSendV2(gObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
	//IOCP.DataSend(aIndex, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
	MsgSendV2(&gObj[uIndex],(BYTE*)&pMsg,pMsg.header.size);

	if (this->m_bGiftEnable == true)
	{
		this->GiveGiftItem(aIndex, 1);
		this->GiveGiftItem(uIndex, 2);
	}

	//wsprintf(info, Lang.GetText(0,389), gObj[uIndex].Name, gObj[aIndex].Name);
	//GSProtocol.AllSendServerMsg(info);
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(598),gObj[uIndex].Name, gObj[aIndex].Name);

	//g_Log.Add("[Marry] New Marriage: %s [%d]  %s [%d]", gObj[uIndex].Name, gObj[aIndex].Married, gObj[aIndex].Name, gObj[uIndex].Married);
	LogAdd(LOG_BLUE, "[Marry] New Marriage: %s [%d]  %s [%d]", gObj[uIndex].Name, gObj[aIndex].IsMarried, gObj[aIndex].Name, gObj[uIndex].IsMarried);
	return true;
}

void CMarry::Divorce(int aIndex)
{
	if (gObj[aIndex].IsMarried == 0)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,390), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(599));
		return;
	}

	if (this->m_bDivorceAllow == false)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,614), aIndex, 1);
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(600));
		return;
	}

	if (!this->CheckDivorceItem(aIndex))
	{
		//MsgOutput(aIndex, Lang.GetText(0,391));
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(601));
		return;
	}

	//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,392), aIndex, 1);
	gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(602));
	
	//int uIndex = gObjGetIndex(gObj[aIndex].MarryName);
	LPOBJ lpTarget = gObjFind(gObj[aIndex].MarryName);

	if (lpTarget != 0)
	{
		//GSProtocol.GCServerMsgStringSend(Lang.GetText(0,392), uIndex, 1);
		gNotice.GCNoticeSend(lpTarget->Index,1,0,0,0,0,0,gMessage.GetMessage(602));
		gObj[lpTarget->Index].IsMarried = 0;
		strcpy(lpTarget->Name, "");
	}

	gObj[aIndex].IsMarried = 0;
	strcpy(gObj[aIndex].MarryName, "");

	this->DeleteDivorceItem(aIndex);

	LogAdd(LOG_BLUE, "[Marry] Divorce: [%s] [%d]", gObj[aIndex].Name, lpTarget->Name);
	//g_Log.Add("[Marry] Divorce: [%s] [%d]", gObj[aIndex].Name, gObj[uIndex].Name);
}

bool CMarry::CheckPosition(int aIndex, int uIndex)
{
	int aX = gObj[aIndex].X, aY = gObj[aIndex].Y, aM = gObj[aIndex].Map, uX = gObj[uIndex].X, uY = gObj[uIndex].Y, uM = gObj[uIndex].Map;

	if((aX >= this->m_btMarryStartX && aX <= this->m_btMarryEndX) && (aY >= this->m_btMarryStartY && aY <= this->m_btMarryEndY) && (uX >= this->m_btMarryStartX && uX <= this->m_btMarryEndX) && (uY >= this->m_btMarryStartY && uY <= this->m_btMarryEndY))
	{
		return true;
	}

	return false;
}

bool CMarry::CheckRequiredItem(int aIndex, int iSide)
{
	if(!this->m_bNeedSpecialItemForMarry) return true;

	EnterCriticalSection(&this->m_criti);

	for (std::vector<MARRY_ITEM>::iterator It = this->m_vtMarryItem.begin(); It != this->m_vtMarryItem.end(); It++)
	{
		if (It->m_iSide != iSide)
		{
			continue;
		}

		if (gItemManager.GetInventoryItemCount(&gObj[aIndex], It->m_wItemID,-1) < It->m_iItemCount)
		{
			LeaveCriticalSection(&this->m_criti);
			return false;
		}
	}

	LeaveCriticalSection(&this->m_criti);
	return true;
}

bool CMarry::CheckDivorceItem(int aIndex)
{
	if(!this->m_bNeedSpecialItemForDivorce) return true;

	EnterCriticalSection(&this->m_criti);

	for (std::vector<MARRY_ITEM>::iterator It = this->m_vtDivorceItem.begin(); It != this->m_vtDivorceItem.end(); It++)
	{
		if (gItemManager.GetInventoryItemCount(&gObj[aIndex], It->m_wItemID,-1) < It->m_iItemCount)
		{
			LeaveCriticalSection(&this->m_criti);
			return false;
		}
	}

	LeaveCriticalSection(&this->m_criti);
	return true;
}

void CMarry::GiveGiftItem(int aIndex, int iSide)
{
	if (!this->m_bGiftEnable) return;

	EnterCriticalSection(&this->m_criti);

	for (std::vector<MARRY_ITEM>::iterator It = this->m_vtGiftItem.begin(); It != this->m_vtGiftItem.end(); It++)
	{
		if (It->m_iSide != iSide)
		{
			continue;
		}

		for (int i = 0; i < It->m_iItemCount; i++)
		{
			//ItemSerialCreateSend(aIndex, 235, 0, 0, It->m_wItemID, 0, 0, 0, 0, 0, aIndex, 0, 0, 0, 0, 0);
			GDCreateItemSend(aIndex,0xEB,0,0,It->m_wItemID,0,0,0,0,0,aIndex,0,0,0,0,0,0xFF,0);
		}
	}

	LeaveCriticalSection(&this->m_criti);
}

void CMarry::DeleteRequiredItem(int aIndex, int iSide)
{
	if(!this->m_bNeedSpecialItemForMarry) return;

	EnterCriticalSection(&this->m_criti);

	for (std::vector<MARRY_ITEM>::iterator It = this->m_vtMarryItem.begin(); It != this->m_vtMarryItem.end(); It++)
	{
		if (It->m_iSide != iSide)
		{
			continue;
		}

		for (int i = 0; i < It->m_iItemCount; i++)
		{
			for(int i=0;i<INVENTORY_SIZE;i++)
			{
				if(gObj[aIndex].Inventory[i].IsItem())
				{
					if (gObj[aIndex].Inventory[i].m_Index == It->m_wItemID)
					{
						gItemManager.InventoryDelItem(aIndex, i);
						gItemManager.GCItemDeleteSend(aIndex, i, 1);
						break;
					}
				}	
			}
		}
	}

	LeaveCriticalSection(&this->m_criti);
}

void CMarry::DeleteDivorceItem(int aIndex)
{
	if(!this->m_bNeedSpecialItemForDivorce) return;

	EnterCriticalSection(&this->m_criti);

	for (std::vector<MARRY_ITEM>::iterator It = this->m_vtDivorceItem.begin(); It != this->m_vtDivorceItem.end(); It++)
	{
		for (int i = 0; i < It->m_iItemCount; i++)
		{
			for (int i = 0; i<INVENTORY_SIZE; i++)
			{
				if (gObj[aIndex].Inventory[i].IsItem())
				{
					if (gObj[aIndex].Inventory[i].m_Index == It->m_wItemID)
					{
						gItemManager.InventoryDelItem(aIndex, i);
						gItemManager.GCItemDeleteSend(aIndex, i, 1);
						break;
					}
				}
			}
		}
	}

	LeaveCriticalSection(&this->m_criti);
}