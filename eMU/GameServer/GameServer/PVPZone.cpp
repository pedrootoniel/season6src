#include "stdafx.h"
#include "PVPZone.h"
#include "MemScript.h"
#include "Util.h"

cPVPZone gPVPZone;

cPVPZone::cPVPZone()
{
	this->m_PvpZone.clear();
}

cPVPZone::~cPVPZone()
{
	
}

void cPVPZone::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	//int index = 0;

	this->m_PvpZone.clear();

	try
	{
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

			PVPZONE_DATA info;

			//info.Index = index;

			info.Map = lpMemScript->GetNumber();

			info.X1 = lpMemScript->GetAsNumber();

			info.Y1 = lpMemScript->GetAsNumber();

			info.X2 = lpMemScript->GetAsNumber();

			info.Y2 = lpMemScript->GetAsNumber();

			this->m_PvpZone.push_back(info);

			//index++;
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool cPVPZone::IsPVPZone(LPOBJ lpObj)
{
	for(std::vector<PVPZONE_DATA>::iterator it=this->m_PvpZone.begin();it != this->m_PvpZone.end();it++)
	{
		if (lpObj->Map == it->Map)
		{
			if((lpObj->X >= it->X1 && lpObj->X <= it->X2)
				&&(lpObj->Y >= it->Y1 && lpObj->Y <= it->Y2) )
			{
				return true;
			}
		}
	}
	return false;
}