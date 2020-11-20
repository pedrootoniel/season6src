#pragma once
// ----
#include "Object.h"
#include "Defines.h"
// ----
class User
{
public:
	void		Load();
	void		Refresh();
	bool		GetTarget();
	// ----
	static void ChangeCharInfo(LPVOID This);
	static char* GetMapName(signed int MapNumber);
	int GetActiveSkill();
	//
	int GetResetPointPriceWC(int AccountLevel);
	int GetResetPointPriceZen(int AccountLevel);
	int GetResetMasterSkillPriceWC(int AccountLevel);
	int GetResetMasterSkillPriceZen(int AccountLevel);
	int GetMaxStatPoint(int AccountLevel);
	// ----
	lpCharObj	lpPlayer;
	lpViewObj	lpViewPlayer;
	lpViewObj	lpViewTarget;
	// ----
	BYTE		m_TargetType;	//1 - npc, 2 - attack
	int			m_MapNumber;
	int			m_CursorX;
	int			m_CursorY;
	short		m_MasterLevel;
	short		m_MasterPoint;
	__int64		m_MasterExp;
	__int64		m_MasterNextExp;
	//
	int MagickAttack;
	//
	int PostItemID;
	int	PostItemLV;
	int	PostItemExc;
	int	PostItemX;
	int	PostItemY;
	int IsArenaEvent;
	BYTE TitleBarSwitch;
	BYTE PlayerHPBarSwitch;
	BYTE SDByPass;
	//default class point
	int	d_Strength;
	int	d_Dexterity;
	int	d_Vitality;
	int	d_Energy;
	int	d_Leadership;
	//jewels bank
	int m_Bless;
	int m_Soul;
	int m_Life;
	int m_Chaos;
	int m_Creation;
	int m_Harmony;
	//
	int m_CustomResetPointPriceWC[MAX_ACCOUNT_LEVEL];
	int m_CustomResetPointPriceZen[MAX_ACCOUNT_LEVEL];
	int m_CustomMasterSkillPriceWC[MAX_ACCOUNT_LEVEL];
	int m_CustomMasterSkillPriceZen[MAX_ACCOUNT_LEVEL];
	int m_MaxStatPoint[MAX_ACCOUNT_LEVEL];
	//
	DWORD BalanceWC;
	DWORD BalanceWP;
	DWORD BalanceGP;
	// Account Security
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
	// Fruit System
	int FStrength;
	int FDexterity;
	int FVitality;
	int FEnergy;
	int FLeadership;
	int FMaxPoint;
	//
	int			m_MaxWarehouse;
	int			m_WarehouseNumber;
	//
}; extern User gObjUser;
// ----------------------------------------------------------------------------------------------