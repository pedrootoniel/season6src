#include "stdafx.h"
#include "PartyBuffs.h"
#include "Offset.h"
#include "Object.h"
#include "Interface.h"
#include "User.h"
#include <string>
#include "NewParty.h"
#include "Defines.h"

cPartyBuffs gPartyBuffs;

cPartyBuffs::cPartyBuffs()
{
	this->m_PartyBuffsData.clear();
}

cPartyBuffs::~cPartyBuffs()
{
	
}



void cPartyBuffs::RecvPartyBuffs(PMSG_PARTY_EFFECT_LIST_SEND* lpMsg)
{
	PARTY_BUFFS_DATA info;

	memcpy(info.name,lpMsg->name,sizeof(info.name));
	info.count = lpMsg->count;

	for(int n=0;n<lpMsg->count;n++)
	{
		PMSG_PARTY_EFFECT_LIST* lpInfo = (PMSG_PARTY_EFFECT_LIST*)(((BYTE*)lpMsg)+sizeof(PMSG_PARTY_EFFECT_LIST_SEND)+(sizeof(PMSG_PARTY_EFFECT_LIST)*n));

		info.Buffs[n].effect = lpInfo->effect;
		info.Buffs[n].count = lpInfo->count;
	}

	std::string Name(lpMsg->name);

	std::map<std::string,PARTY_BUFFS_DATA>::iterator it = this->m_PartyBuffsData.find(Name);

	if(it == this->m_PartyBuffsData.end())
	{
		this->m_PartyBuffsData.insert(std::pair<std::string,PARTY_BUFFS_DATA>(Name,info));
	}
	else
	{
		it->second = info;
	}
}

PARTY_BUFFS_DATA* cPartyBuffs::GetInfoByName(char* Name)
{
	std::map<std::string,PARTY_BUFFS_DATA>::iterator it = this->m_PartyBuffsData.find(Name);

	if(it != this->m_PartyBuffsData.end())
	{
		return &it->second;
	}

	return 0;
}

void cPartyBuffs::DrawPartyBuffs()
{
#if (_NEW_PARTY_SYSTEM_ == TRUE )
	if (g_Party.PartyMemberCount == 0)
#else
	if (pPartyMemberCount == 0)
#endif
	{
		return;
	}

	float StartX = 554.0;
	float StartY = 14.0;
#if (_NEW_PARTY_SYSTEM_ == TRUE )
	for( int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++ )
#else
	for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
#endif
	{
#if (_NEW_PARTY_SYSTEM_ == TRUE )
		
		PARTY_BUFFS_DATA* info = this->GetInfoByName(g_Party.PartyData[PartySlot].Name);
#else
		PartyList PartyMember	= *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
		PARTY_BUFFS_DATA* info = this->GetInfoByName(PartyMember.Name);
#endif

		if (info == 0)
		{
			continue;
		}

		for	(int i=0;i<info->count;i++)
		{
			const float High	= 10.5; //28
			const float Whith	= 7.5; //20

			float Y = StartY+(24*PartySlot);
			float X = StartX;

			if ((i+1)%2 == 0)
			{
				Y+=High+1;
			}

			if (i/2 >=1)
			{
				X-= (Whith-1)*(i/2);
			}

			float a96 = 96.0;

			int EffectValue = (info->Buffs[i].effect - 1) % 80;
			float SourceX = (double)(EffectValue % 10) * Whith / a96;
			float SourceY = (double)(EffectValue / 10) * High / a96;
			float SourceWidth = Whith / a96;
			float SourceHeight = High / a96;
			pDrawCircle((info->Buffs[i].effect - 1) / 80 + 31725, X, Y, Whith, High, SourceX, SourceY, SourceWidth, SourceHeight, 1, 1, 0);

			/*
			 
			const float High	= 10.5; //28
			const float Whith	= 7.5; //20

			float Y = StartY+(24*PartySlot);
			float X = StartX;

			if ((i+1)%2 == 0)
			{
				Y+=High/2+1;
			}

			if (i/2 >=1)
			{
				X-= (Whith/2-1)*(i/2);
			}

			float test = GetPrivateProfileFloat("Custom", "testa", 0, "./Settings.ini");

			int EffectValue = (info->Buffs[i].effect - 1) % 80;
			float SourceX = (double)(EffectValue % 10) * Whith / test;
			float SourceY = (double)(EffectValue / 10) * High / test;
			float SourceWidth = Whith / test;
			float SourceHeight = High / test;
			pDrawCircle((info->Buffs[i].effect - 1) / 80 + 31725, X, Y, Whith, High, SourceX, SourceY, SourceWidth, SourceHeight, 1, 1, 0);
			 
			 */
		}

	}
}