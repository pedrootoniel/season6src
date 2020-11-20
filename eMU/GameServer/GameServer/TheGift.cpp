#include "stdafx.h"
#include "GameServer.h"
#include "GameMain.h"
#include "Util.h"
#include "User.h"
#include "TheGift.h"
#include "CashShop.h"
#include "MemScript.h"
#include "ExUtilits.h"
#include "Notice.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "EffectManager.h"
#include "ServerInfo.h"
#include "Message.h"
CQuaTanThu gQuaTanThu;

CQuaTanThu::CQuaTanThu() // OK
{
	this->Init();
}

CQuaTanThu::~CQuaTanThu() // OK
{

}

void CQuaTanThu::Init() // OK
{
	memset(this->m_QuaTanThuInfo,0,sizeof(this->m_QuaTanThuInfo));
}

void CQuaTanThu::Load(char* path) // OK
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

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			QUATANTHU_INFO info;

			info.Class = lpMemScript->GetNumber();

			info.WeaponType = lpMemScript->GetAsNumber();

			info.WeaponID = lpMemScript->GetAsNumber();

			info.SetID = lpMemScript->GetAsNumber();

			info.BuffID = lpMemScript->GetAsNumber();

			info.Level = lpMemScript->GetAsNumber();

			info.Skill = lpMemScript->GetAsNumber();

			info.Luck = lpMemScript->GetAsNumber();

			info.Option = lpMemScript->GetAsNumber();

			info.Excellent = lpMemScript->GetAsNumber();

			info.Time = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CQuaTanThu::SetInfo(QUATANTHU_INFO info) // OK
{
	if(CHECK_RANGE(info.Class,MAX_CLASS) == 0)
	{
		return;
	}

	this->m_QuaTanThuInfo[info.Class] = info;
}

void CQuaTanThu::GiftItem(LPOBJ lpObj)
{
	if(lpObj->TheGift >= 1)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(539));
		return;
	}

	if(gItemManager.CheckItemInventorySpace(lpObj,4,4) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
		return;
	}
	lpObj->TheGift += 1;
	GDSaveTheGiftData(lpObj->Index);
	int Days = this->m_QuaTanThuInfo[lpObj->Class].Time;
	time_t t = time(NULL);
	localtime(&t);
	DWORD iTime = (DWORD)t + Days * 86400;
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(7,this->m_QuaTanThuInfo[lpObj->Class].SetID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,0,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(8,this->m_QuaTanThuInfo[lpObj->Class].SetID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,0,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(9,this->m_QuaTanThuInfo[lpObj->Class].SetID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,0,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(10,this->m_QuaTanThuInfo[lpObj->Class].SetID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,0,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(11,this->m_QuaTanThuInfo[lpObj->Class].SetID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,0,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(this->m_QuaTanThuInfo[lpObj->Class].WeaponType,this->m_QuaTanThuInfo[lpObj->Class].WeaponID),this->m_QuaTanThuInfo[lpObj->Class].Level,0,this->m_QuaTanThuInfo[lpObj->Class].Skill,this->m_QuaTanThuInfo[lpObj->Class].Luck,this->m_QuaTanThuInfo[lpObj->Class].Option,-1,this->m_QuaTanThuInfo[lpObj->Class].Excellent,0,0,0,0,0xFF,iTime);
	gEffectManager.AddEffect(lpObj,1,this->m_QuaTanThuInfo[lpObj->Class].BuffID,(int)iTime,0,0,0,0);
}
