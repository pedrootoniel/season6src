#include "stdafx.h"
#include "DSProtocol.h"
#include "Util.h"
#include "Message.h"
#include "User.h"
#include "Path.h"
#include "ServerInfo.h"
#include "MemScript.h"
#include "ResetReward.h"
#include "Notice.h"
#include "CashShop.h"

CCustomRankUser gCustomRankUser;

void CCustomRankUser::Load(char* path)
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

	for(int n=0;n < MAX_RANK_USER;n++)
	{
		this->m_Data[n];
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

					int index = lpMemScript->GetNumber();

					this->m_Data[index].m_iResetMin = lpMemScript->GetAsNumber();

					this->m_Data[index].m_iResetMax = lpMemScript->GetAsNumber();

					this->m_Data[index].m_Coin1 = lpMemScript->GetAsNumber();

					this->m_Data[index].m_Coin2 = lpMemScript->GetAsNumber();

					this->m_Data[index].m_Coin3 = lpMemScript->GetAsNumber();

					this->m_count++;
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

void CCustomRankUser::ResetReward(LPOBJ lpObj)
{

	if(gServerInfo.m_CustomResetRewardSwitch == 0)
	{
		return;
	}

	for(int i = 0; i < this->m_count; i++)
	{
		if(lpObj->Reset >= this->m_Data[i].m_iResetMin && lpObj->Reset <= this->m_Data[i].m_iResetMax)
		{
			//-- Reward
			gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->m_Data[i].m_Coin1,this->m_Data[i].m_Coin2,this->m_Data[i].m_Coin3);
			return;
		}
	}
	return;
}