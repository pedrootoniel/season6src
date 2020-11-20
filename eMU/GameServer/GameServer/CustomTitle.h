#include "user.h"
#include "Protocol.h"

// -------------------------------------------------------------------------------
#define MAX_RANK 20

struct DANHHIEU_GD_SAVE_DATA
{
	PSBMSG_HEAD header;
	// ----
	WORD	index;
	char	Name[11];
	int		RankSlot1;
	int		RankTitle1;
	int		RankTitle2;
	int		RankTitle3;
	int		RankTitle4;
	int		RankTitle5;
	int		RankTitle6;
	int		RankTitle7;
	int		RankTitle8;
	int		RankTitle9;
	int		RankTitle10;
	int		RankTitle11;
	int		RankTitle12;
	int		RankTitle13;
	int		RankTitle14;
	int		RankTitle15;
	int		RankTitle16;
	int		RankTitle17;
	int		RankTitle18;
	int		RankTitle19;
	int		RankTitle20;
};

// -------------------------------------------------------------------------------
struct DANHHIEU_GD_REQ_DATA
{
	PSBMSG_HEAD	header;
	WORD index;
	char name[11];
};
// -------------------------------------------------------------------------------


struct DANHHIEU_DG_GET_DATA
{
	PSBMSG_HEAD	header;
	// ----
	WORD	index;
	int		RankSlot1;
	int		RankTitle1;
	int		RankTitle2;
	int		RankTitle3;
	int		RankTitle4;
	int		RankTitle5;
	int		RankTitle6;
	int		RankTitle7;
	int		RankTitle8;
	int		RankTitle9;
	int		RankTitle10;
	int		RankTitle11;
	int		RankTitle12;
	int		RankTitle13;
	int		RankTitle14;
	int		RankTitle15;
	int		RankTitle16;
	int		RankTitle17;
	int		RankTitle18;
	int		RankTitle19;
	int		RankTitle20;
};

// -------------------------------------------------------------------------------
struct ACTIVE_TITLE_REQ
{
	PSBMSG_HEAD h;
	int			Type;
	int			Number;
};
// -------------------------------------------------------------------------------
struct DEACTIVE_TITLE_REQ
{
	PSBMSG_HEAD h;
};
// -------------------------------------------------------------------------------
struct BUY_TITLE_REQ
{
	PSBMSG_HEAD h;
	int			Number;
};
// -------------------------------------------------------------------------------
struct TITLE_OPTION_DATA
{
	int			Index;
	int			Price;
	int			AddHP;
	int			AddMP;
};
// -------------------------------------------------------------------------------
class DanhHieu
{
public:
	// ----
	void		Init();
	DanhHieu();
	virtual ~DanhHieu();
	void		Load(char* path);
	void		SetInfo(TITLE_OPTION_DATA info);
	void		GDSaveData(int aIndex);
	void		GDReqData(int aIndex);
	void		GDSaveUserInfo(int aIndex);
	void		GDReqUserInfo(int aIndex);
	void		DGGetData(DANHHIEU_DG_GET_DATA * aRecv);
	void		ActiveTitle(LPOBJ lpUser, ACTIVE_TITLE_REQ *aRecv);
	void		Deactive(LPOBJ lpUser);
	void		BuyTitle(LPOBJ lpUser, BUY_TITLE_REQ *aRecv);
	void		TitleOption(LPOBJ lpObj, bool flag);
	// ----
	// ----
	TITLE_OPTION_DATA m_OptionTitle[MAX_RANK];
	DANHHIEU_GD_REQ_DATA Title;
	// ----
}; extern DanhHieu gDanhHieu;
// -------------------------------------------------------------------------------