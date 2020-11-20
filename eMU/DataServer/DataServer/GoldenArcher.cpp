#include "stdafx.h"
#include "GoldenArcher.h"
#include "QueryManager.h"
#include "SocketManager.h"

CGoldenArcher gGoldenArcher;

CGoldenArcher::CGoldenArcher()
{

}

CGoldenArcher::~CGoldenArcher()
{

}

void CGoldenArcher::GDEventChipInfo(PMSG_REQ_VIEW_EC_MN* lpMsg, int aIndex)
{
	PMSG_ANS_VIEW_EC_MN pMsg;

	pMsg.header.set(0x1B,0x00,sizeof(pMsg));

	pMsg.iINDEX = lpMsg->aIndex;
	memcpy(pMsg.szUID,lpMsg->AccountID,sizeof(pMsg.szUID));
	pMsg.szUID[10] = 0;

	if(gQueryManager.ExecQuery("SELECT EventChips, Check_Code, MuttoNumber FROM T_MU2003_EVENT WHERE AccountID='%s'",lpMsg->AccountID) == 0)
	{
		pMsg.result = 0;
	}
	else
	{
		if (gQueryManager.Fetch() != SQL_NO_DATA)
		{
			if(gQueryManager.GetAsInteger("Check_Code") != 0)
			{
				pMsg.nEVENT_CHIPS = 0;
			}
			else
			{
				pMsg.nEVENT_CHIPS = (short)gQueryManager.GetAsInteger("EventChips");
			}

			pMsg.iMUTO_NUM = gQueryManager.GetAsInteger("MuttonNumber");
			pMsg.result = TRUE;

			//gQueryManager.Close();
		}
		else
		{
			gQueryManager.Close();
			if(gQueryManager.ExecQuery("INSERT INTO T_MU2003_EVENT (AccountID) VALUES ('%s')",pMsg.szUID) == FALSE)
			{
				pMsg.result = FALSE;
			}
			else
			{
				pMsg.nEVENT_CHIPS = 0;
				pMsg.iMUTO_NUM = 0;
				pMsg.result = TRUE;
			}
		}
	}

	gQueryManager.Close();
	gSocketManager.DataSend(aIndex,(BYTE*)&pMsg,sizeof(pMsg));
}

void CGoldenArcher::GDRegEventChips(PMSG_REQ_REGISTER_EVENTCHIP * lpMsg, int aIndex)
{
	PMSG_ANS_REGISTER_EVENTCHIP pMsg = {0};

	pMsg.header.set(0x1B,0x01,sizeof(pMsg));

	pMsg.iINDEX = lpMsg->iINDEX;
	pMsg.Pos = lpMsg->Pos;

	memcpy(pMsg.szUID,lpMsg->szUID,sizeof(pMsg.szUID));
	pMsg.szUID[10] = 0x00;
	pMsg.bSUCCESS = FALSE;

	if(gQueryManager.ExecQuery("UPDATE T_MU2003_EVENT SET EventChips = EventChips + 1 WHERE AccountID = '%s'", lpMsg->szUID))
	{
		gQueryManager.Fetch();
		gQueryManager.Close();

		if(gQueryManager.ExecQuery("SELECT EventChips FROM T_MU2003_EVENT WHERE AccountID='%s'", lpMsg->szUID))
		{
			if(gQueryManager.Fetch() != SQL_NO_DATA)
			{
				pMsg.nEVENT_CHIPS = gQueryManager.GetAsInteger("EventChips");

				if(pMsg.nEVENT_CHIPS == -1)
				{
					pMsg.nEVENT_CHIPS = -1;
				}

				pMsg.bSUCCESS = TRUE;
			}
		}
	}

	gQueryManager.Close();

	gSocketManager.DataSend(aIndex,(BYTE*)&pMsg,sizeof(pMsg));
}

void CGoldenArcher::GDResetEventChip(PMSG_REQ_RESET_EVENTCHIP * lpMsg, int aIndex)
{
	PMSG_ANS_RESET_EVENTCHIP pMsg = { 0 };

	pMsg.header.set(0x1B,0x02,sizeof(pMsg));

	pMsg.iINDEX = lpMsg->iINDEX;
	memcpy(pMsg.szUID,lpMsg->szUID,sizeof(pMsg.szUID));
	pMsg.szUID[10] = 0;
	
	if (gQueryManager.ExecQuery("UPDATE T_MU2003_EVENT SET EventChips = 0 WHERE AccountID = '%s'", lpMsg->szUID))
	{
		pMsg.bSUCCESS = TRUE;
	}
	else
	{
		pMsg.bSUCCESS = FALSE;
	}

	gQueryManager.Close();

	gSocketManager.DataSend(aIndex,(BYTE*)&pMsg,sizeof(pMsg));
}