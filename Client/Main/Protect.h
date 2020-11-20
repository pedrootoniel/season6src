// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "CustomMonster.h"
#include "CustomSocket.h"
#include "CustomSmoke.h"
#include "CustomTitle.h"
#include "CustomFog.h"
#include "CustomPet.h"
#include "CSmithItem.h"
#include "ModelEffect.h"
#include "ItemPrice.h"
#include "MonsterNameColor.h"
#include "ItemOption.h"
#include "CustomWeapons.h"
#include "CustomGloves.h"
#include "EventTimer.h"
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

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool ReadMainFile(char* name);
	void CheckLauncher();
	void CheckInstance();
	void CheckClientFile();
	void CheckPlugin1File();
	void CheckPlugin2File();
	void CheckPlugin3File();
	void CheckPlugin4File();
	void CheckPlugin5File();
	void CheckCameraFile();
	DWORD GetFileCRC(const char* szFileName);
public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;
