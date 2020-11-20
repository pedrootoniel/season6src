#pragma once
#include "User.h"
#ifdef NOLOAD

struct FakeOnline_Struct
{
	char Name[11];
	int Active;
	int Class;
	int Map;
	int MapX;
	int MapY;
	int isGM;
	int ItemType0;
	int ItemLevel0;
	int ItemType1;
	int ItemLevel1;
	int ItemType2;
	int ItemLevel2;
    int ItemType3;
	int ItemLevel3;
	int ItemType4;
	int ItemLevel4;
	int ItemType5;
	int ItemLevel5;
	int ItemType6;
	int ItemLevel6;
	int ItemType7;
	int ItemLevel7;
	int ItemType8;
	int ItemLevel8;
};



//========================================================================================================================
class CFakeOnline
{
public:
	void Init();
	void CreateFakeOnline();
	void DeleteFakeOnline();
	void ReloadFakeOnline();
	void SetZenoStruct();
	void LoadFileFakeOnline(char *filename);
	void InsertFakeOnline(int iIndex,char Name[11],int Active,int Class,int Map,int MapX,int MapY,int isGM,int ItemType0,int ItemLevel0,int ItemType1,int ItemLevel1,int ItemType2,int ItemLevel2,int ItemType3,int ItemLevel3,int ItemType4,int ItemLevel4,int ItemType5,int ItemLevel5,int ItemType6,int ItemLevel6,int ItemType7,int ItemLevel7,int ItemType8,int ItemLevel8);
	void FakeOnlineSet(char Name[11],int Active,int Class,int Map,int MapX,int MapY,int isGM,int ItemType0,int ItemLevel0,int ItemType1,int ItemLevel1,int ItemType2,int ItemLevel2,int ItemType3,int ItemLevel3,int ItemType4,int ItemLevel4,int ItemType5,int ItemLevel5,int ItemType6,int ItemLevel6,int ItemType7,int ItemLevel7,int ItemType8,int ItemLevel8);    
	void FakeAttackStart();
	void DarkWizardFakeAttack(LPOBJ lpObj);
	void FakeBaseAct(LPOBJ lpObj);
	int iCountFake;
	FakeOnline_Struct m_FakeOnline[512];
}; extern CFakeOnline s_FakeOnline;
//========================================================================================================================
#endif