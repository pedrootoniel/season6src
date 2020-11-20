#pragma once

#include "Object.h"
#define MAX_ITEM_SMOKER 100

struct CUSTOM_SMOKER_INFO
{
	int		Index;
	WORD	ID;
	float	R;
	float	G;
	float	B;
};
class cCustomSmoker
{
public:
	cCustomSmoker();
	virtual ~cCustomSmoker();
	void Init();
	void Load(CUSTOM_SMOKER_INFO* info);
	void SetInfo(CUSTOM_SMOKER_INFO info);
	CUSTOM_SMOKER_INFO* GetInfo(int index);
	CUSTOM_SMOKER_INFO* GetInfoByID(WORD ID);
	BOOL GetItemSmokerInfo(WORD ID,float R,float G,float B);
	public:
	CUSTOM_SMOKER_INFO m_ItemSmokerInfo[MAX_ITEM_SMOKER];

};
extern cCustomSmoker gCustomSmoker;