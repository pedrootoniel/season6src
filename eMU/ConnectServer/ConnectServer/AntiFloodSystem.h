#include "stdafx.h"

#define MAXIPINBLACKLIST	10000

class CAntiFlood
{
public:
	void Initialize(LPSTR filename);
	bool Check(char * IP);
	bool AddToBlackList(LPSTR IP);
private:
	void BlackListClean();
	void AutoClose(char * IP);

	bool BL_IPCheck(char * IP);
	int GetIPCount(char * IP);

	BOOL Enabled;
	BOOL IsAutoAdd;
	BOOL AutoCloseFloodCon;
	int BLSize;
	int MaxIPConnection;
	char BlackListIP[MAXIPINBLACKLIST][16];
	char filename[255];
};

extern CAntiFlood gAntiFlood;