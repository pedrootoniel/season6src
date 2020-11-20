//////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "Object.h"

#define MAX_RANK_TITLE 20

struct TITLE_STRUCT {
	int Index;
    BYTE TitleCode;
    char TitleText[100];
	DWORD ImgCode;
    char ImgDir[MAX_PATH];
    float width;
    float height;
    int color;
	int	AddHP;
	int	AddMP;
};

class cCustomTitle
{
public:
	cCustomTitle();
	virtual ~cCustomTitle();
	void Init();
	void Load(TITLE_STRUCT* info);
	void SetInfo(TITLE_STRUCT info);
	TITLE_STRUCT* GetInfo(int index);
	TITLE_STRUCT* GetInfoTitle(BYTE TitleCode);
	BOOL GetTitleInfo(BYTE TitleCode,char* ImgDir,char* TitleText,DWORD ImgCode,float width,float height,int color, int addhp, int addmp);
public:
	TITLE_STRUCT m_CustomTitle[MAX_RANK_TITLE];
};

extern cCustomTitle gCustomTitle;
