// Party.cpp: implementation of the CParty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Party.h"
#include "EffectManager.h"
#include "Map.h"
#include "PartyMatching.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "Util.h"
#include "Message.h"
#include "MoveSummon.h"
CParty gParty;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParty::CParty() // OK
{
	this->m_PartyCount = 0;
}

CParty::~CParty() // OK
{

}

bool CParty::IsParty(int index) // OK
{
	if(OBJECT_RANGE(index) == 0)
	{
		return 0;
	}

	if(this->m_PartyInfo[index].Count == 0)
	{
		return 0;
	}

	return 1;
}

bool CParty::IsLeader(int index,int aIndex) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	if(this->m_PartyInfo[index].Index[0] == aIndex)
	{
		return 1;
	}

	return 0;
}

bool CParty::IsMember(int index,int aIndex) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(this->m_PartyInfo[index].Index[n] == aIndex)
		{
			return 1;
		}
	}

	return 0;
}

int CParty::GetMemberCount(int index) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	return this->m_PartyInfo[index].Count;
}

int CParty::GetMemberIndex(int index,int number) // OK
{
	if(this->IsParty(index) == 0)
	{
		return -1;
	}

	if(number < 0 || number >= MAX_PARTY_USER)
	{
		return -1;
	}

	return this->m_PartyInfo[index].Index[number];
}

int CParty::GetMemberNumber(int index,int aIndex) // OK
{
	if(this->IsParty(index) == 0)
	{
		return -1;
	}

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(this->m_PartyInfo[index].Index[n] == aIndex)
		{
			return n;
		}
	}

	return -1;
}

bool CParty::Create(int aIndex) // OK
{
	if(this->IsParty(gObj[aIndex].PartyNumber) != 0)
	{
		return 0;
	}

	int count = this->m_PartyCount;

	for(int n=0;n < MAX_OBJECT;n++)
	{
		if(this->m_PartyInfo[count].Count == 0)
		{
			gObj[aIndex].PartyNumber = count;
			this->m_PartyInfo[count].Count = 1;
			this->m_PartyInfo[count].Index[0] = aIndex;
			this->m_PartyInfo[count].Index[1] = -1;
			this->m_PartyInfo[count].Index[2] = -1;
			this->m_PartyInfo[count].Index[3] = -1;
			this->m_PartyInfo[count].Index[4] = -1;
			//this->m_PartyInfo[count].Index[5] = -1;
			//this->m_PartyInfo[count].Index[6] = -1;
			this->GCPartyListSend(count);
			this->m_PartyCount = (((++this->m_PartyCount)>=MAX_OBJECT)?0:this->m_PartyCount);
			return 1;
		}
		else
		{
			count = (((++count)>=MAX_OBJECT)?0:count);
		}
	}

	return 0;
}

bool CParty::Destroy(int index) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			gObj[this->m_PartyInfo[index].Index[n]].PartyNumber = -1;
			this->GCPartyDelMemberSend(this->m_PartyInfo[index].Index[n]);
			this->m_PartyInfo[index].Count--;
			this->m_PartyInfo[index].Index[n] = -1;
		}
	}

	return 1;
}

bool CParty::AddMember(int index,int aIndex) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	if(this->GetMemberNumber(index,aIndex) != -1)
	{
		return 0;
	}

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) == 0)
		{
			gObj[aIndex].PartyNumber = index;
			this->m_PartyInfo[index].Count++;
			this->m_PartyInfo[index].Index[n] = aIndex;
			this->GCPartyListSend(index);
			return 1;
		}
	}

	return 0;
}

bool CParty::DelMember(int index,int aIndex) // OK
{
	if(this->IsParty(index) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(this->m_PartyInfo[index].Index[n] == aIndex)
		{
			gObj[aIndex].PartyNumber = -1;
			this->m_PartyInfo[index].Count--;
			this->m_PartyInfo[index].Index[n] = -1;
			this->ChangeLeader(index,n);
			this->GCPartyDelMemberSend(aIndex);
			this->GCPartyListSend(index);
			return 1;
		}
	}

	return 0;
}

void CParty::ChangeLeader(int index,int number) // OK
{
	if(this->IsParty(index) == 0 || number != 0)
	{
		return;
	}

	for(int n=1;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			this->m_PartyInfo[index].Index[0] = this->m_PartyInfo[index].Index[n];
			this->m_PartyInfo[index].Index[n] = -1;
			break;
		}
	}
}

bool CParty::SetLeader(int OldLeader, int NewLeader)
{
	LPOBJ lpObj			= &gObj[OldLeader];
	LPOBJ lpTargetObj	= &gObj[NewLeader];		
	// ----
	int PartyNumber		= lpObj->PartyNumber;
	// ----
	if( !this->IsParty(PartyNumber) )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(604));
		return false;
	}
	// ----
	if( lpObj->PartyNumber != lpTargetObj->PartyNumber )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(605));
		return false;
	}
	// ----
	if( !this->IsLeader(PartyNumber, lpObj->Index) )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(606));
		return false;
	}
	// ----
	int TempIndex = this->GetMemberNumber(PartyNumber, lpTargetObj->Index);
	// ----
	this->m_PartyInfo[PartyNumber].Index[0]					= this->m_PartyInfo[PartyNumber].Index[TempIndex];
	// ----
	this->m_PartyInfo[PartyNumber].Index[TempIndex]			= lpObj->Index;
	// ----
	char Text[100] = { 0 };
	sprintf(Text, gMessage.GetMessage(607), lpTargetObj->Name);
	// ----
	for( int i = 0; i < MAX_PARTY_USER; i++ )
	{
		int UserIndex = this->m_PartyInfo[PartyNumber].Index[i];
		// ----
		if( UserIndex >= 0 && gObj[UserIndex].Connected == 3 )
		{
			gNotice.GCNoticeSend(this->m_PartyInfo[PartyNumber].Index[i],1,0,0,0,0,0,Text);
		}
	}
	this->GCPartyListSend(PartyNumber);
	// ----
	return true;
}

void CParty::SetLeader(LPOBJ lpObj, int number)
{
	//LPOBJ lpObj			= &gObj[OldLeader];
	//
	// ----
	int PartyNumber		= lpObj->PartyNumber;
	int bIndex = this->GetMemberIndex(lpObj->PartyNumber,number);
	LPOBJ lpTargetObj	= &gObj[bIndex];		
	// ----
	if( !this->IsParty(PartyNumber) )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(604));
		return;
	}
	// ----
	if( lpObj->PartyNumber != lpTargetObj->PartyNumber )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(605));
		return;
	}
	// ----
	if( !this->IsLeader(PartyNumber, lpObj->Index) )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(606));
		return;
	}
	// ----
	int TempIndex = this->GetMemberNumber(PartyNumber, lpTargetObj->Index);
	// ----
	this->m_PartyInfo[PartyNumber].Index[0]					= this->m_PartyInfo[PartyNumber].Index[TempIndex];
	// ----
	this->m_PartyInfo[PartyNumber].Index[TempIndex]			= lpObj->Index;
	// ----
	char Text[100] = { 0 };
	sprintf(Text, gMessage.GetMessage(607), lpTargetObj->Name);
	// ----
	for( int i = 0; i < MAX_PARTY_USER; i++ )
	{
		int UserIndex = this->m_PartyInfo[PartyNumber].Index[i];
		// ----
		if( UserIndex >= 0 && gObj[UserIndex].Connected == 3 )
		{
			gNotice.GCNoticeSend(this->m_PartyInfo[PartyNumber].Index[i],1,0,0,0,0,0,Text);
		}
	}
	this->GCPartyListSend(PartyNumber);
}

void CParty::TracePlayer(LPOBJ lpObj, int number)
{
	//LPOBJ lpObj			= &gObj[OldLeader];
	//
	// ----
	int PartyNumber		= lpObj->PartyNumber;
	int bIndex = this->GetMemberIndex(lpObj->PartyNumber,number);
	LPOBJ lpTargetObj	= &gObj[bIndex];		
	// ----
	if( !this->IsParty(PartyNumber) )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(604));
		return;
	}
	// ----
	if(gMoveSummon.CheckMoveSummon(lpObj,lpTargetObj->Map,lpTargetObj->X,lpTargetObj->Y) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(272));
		return;
	}
	if((lpTargetObj->Map >= 11 && lpTargetObj->Map <= 17) || lpTargetObj->Map == 52 || (lpTargetObj->Map >= 18 && lpTargetObj->Map <= 23) || lpTargetObj->Map == 53 || lpTargetObj->Map == 9 || lpTargetObj->Map == 32 || lpTargetObj->Map == 30 || lpTargetObj->Map == 36 || (lpTargetObj->Map >= 24 && lpTargetObj->Map <= 29) || (lpTargetObj->Map >= 45 && lpTargetObj->Map <= 50) || lpTargetObj->Map == 64 || (lpTargetObj->Map >= 65 && lpTargetObj->Map <= 72))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(259));
		return;
	}
	if(lpObj->Money < gServerInfo.TracePlayerPartyZen[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(518),gServerInfo.TracePlayerPartyZen[lpObj->AccountLevel]);
		return;
	}
	lpObj->Money -= gServerInfo.TracePlayerPartyZen[lpObj->AccountLevel];
	GCMoneySend(lpObj->Index,lpObj->Money);
	gObjTeleport(lpObj->Index,lpTargetObj->Map,lpTargetObj->X,lpTargetObj->Y);
}


bool CParty::AutoAcceptPartyRequest(LPOBJ lpObj,LPOBJ lpTarget)
{
	if(this->IsParty(lpTarget->PartyNumber) == 0)
	{
		if(gObjCheckAutoParty(lpObj,lpTarget) != 0)
		{
			if(this->IsParty(lpObj->PartyNumber) == 0)
			{
				if(this->Create(lpObj->Index) == 0 || this->AddMember(lpObj->PartyNumber,lpTarget->Index) == 0)
				{
					this->GCPartyResultSend(lpObj->Index,2);
					this->GCPartyResultSend(lpTarget->Index,2);
					this->Destroy(lpObj->PartyNumber);
					return 1;
				}
				else
				{
					gPartyMatching.GDPartyMatchingJoinCancelSend(lpObj->Index,1,1);
					gPartyMatching.GDPartyMatchingJoinCancelSend(lpTarget->Index,0,1);
					gPartyMatching.GDPartyMatchingJoinCancelSend(lpTarget->Index,1,1);
					return 1;
				}
			}
			else
			{
				if(this->IsLeader(lpObj->PartyNumber,lpObj->Index) != 0 || gObjCheckAutoParty(lpTarget,&gObj[this->GetMemberIndex(lpObj->PartyNumber,0)]) != 0)
				{
					if(this->AddMember(lpObj->PartyNumber,lpTarget->Index) == 0)
					{
						this->GCPartyResultSend(lpObj->Index,2);
						this->GCPartyResultSend(lpTarget->Index,2);
						return 1;
					}
					else
					{
						gPartyMatching.GDPartyMatchingJoinCancelSend(lpTarget->Index,0,1);
						gPartyMatching.GDPartyMatchingJoinCancelSend(lpTarget->Index,1,1);
						return 1;
					}
				}
			}
		}
	}
	else
	{
		if(gObjCheckAutoParty(lpObj,&gObj[this->GetMemberIndex(lpTarget->PartyNumber,0)]) != 0)
		{
			if(this->IsParty(lpObj->PartyNumber) == 0)
			{
				if(this->AddMember(lpTarget->PartyNumber,lpObj->Index) == 0)
				{
					this->GCPartyResultSend(lpObj->Index,2);
					this->GCPartyResultSend(lpTarget->Index,2);
					return 1;
				}
				else
				{
					gPartyMatching.GDPartyMatchingJoinCancelSend(lpObj->Index,0,1);
					gPartyMatching.GDPartyMatchingJoinCancelSend(lpObj->Index,1,1);
					return 1;
				}
			}
		}
	}

	return 0;
}

void CParty::CGPartyRequestRecv(PMSG_PARTY_REQUEST_RECV* lpMsg,int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (PacketCheckTime(&gObj[aIndex]) == 0)
	{
		return;
	}

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);

	if(gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(lpObj->Interface.use != 0 || lpTarget->Interface.use != 0)
	{
		return;
	}

	if(CA_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		this->GCPartyResultSend(aIndex,0);
		return;
	}

	if(OBJECT_RANGE(lpObj->PartyTargetUser) != 0 || OBJECT_RANGE(lpTarget->PartyTargetUser) != 0)
	{
		this->GCPartyResultSend(aIndex,0);
		return;
	}

	if(gServerInfo.m_GensSystemPartyLock != 0 && lpObj->GensFamily != lpTarget->GensFamily)
	{
		this->GCPartyResultSend(aIndex,6);
		return;
	}

	int TotalLevel = 0, PartyCount = 0;
	// ----
	if( gObj[aIndex].PartyNumber >= 0 )
	{
		for( int i = 0; i < MAX_PARTY_USER; i++ )
		{
			int PartyIndex = gParty.m_PartyInfo[gObj[aIndex].PartyNumber].Index[i];
			// ----
			if( PartyIndex != -1 )
			{
				TotalLevel += gObj[PartyIndex].Level;
				PartyCount++;
			}
		}
		// ----
		TotalLevel = TotalLevel / PartyCount;
	}
	else
	{
		TotalLevel = gObj[aIndex].Level;
	}
	// ----
	if( TotalLevel > gObj[bIndex].Level && TotalLevel - gObj[bIndex].Level > gServerInfo.m_MaxPartyLevelDiff )
	{	
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(608), gObj[bIndex].Name, gObj[bIndex].Name, TotalLevel - gServerInfo.m_MaxPartyLevelDiff - gObj[bIndex].Level);
		this->GCPartyResultSend(aIndex,5);
		return;
	}
	// ----
	if( TotalLevel < gObj[bIndex].Level && gObj[bIndex].Level - TotalLevel > gServerInfo.m_MaxPartyLevelDiff )
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(609), gObj[bIndex].Name, gObj[bIndex].Level - gServerInfo.m_MaxPartyLevelDiff - TotalLevel);
		this->GCPartyResultSend(aIndex,5);
		return;
	}	

	if(this->AutoAcceptPartyRequest(lpObj,lpTarget) != 0)
	{
		return;
	}

	if(this->IsParty(lpObj->PartyNumber) != 0 && this->IsLeader(lpObj->PartyNumber,aIndex) == 0)
	{
		this->GCPartyResultSend(aIndex,0);
		return;
	}

	if((lpTarget->Option & 1) == 0)
	{
		this->GCPartyResultSend(aIndex,1);
		return;
	}

	if(this->IsParty(lpTarget->PartyNumber) != 0)
	{
		this->GCPartyResultSend(aIndex,4);
		return;
	}

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_PARTY;
	lpObj->Interface.state = 0;
	lpObj->InterfaceTime = GetTickCount();
	lpObj->TargetNumber = bIndex;
	lpObj->PartyTargetUser = bIndex;

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_PARTY;
	lpTarget->Interface.state = 0;
	lpTarget->InterfaceTime = GetTickCount();
	lpTarget->TargetNumber = aIndex;

	PMSG_PARTY_REQUEST_SEND pMsg;

	pMsg.header.set(0x40,sizeof(pMsg));

	pMsg.index[0] = SET_NUMBERHB(aIndex);
	pMsg.index[1] = SET_NUMBERLB(aIndex);

	DataSend(bIndex,(BYTE*)&pMsg,pMsg.header.size);
}

void CParty::CGPartyRequestResultRecv(PMSG_PARTY_REQUEST_RESULT_RECV* lpMsg,int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (PacketCheckTime(&gObj[aIndex]) == 0)
	{
		return;
	}

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);

	if(gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_PARTY)
	{
		return;
	}

	if(lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_PARTY)
	{
		return;
	}

	if(CA_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		this->GCPartyResultSend(aIndex,0);
		goto CLEAR_JUMP;
	}

	if(lpMsg->result == 0)
	{
		this->GCPartyResultSend(aIndex,1);
		goto CLEAR_JUMP;
	}

	if(this->Create(bIndex) == 0)
	{
		if(this->AddMember(lpTarget->PartyNumber,aIndex) == 0)
		{
			this->GCPartyResultSend(aIndex,2);
			this->GCPartyResultSend(bIndex,2);
		}
		else
		{
			gPartyMatching.GDPartyMatchingJoinCancelSend(aIndex,0,1);
			gPartyMatching.GDPartyMatchingJoinCancelSend(aIndex,1,1);
		}
	}
	else
	{
		if(this->AddMember(lpTarget->PartyNumber,aIndex) == 0)
		{
			this->GCPartyResultSend(aIndex,2);
			this->GCPartyResultSend(bIndex,2);
			this->Destroy(lpTarget->PartyNumber);
		}
		else
		{
			gPartyMatching.GDPartyMatchingJoinCancelSend(aIndex,0,1);
			gPartyMatching.GDPartyMatchingJoinCancelSend(aIndex,1,1);
			gPartyMatching.GDPartyMatchingJoinCancelSend(bIndex,1,1);
		}
	}

	CLEAR_JUMP:

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->InterfaceTime = 0;
	lpObj->TargetNumber = -1;
	lpObj->PartyTargetUser = -1;

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->InterfaceTime = 0;
	lpTarget->TargetNumber = -1;
	lpTarget->PartyTargetUser = -1;
}

void CParty::CGPartyListRecv(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (PacketCheckTime(&gObj[aIndex]) == 0)
	{
		return;
	}

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	BYTE send[256];

	PMSG_PARTY_LIST_SEND pMsg;

	pMsg.header.set(0x42,0);

	int size = sizeof(pMsg);

	pMsg.result = 0;

	pMsg.count = 0;

	if(this->IsParty(lpObj->PartyNumber) != 0)
	{
		PMSG_PARTY_LIST info;

		for(int n=0;n < MAX_PARTY_USER;n++)
		{
			if(OBJECT_RANGE(this->m_PartyInfo[lpObj->PartyNumber].Index[n]) == 0)
			{
				continue;
			}

			LPOBJ lpTarget = &gObj[this->m_PartyInfo[lpObj->PartyNumber].Index[n]];

			memcpy(info.name,lpTarget->Name,sizeof(info.name));

			info.number = n;

			info.map = lpTarget->Map;

			info.x = (BYTE)lpTarget->X;

			info.y = (BYTE)lpTarget->Y;

			info.CurLife = (DWORD)(lpTarget->Life);

			info.MaxLife = (DWORD)(lpTarget->MaxLife+lpTarget->AddLife);

			#if(GAMESERVER_UPDATE>=801)

			info.ServerCode = gServerInfo.m_ServerCode+1;

			info.CurMana = (DWORD)(lpTarget->Mana);

			info.MaxMana = (DWORD)(lpTarget->MaxMana+lpTarget->AddMana);

			#endif

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.count++;
		}

		pMsg.result = 1;
	}

	pMsg.header.size = size;

	memcpy(send,&pMsg,sizeof(pMsg));

	DataSend(aIndex,send,size);
}

void CParty::CGPartyDelMemberRecv(PMSG_PARTY_DEL_MEMBER_RECV* lpMsg,int aIndex) // OK
{
	//LogAdd(LOG_TEST,"DELETE!");
	LPOBJ lpObj = &gObj[aIndex];

	if (PacketCheckTime(&gObj[aIndex]) == 0)
	{
		return;
	}

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = this->GetMemberIndex(lpObj->PartyNumber,lpMsg->number);

	if(gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(aIndex != bIndex && this->IsLeader(lpObj->PartyNumber,aIndex) == 0)
	{
		return;
	}

	if(IT_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		return;
	}

	if(this->GetMemberCount(lpObj->PartyNumber) <= 2)
	{
		this->Destroy(lpObj->PartyNumber);
	}
	else
	{
		this->DelMember(lpObj->PartyNumber,bIndex);
	}
}

void CParty::GCPartyResultSend(int aIndex,BYTE result) // OK
{
	PMSG_PARTY_RESULT_SEND pMsg;

	pMsg.header.set(0x41,sizeof(pMsg));

	pMsg.result = result;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
}

void CParty::GCPartyListSend(int index) // OK
{
	if(this->IsParty(index) == 0)
	{
		return;
	}

	BYTE send[256];

	PMSG_PARTY_LIST_SEND pMsg;

	pMsg.header.set(0x42,0);

	int size = sizeof(pMsg);

	pMsg.result = 1;

	pMsg.count = 0;

	PMSG_PARTY_LIST info;

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[this->m_PartyInfo[index].Index[n]];

		memcpy(info.name,lpObj->Name,sizeof(info.name));

		info.number = n;

		info.map = lpObj->Map;

		info.x = (BYTE)lpObj->X;

		info.y = (BYTE)lpObj->Y;

		info.CurLife = (DWORD)(lpObj->Life);

		info.MaxLife = (DWORD)(lpObj->MaxLife+lpObj->AddLife);

		#if(GAMESERVER_UPDATE>=801)

		info.ServerCode = gServerInfo.m_ServerCode+1;

		info.CurMana = (DWORD)(lpObj->Mana);

		info.MaxMana = (DWORD)(lpObj->MaxMana+lpObj->AddMana);

		#endif

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;
	}

	pMsg.header.size = size;

	memcpy(send,&pMsg,sizeof(pMsg));

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			DataSend(this->m_PartyInfo[index].Index[n],send,size);
		}
	}

	#if(GAMESERVER_UPDATE>=803 || GAMESERVER_UPDATE == 603)

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			gEffectManager.GCPartyEffectListSend(&gObj[this->m_PartyInfo[index].Index[n]]);
		}
	}

	#endif
}

void CParty::GCPartyDelMemberSend(int aIndex) // OK
{
	PBMSG_HEAD pMsg;

	pMsg.set(0x43,sizeof(pMsg));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.size);
}

void CParty::GCPartyLifeSend(int index) // OK
{
	if(this->IsParty(index) == 0)
	{
		return;
	}

	BYTE send[256];

	PMSG_PARTY_LIFE_SEND pMsg;

	pMsg.header.set(0x44,0);

	int size = sizeof(pMsg);

	pMsg.count = 0;

	PMSG_PARTY_LIFE info;

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[this->m_PartyInfo[index].Index[n]];

		#if(GAMESERVER_UPDATE>=801)

		info.life = (BYTE)(lpObj->Life/((lpObj->MaxLife+lpObj->AddLife)/100));

		info.mana = (BYTE)(lpObj->Mana/((lpObj->MaxMana+lpObj->AddMana)/100));

		memcpy(info.name,lpObj->Name,sizeof(info.name));

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;

		#else

		info.number = ((n*16) & 0xF0) | ((BYTE)(lpObj->Life/((lpObj->MaxLife+lpObj->AddLife)/10)) & 0x0F);
		//info.number	= (n << 4) & 0xF0;
		//int	tlife = ( (BYTE)(lpObj->Life / ((lpObj->MaxLife + lpObj->AddLife )/10.0f)) ) & 0x0F;
		//info.number	|= tlife;

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;

		#endif
	}

	pMsg.header.size = size;
	
	memcpy(send,&pMsg,sizeof(pMsg));

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			DataSend(this->m_PartyInfo[index].Index[n],send,size);
		}
	}

	#if(GAMESERVER_UPDATE>=803 || GAMESERVER_UPDATE == 603)

	for(int n=0;n < MAX_PARTY_USER;n++)
	{
		if(OBJECT_RANGE(this->m_PartyInfo[index].Index[n]) != 0)
		{
			gEffectManager.GCPartyEffectListSend(&gObj[this->m_PartyInfo[index].Index[n]]);
		}
	}

	#endif
}
