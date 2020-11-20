// DefaultClassInfo.h: interface for the CQuaTanThu class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CLASS 7

struct QUATANTHU_INFO
{
	int Class;
	int	WeaponType;
	int WeaponID;
	int SetID;
	int	BuffID;
	int Level;
	int	Skill;
	int Luck;
	int Option;
	int Excellent;
	int	Time;
};

class CQuaTanThu
{
public:
	CQuaTanThu();
	virtual ~CQuaTanThu();
	void Init();
	void Load(char* path);
	void SetInfo(QUATANTHU_INFO info);
	void GiftItem(LPOBJ lpObj);
public:
	QUATANTHU_INFO m_QuaTanThuInfo[MAX_CLASS];
};

extern CQuaTanThu gQuaTanThu;
