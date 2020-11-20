#pragma once

struct ZEN_DROP
{
	BYTE MapNumber;
	DWORD MinMoney;
	DWORD MaxMoney;
};

class cZenDrop
{
public:
	cZenDrop();
	virtual ~cZenDrop();
	void Load(char* path);
	bool IsZenDropActive(BYTE Map);
	DWORD GetZenAmount(BYTE MapNumber, WORD MonsterLevel);
	// ----
	bool m_ZenDropEnable;
	bool m_MultiplyZenDropByMonLevel;
	DWORD m_MultiplyZenChanceRate;
	std::map<int, ZEN_DROP> m_ZenDrop;
}; extern cZenDrop gZenDrop;