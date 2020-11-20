#pragma once
// -------------------------------------------------------------------------------
#include "Protocol.h"
//#include "NewInterface.h"
// -------------------------------------------------------------------------------

#define USER_PANEL_BUTTONS 21
#define MAX_ON_PAGE 6

enum eUserPanelButtons
{
	Settings,
	RollDice,
	HeadsTails,
	LuckyNumber,
	QuickAdd,
	ResetStats,
	ChangeClass,
	OffAttack,
	BuyVip,
	TitleManager,
	PartySearch,
	Smithy,
	AccSecurity,
	JewelsBank,
	RenameBox,
	TopPlayer,
	NewBoard,
	FruitMain,
	LuckySpin,
	GiftCode,
	EventTimer,
};

static char* UserPanelText	[USER_PANEL_BUTTONS] = 
{
	"Settings",
	"Roll Dice",
	"Heads Tails",
	"Lucky Number",
	"Change Class",
	"Offline Attack",
	"Buy Vip",
	"Title Manager",
	"Party Search",
	"Smithy",
	"Account Security",
	"Jewels Bank",
	"Rename Character",
	"Top Player",
	"News Board",
	"Lucky Spin",
	"Gift Code",
	"Event Time",
};

// -------------------------------------------------------------------------------

class UserPanel
{
public:
			UserPanel();
			~UserPanel();
	// ----
	void DrawUserPanel();
	void EventUserPanel(DWORD Event,MOUSEHOOKSTRUCTEX* Mouse);
	void UserPanelSwitchState();

	void	Init();
	void	GetUserPanel();
	// ----
private :
	int StartIndex;
	int ButtonsArr[USER_PANEL_BUTTONS];
	// ----
}; extern UserPanel gUserPanel;
// -------------------------------------------------------------------------------