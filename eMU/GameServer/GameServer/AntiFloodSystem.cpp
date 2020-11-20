#include "stdafx.h"
#include "Log.h"
#include "User.h"
#include "LogToFile.h"
#include "MemScript.h"
#include "AntiFloodSystem.h"
#include "GameMain.h"
#include "Util.h"
CAntiFlood gAntiFlood;


void CAntiFlood::Initialize(LPSTR filename)
{
	strcpy(this->filename, filename);

	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		return;
	}

	if(lpMemScript->SetBuffer(filename) == 0)
	{
		MsgBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->BLSize = 0;
	//memcpy(this->BlackListIP, 0, sizeof(this->BlackListIP));

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(lpMemScript->GetToken() == TOKEN_END)
				{
					break;
				}

				if(strcmp("end",lpMemScript->GetString()) == 0)
				{
					break;
				}

				if(section == 0)
				{
					this->Enabled			= lpMemScript->GetNumber();
					this->IsAutoAdd			= lpMemScript->GetAsNumber();
					this->MaxIPConnection	= lpMemScript->GetAsNumber();
					this->AutoCloseFloodCon	=  lpMemScript->GetAsNumber();
				}
				else if(section == 1)
				{
					if(this->AddToBlackList(lpMemScript->GetString()) == false)
					{
						MsgBox("error-L3 : Max IP count in BlackList reached!");
						break;
					}
				}
			}
		}
	}
	catch(...)
	{
		MsgBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;

	LogAdd(LOG_BLUE, "[AntiFlood] File Loaded Successfull!");
}

void CAntiFlood::BlackListClean()
{
	for(int i=0;i<=MAXIPINBLACKLIST;i++)
	{
		memset(this->BlackListIP[i],0,sizeof(this->BlackListIP[i])-1);
	}
}

int CAntiFlood::GetIPCount(char * IP)
{
	int Count = 0;

	for (int n=OBJECT_START_USER;n<MAX_OBJECT; n++)
	{
		if ( gObj[n].Connected >= OBJECT_CONNECTED)
		{
			if ( strcmp(&gObj[n].IpAddr[0] , IP) == 0)
			{
				Count++;
			}
		}
	}
	return Count;
}

void CAntiFlood::AutoClose(char * IP)
{
	for (int n=OBJECT_START_USER;n<MAX_OBJECT; n++)
	{
		if ( gObj[n].Connected >= OBJECT_CONNECTED)
		{
			if ( strcmp(&gObj[n].IpAddr[0] , IP) == 0)
			{
				LogAdd(LOG_RED,"[AntiFlood] Close Index: %d",n);
				CloseClient(n);
			}
		}
	}
}

bool CAntiFlood::Check(char * IP)
{
	if(this->Enabled == TRUE)
	{
		if(this->BL_IPCheck(IP) == false)
		{
			LogAdd(LOG_RED,"[AntiFlood]BlackList Rejected IP %s",IP);
			return false;
		}

		if(this->MaxIPConnection < this->GetIPCount(IP))
		{
			if(this->IsAutoAdd == 1)
			{
				if(this->AddToBlackList(IP) == true)
				{
					FILE *f;
					f = fopen (this->filename,"a+");
					char Print[255]={0};
					wsprintf(Print,"\n\"%s\"", IP);

					if (fputs (Print,f) == EOF) 
					{
						LogAdd(LOG_RED, "[AntiFlood] Fail to Add IP on BlockList File");
					}

					fclose (f);

					LogAdd(LOG_RED,"[AntiFlood] IP: %s Added to Black List - Flood Attempt: %d",IP,this->MaxIPConnection);
				}
				else
				{
					LogAdd(LOG_RED,"[AntiFlood][BLACKLIST FULL] IP: %s Fail Add to Black List - Flood Attempt: %d",IP,this->MaxIPConnection);
				}
				if(this->AutoCloseFloodCon == 1)
				{
					this->AutoClose(IP);
				}
			}
			return false;
		}
	}
	return true;
}

bool CAntiFlood::BL_IPCheck(char * IP)
{
	for(int i=0;i<this->BLSize;i++)
		if(this->BlackListIP[i][0] != 0)
			if(!stricmp(IP,this->BlackListIP[i]))
				return false;
	return true;
}

bool CAntiFlood::AddToBlackList(LPSTR IP)
{
	if(this->BLSize >= MAXIPINBLACKLIST)
	{
		return false;
	}

	strcpy(this->BlackListIP[this->BLSize],IP);
	this->BLSize++;
	return true;
}