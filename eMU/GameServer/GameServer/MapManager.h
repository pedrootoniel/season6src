// MapManager.h: interface for the CMapManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct MAP_MANAGER_INFO
{
	int Index;
	int NonPK;
	int ViewRange;
	int ExperienceRate;
	int ItemDropRate;
	int ExcItemDropRate;
	int SetItemDropRate;
	int SocketItemDrop;
	int HelperEnable;
	int GensBattle;
	int OffStoreEnable;
	int OffAttackEnable;
};

class CMapManager
{
public:
	CMapManager();
	virtual ~CMapManager();
	void Load(char* path);
	int GetMapNonPK(int index);
	int GetMapNonOutlaw(int index);
	int GetMapViewRange(int index);
	int GetMapExperienceRate(int index);
	int GetMapMasterExperienceRate(int index);
	int GetMapItemDropRate(int index);
	int GetMapExcItemDropRate(int index);
	int GetMapSetItemDropRate(int index);
	int GetMapSocketItemDrop(int index);
	int GetMapHelperEnable(int index);
	int GetMapGensBattle(int index);
	int	GetMapOffStoreEnable(int index);
	int	GetMapOffAttackEnable(int index);
public:
	std::map<int,MAP_MANAGER_INFO> m_MapManagerInfo;
};

extern CMapManager gMapManager;
