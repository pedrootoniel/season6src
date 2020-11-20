#include "user.h"

#define MAX_SURVIVOR_SCHEDULE 199
#define MAX_SURVIVOR_COMPETITORS 64

enum Survivor_States
{
	SURVIVOR_STATE_IDLE = 0,
	SURVIVOR_STATE_JOIN_TIMER = 1,
	SURVIVOR_STATE_PREPARE = 2,
	SURVIVOR_STATE_BATTLE = 3,
};

struct SURVIVOR_SCHEDULE
{
	int DayOfWeek;
	int Hour;
	int Minute;
	int Type;
	int Enable;
};

class CSurvivor
{
public:
	CSurvivor();
	virtual ~CSurvivor();

	void Run();
	void LoadSchedule();
		
	void ClearSchedule();
	void StartCycle(int i, int Type);
	bool IsInSurvivorArea(LPOBJ lpObj);
	void ClearEventData();
	void RunningBattle();
	void ClearPlayerData(LPOBJ lpObj);
	bool IsIntruder(LPOBJ lpObj);
	bool IsOutruder(LPOBJ lpObj);
	void PrepareToBattle();
	void GiveWinnerPrize(LPOBJ lpObj);
	SURVIVOR_SCHEDULE SurvivorSchedule[MAX_SURVIVOR_SCHEDULE];

	int ActiveEvent;
	int JoiningTimer;
	int EventType;
	DWORD StartedAtTick;
	int MinutesShowing;
	int State;
	DWORD BattleStartTick;
	int PlayerCount;
	int WinnerIndex;
	int wCoinC;
	int	wCoinP;
	int	GoblinCoin;
};

extern CSurvivor g_Survivor;