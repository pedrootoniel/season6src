#pragma once

#include "User.h"

struct PVPZONE_DATA
{
	WORD	Map;
	BYTE	X1;
	BYTE	X2;
	BYTE	Y1;
	BYTE	Y2;
};

class cPVPZone
{
public:
	cPVPZone();
	virtual ~cPVPZone();
	void Load(char* path);
	bool IsPVPZone(LPOBJ lpObj);
public:
	std::vector<PVPZONE_DATA> m_PvpZone;
}; extern cPVPZone gPVPZone;