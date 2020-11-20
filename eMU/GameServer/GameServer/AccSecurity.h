#include "user.h"
#include "Protocol.h"

struct ACC_SECURITY_REQ
{
	PSBMSG_HEAD	header;
	WORD index;
	char account[11];
};

struct ACC_SECURITY_DATA
{
	PSBMSG_HEAD header;
	// ----
	WORD index;
	int SecurityPass;
	BYTE SecurityLock;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct ACC_SECURITY_DATA_SAVE
{
	PSBMSG_HEAD header;
	// ----
	WORD index;
	char account[11];
	BYTE SecurityLock;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct PMSG_ACCOUNT_SECURITY_RECV
{
	PSBMSG_HEAD header;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct PMSG_SECURITY_PW_RECV
{
	PSBMSG_HEAD header;
	int	SecretNumber;
};


class cAccSecurity
{
public:
	// ----
	cAccSecurity();
	virtual ~cAccSecurity();
	void	GDSaveData(int aIndex);
	void	GDReqData(int aIndex);
	void	SecurityData(ACC_SECURITY_DATA * aRecv);
	void	gObjAccountSecurityPW(PMSG_SECURITY_PW_RECV* lpMsg, int aIndex);
	void	gObjAccountSecuritySave(PMSG_ACCOUNT_SECURITY_RECV* aRecv,int index);
	// ----
	// ----
}; extern cAccSecurity gAccSecurity;
// -------------------------------------------------------------------------------