#include "StdAfx.h"
#include "Ranking.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "user.h"
#include "protocol.h"
#include "Util.h"
#include "Log.h"
cRanking gRanking;

void cRanking::SendDS()
{
	BYTE send[4096];
	GDTop pMsg;
	pMsg.h.set(0xD9, 0x17, 0);
	int size = sizeof(pMsg);
	pMsg.Result = 1;
	pMsg.h.size[0] = SET_NUMBERHB(size);
	pMsg.h.size[1] = SET_NUMBERLB(size);
	memcpy(send,&pMsg,sizeof(pMsg));
	gDataServerConnection.DataSend(send,size);
}

void cRanking::RecvDS(DGCharTop *Recv)
{
	for(int i=0;i<MAXTOP;i++)
	{
		strncpy(this->RankingChar[i].Name,Recv->tp[i].Name,11);
		this->RankingChar[i].Class = Recv->tp[i].Class;
		this->RankingChar[i].level = Recv->tp[i].level;
		this->RankingChar[i].Reset = Recv->tp[i].Reset;
		this->RankingChar[i].Map = Recv->tp[i].Map;
		strncpy(this->RankingChar[i].Guild,Recv->tp[i].Guild,9);
		//LogAdd(LOG_BLUE,"%s %d %d %d %d %s",RankingChar[i].Name,RankingChar[i].Class,RankingChar[i].level,RankingChar[i].Reset,RankingChar[i].Map,RankingChar[i].Guild);
	}
}
void cRanking::SendUser(LPOBJ lpObj)
{
		DGCharTop2	sClient;
		//ZeroMemory(&sClient,sizeof(sClient));
		sClient.h.set(0xFE,sizeof(sClient));
		for(int i=0;i<MAXTOP;i++)
		{
			strncpy(sClient.tp[i].Name,this->RankingChar[i].Name,11);
			sClient.tp[i].Class = this->RankingChar[i].Class;
			sClient.tp[i].level = this->RankingChar[i].level;
			sClient.tp[i].Reset = this->RankingChar[i].Reset;
			sClient.tp[i].Map = this->RankingChar[i].Map;
			strncpy(sClient.tp[i].Guild,this->RankingChar[i].Guild,9);
		}
		DataSend(lpObj->Index,(BYTE*)&sClient,sizeof(sClient));
}
