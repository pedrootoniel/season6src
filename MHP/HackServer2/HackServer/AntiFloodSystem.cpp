#include "stdafx.h"
#include "MemScript.h"
#include "AntiFloodSystem.h"
#include "SocketManager.h"
#include "ClientManager.h"
#include "HackServerProtocol.h"
#include "IpManager.h"
#include "Util.h"

CAntiFlood gAntiFlood;


void CAntiFlood::Initialize(LPSTR filename)
{
	strcpy(this->filename, filename);

	CMemScript* lpScript = new CMemScript;

	if(lpScript == 0)
	{
		return;
	}

	if(lpScript->SetBuffer(filename,0) == 0)
	{
		delete lpScript;
		return;
	}

	this->BLSize = 0;
	//memcpy(this->BlackListIP, 0, sizeof(this->BlackListIP));

	try
	{
		while(true)
		{
			if(lpScript->GetToken() == 2)
			{
				break;
			}

			int section = lpScript->GetNumber();

			while(true)
			{
				if(lpScript->GetToken() == 2)
				{
					break;
				}

				if(strcmp("end",lpScript->GetString()) == 0)
				{
					break;
				}

				if(section == 0)
				{
					this->Enabled			= lpScript->GetNumber();
					this->IsAutoAdd			= lpScript->GetAsNumber();
					this->MaxIPConnection	= lpScript->GetAsNumber();
					this->AutoCloseFloodCon	=  lpScript->GetAsNumber();
				}
				else if(section == 1)
				{
					if(this->AddToBlackList(lpScript->GetString()) == false)
					{
						ErrorMessageBox("error-L3 : Max IP count in BlackList reached!");
						break;
					}
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;

	LogAdd(LOG_BLUE, "[ServerInfo] AntiFlood Loaded Successfull!");
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

	for (int n=0;n<MAX_CLIENT; n++)
	{
		if ( gClientManager[n].m_state >= CLIENT_ONLINE)
		{
			if ( strcmp(&gClientManager[n].m_IpAddr[0] , IP) == 0)
			{
				Count++;
			}
		}
	}
	return Count;
}

void CAntiFlood::AutoClose(char * IP)
{
	for (int n=1;n<MAX_CLIENT; n++)
	{
		if ( gClientManager[n].m_state >= CLIENT_ONLINE)
		{
			if ( strcmp(&gClientManager[n].m_IpAddr[0] , IP) == 0)
			{
				LogAdd(LOG_RED,"[AntiFlood] Close Index: %d",n);
				gSocketManager.Disconnect(n);
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
			LogAdd(LOG_BLACK,"[Anti Flood] Rejected IP %s",IP);
			return false;
		}

		if(this->MaxIPConnection < gIpManager.GetIpCount(IP))//this->GetIPCount(IP))
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
						LogAdd(LOG_BLACK, "[AntiFlood] Fail to Add IP on BlockList File");
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