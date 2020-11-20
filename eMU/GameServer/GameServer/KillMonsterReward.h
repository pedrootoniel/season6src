#pragma once

#define MAX_SHOPPOINTEX_MONSTER		1024

struct SHOPPOINTEX_MONSTER
{
	DWORD	MonsterID;
	int		MapNumber;
	int		AddCoinC;
	int		AddCoinP;
	int		AddCoinG;
	//int		AddUpPoint;
};


class ShopPointEx
{
public:
	ShopPointEx();
	~ShopPointEx();

	void	Init();
	void	Load();
	void	ReadData(char * File);

	int		GetMonsterSlot(int Class, int Map);

	void	AddMonsterBonus(int UserIndex, int MonsterIndex);

	void	SendRcvNotify(int UserIndex, int CoinC, int CoinP, int CoinG);

private:
	bool	m_IsLoaded;
	int		m_MonsterLoaded;

	SHOPPOINTEX_MONSTER m_MonsterBonus[MAX_SHOPPOINTEX_MONSTER];

};
extern ShopPointEx g_ShopPointEx;
