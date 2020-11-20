#pragma once
class cOnlineBonus
{
public:
	cOnlineBonus();
	~cOnlineBonus();

	void	Init();
	void	Load();
	void	ReadData(char * File);

	void	AddTimeBonus(int UserIndex);
	void	SendRcvNotify(int UserIndex, int CoinC, int CoinP, int CoinG, int Zen);

private:
	bool	m_IsLoaded;
	bool	m_TimeBonusOn[4];
	int		m_TimeBonusAdd[4];
	DWORD	m_TimeBonusInterval[4];
};
extern cOnlineBonus gOnlineBonus;
