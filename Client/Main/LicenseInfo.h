#if !defined(AFX_PROTECT_H__04E9C13E_0D16_4A91_9FE4_463097AA5336__INCLUDED_)
#define AFX_PROTECT_H__04E9C13E_0D16_4A91_9FE4_463097AA5336__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLicenseInfo
{
public:
	CLicenseInfo();
	virtual ~CLicenseInfo();

	bool SetBuffer(char* filename);

	bool CheckSumLoad(char* filename);

	bool CreateTempFile();
	void DeleteTempFile();
	char* GetTempFilePath();

	bool DecryptBMD(char* filename);

	char Instances[2];
	char Login[16];
	char ServerIP[16];
	char ScreenShot[129];
	char WindowName[33];
	char CSPortChar[5];
	WORD CSPort;
	char RFbt[3];
	char Serial[17];
	char MainCRCchar[9];
	DWORD MainCRC;

private:
	DWORD m_size;
	BYTE* m_buff;
	BYTE m_XorTable[21];
	HANDLE m_file;
	char m_name[64];
};

extern CLicenseInfo gLicenseInfo;

#endif // !defined(AFX_PROTECT_H__04E9C13E_0D16_4A91_9FE4_463097AA5336__INCLUDED_)