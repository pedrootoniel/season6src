#pragma once
#define MAX_OBJECT			350
#define MAX_WIN_WIDTH		640
#define MAX_WIN_HEIGHT		480
#include "Import.h"
#include "OfflineMode.h"
enum InterfaceID
{
	iBg1				= 0x787B,
	iBg2				= 0x787C,
	iBg3				= 0x787D,
	iBg4				= 0x787E,
	iBg5				= 0x787F,
	iBg6				= 0x7880,
	iBg7				= 0x7881,
	iBg8				= 0x7882,
	//-
	iDragonLeft			= 0x7892,
	iDragonRight		= 0x7893,
	iNewInventory		= 0x7A49,
	iNewCharacter		= 0x7A48,
	iNewParty		    = 0x910,
	iNewWinpush			= 0x7A4A,
	iNewFastMenu		= 0x7A4B,
	iNewSkillBox		= 0x7A50,
	//-
	iCapeDeath1			= 0x789C,
	iCapeDeath2			= 0x789D,
	iCapeLvl4DL			= 0x78A5,
	iCapeLvl4DL2		= 0x78A6,
	iDLRedwing02		= 0x7758,
	iDLRedwing03		= 0x7759,
	iCapeLvl4RF			= 0x8E98,
	//
	iRollMain			= 0x9980,
	iRollUp				= 0x9981,
	iRollDown			= 0x9982,
	iRollOver			= 0x9983,
	iRollUnder			= 0x9984,
	iRollStart			= 0x9985,
	iRollNum1			= 0x9986,
	iRollNum2			= 0x9987,
	iRollNum3			= 0x9988,
	iRollNum4			= 0x9989,
	iRollNum5			= 0x9990,
	iRollNum6			= 0x9991,
	iRollButton			= 0x9992,
	//
	iNewuiDialogHr		= 0x7887,
	iGfxDialoge			= 0x7888,
	iGfxBtnSmall		= 0x7886,
	iGfxBtnSmall2		= 0x788E,
	iOptionLine			= 0x7B5E,
	iOptionDot			= 0x7B68,
	iOptionCheck		= 0x7B69,
	iGfxBtn				= 0x7885,
};
enum ObjectID
{
	eSkillBox,
	eDragonLeft,
	eDragonRight,
	eCharacter,
	eInventory,
	eParty,
	eFriend,
	eFastMenu,
	ePkMenu,
	eRollMain,
	eRollUp,
	eRollDown,
	eRollOver,
	eRollUnder,
	eRollStart,
	eRollButtonA,
	eRollButtonB,
	eTitle,
	eClickLeft,
	eClickRight,
	eRankBuy,
	eRankSlot1,
	eRankDeactive,
	eTitleManagerButton,
	eSmithItemButton,
	ePartySearchButton,
	eUSERSPANEL_MAIN,
	eNewButton1,
	eNewButton2,
	eNewButton3,
	eBUTTON3_1,
	eBUTTON4_1,
	eUNCHECK_1,
	eUNCHECK_2,
	eUNCHECK_3,
	eUNCHECK_4,
	eUNCHECK_5,
	eUNCHECK_6,
	eCHECKED_1,
	eCHECKED_2,
	eCHECKED_3,
	eCHECKED_4,
	eCHECKED_5,
	eCHECKED_6,
	eFlipMain,
	eFlipHeads,
	eFlipTails,
	eFlipStart,
	eFlipButtonA,
	eFlipButtonB,
	eLuckyMain,
	eLuckyStart,
	eLuckyButtonA,
	eLuckyButtonB,
	eEmptySmall1,
	eEmptySmall2,
	eEmptySmall3,
	eEmptySmall4, //Close
	eEmptySmall5, //Smith Item
	eEmptySmall6, //Title Manager
	eEmptySmall7, //Party Search
	eEmptySmall8, //OffAttack
	eEmptySmall9, //Buy Vip
	eEmptySmall10, //Change Class
	ROLLDICE_CLOSE,
	HEADSTAILS_CLOSE,
	LUCKYNUMBER_CLOSE,
	TITLEMANAGER_CLOSE,
	/*
	//watafak
	eSMITH_MAIN,
	eSMITH_TITLE,
	eSMITH_FRAME,
	eSMITH_FOOTER,
	eSMITH_DIV,
	eSMITH_CLOSE,
	eSMITH_BUY,
	//controll -
	eSMITH_ITEMTYPE,
	eSMITH_ITEMINDEX,
	eSMITH_LEVEL,
	eSMITH_SKILL,
	eSMITH_LUCK,
	eSMITH_OPT,
	eSMITH_EXC,
	eSMITH_EXC1,
	eSMITH_EXC2,
	eSMITH_EXC3,
	eSMITH_EXC4,
	eSMITH_EXC5,
	eSMITH_DAYS,
	//controll +
	eSMITH_ITEMTYPE_1,
	eSMITH_ITEMINDEX_1,
	eSMITH_LEVEL_1,
	eSMITH_SKILL_1,
	eSMITH_LUCK_1,
	eSMITH_OPT_1,
	eSMITH_EXC_1,
	eSMITH_EXC1_1,
	eSMITH_EXC2_1,
	eSMITH_EXC3_1,
	eSMITH_EXC4_1,
	eSMITH_EXC5_1,
	eSMITH_DAYS_1,
	*/
	// ----
	eSMITHY_MAIN,
	eSMITHY_TITLE,
	eSMITHY_FRAME,
	eSMITHY_FOOTER,
	eSMITHY_DIV,
	eSMITHY_DIV2,
	eSMITHY_INFOBG,
	eSMITHY_CLOSE, 
	eSMITHY_BACK,
	eSMITHY_TEXT,
	eSMITHY_TEXT2, 
	eSMITHY_TEXT3, 
	eSMITHY_TEXT4, 
	eSMITHY_TEXT5, 
	eSMITHY_TEXT6, 
	eSMITHY_TEXT7, 
	eSMITHY_TEXT8, 
	eSMITHY_TEXT9, 
	eSMITHY_TEXT10,
	eSMITHY_L,
	eSMITHY_R,
	eSMITHY_INFOBG2,
	eSMITHY_INFOBG3,
	eSMITHY_LINE,
	eSMITHY_POINT, 
	eSMITHY_CHECK0,
	eSMITHY_CHECK1,
	eSMITHY_CHECK2,
	eSMITHY_CHECK3,
	eSMITHY_CHECK4,
	eSMITHY_CHECK5,
	eSMITHY_CHECK6,
	eSMITHY_CHECK7,
	eSMITHY_PAGEUP,
	eSMITHY_PAGEDN,
	eSMITHY_BT1,
	eSMITHY_BT2,
	eSMITHY_PAGEUP2,
	eSMITHY_PAGEDN2,
	eSMITHY_PAGEUP3,
	eSMITHY_PAGEDN3,
	eSMITHY_CHECKWIN_MAIN,
	eSMITHY_CHECKWIN_TITLE, 
	eSMITHY_CHECKWIN_FRAME, 
	eSMITHY_CHECKWIN_FOOTER,
	eSMITHY_CHECKWIN_DIV,
	eSMITHY_CHECKWIN_OK,
	eSMITHY_CHECKWIN_CLOSE, 
	// ----
	//
	ePARTYSETTINGS_MAIN,
	ePARTYSETTINGS_TITLE,
	ePARTYSETTINGS_FRAME,
	ePARTYSETTINGS_FOOTER,
	ePARTYSETTINGS_DIV,
	ePARTYSETTINGS_CLOSE,
	ePARTYSETTINGS_SYSTEM_ACTIVE,
	ePARTYSETTINGS_ONLY_GUILD,
	ePARTYSETTINGS_ONE_CLASS,
	ePARTYSETTINGS_DARK_WIZARD,
	ePARTYSETTINGS_DARK_KNIGHT,
	ePARTYSETTINGS_ELF,
	ePARTYSETTINGS_MAGIC_GLADIATOR,
	ePARTYSETTINGS_DARK_LORD,
	ePARTYSETTINGS_SUMMONER,
	ePARTYSETTINGS_RAGE_FIGHTER,
	ePARTYSETTINGS_LEVEL_MINUS,
	ePARTYSETTINGS_LEVEL_PLUS,
	ePARTYSETTINGS_OK,
	ePARTYSEARCH_LEFT,
	ePARTYSEARCH_RIGHT,
	ePARTYSEARCH_MAIN,
	ePARTYSEARCH_TITLE,
	ePARTYSEARCH_FRAME,
	ePARTYSEARCH_FOOTER,
	ePARTYSEARCH_DIV,
	ePARTYSEARCH_CLOSE,
	//
	eSTATSADD_MAIN,
	eSTATSADD_TITLE,
	eSTATSADD_FRAME,
	eSTATSADD_FOOTER,
	eSTATSADD_CLOSE,
	eSTATSADD_TEXTBOX01,
	eSTATSADD_STATBOX01,
	eSTATSADD_STATBOX02,
	eSTATSADD_STATBOX03,
	eSTATSADD_STATBOX04,
	eSTATSADD_STATBOX05,
	eSTATSADD_BTN_OK,
	eRESETSTATS_MAIN,
	eRESETSTATS_TITLE,
	eRESETSTATS_FRAME,
	eRESETSTATS_FOOTER,
	eRESETSTATS_CLOSE,
	eRESETSTATS_POINT,
	eRESETSTATS_CHECK_WC,
	eRESETSTATS_CHECK_STAT,
	eRESETMASTER_CHECK_WC,
	eRESETMASTER_CHECK_STAT,
	eRESETSTATS_BTN_OK,
	eCHARINFO_BTN_STAT,
	eCHARINFO_BTN_RESSTAT,
	//
	eOFFEXP_MAIN,
	eOFFEXP_TITLE,
	eOFFEXP_FRAME,
	eOFFEXP_FOOTER,
	eOFFEXP_DIV,
	eOFFEXP_CLOSE,
	eOFFEXP_FINISH,
	eOFFEXP_POINT,
	eOFFEXP_CHECKBOX_BUFF,
	eOFFEXP_CHECKBOX_PICK_ZEN,
	eOFFEXP_CHECKBOX_PICK_JEWELS,
	eOFFEXP_CHECKBOX_PICK_EXC,
	eOFFEXP_CHECKBOX_PICK_ANC,
	eOFFEXP_CHECKBOX_SELECTED_HELPER,
	eOFFEXP_BTN_OK,
	eOFFEXP_SKILL1,
	eOFFEXP_SKILL2,
	eOFFEXP_SKILL3,
	//
	eSECURITY_MAIN,
	eSECURITY_TITLE,
	eSECURITY_FRAME,
	eSECURITY_FOOTER,
	eSECURITY_DIV,
	eSECURITY_TRADE,
	eSECURITY_INVENTORY,
	eSECURITY_WAREHOUSE,
	eSECURITY_PERSONALSHOP,
	eSECURITY_SHOP,
	eSECURITY_CHAOBOX,
	eSECURITY_DELCHAR,
	eSECURITY_SAVE,
	//
	eSECURITY_CHECK_MAIN,
	eSECURITY_CHECK_TITLE, 
	eSECURITY_CHECK_FRAME, 
	eSECURITY_CHECK_FOOTER,
	eSECURITY_CHECK_DIV,
	eSECURITY_CHECK_BOX,
	eSECURITY_CHECK_OK,
	eSECURITY_CHECK_CLOSE, 
	//
	eSELECTCHAR_LEFT,
	eSELECTCHAR_RIGHT,
	//
	eCHANGINGCLASS_MAIN,
	eCHANGINGCLASS_TITLE,
	eCHANGINGCLASS_FRAME,
	eCHANGINGCLASS_FOOTER,
	eCHANGINGCLASS_DIV,
	eCHANGINGCLASS_INFOBG,
	eCHANGINGCLASS_MONEYBG,
	eCHANGINGCLASS_CLOSE,
	eCHANGINGCLASS_DW,
	eCHANGINGCLASS_DK,
	eCHANGINGCLASS_ELF,
	eCHANGINGCLASS_MG,
	eCHANGINGCLASS_DL,
	eCHANGINGCLASS_SUM,
	eCHANGINGCLASS_RF,
	//
	eVIP_MAIN,
	eVIP_TITLE,
	eVIP_FRAME,
	eVIP_FOOTER,
	eVIP_DIV,
	eVIP_INFOBG,
	eVIP_MONEYBG,
	eVIP_CLOSE,
	eVIP_INFO,
	eVIP_SILVER,
	eVIP_GOLD,
	eVIP_PLATINUM,
	eVIP_RIGHT,
	eVIP_LEFT,
	//
	eRENAME_MAIN,
	eRENAME_TITLE, 
	eRENAME_FRAME, 
	eRENAME_FOOTER,
	eRENAME_DIV,
	eRENAME_BOX,
	eRENAME_OK,
	eRENAME_CLOSE,
	//
	eSHOP_WC,
	eSHOP_B,
	eSHOP_WP,
	eSHOP_S,
	eSHOP_GP,
	eSHOP_C,
	eSHOP_OFF,
	eSHOP_OFFMAIN,
	eSHOP_OFFOK,
	eSHOP_OFFNO,
	eSHOP_CLOSE,
	//
	eOFFPANEL_MAIN,
	eOFFPANEL_TITLE,
	eOFFPANEL_FRAME,
	eOFFPANEL_FOOTER,
	eOFFPANEL_YES,
	eOFFPANEL_CANE,
	//
	eJewelsBank,
	eJewels_Des,
	eJewels_Wid,
	eJewels_Close,
	eJewels_Bless,
	eJewels_Soul,
	eJewels_Chaos,
	eJewels_Life,
	eJewels_Creation,
	eJewels_Harmony,
	eJewels_Box,
	eJewels_OK,
	//
	eARROW_RIGHT,
	eARROW_LEFT,
	//
	ePT_PERSONAL_SEARCH_MAIN, 
	ePT_PERSONAL_SEARCH_TITLE,
	ePT_PERSONAL_SEARCH_FRAME,
	ePT_PERSONAL_SEARCH_FOOTER,
	ePT_PERSONAL_SEARCH_DIV,
	ePT_PERSONAL_SEARCH_CLOSE,
	ePT_PERSONAL_SEARCH_L,
	ePT_PERSONAL_SEARCH_R,
	ePT_PERSONAL_SEARCH_PAGEUP1, 
	ePT_PERSONAL_SEARCH_PAGEUP2, 
	ePT_PERSONAL_SEARCH_PAGEUP3, 
	ePT_PERSONAL_SEARCH_PAGEUP4, 
	ePT_PERSONAL_SEARCH_PAGEUP5, 
	ePT_PERSONAL_SEARCH_PAGEUP6, 
	ePT_PERSONAL_SEARCH_PAGEUP7, 
	ePT_PERSONAL_SEARCH_PAGEUP8, 
	ePT_PERSONAL_SEARCH_PAGEUP9, 
	ePT_PERSONAL_SEARCH_PAGEUP10,
	//
	eRock,
	ePaper,
	eScissors,
	eRPSMODE,
	//
	eNEWS_MAIN,
	eNEWS_TITLE,
	eNEWS_FRAME,
	eNEWS_FOOTER,
	eNEWS_DIV,
	eNEWS_INFOBG,
	eNEWS_CLOSE,
	eNEWS_BACK,
	//
	eFruitMain,
	eAttention,
	eFruitClose,
	//
	eLuckySpin,
	eLuckySpinRoll,
	eLuckySpinClose,
	//
	eGIFTCODE_MAIN,
	eGIFTCODE_TITLE, 
	eGIFTCODE_FRAME, 
	eGIFTCODE_FOOTER,
	eGIFTCODE_DIV,
	eGIFTCODE_BOX,
	eGIFTCODE_OK,
	eGIFTCODE_CLOSE,
	eUSERSPANELBG,
	eUSERSPANEL_BUTTON,
	//
	eARROW_RIGHT2,
	eARROW_LEFT2,
	eEVENTTABLE_MAIN,
	eEVENTTABLE_TITLE,
	eEVENTTABLE_LEFT,
	eEVENTTABLE_RIGHT,
	eEVENTTABLE_FOOTER,
	eEVENTTABLE_DIV,
	eEVENTTABLE_CLOSE,
	//
	eWAREHOUSE_MAIN,
	eWAREHOUSE,
	eWAREHOUSE1,
	eWAREHOUSE_OPEN,
	//
	ePARTYLEADER,
	ePARTYLEADER2,
	ePARTYLEADER3,
	ePARTYLEADER4,
	ePARTYTRACE,
	ePARTYTRACE2,
	ePARTYTRACE3,
	ePARTYTRACE4,
	ePARTYTRACE5,
};

struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	DWORD	Attribute;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	bool	ByClose;
	bool	FirstLoad;

	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Close()
	{ 
		this->OnShow = false; 
		pSetCursorFocus = false; 
		this->ByClose = false;
	};

	void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false; 
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		//this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = true;
	}
};
class Interface
{
public:
	Interface();
	virtual ~Interface();
	void		Load();
	static void Work();
	static void LoadModels();
	static void LoadImages();
	void		BindObject(short ObjectID,DWORD ModelID,float Width,float Height,float x,float y);

	void	DrawS2Interface();
	void	DrawMenuButton();
	void	DrawMenuButton1();
	void	DrawDragonLeft();
	void	DrawDragonRight();
	void	EventMenuButton(DWORD Event);
	void	EventMenuButton1(DWORD Event);
	void	DrawAutoInfo();
	bool	ShowAutoInfo;
	void	DrawExpBar();

	void	DrawUserPanel();
	void	EventUserPanel(DWORD Event);
	bool	ShowUserPanel;
	bool	CheckUserPanel() { return this->Data[eUSERSPANEL_MAIN].OnShow; };
	void	OpenUserPanel(){ this->ShowUserPanel = true; };
	void	CloseUserPanel(){ this->ShowUserPanel = false; };
	//void	DrawGamblingPanel();
	//void	EventGamblingPanel(DWORD Event);
	//void	OpenGamblingPanel(){ this->ShowExtraPanel = true; };
	//void	CloseGamblingPanel(){ this->ShowExtraPanel = false; };
	//bool	ShowExtraPanel;
	// --- Roll the Dice
	void	RolltheDice();
	void	OpenRolltheDiceWindow() { this->Data[eRollMain].OnShow = true; };
	void	CloseRolltheDiceWindow() { this->Data[eRollMain].OnShow = false; };
	bool	CheckRolltheDiceWindow() { return this->Data[eRollMain].OnShow; };
	void	EventRolltheDice_Main(DWORD Event);
	int		DiceType;
	int		DiceNumber;
	float	DiceMoney;
	int		Dice1;
	int		Dice2;
	int		TotalPoint;
	int		LastBet;
	float	LastPay;
	int		LastGame;
	int		LastGame2;
	int		LastProfit;
	int		Winner;
	int		Balance;
	// --- Title System
	void	TitleSystem();
	void	OpenTitleSystemWindow() { this->Data[eTitle].OnShow = true; };
	void	CloseTitleSystemWindow() { this->Data[eTitle].OnShow = false; };
	bool	CheckTitleSystemWindow() { return this->Data[eTitle].OnShow; };
	void	EventTitleSystem_Main(DWORD Event);
	int		TitleCode;
	void	DrawTitleManagerButton();
	void	EventTitleManagerButton_Main(DWORD Event);
	// --- Heads Tails
	void	HeadsTails();
	void	OpenHeadsTailsWindow() { this->Data[eFlipMain].OnShow = true; };
	void	CloseHeadsTailsWindow() { this->Data[eFlipMain].OnShow = false; };
	bool	CheckHeadsTailsWindow() { return this->Data[eFlipMain].OnShow; };
	void	EventHeadsTails_Main(DWORD Event);
	int		HeadsTailsType;
	float	HeadsTailsMoney;
	int		HeadsTailsWiner;
	int		HeadsTailsLastGame;
	int		HeadsTailsLastBet;
	int		HeadsTailsProfit;
	// --- Lucky Number
	void	DrawLuckyNumber();
	void	OpenLuckyNumberWindow() { this->Data[eLuckyMain].OnShow = true; };
	void	CloseLuckyNumberWindow() { this->Data[eLuckyMain].OnShow = false; };
	bool	CheckLuckyNumberWindow() { return this->Data[eLuckyMain].OnShow; };
	void	EventLuckyNumber_Main(DWORD Event);
	int		LuckyLines;
	int		LuckyLastLines;
	int		LuckyNumber;
	int		LuckyWinPrice;
	int		LuckyNumber1[5];
	int		LuckyTicketID;
	char	LuckyDrawDate[128];
	//
	// ----
	void		DrawPartySettingsWindow();
	void		SwitchPartySettingsWindowState();
	bool		EventPartySettingsWindow_Main(DWORD Event);
	bool		EventPartySettingsWindow_Close(DWORD Event);
	bool		EventPartySettingsWindow_All(DWORD Event);
	void		ClosePartySettingsWindow() { this->Data[ePARTYSETTINGS_MAIN].OnShow = false; };
	// ----
	void		DrawPartySearchWindow();
	void		SwitchPartySearchWindowState() {(Data[ePARTYSEARCH_MAIN].OnShow == true)? Data[ePARTYSEARCH_MAIN].Close():Data[ePARTYSEARCH_MAIN].Open();};
	void		EventPartySearchWindow_All(DWORD Event);
	void		ClosePartySearchWindow() { this->Data[ePARTYSEARCH_MAIN].OnShow = false; };
	// ----
	void		DrawStatsAddWindow();
	void		EventStatsAddWindow(DWORD Event);
	void		EventStatsAddWindow_Close(DWORD Event);
	void		SwitchStatsWindowState() {(Data[eSTATSADD_MAIN].OnShow == true)? Data[eSTATSADD_MAIN].CloseAnimated(15) : Data[eSTATSADD_MAIN].Open(-226, 20);};
	void		CloseStatsAddWindow() { this->Data[eSTATSADD_MAIN].OnShow = false; };
	//
	void		DrawResetStatsWindow();
	void		EventResetStatsWindow(DWORD Event);
	void		EventResetStatsWindow_Close(DWORD Event);
	void		SwitchResetStatsWindowState() {(Data[eRESETSTATS_MAIN].OnShow == true)? Data[eRESETSTATS_MAIN].Close():Data[eRESETSTATS_MAIN].Open();};
	void		CloseResetStatsWindow() { this->Data[eRESETSTATS_MAIN].OnShow = false; };
	// ----
	void		DrawOffExpWindow();
	bool		EventOffExpWindow_Main(DWORD Event);
	void		SwitchOffExpWindoState() {(Data[eOFFEXP_MAIN].OnShow == true)? Data[eOFFEXP_MAIN].Close() : gOfflineMode.CGOfflineModeSend();};
	void		CloseOffExpWindow() { this->Data[eOFFEXP_MAIN].OnShow = false; };
	//
	void		EventCharacterWindow(DWORD Event);
	//
	void		DrawAccountSecurityPW();
	void		OpenAccountSecurityPWWindow() { this->Data[eSECURITY_CHECK_MAIN].OnShow = true; };
	void		CloseAccountSecurityPWWindow() { this->Data[eSECURITY_CHECK_MAIN].OnShow = false; };
	bool		CheckAccountSecurityPWWindow() { return this->Data[eSECURITY_CHECK_MAIN].OnShow; };
	void		AccountSecurityPWState(){(Data[eSECURITY_CHECK_MAIN].OnShow == true)? Data[eSECURITY_CHECK_MAIN].Close():Data[eSECURITY_CHECK_MAIN].Open();};
	void		EventAccountSecurityPW_Main(DWORD Event);
	//
	void		DrawAccountSecurity();
	void		OpenAccountSecurityWindow() { this->Data[eSECURITY_MAIN].OnShow = true; };
	void		CloseAccountSecurityWindow() { this->Data[eSECURITY_MAIN].OnShow = false; };
	bool		CheckAccountSecurityWindow() { return this->Data[eSECURITY_MAIN].OnShow; };
	void		AccountSecurityState(){(Data[eSECURITY_MAIN].OnShow == true)? Data[eSECURITY_MAIN].Close():Data[eSECURITY_MAIN].Open();};
	void		EventAccountSecurity_Main(DWORD Event);
	//
	static void SelectChar();
	void		EventSelectChar(DWORD Event);
	//
	void		DrawChangingClassWindow();
	void		ChangingClassWindowState(){(Data[eCHANGINGCLASS_MAIN].OnShow == true)? Data[eCHANGINGCLASS_MAIN].Close():Data[eCHANGINGCLASS_MAIN].Open();};
	void		EventChangingClassWindow_Main(DWORD Event);
	void		CloseChangingClassWindow() { this->Data[eCHANGINGCLASS_MAIN].OnShow = false; };
	//
	void		DrawVipWindow();
	void		BuyVipWindowState(){(Data[eVIP_MAIN].OnShow == true)? Data[eVIP_MAIN].Close():Data[eVIP_MAIN].Open();};
	void		EventVipWindow_Main(DWORD Event);\
	int			VipType;
	int			VipTime;
	void		CloseBuyVipWindow() { this->Data[eVIP_MAIN].OnShow = false; };
	//
	void		DrawRename();
	void		RenameState(){(Data[eRENAME_MAIN].OnShow == true)? Data[eRENAME_MAIN].Close():Data[eRENAME_MAIN].Open();};
	void		EventRename_Main(DWORD Event);
	void		CloseRenameWindow() { this->Data[eRENAME_MAIN].OnShow = false; };
	//
	void		DrawPSHOP();
	void		EventPSHOP_Main(DWORD Event);
	void		DrawPSHOP_OFFMODE();
	void		PSHOP_OFFMODE_STATE(){(Data[eOFFPANEL_MAIN].OnShow == true)? Data[eOFFPANEL_MAIN].Close():Data[eOFFPANEL_MAIN].Open();};
	void		EventPSHOP_OFFMODE(DWORD Event);
	void		ClosePShopWindow() { this->Data[eOFFPANEL_MAIN].OnShow = false; };
	DWORD		PShop;
	//
	void		DrawJewelsBank();
	void		JewelsBank_State(){(Data[eJewelsBank].OnShow == true)? Data[eJewelsBank].Close():Data[eJewelsBank].Open();};
	void		EventJewelsBank(DWORD Event);
	void		CloseJewelsBankWindow() { this->Data[eJewelsBank].OnShow = false; };
	int			JewelsType;
	//
	void		DrawRPS();
	void		EventRPS_Main(DWORD Event);
	//
	void		DrawNewsWindow();
	bool		EventNewsWindow_Main(DWORD Event);
	bool		EventNewsWindow_Close(DWORD Event);
	bool		EventNewsWindow_Back(DWORD Event);
	void		CloseNewsWindow() { this->Data[eNEWS_MAIN].OnShow = false; };
	//
	void		DrawFruit();
	void		EventFruitWindow_Main(DWORD Event);
	void		Fruit_State(){(Data[eFruitMain].OnShow == true)? Data[eFruitMain].Close():Data[eFruitMain].Open();};
	void		CloseFruitWindow() { this->Data[eFruitMain].OnShow = false; };
	//
	void		DrawAttention();
	//
	void		DrawGiftCode();
	void		GiftCodeState(){(Data[eGIFTCODE_MAIN].OnShow == true)? Data[eGIFTCODE_MAIN].Close():Data[eGIFTCODE_MAIN].Open();};
	void		EventGiftCode_Main(DWORD Event);
	void		CloseGiftCodeWindow() { this->Data[eGIFTCODE_MAIN].OnShow = false; };
	//
	void		DrawEventTableWindow();
	void		EventEventTableWindow(DWORD Event);
	void		CloseEventTableWindow() { this->Data[eEVENTTABLE_MAIN].OnShow = false; };
	//
	void		DrawWarehouseUI();
	void		EventWarehouseUI(DWORD Event);
	void		CloseWarehouseWindow() { this->Data[eWAREHOUSE_MAIN].OnShow = false; };
	//
	//bool		ControlTextBox(KBDLLHOOKSTRUCT Hook);
	void		ControlTextBox(DWORD Event);
	/*
	void	DrawSmithItem();
	void	OpenSmithItemWindow() { this->Data[eSMITH_MAIN].OnShow = true; };
	void	CloseSmithItemWindow() { this->Data[eSMITH_MAIN].OnShow = false; };
	bool	CheckSmithItemWindow() { return this->Data[eSMITH_MAIN].OnShow; };
	void	EventSmithItem_Main(DWORD Event);
	*/
	void	DrawUsersPanel();
	void	EventUsersPanel(DWORD Event);
	void	DrawMiniMap();
	void	EventMiniMap(DWORD Event);
	void	Minimap_State(){(showMiniMap == true)? showMiniMap = false:showMiniMap=true;};
	bool	MiniMapCheck();
	bool    showMiniMap;
	//
	void	HUDEvent();
	//-----
	int DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...);
	void DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color);
	bool		CombinedChecks();
	bool		CheckWindow(int WindowID);
	int			CloseWindow(int WindowID);
	int			OpenWindow(int WindowID);
	
	/*---------------*/
	static void Work2();
    static void DrawChat ( int mode, char* character, char* message );
    static void DrawItemToolTipText ( void * item, int x, int y );
    void * item_post_;
    DWORD last_tickcount_view_;
	/*---------------*/
	// ---
	static bool	AllowGUI();
	int		CDrawText(int x, int y,  BYTE *Color,  BYTE * BgColor, int width, LPINT align, LPCSTR Text,...);
	void	SetTextColor(BYTE Red,BYTE Green,BYTE Blue,BYTE Opacity);
	int		DrawFormat(DWORD Color, int PosX, int PosY,int Width, int Align, LPCSTR Text, ...);
	void	DrawGUI(short ObjectID, float X, float Y);
	int		DrawMessage(int Mode, LPCSTR Text, ...);
	void	DrawBarForm(float PosX,float PosY,float Width,float Height,GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void	DrawCheckLineEx(bool isChecked, int PointID, int CheckID, int LineID, float X, float Y, DWORD Color, char* Text);
	void	DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void	DrawImage(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void	DrawImage10(short ObjectID, float PosX, float PosY);
	void	DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	int		DrawFormat_Ex(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	float	DrawRepeatGUI(short ObjectID, float X, float Y, int Count);
	float	DrawRepeatGUIX(short ObjectID, float X, float Y, int Count);
	void	DrawAnimatedGUI(short ObjectID, float PosX, float PosY);
	void	DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
	int		DrawToolTip(int X, int Y, LPCSTR Text, ...);
	void	PartUPandDNEx(int PointID, int UpID, int DownID, int LineID, float X, float Y, DWORD Color, int Value, char* Text);
	void	MiniButtonDraw(int BtnID, float X, float Y, bool isHover, char* Text);
	void	DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void	DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color);
	static int		LoadImg(char * Folder,DWORD ID);
	static void DrawCSServer(BYTE Red, BYTE Green, BYTE Blue, BYTE Opacity);
	bool		ButtonEx(DWORD Event, int ButtonID, bool Type);
	//bool		IsWorkZone(short ObjectID);
	bool		IsWorkZone2(short ObjectID);
	bool		IsWorkZone(float X, float Y, float MaxX, float MaxY);
	float		GetResizeX(short ObjectID);
	static void	DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, float a8, char a9);
	static void DrawItem2(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);
	bool CheckWindowEx(int WindowID);
	void		OpenWindowEx(int WindowID);
	void		CloseWindowEx(int WindowID);
	void TextDraw(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...);
	void DrawMessageBox(LPCSTR Text, ...);
	bool CursorZoneButton(float X, float Y, float MaxX, float MaxY);
	void PartyInterface();
	void EventPartyInterface(DWORD Event);
	//--
	BYTE m_SettingButton;
	BYTE m_RolltheDiceButton;
	BYTE m_HeadsTailsButton;
	BYTE m_LuckyNumberButton;
	BYTE m_SmithItemButton;
	BYTE m_TitleManagerButton;
	BYTE m_PartySearchSettingButton;
	BYTE m_OffAttackButton;
	BYTE m_BuyVipButton;
	BYTE m_ChangeClassButton;
	BYTE m_ResetPointCheckBox;
	BYTE m_ResetPointCheckBox1;
	BYTE m_ResetMasterSkillCheckBox;
	BYTE m_ResetMasterSkillCheckBox1;
	BYTE m_AccountSecurityButton;
	BYTE m_JewelsBankButton;
	BYTE m_RenameButton;
	BYTE m_TopPlayer;
	BYTE m_PShopCurrency;
	BYTE m_PShopOffStore;
	BYTE m_RPSMode;
	BYTE m_NewsBoard;
	BYTE m_FruitMain;
	BYTE m_LuckySpinMain;
	BYTE m_GiftCode;
	BYTE m_PSBless;
	BYTE m_PSSoul;
	BYTE m_PSChaos;
	BYTE m_PSWcoinC;
	BYTE m_PSWcoinP;
	BYTE m_PSWcoinG;
	BYTE m_QuickAdd;
	BYTE m_ResetStats;
	BYTE m_EventTimer;
	BYTE m_CustomWare;
	BYTE m_PartyLeader;
	BYTE m_PartyTrace;
	//--
	int m_CharacterPage;
	//
	long long m_TimeDiff;
	InterfaceObject Data[MAX_OBJECT];
private:
};

extern Interface gInterface;
