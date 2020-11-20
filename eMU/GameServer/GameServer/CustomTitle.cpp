#include "StdAfx.h"
#include "user.h"
#include "CustomTitle.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "Path.h"
#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "Message.h"
#include "Notice.h"
#include "ObjectManager.h"
DanhHieu gDanhHieu;

DanhHieu::DanhHieu() // OK
{
	this->Init();
}

DanhHieu::~DanhHieu() // OK
{

}



void DanhHieu::Init()
{
	for(int n=0;n < MAX_RANK;n++)
	{
		this->m_OptionTitle[n].Index = 0;
	}
}

void DanhHieu::Load(char* path) // OK
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

					TITLE_OPTION_DATA info;

					memset(&info,0,sizeof(info));

					info.Index	=	lpMemScript->GetNumber();

					info.Price = lpMemScript->GetAsNumber();

					info.AddHP = lpMemScript->GetAsNumber();

					info.AddMP = lpMemScript->GetAsNumber();

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

void DanhHieu::SetInfo(TITLE_OPTION_DATA info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_RANK)
	{
		return;
	}

	this->m_OptionTitle[info.Index] = info;
}

void DanhHieu::GDSaveData(int aIndex)
{
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	DANHHIEU_GD_SAVE_DATA pRequest;
	pRequest.header.set(0xD9, 0x02, sizeof(pRequest));
	memcpy(pRequest.Name, lpUser->Name, 11);
	pRequest.index	= aIndex;
	pRequest.RankSlot1		= lpUser->Hornor.RankSlot1;
	pRequest.RankTitle1		= lpUser->Hornor.RankTitle[0];
	pRequest.RankTitle2		= lpUser->Hornor.RankTitle[1];
	pRequest.RankTitle3		= lpUser->Hornor.RankTitle[2];
	pRequest.RankTitle4		= lpUser->Hornor.RankTitle[3];
	pRequest.RankTitle5		= lpUser->Hornor.RankTitle[4];
	pRequest.RankTitle6		= lpUser->Hornor.RankTitle[5];
	pRequest.RankTitle7		= lpUser->Hornor.RankTitle[6];
	pRequest.RankTitle8		= lpUser->Hornor.RankTitle[7];
	pRequest.RankTitle9		= lpUser->Hornor.RankTitle[8];
	pRequest.RankTitle10		= lpUser->Hornor.RankTitle[9];
	pRequest.RankTitle11		= lpUser->Hornor.RankTitle[10];
	pRequest.RankTitle12		= lpUser->Hornor.RankTitle[11];
	pRequest.RankTitle13		= lpUser->Hornor.RankTitle[12];
	pRequest.RankTitle14		= lpUser->Hornor.RankTitle[13];
	pRequest.RankTitle15		= lpUser->Hornor.RankTitle[14];
	pRequest.RankTitle16		= lpUser->Hornor.RankTitle[15];
	pRequest.RankTitle17		= lpUser->Hornor.RankTitle[16];
	pRequest.RankTitle18		= lpUser->Hornor.RankTitle[17];
	pRequest.RankTitle19		= lpUser->Hornor.RankTitle[18];
	pRequest.RankTitle20		= lpUser->Hornor.RankTitle[19];
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.header.size);
}
// -------------------------------------------------------------------------------

void DanhHieu::GDReqData(int aIndex)
{

	LPOBJ lpObj = &gObj[aIndex];
	DANHHIEU_GD_REQ_DATA pMsg;
	pMsg.header.set(0xD9,0x01,sizeof(pMsg));
	pMsg.index = aIndex;
	memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));
	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

}
// -------------------------------------------------------------------------------


void DanhHieu::GDSaveUserInfo(int aIndex)	//-> Complete
{

	this->GDSaveData(aIndex);
}
// -------------------------------------------------------------------------------
void DanhHieu::GDReqUserInfo(int aIndex)	//-> Complete
{
	// ----
	this->GDReqData(aIndex);
}
// -------------------------------------------------------------------------------
void DanhHieu::DGGetData(DANHHIEU_DG_GET_DATA * aRecv)
{
	// ----
	LPOBJ lpUser = &gObj[aRecv->index];
	// ----
	if( aRecv->RankSlot1 < 0 )
	{
		aRecv->RankSlot1 = 0;
	}

	if( aRecv->RankTitle1 < 0 )
	{
		aRecv->RankTitle1 = 0;
	}
	else if( aRecv->RankTitle2 < 0 )
	{
		aRecv->RankTitle2 = 0;
	}
	else if( aRecv->RankTitle3 < 0 )
	{
		aRecv->RankTitle3 = 0;
	}
	else if( aRecv->RankTitle4 < 0 )
	{
		aRecv->RankTitle4 = 0;
	}
	else if( aRecv->RankTitle5 < 0 )
	{
		aRecv->RankTitle5 = 0;
	}
	else if( aRecv->RankTitle6 < 0 )
	{
		aRecv->RankTitle6 = 0;
	}
	else if( aRecv->RankTitle7 < 0 )
	{
		aRecv->RankTitle7 = 0;
	}
	else if( aRecv->RankTitle8 < 0 )
	{
		aRecv->RankTitle8 = 0;
	}
	else if( aRecv->RankTitle9 < 0 )
	{
		aRecv->RankTitle9 = 0;
	}
	else if( aRecv->RankTitle10 < 0 )
	{
		aRecv->RankTitle10 = 0;
	}
	else if( aRecv->RankTitle11 < 0 )
	{
		aRecv->RankTitle11 = 0;
	}
	else if( aRecv->RankTitle12 < 0 )
	{
		aRecv->RankTitle12 = 0;
	}
	else if( aRecv->RankTitle13 < 0 )
	{
		aRecv->RankTitle13 = 0;
	}
	else if( aRecv->RankTitle14 < 0 )
	{
		aRecv->RankTitle14 = 0;
	}
	else if( aRecv->RankTitle15 < 0 )
	{
		aRecv->RankTitle15 = 0;
	}
	else if( aRecv->RankTitle16 < 0 )
	{
		aRecv->RankTitle16 = 0;
	}
	else if( aRecv->RankTitle17 < 0 )
	{
		aRecv->RankTitle17 = 0;
	}
	else if( aRecv->RankTitle18 < 0 )
	{
		aRecv->RankTitle18 = 0;
	}
	else if( aRecv->RankTitle19 < 0 )
	{
		aRecv->RankTitle19 = 0;
	}
	else if( aRecv->RankTitle20 < 0 )
	{
		aRecv->RankTitle20 = 0;
	}
	// ----
	lpUser->Hornor.RankSlot1		= aRecv->RankSlot1;
	lpUser->Hornor.RankTitle[0]		= aRecv->RankTitle1;
	lpUser->Hornor.RankTitle[1]		= aRecv->RankTitle2;
	lpUser->Hornor.RankTitle[2]		= aRecv->RankTitle3;
	lpUser->Hornor.RankTitle[3]		= aRecv->RankTitle4;
	lpUser->Hornor.RankTitle[4]		= aRecv->RankTitle5;
	lpUser->Hornor.RankTitle[5]		= aRecv->RankTitle6;
	lpUser->Hornor.RankTitle[6]		= aRecv->RankTitle7;
	lpUser->Hornor.RankTitle[7]		= aRecv->RankTitle8;
	lpUser->Hornor.RankTitle[8]		= aRecv->RankTitle9;
	lpUser->Hornor.RankTitle[9]		= aRecv->RankTitle10;
	lpUser->Hornor.RankTitle[10]		= aRecv->RankTitle11;
	lpUser->Hornor.RankTitle[11]		= aRecv->RankTitle12;
	lpUser->Hornor.RankTitle[12]		= aRecv->RankTitle13;
	lpUser->Hornor.RankTitle[13]		= aRecv->RankTitle14;
	lpUser->Hornor.RankTitle[14]		= aRecv->RankTitle15;
	lpUser->Hornor.RankTitle[15]		= aRecv->RankTitle16;
	lpUser->Hornor.RankTitle[16]		= aRecv->RankTitle17;
	lpUser->Hornor.RankTitle[17]		= aRecv->RankTitle18;
	lpUser->Hornor.RankTitle[18]		= aRecv->RankTitle19;
	lpUser->Hornor.RankTitle[19]		= aRecv->RankTitle20;
}
// -------------------------------------------------------------------------------
void DanhHieu::ActiveTitle(LPOBJ lpUser, ACTIVE_TITLE_REQ *aRecv)
{
	char sbuff[1024]={0};
	// ----
	if (aRecv->Type == 1) //-> Slot 1
		{
			lpUser->Hornor.RankSlot1	= aRecv->Number;
			this->GDSaveUserInfo(lpUser->Index);
		}
}
// -------------------------------------------------------------------------------
void DanhHieu::Deactive(LPOBJ lpUser)
{
	lpUser->Hornor.RankSlot1 = 0;
	this->GDSaveUserInfo(lpUser->Index);
}
// -------------------------------------------------------------------------------
void DanhHieu::BuyTitle(LPOBJ lpUser, BUY_TITLE_REQ *aRecv)
{
	if(lpUser->Hornor.RankTitle[aRecv->Number] == 1)
		{return;}
	else{
			if (lpUser->WCoinCaRecv < m_OptionTitle[aRecv->Number].Price)
				{
					gNotice.GCNoticeSend(lpUser->Index,1,0,0,0,0,0,gMessage.GetMessage(494),m_OptionTitle[aRecv->Number].Price);
					return;
				}
				else
				{	
					gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,m_OptionTitle[aRecv->Number].Price,0,0);
					lpUser->Hornor.RankTitle[aRecv->Number] = 1;
					this->GDSaveUserInfo(lpUser->Index);
				}
			}
}
// -------------------------------------------------------------------------------
void DanhHieu::TitleOption(LPOBJ lpObj,bool flag)
{
	if(flag != 0)
	{
		return;
	}
		// Add HP
			lpObj->AddLife += this->m_OptionTitle[lpObj->Hornor.RankSlot1].AddHP;	
			//lpObj->AddLife += (int)((lpObj->MaxLife*m_OptionTitle[lpObj->Hornor.RankSlot1].AddHP)/100);
		// Add MP
			lpObj->AddMana += this->m_OptionTitle[lpObj->Hornor.RankSlot1].AddMP;
			//lpObj->AddMana += (int)((lpObj->MaxMana*m_OptionTitle[lpObj->Hornor.RankSlot1].AddHP)/100);
}