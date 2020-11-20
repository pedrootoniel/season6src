#ifndef _CUSTOM_RANK_USER_H
#define _CUSTOM_RANK_USER_H
// ---
#include "Protocol.h"
// ---
#define MAX_RANK_USER  50
// ---
struct CUSTOM_RANK_USER_DATA
{
	int  m_iResetMin;
	int  m_iResetMax;
	int  m_Coin1;
	int  m_Coin2;
	int  m_Coin3;
};
// ---
class CCustomRankUser
{
public:
	void Load(char* path);
	void ResetReward(LPOBJ lpObj);

private:
	int m_count;
	// ---
	CUSTOM_RANK_USER_DATA m_Data[MAX_RANK_USER];
};
extern CCustomRankUser gCustomRankUser;
// ---
#endif