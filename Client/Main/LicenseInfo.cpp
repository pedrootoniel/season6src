#include "stdafx.h"
#include "LicenseInfo.h"
#include <time.h>
CLicenseInfo gLicenseInfo;

CLicenseInfo::CLicenseInfo()
{
	this->m_buff = 0;
	this->m_size = 0;

	this->m_file = INVALID_HANDLE_VALUE;

	memset(this->m_name,0,sizeof(this->m_name));

	srand((unsigned int)time(0));
}

CLicenseInfo::~CLicenseInfo()
{
}

bool CLicenseInfo::SetBuffer(char* filename)
{
	if(this->m_buff != 0)
	{
		delete[] this->m_buff;
		this->m_buff = 0;
	}

	HANDLE file = CreateFile(filename,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	this->m_size = GetFileSize(file,0);

	this->m_buff = new unsigned char[this->m_size];

	if(this->m_buff == 0)
	{
		return 0;
	}

	DWORD BytesRead = 0;

	if(ReadFile(file,this->m_buff,this->m_size,&BytesRead,NULL) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	return 1;
}

bool CLicenseInfo::CheckSumLoad(char* filename)
{
	if(this->SetBuffer(filename) == 0)
	{
		return 0;
	}

	int n;

	memcpy(&this->WindowName,&this->m_buff[0],32);
	memcpy(&this->ScreenShot,&this->m_buff[32],128);
	memcpy(&this->ServerIP,&this->m_buff[160],15);
	memcpy(&this->Login,&this->m_buff[175],31);
	memcpy(&this->Instances,&this->m_buff[190],1);
	memcpy(&this->CSPortChar,&this->m_buff[191],5);
	memcpy(&this->RFbt,&this->m_buff[196],1);
	memcpy(&this->Serial,&this->m_buff[197],16);
	memcpy(&this->MainCRCchar,&this->m_buff[213],8);

	for(n=0; n < 32; n++)
	{
		this->WindowName[n] ^= 0xD6;
	}

	for(n=0; n < 128; n++)
	{
		this->ScreenShot[n] ^= 0xC3;
	}

	for(n=0; n < 15; n++)
	{
		this->ServerIP[n] ^= 0xB1;
	}

	for(n=0; n < 15; n++)
	{
		this->Login[n] ^= 0xA8;
	}

	this->Instances[0] ^= 0x65;

	for(n=0; n < 5; n++)
	{
		this->CSPortChar[n] ^= 0x91;
	}
	this->CSPort = atoi(this->CSPortChar);

	this->RFbt[0] ^= 0x73;

	for(n=0; n < 17; n++)
	{
		this->Serial[n] ^= 0xA9;
	}

	for(n=0; n < 8; n++)
	{
		this->MainCRCchar[n] ^= 0xD3;
	}

	//this->MainCRC = strtoul(this->MainCRCchar,NULL,16);

	return 1;
}