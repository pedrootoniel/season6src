#include "StdAfx.h"
#include "Smithy.h"
#include "GameMain.h"
//#include "..\\include\\ReadScript.h"
//#include "logproc.h"
#include "DSProtocol.h"
#include "Log.h"
#include "Notice.h"
//#include "..\common\SetItemOption.h"
//#include "ExUser.h"
//#include "ExLicense.h"
//#include "LogToFile.h"
#include "MemScript.h"
#include "Util.h"
#include "ItemManager.h"
#include "SetItemType.h"
//#include "BankEx.h"
#include "CashShop.h"
#include "SocketItemType.h"
#include "Path.h"
//#include "Protection.h"
#include "Message.h"
//CLogToFile g_SmithLog("Smith", ".\\LOG\\Smith", TRUE);

CSmithy gSmithy;

CSmithy::CSmithy()
{
	this->Init();
}

CSmithy::~CSmithy()
{
}

void CSmithy::Init()
{
	this->itemdata.clear();
	this->MaxLevel = 0;
	this->LevelPrice = 0;
	this->LuckPrice = 0;
	this->AddPrice = 0;
	this->Opt1Price = 0;
	this->Opt2Price = 0;
	this->Opt3Price = 0;
	this->Opt4Price = 0;
	this->Opt5Price = 0;
	this->Opt6Price = 0;
	this->AncientPrice = 0;
}

void CSmithy::Load()
{
	this->Init();
	this->Read(gPath.GetFullPath("..\\Data\\Custom\\Smithy.txt"));
}

void CSmithy::Read(char* path)
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

					this->MaxLevel = lpMemScript->GetNumber();
					this->LevelPrice = lpMemScript->GetAsNumber();
					this->MaxDays = lpMemScript->GetAsNumber();
					this->DaysPrice = lpMemScript->GetAsNumber();
					this->LuckPrice = lpMemScript->GetAsNumber();
					this->AddPrice = lpMemScript->GetAsNumber();
					this->Opt1Price = lpMemScript->GetAsNumber();
					this->Opt2Price = lpMemScript->GetAsNumber();
					this->Opt3Price = lpMemScript->GetAsNumber();
					this->Opt4Price = lpMemScript->GetAsNumber();
					this->Opt5Price = lpMemScript->GetAsNumber();
					this->Opt6Price = lpMemScript->GetAsNumber();
					//this->AncientPrice = lpMemScript->GetAsNumber();
					//this->SocketPrice = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 3)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 4)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 5)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 6)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
				}
				else if (section == 7)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SmithyDATA lpData;
					lpData.Type = lpMemScript->GetNumber();
					lpData.Index = lpMemScript->GetAsNumber();
					lpData.Class = section-1;
					lpData.Price = lpMemScript->GetAsNumber();
					lpData.Time = lpMemScript->GetAsNumber();
					this->itemdata.push_back(lpData);
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

void CSmithy::GCInitItem(int aIndex)
{
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	GC_SmithyInit pMsg;
	//pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x1E,  sizeof(pMsg));
	pMsg.h.set(0xFB, 0x31,  sizeof(pMsg));
	pMsg.result = true;
	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void CSmithy::GCItemSend(int aIndex)
{
	//LogAdd(LOG_TEST,"KEK");
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	this->GCSettingsSend(aIndex);
	//this->GCSendAncientList(aIndex);
	//this->GCSendSocketList(aIndex);
	this->GCInitItem(aIndex);
	for(int i = 0; i < itemdata.size(); i++)
	{
		GC_SmithyDATA pMsg;
		pMsg.h.set(0xFB, 0x32,  sizeof(pMsg));
		pMsg.Class = itemdata[i].Class;
		pMsg.Type = itemdata[i].Type;
		pMsg.Index = itemdata[i].Index;
		pMsg.Price = itemdata[i].Price;
		pMsg.Time = itemdata[i].Time;
		DataSend(aIndex,(BYTE*)&pMsg,sizeof(pMsg));
	}
}

void CSmithy::GCSettingsSend(int aIndex)
{
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	GC_SmithySettings pMsg;
	pMsg.h.set(0xFB, 0x30,  sizeof(pMsg));
	pMsg.MaxLevel = this->MaxLevel;
	pMsg.LevelPrice = this->LevelPrice;
	pMsg.MaxDays = this->MaxDays;
	pMsg.DaysPrice = this->DaysPrice;
	pMsg.LuckPrice = this->LuckPrice;
	pMsg.AddPrice = this->AddPrice;
	pMsg.Opt1Price = this->Opt1Price;
	pMsg.Opt2Price = this->Opt2Price;
	pMsg.Opt3Price = this->Opt3Price;
	pMsg.Opt4Price = this->Opt4Price;
	pMsg.Opt5Price = this->Opt5Price;
	pMsg.Opt6Price = this->Opt6Price;
	//pMsg.AncientPrice = this->AncientPrice;
	//pMsg.SocketPrice = this->SocketPrice;
	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void CSmithy::GCSendAncientList(int aIndex)
{
	//LogAdd(LOG_TEST,"Count = %d",gSocketItemType.GetCountOfSocketItems());
	BYTE send[4096];

	PMSG_SMITHY_ANCIENT_SEND pMsg;

	pMsg.header.set(0xF3,0xF3,0);

	int size = sizeof(pMsg);

	pMsg.count = 0;

	PMSG_SMITHY_ANCIENT info;

	for	(int i=0;i<gSetItemType.GetCountOfItems();i++)
	{
		SET_ITEM_TYPE_INFO* lpInfo = gSetItemType.GetInfoByIndex(i);
		if (lpInfo == 0)
		{
			continue;
		}

		info.index = lpInfo->Index;

		/*if (lpInfo->Index == GET_ITEM(8,1))
		{
			LogAdd(LOG_TEST,"Send = %d %d",lpInfo->OptionIndex[0],lpInfo->OptionIndex[1]);
		}*/
		if (lpInfo->OptionIndex[0] != 0)
		{
			info.options[0] = 5;
		}
		else
		{
			info.options[0] = 0;
		}
		if (lpInfo->OptionIndex[1] != 0)
		{
			info.options[1] = 6;
		}
		else
		{
			info.options[1] = 0;
		}

		/*info.options[0] = lpInfo->OptionIndex[0];
		info.options[1] = lpInfo->OptionIndex[1];*/
		/*if (lpInfo->Index == GET_ITEM(8,1))
		{
			LogAdd(LOG_TEST,"Send = %d %d",info.options[0],info.options[1]);
		}*/

		/*info.options[0] = 1;

		if (lpInfo->OptionIndex[0] != 0 && lpInfo->OptionIndex[1] != 0)
		{
			info.options[2] = 2;
		}*/

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);

	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));
	DataSend(aIndex,send,size);
}

void CSmithy::GCSendSocketList(int aIndex)
{
	BYTE send[4096];

	PMSG_SMITHY_SOCKET_SEND pMsg;

	pMsg.header.set(0xF3,0xF4,0);

	int size = sizeof(pMsg);

	pMsg.count = 0;

	PMSG_SMITHY_SOCKET info;

	//LogAdd(LOG_TEST,"count = %d",gSocketItemType.GetCountOfSocketItems());

	for(std::map<int,SOCKET_ITEM_TYPE_INFO>::iterator it = gSocketItemType.m_SocketItemTypeInfo.begin(); it != gSocketItemType.m_SocketItemTypeInfo.end();it++)
	{
		info.index = it->second.Index;

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);

	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));
	DataSend(aIndex,send,size);
}



void CSmithy::CGCreateItem(CG_SmithyCreateItem* aRecv, int aIndex)
{

	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < OBJECT_ONLINE)
	{
		return;
	}

	unsigned short id = aRecv->Item;

	if(id > itemdata.size())
	{
		return;
	}

	SmithyDATA smItem =  this->itemdata[id];

	short iType = GET_ITEM(smItem.Type,smItem.Index);

	int result = smItem.Price;
	result += aRecv->ItemLevel * this->LevelPrice;
	result += aRecv->ItemAdd * this->AddPrice;
	BYTE NewOption = 0;
	int SetOption = 0;
	if(smItem.Time == 1)
	{
		result += aRecv->ItemTime * this->DaysPrice;
	}
	if(aRecv->ItemLuck)
	{
		result += this->LuckPrice;
	}
	if(aRecv->ItemOpt1)
	{
		result += this->Opt1Price;
		 NewOption |= 0x20;
	}
	if(aRecv->ItemOpt2)
	{
		result += this->Opt2Price;
		NewOption |= 0x10;
	}
	if(aRecv->ItemOpt3)
	{
		result += this->Opt3Price;
		NewOption |= 0x08;
	}
	if(aRecv->ItemOpt4)
	{
		result += this->Opt4Price;
		NewOption |= 0x04;
	}
	if(aRecv->ItemOpt5)
	{
		result += this->Opt5Price;
		NewOption |= 0x02;
	}
	if(aRecv->ItemOpt6)
	{
		result += this->Opt6Price;
		NewOption |= 0x01;
	}
	if(aRecv->Ancient)
	{
		result += this->AncientPrice;
		//SetOption = gSetItemType.GetSetOption(iType);
		
		SetOption = aRecv->Ancient;
		/*if (aRecv->Ancient == 1)
		{
			SetOption = 5;
		}
		else if (aRecv->Ancient == 2)
		{
			SetOption = 6;
		}*/
	}

	ITEM_INFO ItemInfo;

	if(gItemManager.GetInfo(iType,&ItemInfo) == 0)
	{
		LogAdd(LOG_RED, "[Smithy Shop] Error [0x1] Contact support! Item Dont Exist [%d]",iType);
		return;
	}

	//int iHeight = ItemAttribute[iType].Height;
	//int iWidth = ItemAttribute[iType].Width;
					
	if(gItemManager.CheckItemInventorySpace(lpUser,ItemInfo.Height,ItemInfo.Width) == false)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(536), ItemInfo.Height,ItemInfo.Width);
		return;
	}

	//gItemManager.InventoryInsertItem(lpObj->Index,lpObj->ChaosBox[n]);

	if(result > lpUser->WCoinCaRecv)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(537), result);
		return;
	}

	/*if(lpUser->GameShop.WCoinC > 30000)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"[Tokens Shop]: Error");
		return;
	}*/
	gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,result,0,0);
	//lpUser->BankEx.Credits -= result;
	//gBankEx.GCUpdateBankEx(lpUser->Index);
	//gBankEx.GDSavePoint(lpUser->Index);
	//gGameShop.GDSaveUserInfo(lpUser->m_Index);

	//ExUserDataSend(aIndex);
	//ItemSerialCreateSend(aIndex, 235, lpUser->X, lpUser->Y, iType, aRecv->ItemLevel, 0, 1, aRecv->ItemLuck, aRecv->ItemAdd, aIndex, NewOption, 0);
	
	
	
	
		int SocketCount		= 0;
	BYTE SocketBonus	= (BYTE)-1;
	BYTE SocketOption[5] = {0xFF,0xFF,0xFF,0xFF,0xFF};

	if( gSocketItemType.CheckSocketItemType(iType) )
	{
		SocketCount = gSocketItemType.GetSocketItemMaxSocket(iType);
		for( int i = 0; i < 5; i++ )
		{
			if( i < SocketCount )
			{
				if (aRecv->ItemSocket == 1)
				{
					SocketOption[i]=0xFE;
				}
			}
		}		
	}
	//
	time_t t = time(NULL);
	localtime(&t);
	DWORD iTime = (DWORD)t + aRecv->ItemTime * 86400;
	//
	//ItemSerialCreateSend(aIndex, 235, lpUser->X, lpUser->Y, iType, aRecv->ItemLevel, 0, 1, aRecv->ItemLuck, aRecv->ItemAdd,
	//		aIndex, NewOption, SetOption, SocketBonus, SocketOption);
	if(smItem.Time == 1)
	GDCreateItemSend(aIndex,235,lpUser->X,lpUser->Y,iType,aRecv->ItemLevel,0,1,aRecv->ItemLuck,aRecv->ItemAdd,aIndex,NewOption,0,0,0,0,0,iTime);
	else
	GDCreateItemSend(aIndex,235,lpUser->X,lpUser->Y,iType,aRecv->ItemLevel,0,1,aRecv->ItemLuck,aRecv->ItemAdd,aIndex,NewOption,0,0,0,0,0,0);

	gLog.Output(LOG_SMITHITEM, "Item buy! Price:%d - Login: %s Name: %s, iType ID: %d,Level: %d,Dur: %d,Skill: %d, Luck: %d, Opt: %d, Exe: %d, Time: %d",
					result,lpUser->Account, lpUser->Name, iType, aRecv->ItemLevel, 0, 1, aRecv->ItemLuck, aRecv->ItemAdd, NewOption, aRecv->ItemTime);


	//}
	#if(SYSTEM_ACHIEVEMENTS)
		g_Achievements.BuyDonateShopItem(lpUser->m_Index, result);
	#endif
	
	
	//MsgOutput(aIndex, "[Tokens Shop]: Item Created!");
	gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(538));
}