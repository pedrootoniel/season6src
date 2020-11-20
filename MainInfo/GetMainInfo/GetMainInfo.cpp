#include "stdafx.h"
#include "..\\..\Util\CCRC32.H"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "CustomWIngEffect.h"
#include "DynamicEffect.h"
#include "CustomMonster.h"
#include "CustomSocket.h"
#include "CustomSmoke.h"
#include "CustomTitle.h"
#include "ThemidaSDK.h"
#include "CustomFog.h"
#include "CustomPet.h"
#include "CSmithItem.h"
#include "ModelEffect.h"
#include "ItemPrice.h"
#include "MonsterNameColor.h"
#include "ItemOption.h"
#include "CustomWeapons.h"
#include "CustomRFGloves.h"
#include "EventTimerText.h"
struct MAIN_FILE_INFO
{
	BYTE LauncherType; 
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[64];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName1[32];
	char PluginName2[32];
	char PluginName3[32];
	char PluginName4[32];
	char PluginName5[32];
	char CameraName[32];
	DWORD MasterSkillTree;
	DWORD CharacterCount;
	DWORD ExpandedCharacter;
	DWORD CastleSiegeSkill;
	DWORD Instances;
	DWORD CustomItemPack;
	DWORD ClientCRC32;
	DWORD Plugin1CRC32;
	DWORD Plugin2CRC32;
	DWORD Plugin3CRC32;
	DWORD Plugin4CRC32;
	DWORD Plugin5CRC32;
	DWORD CameraCRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	DWORD HealthBar;
	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO VtmCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_MONSTER_INFO CustomMonsterInfo[MAX_CUSTOM_MONSTER];
	CUSTOM_SOCKET_INFO CustomSocketInfo[MAX_CUSTOM_SOCKET];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	CUSTOM_SMOKER_INFO CustomSmokerInfo[MAX_ITEM_SMOKER];
	TITLE_STRUCT CustomTitleInfo[MAX_RANK_TITLE];
	CUSTOM_PET_INFO CustomPetInfo[MAX_PET_ITEM];
	CUSTOM_MODEL_EFFECT_INFO ModelEffectInfo[MAX_MODEL_EFFECT];
	CUSTOM_FOG CustomFog[MAX_FOG];
	CUSTOM_ITEMPRICE CustomItemPrice[MAX_ITEMPRICE];
	CUSTOM_MONSTER_COLOR_INFO CustomMonsterNameColor[MAX_NAME_COLOR];
	ItemOption_Data CustomItemOption[MAX_OPTION_ITEM];
	CUSTOM_WEAPONS_INFO CustomWeapons[MAX_CUSTOM_WEAPONS];
	CUSTOM_RF_GLOVES CustomGloves[MAX_CUSTOM_GLOVES];
	EVENT_TEXT_INFO CustomEventTime[MAX_TIMER_TEXT];
};

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info,0,sizeof(info));

	info.LauncherType = GetPrivateProfileInt("MainInfo","LauncherType",0,".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("MainInfo","IpAddressPort",44405,".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","IpAddress","",info.IpAddress,sizeof(info.IpAddress),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientVersion","",info.ClientVersion,sizeof(info.ClientVersion),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientSerial","",info.ClientSerial,sizeof(info.ClientSerial),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","WindowName","",info.WindowName,sizeof(info.WindowName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ScreenShotPath","",info.ScreenShotPath,sizeof(info.ScreenShotPath),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientName","",info.ClientName,sizeof(info.ClientName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName1","",info.PluginName1,sizeof(info.PluginName1),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName2", "", info.PluginName2, sizeof(info.PluginName2), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName3", "", info.PluginName3, sizeof(info.PluginName3), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName4", "", info.PluginName4, sizeof(info.PluginName4), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName5", "", info.PluginName5, sizeof(info.PluginName5), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CameraName", "",info.CameraName,sizeof(info.CameraName),".\\MainInfo.ini");

	info.HelperActiveAlert = GetPrivateProfileInt("HelperInfo","HelperActiveAlert",0,".\\MainInfo.ini");

	info.HelperActiveLevel = GetPrivateProfileInt("HelperInfo","HelperActiveLevel",80,".\\MainInfo.ini");

	info.DWMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DWMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DKMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DKMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.FEMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","FEMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.MGMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","MGMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DLMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DLMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.SUMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","SUMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.RFMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","RFMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.ReconnectTime = GetPrivateProfileInt("ReconnectInfo","ReconnectTime",0,".\\MainInfo.ini");

	info.CharacterCount = GetPrivateProfileInt("MainInfo","CharacterCount",7,".\\MainInfo.ini");

	info.MasterSkillTree = GetPrivateProfileInt("MainInfo","MasterSkillTreeWindow",1,".\\MainInfo.ini");

	info.CastleSiegeSkill = GetPrivateProfileInt("MainInfo","UnlockCSSkill",1,".\\MainInfo.ini");

	info.ExpandedCharacter = GetPrivateProfileInt("MainInfo","Expanded25Character",1,".\\MainInfo.ini");

	info.Instances = GetPrivateProfileInt("MainInfo","MultiMainWindow",0,".\\MainInfo.ini");

	//info.CustomItemPack = GetPrivateProfileInt("MainInfo","CustomItemPack",0,".\\MainInfo.ini");

	info.HealthBar = GetPrivateProfileInt("MainInfo","HealthBar",0,".\\MainInfo.ini");

	gCustomMessage.Load("CustomMessage.txt");

	gCustomJewel.Load("CustomJewel.txt");

	gCustomWing.Load("CustomWing.txt");

	gCustomItem.Load("CustomItem.txt");

	gCustomMonster.Load("CustomMonster.txt");

	gCustomSocket.Load("ItemSocket.txt");

	gCustomWingEffect.Load("ItemStaticEffect.txt");

	gDynamicWingEffect.Load("ItemDynamicEffect.txt");

	gCustomSmoker.Load("ItemSmoker.txt");

	gCustomTitle.Load("CustomTitle.txt");

	gFog.Load("CustomFog.txt");

	gCustomPet2.Load("CustomPet.txt");

	gCustomModelEffect.Load("ModelEffect.txt");

	gItemPrice.Load("ItemValue.txt");

	gCustomMonsterNameColor.Load("MonsterNameColor.txt");

	gItemOption.Load("ItemOptionValue.txt");

	gCustomWeapons.Load("CustomWeapons.txt");

	gCustomGloves.Load("CustomGloves.txt");

	gEventText.Load("EventTimerText.txt");

	memcpy(info.EngCustomMessageInfo,gCustomMessage.m_EngCustomMessageInfo,sizeof(info.EngCustomMessageInfo));

	memcpy(info.PorCustomMessageInfo,gCustomMessage.m_PorCustomMessageInfo,sizeof(info.PorCustomMessageInfo));

	memcpy(info.SpnCustomMessageInfo,gCustomMessage.m_SpnCustomMessageInfo,sizeof(info.SpnCustomMessageInfo));

	memcpy(info.VtmCustomMessageInfo,gCustomMessage.m_VtmCustomMessageInfo,sizeof(info.VtmCustomMessageInfo));

	memcpy(info.CustomJewelInfo,gCustomJewel.m_CustomJewelInfo,sizeof(info.CustomJewelInfo));

	memcpy(info.CustomWingInfo,gCustomWing.m_CustomWingInfo,sizeof(info.CustomWingInfo));

	memcpy(info.CustomItemInfo,gCustomItem.m_CustomItemInfo,sizeof(info.CustomItemInfo));

	memcpy(info.CustomMonsterInfo,gCustomMonster.m_CustomMonsterInfo,sizeof(info.CustomMonsterInfo));

	memcpy(info.CustomSocketInfo,gCustomSocket.m_CustomSocketInfo,sizeof(info.CustomSocketInfo));

	memcpy(info.CustomWingEffectInfo,gCustomWingEffect.m_CustomWingEffectInfo,sizeof(info.CustomWingEffectInfo));

	memcpy(info.DynamicWingEffectInfo,gDynamicWingEffect.m_DynamicWingEffectInfo,sizeof(info.DynamicWingEffectInfo));

	memcpy(info.CustomSmokerInfo,gCustomSmoker.m_ItemSmokerInfo,sizeof(info.CustomSmokerInfo));

	memcpy(info.CustomTitleInfo,gCustomTitle.m_CustomTitle,sizeof(info.CustomTitleInfo));

	memcpy(info.ModelEffectInfo,gCustomModelEffect.m_CustomModelEffectInfo,sizeof(info.ModelEffectInfo));

	memcpy(info.CustomPetInfo,gCustomPet2.m_CustomPetInfo,sizeof(info.CustomPetInfo));

	memcpy(info.CustomFog, gFog.m_CustomFog, sizeof(info.CustomFog));

	memcpy(info.CustomItemPrice, gItemPrice.m_ItemPrice, sizeof(info.CustomItemPrice));

	memcpy(info.CustomMonsterNameColor, gCustomMonsterNameColor.m_CustomMonsterColorInfo, sizeof(info.CustomMonsterNameColor));

	memcpy(info.CustomItemOption, gItemOption.m_CustomOptionInfo, sizeof(info.CustomItemOption));

	memcpy(info.CustomWeapons, gCustomWeapons.m_CustomWeaponsInfo, sizeof(info.CustomWeapons));

	memcpy(info.CustomGloves, gCustomGloves.m_CustomGlovesInfo, sizeof(info.CustomGloves));

	memcpy(info.CustomEventTime, gEventText.m_EventTextInfo, sizeof(info.CustomEventTime));

	CCRC32 CRC32;

	if(CRC32.FileCRC(info.ClientName,&info.ClientCRC32,1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName1,&info.Plugin1CRC32,1024) == 0)
	{
		info.Plugin1CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName2, &info.Plugin2CRC32, 1024) == 0)
	{
		info.Plugin2CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName3, &info.Plugin3CRC32, 1024) == 0)
	{
		info.Plugin3CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName4, &info.Plugin4CRC32, 1024) == 0)
	{
		info.Plugin4CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName5, &info.Plugin5CRC32, 1024) == 0)
	{
		info.Plugin5CRC32 = 0;
	}


	if(CRC32.FileCRC(info.CameraName,&info.CameraCRC32,1024) == 0)
	{
		info.CameraCRC32 = 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xCA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x95^HIBYTE(n));
	}

	HANDLE file = CreateFile("main.supremo",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&info,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	ENCODE_END

	CLEAR_END

	return 0;
}
