#include "stdafx.h"
#include "Protocol.h"
#include "Common.h"
#include "HealthBar.h"
#include "Offset.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Reconnect.h"
#include "Interface.h"
#include "post_item.h"
#include "User.h"
#include "Import.h"
#include "PetProtocol.h"
#include "Util.h"
#include "DanhHieu.h"
#include "post_item.h"
#include "Smithy.h"
#include "PartySearch.h"
#include "PartySearchSettings.h"
#include "InfoLog.h"
#include "BuffIcon.h"
#include "PartyBuffs.h"
#include "HWID.h"
#include "CharacterList.h"
#include "ChangeClass.h"
#include "BuyVip.h"
#include "UserPanel.h"
#include "ShopSearch.h"
#include "Ranking.h"
#include "NewsBoard.h"
#include "LuckySpin.h"
#include "EventTimer.h"
#include "Minimap.h"
BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key) // OK
{
	BYTE ProtocolType = lpMsg[0];
	//g_Console.AddMessage(3, "%x size (%d)", head, size);
	if (ProtocolType == 0xC1)
	{
		switch(head)
		{
			case 0x11:
				GCDamageRecv((PMSG_DAMAGE_RECV*)lpMsg);
				break;
			case 0x16:
				GCMonsterDieRecv((PMSG_MONSTER_DIE_RECV*)lpMsg);
				break;
			case 0x17:
				GCUserDieRecv((PMSG_USER_DIE_RECV*)lpMsg);
				break;
			case 0x26:
				GCLifeRecv((PMSG_LIFE_RECV*)lpMsg);
				break;
			case 0x27:
				GCManaRecv((PMSG_MANA_RECV*)lpMsg);
				break;
			case 0x2C:
				GCFruitResultRecv((PMSG_FRUIT_RESULT_RECV*)lpMsg);
				break;
			case 0x78:
				RecvPostItem((PMSG_POSTITEM*)lpMsg);
				break;
			case 0x9C:
				GCRewardExperienceRecv((PMSG_REWARD_EXPERIENCE_RECV*)lpMsg);
				break;
			case 0xA3:
				GCQuestRewardRecv((PMSG_QUEST_REWARD_RECV*)lpMsg);
				break;
			case 0xB1:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
					case 0x00:
						GCMapServerMoveRecv((PMSG_MAP_SERVER_MOVE_RECV*)lpMsg);
						break;
					case 0x01:
						GCMapServerMoveAuthRecv((PMSG_MAP_SERVER_MOVE_AUTH_RECV*)lpMsg);
						break;
				}
				break;
			case 0x2D:
				g_BuffIcon.Recv((PMSG_SEND_BUFF_ICON*)lpMsg);
				break;
			case 0x2E:
				gPartyBuffs.RecvPartyBuffs((PMSG_PARTY_EFFECT_LIST_SEND*)lpMsg);
				break;
			case 0xF1:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
					case 0x00:
						GCConnectClientRecv((PMSG_CONNECT_CLIENT_RECV*)lpMsg);
						break;
					case 0x01:
						GCConnectAccountRecv((PMSG_CONNECT_ACCOUNT_RECV*)lpMsg);
						break;
					case 0x02:
						GCCloseClientRecv((PMSG_CLOSE_CLIENT_RECV*)lpMsg);
						break;
				}
				break;
			case 0xF3:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
					case 0x00:
						GCCharacterListRecv((PMSG_CHARACTER_LIST_RECV*)lpMsg);
						g_BuffIcon.DeleteAllBuff();
						break;
					case 0x03:
						GCCharacterInfoRecv((PMSG_CHARACTER_INFO_RECV*)lpMsg);
						break;
					case 0x04:
						GCCharacterRegenRecv((PMSG_CHARACTER_REGEN_RECV*)lpMsg);
						break;
					case 0x05:
						GCLevelUpRecv((PMSG_LEVEL_UP_RECV*)lpMsg);
						break;
					case 0x06:
						GCLevelUpPointRecv((PMSG_LEVEL_UP_POINT_RECV*)lpMsg);
						break;
					case 0x07:
						GCMonsterDamageRecv((PMSG_MONSTER_DAMAGE_RECV*)lpMsg);
						break;
					case 0x50:
						GCMasterInfoRecv((PMSG_MASTER_INFO_RECV*)lpMsg);
						break;
					case 0x51:
						GCMasterLevelUpRecv((PMSG_MASTER_LEVEL_UP_RECV*)lpMsg);
						break;
					case 0xE0:
						GCNewCharacterInfoRecv((PMSG_NEW_CHARACTER_INFO_RECV*)lpMsg);
						break;
					case 0xE1:
						GCNewCharacterCalcRecv((PMSG_NEW_CHARACTER_CALC_RECV*)lpMsg);
						break;			
					case 0xE2:
						GCNewHealthBarRecv((PMSG_NEW_HEALTH_BAR_RECV*)lpMsg);
						//gHPBar.SetTargetData((PMSG_TARGETDATA_ANS*)lpMsg);
						break;
					case 0xE3:
						GCNewGensBattleInfoRecv((PMSG_NEW_GENS_BATTLE_INFO_RECV*)lpMsg);
						break;
					case 0xE4:
						GCNewMessageRecv((PMSG_NEW_MESSAGE_RECV*)lpMsg);
						break;
					case 0xF0:
						GCPartyListRecv((PMSG_RECV_PARTYLIST*)lpMsg);
						break;	
					case 0xF1:
						GCPetCharSetRecv((PMSG_NEW_PET_CHARSET_RECV*)lpMsg);
						break;
					case 0xF2:
						GCPetCharSetSelectCharacterRecv((PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV*)lpMsg);
						break;
					case 0xF3:
						GCSmithyAncRecv((PMSG_SMITHY_ANCIENT_RECV*)lpMsg);
						break;
					case 0xF4:
						GCSmithySocketRecv((PMSG_SMITHY_SOCKET_RECV*)lpMsg);
						break;
					case 0xF5:
						gInterface.AccountSecurityState();
						break;
					case 0xF6:
						gCharacterList.SetList((PMSG_CHARACTER_INFO_DATA*)lpMsg);
						break;
					case 0xF8:
						gEventTimer.RecvEventTimer((PMSG_SEND_EVENTTIMER*)lpMsg);
						break;
					case 0xF9:
						gMiniMap.RecvPartyInfo((MINIMAP_PARTY_INFO_RECV*)lpMsg);
						break;
				}
				break;
			case 0xFF:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
					case 0x00:
						gOfflineMode.GCOfflineModeRecv((PMSG_OFFLINEMODE_REQ*)lpMsg);
					break;
				}
				break;
			case 0xFB:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
				case 0x01:
					GCAccountSecurityRecv((PMSG_ACCOUNT_SECURITY_RECV*)lpMsg);
					break;
				case 0x06:
					GCBalanceRecv((PMSG_BALANCE_UPDATE_RECV*)lpMsg);
					break;
				case 0x08:
					gChangeClass.RecvData((PMSG_CHANGECLASS_DATA*)lpMsg);
					break;
				case 0x09:
					gBuyVip.RecvData((PMSG_BUYAL_DATA*)lpMsg);
					break;
				case 0x10:
					RecvServerTime((PMSG_SERVERTIME_RECV*)lpMsg);
					break;
				case 0x11:
					GCSetCharacterPage((PMSG_CHARACTERPAGE_RECV*)lpMsg);
					break;
				case 0x12:
					gPartySearchSettings.GCPartySettingsRecv((PMSG_PARTYSETTINGS_RECV*)lpMsg);
					break;
				case 0x13:
					g_BuffIcon.GC_BuffInfo((PMSG_SEND_BUFF_ICON_EX*)lpMsg);
					break;
				case 0x15:
					gDanhHieu.GetInfo((PMSG_HORNOR_UPD*)lpMsg);
					break;
				case 0x16:
					HeadsTailsData((HEADSTAILS_UPDATEINFO*)lpMsg);
					break;
				case 0x17:
					RolltheDiceData((DICE_UPDATEINFO*)lpMsg);
					break;
				case 0x18:
					LuckyNumberData((LUCKYNUMBER_UPDATEINFO*)lpMsg);
					break;
				case 0x19:
					//gSmithItem.GetInfo((SDHP_SENDSVSHOP*)lpMsg);
					break;
				case 0x20:
					ExtraCpanelGetInfo((EXTRA_CPANEL_SENDINFO*)lpMsg);
					break;
				case 0x21:
					GCJewelsBankRecv((PMSG_BANKEX_UPDATE_RECV*)lpMsg);
					break;
				case 0x22:
					UpdateRPSMode();
					break;
				case 0x23:
					GCFruitRecv((PMSG_FRUIT_UPDATE_RECV*)lpMsg);
					break;
				case 0x24:
					UpdatePShop((PSSHOP_INTERFACE*)lpMsg);
					break;
				case 0x25:
					gLuckySpin.LuckySpinData((GC_LuckySpinUpdateData*)lpMsg);
					break;
				case 0x26:
					LuckySpinRoll();
					break;
				case 0x27:
					OpenCustomWare();
					break;
					//LTP TEAM
				case 0x30:
					gSmithy.GCSettingsRecv((GC_SmithySettings*)lpMsg);
					break;
				case 0x31:
					gSmithy.GCItemInit((GC_SmithyInit*)lpMsg);
					break;
				case 0x32:
					gSmithy.GCItemSend((GC_SmithyDATA*)lpMsg);
					break;
				case 0x33:
					gLuckySpin.GCItemSend((GC_LuckySpin_Data*)lpMsg);
					break;
				case 0x34:
					gLuckySpin.GCLuckySpinInit((GC_LuckySpinInit*)lpMsg);
					break;
				}
				break;
			}		
	}
	else if (ProtocolType == 0xC2)
	{
		switch(head)
		{
			case 0xF3:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{	
					case 0xF0:
						GCPartyListRecv((PMSG_RECV_PARTYLIST*)lpMsg);
						break;	
					case 0xF1:
						GCPetCharSetRecv((PMSG_NEW_PET_CHARSET_RECV*)lpMsg);
						break;
					case 0xF2:
						GCPetCharSetSelectCharacterRecv((PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV*)lpMsg);
						break;
					case 0xF6:
						gCharacterList.SetList((PMSG_CHARACTER_INFO_DATA*)lpMsg);
						break;
					case 0xF8:
						gEventTimer.RecvEventTimer((PMSG_SEND_EVENTTIMER*)lpMsg);
						break;
					case 0xE2:
						GCNewHealthBarRecv((PMSG_NEW_HEALTH_BAR_RECV*)lpMsg);
						//gHPBar.SetTargetData((PMSG_TARGETDATA_ANS*)lpMsg);
						break;
					case 0xF9:
						gMiniMap.RecvPartyInfo((MINIMAP_PARTY_INFO_RECV*)lpMsg);
						break;
				}
				break;
			case 0xFA:
				switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
				{
					case 0x09:
						g_PersonalShopEx.GC_Recv(lpMsg);
						break;
				}
				break;
			case 0xFE:
				gRanking.RecvInfo((DGCharTop*)lpMsg);
				break;
			case 0xFD:
				gNewsBoard.OpenMain((NEWS_ANS_TITLES*)lpMsg);
				break;
			case 0xFF:
				gNewsBoard.OpenItem((NEWS_ANS_NEWS*)lpMsg);
				break;
		}
	}
	return ProtocolCore(head,lpMsg,size,key);
}

void GCPetCharSetSelectCharacterRecv(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSetSelectCharacter();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_NEW_CHARACTER_CHARSET_RECV* lpInfo = (PMSG_NEW_CHARACTER_CHARSET_RECV*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV) + (sizeof(PMSG_NEW_CHARACTER_CHARSET_RECV)*n));

		InsertNewPetCharSetSelectCharacter( lpInfo->Name, lpInfo->PetCharSet);
	}
}

void GCPetCharSetRecv(PMSG_NEW_PET_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSet();

	for (int n = 0; n < lpMsg->count; n++)
	{
		NEW_PET_STRUCT* lpInfo = (NEW_PET_STRUCT*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_PET_CHARSET_RECV) + (sizeof(NEW_PET_STRUCT)*n));

		InsertNewPetCharSet(lpInfo->index, lpInfo->PetCharSet);
	}
}

void GCEventStatusRecv(PMSG_ARENA_STATUS_RECV* lpMsg)
{
	gObjUser.IsArenaEvent = lpMsg->result;
}

void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = lpMsg->ViewCurHP;
		ViewCurSD = lpMsg->ViewCurSD;
	}

	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;

	if((lpMsg->type & 0x10) != 0)
	{
		if(ViewDamageCount < 3)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}

	if((lpMsg->type & 0x20) != 0)
	{
		if(ViewDamageCount < 4)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}
}

void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = 0;
	}
}

void GCLifeRecv(PMSG_LIFE_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxHP = lpMsg->ViewHP;
		ViewMaxSD = lpMsg->ViewSD;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurHP = ((ViewCurHP==0)?ViewCurHP:lpMsg->ViewHP);
		ViewCurSD = lpMsg->ViewSD;
	}
}

void GCManaRecv(PMSG_MANA_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxMP = lpMsg->ViewMP;
		ViewMaxBP = lpMsg->ViewBP;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurMP = lpMsg->ViewMP;
		ViewCurBP = lpMsg->ViewBP;
	}
}

void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg) // OK
{
	if(lpMsg->result == 0 || lpMsg->result == 3 || lpMsg->result == 6 || lpMsg->result == 17)
	{
		ViewValue = lpMsg->ViewValue;
		ViewPoint = lpMsg->ViewPoint;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewPoint = lpMsg->ViewPoint;
	}
}

void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMove(lpMsg->IpAddress,lpMsg->ServerPort);
}

void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMoveAuth(lpMsg->result);
}

void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg) // OK
{
	gHwid.SendHwid();
	ViewIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);
}

void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg) // OK
{
	ReconnectOnConnectAccount(lpMsg->result);
}

void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg) // OK
{
	ReconnectOnCloseClient(lpMsg->result);
}

void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg) // OK
{
	ReconnectOnCharacterList();
}

void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg) // OK
{
	ReconnectOnCharacterInfo();

	ViewReset = lpMsg->ViewReset;
	ViewAccountLevel = lpMsg->ViewAccountLevel;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;

	*(WORD*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x07E) = 0;

	*(BYTE*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x30C) = 0;

	switch(((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7))
	{
		case 0:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DWMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 1:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DKMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 2:
			SetByte(0x00556C38,((gProtect.m_MainInfo.FEMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 3:
			SetByte(0x00556C38,((gProtect.m_MainInfo.MGMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 4:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DLMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 5:
			SetByte(0x00556C38,((gProtect.m_MainInfo.SUMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 6:
			SetByte(0x00556C38,((gProtect.m_MainInfo.RFMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
	}
	CGSendFilesCrc();
}

void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewCurSD = lpMsg->ViewCurSD;
}

void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewPoint = lpMsg->ViewPoint;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewExperience = lpMsg->ViewExperience;
	ViewNextExperience = lpMsg->ViewNextExperience;
}

void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg) // OK
{
	if(lpMsg->result >= 16 && lpMsg->result <= 20)
	{
		ViewPoint = lpMsg->ViewPoint;
		ViewMaxHP = lpMsg->ViewMaxHP;
		ViewMaxMP = lpMsg->ViewMaxMP;
		ViewMaxBP = lpMsg->ViewMaxBP;
		ViewMaxSD = lpMsg->ViewMaxSD;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;
}

void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
}

void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMasterExperience = lpMsg->ViewMasterExperience;
	ViewMasterNextExperience = lpMsg->ViewMasterNextExperience;
}

void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg) // OK
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E) = lpMsg->Level;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x74) = lpMsg->LevelUpPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = lpMsg->Strength;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = lpMsg->Dexterity;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = lpMsg->Vitality;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = lpMsg->Energy;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = lpMsg->Leadership;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x22) = lpMsg->Life;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x26) = lpMsg->MaxLife;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x24) = lpMsg->Mana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x28) = lpMsg->MaxMana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x40) = lpMsg->BP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x42) = lpMsg->MaxBP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2A) = lpMsg->Shield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2C) = lpMsg->MaxShield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4C) = lpMsg->FruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4E) = lpMsg->MaxFruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x50) = lpMsg->FruitSubPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x52) = lpMsg->MaxFruitSubPoint;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = lpMsg->Experience;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14) = lpMsg->NextExperience;

	//EXTRA
	ViewReset = lpMsg->ViewReset;
	ViewAccountLevel = lpMsg->ViewAccountLevel;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;
}

void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewAddStrength = lpMsg->ViewAddStrength;
	ViewAddDexterity = lpMsg->ViewAddDexterity;
	ViewAddVitality = lpMsg->ViewAddVitality;
	ViewAddEnergy = lpMsg->ViewAddEnergy;
	ViewAddLeadership = lpMsg->ViewAddLeadership;
	ViewPhysiDamageMin = lpMsg->ViewPhysiDamageMin;
	ViewPhysiDamageMax = lpMsg->ViewPhysiDamageMax;
	ViewMagicDamageMin = lpMsg->ViewMagicDamageMin;
	ViewMagicDamageMax = lpMsg->ViewMagicDamageMax;
	ViewCurseDamageMin = lpMsg->ViewCurseDamageMin;
	ViewCurseDamageMax = lpMsg->ViewCurseDamageMax;
	ViewMulPhysiDamage = lpMsg->ViewMulPhysiDamage;
	ViewDivPhysiDamage = lpMsg->ViewDivPhysiDamage;
	ViewMulMagicDamage = lpMsg->ViewMulMagicDamage;
	ViewDivMagicDamage = lpMsg->ViewDivMagicDamage;
	ViewMulCurseDamage = lpMsg->ViewMulCurseDamage;
	ViewDivCurseDamage = lpMsg->ViewDivCurseDamage;
	ViewMagicDamageRate = lpMsg->ViewMagicDamageRate;
	ViewCurseDamageRate = lpMsg->ViewCurseDamageRate;
	ViewPhysiSpeed = lpMsg->ViewPhysiSpeed;
	ViewMagicSpeed = lpMsg->ViewMagicSpeed;
	ViewAttackSuccessRate = lpMsg->ViewAttackSuccessRate;
	ViewAttackSuccessRatePvP = lpMsg->ViewAttackSuccessRatePvP;
	ViewDefense = lpMsg->ViewDefense;
	ViewDefenseSuccessRate = lpMsg->ViewDefenseSuccessRate;
	ViewDefenseSuccessRatePvP = lpMsg->ViewDefenseSuccessRatePvP;
	ViewDamageMultiplier = lpMsg->ViewDamageMultiplier;
	ViewRFDamageMultiplierA = lpMsg->ViewRFDamageMultiplierA;
	ViewRFDamageMultiplierB = lpMsg->ViewRFDamageMultiplierB;
	ViewRFDamageMultiplierC = lpMsg->ViewRFDamageMultiplierC;
	ViewDarkSpiritAttackDamageMin = lpMsg->ViewDarkSpiritAttackDamageMin;
	ViewDarkSpiritAttackDamageMax = lpMsg->ViewDarkSpiritAttackDamageMax;
	ViewDarkSpiritAttackSpeed = lpMsg->ViewDarkSpiritAttackSpeed;
	ViewDarkSpiritAttackSuccessRate = lpMsg->ViewDarkSpiritAttackSuccessRate;
}

void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg) // OK
{
	gHPBar.ClearNewHealthBar();

	for(int n=0;n < lpMsg->count;n++)
	{
		PMSG_NEW_HEALTH_RECV* lpInfo = (PMSG_NEW_HEALTH_RECV*)(((BYTE*)lpMsg)+sizeof(PMSG_NEW_HEALTH_BAR_RECV)+(sizeof(PMSG_NEW_HEALTH_RECV)*n));

		gHPBar.InsertNewHealthBar(lpInfo);
	}
}

void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg) // OK
{
	GensBattleMapCount = lpMsg->GensBattleMapCount;

	GensMoveIndexCount = lpMsg->GensMoveIndexCount;

	memcpy(GensBattleMap,lpMsg->GensBattleMap,sizeof(GensBattleMap));

	memcpy(GensMoveIndex,lpMsg->GensMoveIndex,sizeof(GensMoveIndex));
}

void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg) // OK
{

}

void StartRoll(int Type, int Number, float Money)
{
	ROLL_DICE_REQ pMsg;
	pMsg.header.set(0x79, sizeof(pMsg));
	pMsg.Type = Type;
	pMsg.Number = Number;
	pMsg.Money = Money;
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
void StartFlip(int Type, float Money)
{
	PMSG_HEADSTAILS_SEND pMsg;
	pMsg.header.set(0xFB, 0x06, sizeof(pMsg));
	pMsg.Type = Type;
	pMsg.Money = Money;
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
void StartLucky(int Lines)
{
	PMSG_HEADSTAILS_SEND pMsg;
	pMsg.header.set(0xFB, 0x07, sizeof(pMsg));
	pMsg.Type = Lines;
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
void RolltheDiceData(DICE_UPDATEINFO * aRecv)
{
	gInterface.Dice1 = aRecv->Dice1;
	gInterface.Dice2 = aRecv->Dice2;
	gInterface.TotalPoint = aRecv->TotalPoint;
	gInterface.LastProfit = aRecv->LastProfit;
	gInterface.Balance = aRecv->WCoinC;
	gInterface.Winner	=	aRecv->Winner;
}
void HeadsTailsData(HEADSTAILS_UPDATEINFO * aRecv)
{
	gInterface.HeadsTailsWiner = aRecv->Winer;
	gInterface.HeadsTailsProfit = aRecv->WinerPrice;
	gInterface.Balance = aRecv->WCoinC;
	//gInterface.HeadsTailsLastGame = aRecv->HeadsTails;
}
void LuckyNumberData(LUCKYNUMBER_UPDATEINFO * aRecv)
{
	gInterface.LuckyNumber = aRecv->LuckyNumber;
	gInterface.LuckyWinPrice = aRecv->WinnerPrice;
	gInterface.LuckyNumber1[0] = aRecv->Number[0];
	gInterface.LuckyNumber1[1] = aRecv->Number[1];
	gInterface.LuckyNumber1[2] = aRecv->Number[2];
	gInterface.LuckyNumber1[3] = aRecv->Number[3];
	gInterface.LuckyNumber1[4] = aRecv->Number[4];
	gInterface.LuckyTicketID = aRecv->TicketID;
}

bool RecvPostItem(PMSG_POSTITEM * lpMsg) {
    void * item_post = PostItem::AddItem ( &lpMsg->item_data[0] );

    if ( item_post == nullptr ) { return false; }

    char Name[11] = { '\0' };
    char Messase[61] = { '\0' };
    char Messase_API[70] = { '\0' };
    memcpy_s ( &Name[0], 10, &lpMsg->chatid[0], 10 );
    memcpy_s ( &Messase[0], 60, &lpMsg->chatmsg[0], 60 );
    int len = strlen ( Messase );
    // ----
    // Cat text Excillent

    if ( ( BYTE ) Messase[0] == 0xC4 &&
            ( BYTE ) Messase[1] == 0x90 &&
            ( BYTE ) Messase[2] == 0xE1 &&
            ( BYTE ) Messase[3] == 0xBB &&
            ( BYTE ) Messase[4] == 0x93 &&
            ( BYTE ) Messase[5] == 0x20 &&
            ( BYTE ) Messase[6] == 0x68 &&
            ( BYTE ) Messase[7] == 0x6F &&
            ( BYTE ) Messase[8] == 0xC3 &&
            ( BYTE ) Messase[9] == 0xA0 &&
            ( BYTE ) Messase[10] == 0x6E &&
            ( BYTE ) Messase[11] == 0x20 &&
            ( BYTE ) Messase[12] == 0x68 &&
            ( BYTE ) Messase[13] == 0xE1 &&
            ( BYTE ) Messase[14] == 0xBA &&
            ( BYTE ) Messase[15] == 0xA3 &&
            ( BYTE ) Messase[16] == 0x6F &&
            ( BYTE ) Messase[17] == 0x20 ) {
        strcpy_s ( &Messase[0], 61, &Messase[18] );
    }

    // ----
    // Cat bot ten neu qua dai
    if ( len > 35 ) {
        for ( int i = 30; i < len; ++i ) {
            if ( isalpha ( Messase[i] ) || Messase[i] == ' ' ) {
                Messase[i] = '.';
                Messase[i + 1] = '.';
                Messase[i + 2] = '.';
                Messase[i + 3] = '\0';
            }
        }
    }
	sprintf_s( Messase_API, "%s %s_[%08X]",gCustomMessage.GetMessage(257), Messase, (DWORD)item_post);
	gInfoLog.Output(LOG_POSTITEM,"[%s] %s",Name,Messase);
    gPostItem.draw_character_head_chat_text_ = true;
    Interface::DrawChat ( gPostItem.PostItemColor, &Name[0], &Messase_API[0] );
    // ----

    if ( !gPostItem.draw_character_head_chat_text_ ) { // da lay duoc base_address
        // xu ly doan chat tren dau nhan vat
        char message[256] = { 0 };
        char * chat_text_first = CharacterHeadChatTextFirst ( gPostItem.draw_character_head_chat_text_base_address_ );
        char * chat_text_last = CharacterHeadChatTextLast ( gPostItem.draw_character_head_chat_text_base_address_ );
        unsigned long msgfirst_len = strlen ( chat_text_first );
        unsigned long msglast_len = strlen ( chat_text_last );
        strcpy_s ( message, sizeof ( message ), chat_text_first );
        strcat_s ( message, chat_text_last );
        unsigned long message_len = strlen ( message );

        if ( message[message_len - 1 - 8 - 2] != '_' ||
                message[message_len - 1 - 8 - 1] != '[' ||
                message[message_len - 1] != ']' ) {
        }
        else {
            message[message_len - 1 - 8 - 2] = '\0';  // cat bo doan duoi

            // copy lai
            if ( msgfirst_len ) {
                memcpy_s ( chat_text_first, 0x50, message, msgfirst_len );
                chat_text_first[msgfirst_len] = '\0';
            }

            if ( msglast_len ) {
                memcpy_s ( chat_text_last, 0x50, &message[msgfirst_len], msglast_len );
                chat_text_last[msglast_len] = '\0';
            }
        }
    }

    return true;
}

void GCPartyListRecv(PMSG_RECV_PARTYLIST* lpMsg)
{
	gPartySearch.ClearPartyList();

	for (int n=0;n<lpMsg->Count;n++)
	{
		PMSG_PARTYSEARCH_PARTYLIST* lpInfo = (PMSG_PARTYSEARCH_PARTYLIST*)(((BYTE*)lpMsg)+sizeof(PMSG_RECV_PARTYLIST)+(sizeof(PMSG_PARTYSEARCH_PARTYLIST)*n));

		gPartySearch.InsertPartyList(lpInfo);
	}

	gInterface.SwitchPartySearchWindowState();
}

void GCSmithyAncRecv(PMSG_SMITHY_ANCIENT_RECV* lpMsg)
{
	//g_Console.AddMessage(5,"RecvAnc");
	gSmithy.ClearAncientList();

	for (int n=0;n<lpMsg->count;n++)
	{
		PMSG_SMITHY_ANCIENT* lpInfo = (PMSG_SMITHY_ANCIENT*)(((BYTE*)lpMsg)+sizeof(PMSG_SMITHY_ANCIENT_RECV)+(sizeof(PMSG_SMITHY_ANCIENT)*n));

		gSmithy.GCAncientRecv(lpInfo->index,lpInfo->options);
	}
}

void GCSmithySocketRecv(PMSG_SMITHY_SOCKET_RECV* lpMsg)
{
	gSmithy.ClearSocketList();

	for (int n=0;n<lpMsg->count;n++)
	{
		PMSG_SMITHY_SOCKET* lpInfo = (PMSG_SMITHY_SOCKET*)(((BYTE*)lpMsg)+sizeof(PMSG_SMITHY_SOCKET_RECV)+(sizeof(PMSG_SMITHY_SOCKET)*n));

		gSmithy.GCSocketRecv(lpInfo->index);
	}
}

void CGSendStatsAdd(PMSG_UPDATE_STATS_SEND pMsg)
{
	pMsg.header.set(0xFF,0x0C,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CGSendResetStats(int type)
{
	PMSG_RESET_STATS_SEND pMsg;
	pMsg.header.set(0xFF,0x0F,sizeof(pMsg));
	pMsg.Type = type;
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void ExtraCpanelGetInfo(EXTRA_CPANEL_SENDINFO * lpMsg)
{
	gInterface.m_SettingButton		=	lpMsg->Settings;
	gInterface.m_RolltheDiceButton	=	lpMsg->RolltheDice;
	gInterface.m_HeadsTailsButton	=	lpMsg->HeadsTails;
	gInterface.m_LuckyNumberButton	=	lpMsg->LuckyNumber;
	gInterface.m_SmithItemButton	=	lpMsg->SmithItem;
	gInterface.m_TitleManagerButton	=	lpMsg->TitleManager;
	gInterface.m_PartySearchSettingButton	=	lpMsg->PartySearchSetting;
	gInterface.m_OffAttackButton	=	lpMsg->OffAttack;
	gInterface.m_BuyVipButton		=	lpMsg->BuyVip;
	gInterface.m_ChangeClassButton	=	lpMsg->ChangeClass;
	gInterface.m_ResetPointCheckBox	=	lpMsg->ResetPoint;
	gInterface.m_ResetPointCheckBox1	=	lpMsg->ResetPoint2;
	gInterface.m_ResetMasterSkillCheckBox	=	lpMsg->ResetMasterSkill;
	gInterface.m_ResetMasterSkillCheckBox1	=	lpMsg->ResetMasterSkill2;
	gInterface.m_AccountSecurityButton	=	lpMsg->AccountSecurity;
	gInterface.m_JewelsBankButton	=	lpMsg->JewelsBank;
	gInterface.m_RenameButton	=	lpMsg->Rename;
	gInterface.m_TopPlayer	=	lpMsg->TopPlayer;
	gInterface.m_PShopCurrency	=	lpMsg->PShopCurrency;
	gInterface.m_PShopOffStore	=	lpMsg->PShopOffStore;
	gInterface.m_RPSMode	=	lpMsg->RPSMode;
	gInterface.m_NewsBoard	=	lpMsg->NewsBoard;
	gInterface.m_FruitMain = lpMsg->FruitMain;
	gInterface.m_LuckySpinMain = lpMsg->LuckySpinMain;
	gInterface.m_GiftCode = lpMsg->GiftCode;
	gInterface.m_PSBless = lpMsg->PSBless;
	gInterface.m_PSSoul = lpMsg->PSSoul;
	gInterface.m_PSChaos = lpMsg->PSChaos;
	gInterface.m_PSWcoinC = lpMsg->PSWcoinC;
	gInterface.m_PSWcoinP = lpMsg->PSWcoinP;
	gInterface.m_PSWcoinG = lpMsg->PSWcoinG;
	gInterface.m_QuickAdd = lpMsg->QuickAdd;
	gInterface.m_ResetStats = lpMsg->ResetStat;
	gInterface.m_EventTimer = lpMsg->EventTimer;
	gInterface.m_CustomWare = lpMsg->CustomWare;
	gInterface.m_PartyLeader = lpMsg->PartyLeader;
	gInterface.m_PartyTrace = lpMsg->PartyTrace;
	//
	gObjUser.TitleBarSwitch = lpMsg->TitleBarSwitch;
	gObjUser.PlayerHPBarSwitch = lpMsg->PlayerHPBarSwitch;
	gObjUser.SDByPass = lpMsg->SDByPass;
	//
	gObjUser.d_Strength = lpMsg->dStrength;
	gObjUser.d_Dexterity = lpMsg->dDexterity;
	gObjUser.d_Vitality = lpMsg->dVitality;
	gObjUser.d_Energy = lpMsg->dEnergy;
	gObjUser.d_Leadership = lpMsg->dLeadership;
	gObjUser.m_MaxWarehouse = lpMsg->MaxWarehouse;
	//
	for (int i=0;i<MAX_ACCOUNT_LEVEL;i++)
	{
		gObjUser.m_CustomResetPointPriceWC[i] = lpMsg->CustomResetPointPriceWC[i];
		gObjUser.m_CustomResetPointPriceZen[i] = lpMsg->CustomResetPointPriceZen[i];
		gObjUser.m_CustomMasterSkillPriceWC[i] = lpMsg->CustomMasterSkillPriceWC[i];
		gObjUser.m_CustomMasterSkillPriceZen[i] = lpMsg->CustomMasterSkillPriceZen[i];
		gObjUser.m_MaxStatPoint[i] = lpMsg->MaxStatPoint[i];
	}
	gUserPanel.GetUserPanel();
}

void GCBalanceRecv(PMSG_BALANCE_UPDATE_RECV* lpMsg)
{
	gObjUser.BalanceWC = lpMsg->wCoinC;
	gObjUser.BalanceWP = lpMsg->GoblinPoint;
	gObjUser.BalanceGP = lpMsg->GoblinPoint;
}

void GCAccountSecurityRecv(PMSG_ACCOUNT_SECURITY_RECV* lpMsg)
{
	gObjUser.TradeLock = lpMsg->TradeLock;
	gObjUser.InventoryLock = lpMsg->InventoryLock;
	gObjUser.WareLock = lpMsg->WareLock;
	gObjUser.PShopLock = lpMsg->PShopLock;
	gObjUser.ShopLock = lpMsg->ShopLock;
	gObjUser.ChaosMixLock = lpMsg->ChaosMixLock;
	gObjUser.DelCharLock = lpMsg->DelCharLock;
}

void GCAccountSecuritySave()
{
	PMSG_ACCOUNT_SECURITY_SEND pMsg;
	pMsg.header.set(0xFF, 0x01,  sizeof(pMsg));
	pMsg.TradeLock = gObjUser.TradeLock;
	pMsg.InventoryLock = gObjUser.InventoryLock;
	pMsg.PShopLock = gObjUser.PShopLock;
	pMsg.ShopLock = gObjUser.ShopLock;
	pMsg.WareLock = gObjUser.WareLock;
	pMsg.ChaosMixLock = gObjUser.ChaosMixLock;
	pMsg.DelCharLock = gObjUser.DelCharLock;
	DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

void GCSetCharacterPage(PMSG_CHARACTERPAGE_RECV* lpMsg)
{
	gInterface.m_CharacterPage = lpMsg->Page;
}


void CGSendMultiChar(int Page)
{
	PMSG_REQ_MULTI_CHAR_SEND pMsg;
	pMsg.header.set(0xFF, 0x10, sizeof(pMsg));
	pMsg.Page = Page;
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CGSendDepositJewels(int type,int count)
{
	PMSG_JEWELSBANK_SEND pMsg;
	pMsg.header.set(0xFF,0x19,sizeof(pMsg));
	pMsg.Type = type;
	pMsg.Count = count;
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CGSendWithdrawJewels(int type,int count)
{
	PMSG_JEWELSBANK_SEND pMsg;
	pMsg.header.set(0xFF,0x18,sizeof(pMsg));
	pMsg.Type = type;
	pMsg.Count = count;
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void GCJewelsBankRecv(PMSG_BANKEX_UPDATE_RECV* lpMsg)
{
	gObjUser.m_Bless = lpMsg->Bless;
	gObjUser.m_Soul = lpMsg->Soul;
	gObjUser.m_Chaos = lpMsg->Chaos;
	gObjUser.m_Life = lpMsg->Life;
	gObjUser.m_Creation = lpMsg->Creation;
	gObjUser.m_Harmony = lpMsg->Harmony;
}

void GCFruitRecv(PMSG_FRUIT_UPDATE_RECV* lpMsg)
{
	gObjUser.FStrength = lpMsg->Strength;
	gObjUser.FDexterity = lpMsg->Dexterity;
	gObjUser.FVitality = lpMsg->Vitality;
	gObjUser.FEnergy = lpMsg->Energy;
	gObjUser.FLeadership = lpMsg->Leadership;
	gObjUser.FMaxPoint = lpMsg->MaxPoint;
}

void RPSMode(int Number)
{
	RPSMODE_REQ pMsg;
	pMsg.h.set(0xFB, 0x27, sizeof(pMsg));
	pMsg.Number = Number;
	DataSend((BYTE*)&pMsg, pMsg.h.size);
}

void UpdateRPSMode()
{
	gInterface.Data[eRock].Attribute = 0;
	gInterface.Data[ePaper].Attribute = 0;
	gInterface.Data[eScissors].Attribute = 0;
	gInterface.Data[eRPSMODE].Attribute = 0;
}

void CGSendFilesCrc()
{
	PMSG_SEND_CRC pMsg;
	pMsg.h.set(0xFB, 0x28, sizeof(pMsg));
	pMsg.CheckTime = 2018;
	DataSend((BYTE*)&pMsg, pMsg.h.size);
}

void UpdatePShop(PSSHOP_INTERFACE* lpMsg)
{
	if(lpMsg->result == 0)
	{
		gInterface.PShop = 0;
	}
	else
	{
		gInterface.PShop = 1;
	}
}

void LuckySpinRoll()
{
	gLuckySpin.StartRoll = 1;
}

void OpenCustomWare()
{
	gInterface.Data[eWAREHOUSE_MAIN].OnShow = true;
}

void RecvServerTime(PMSG_SERVERTIME_RECV* Data)
{
	CTime local_time(time(0));
	CTime server_time(Data->year,Data->month,Data->day,Data->hour,Data->minute,Data->seconds,-1);

	gInterface.m_TimeDiff = local_time.GetTime() - server_time.GetTime();
}


void DataSend(BYTE* lpMsg,DWORD size) // OK
{
	BYTE EncBuff[2048];

	if(gPacketManager.AddData(lpMsg,size) != 0 && gPacketManager.ExtractPacket(EncBuff) != 0)
	{
		BYTE send[2048];

		memcpy(send,EncBuff,size);

		if(EncBuff[0] == 0xC3 || EncBuff[0] == 0xC4)
		{
			if(EncBuff[0] == 0xC3)
			{
				BYTE save = EncBuff[1];

				EncBuff[1] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[2],&EncBuff[1],(size-1))+2;

				EncBuff[1] = save;

				send[0] = 0xC3;
				send[1] = LOBYTE(size);
			}
			else
			{
				BYTE save = EncBuff[2];

				EncBuff[2] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[3],&EncBuff[2],(size-2))+3;

				EncBuff[2] = save;

				send[0] = 0xC4;
				send[1] = HIBYTE(size);
				send[2] = LOBYTE(size);
			}
		}

		((void(__thiscall*)(void*,BYTE*,DWORD))0x00405110)((void*)0x08793750,send,size);
	}
}
