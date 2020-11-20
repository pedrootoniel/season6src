#pragma once
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
	void Load(char* path);
	void SetInfo(CUSTOM_SMOKER_INFO info);
public:
	CUSTOM_SMOKER_INFO m_ItemSmokerInfo[MAX_ITEM_SMOKER];
};
extern cCustomSmoker gCustomSmoker; 