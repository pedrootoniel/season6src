// CustomJewel.cpp: implementation of the CCustomJewel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomTitle.h"
#include "MemScript.h"

cCustomTitle gCustomTitle;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cCustomTitle::cCustomTitle() // OK
{
	this->Init();
}

cCustomTitle::~cCustomTitle() // OK
{

}

void cCustomTitle::Init() // OK
{
	for(int n=0;n < MAX_RANK_TITLE;n++)
	{
		this->m_CustomTitle[n].Index = -1;
	}
}

void cCustomTitle::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

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
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					TITLE_STRUCT info;

					memset(&info,0,sizeof(info));
					static int CustomTitleIndexCount = 0;
					info.Index	=	CustomTitleIndexCount++;
					info.TitleCode	=	lpMemScript->GetNumber();
					strcpy_s(info.ImgDir,lpMemScript->GetAsString());
					strcpy_s(info.TitleText,lpMemScript->GetAsString());
					info.ImgCode	=	lpMemScript->GetAsNumber();
					info.width	=	lpMemScript->GetAsFloatNumber();
					info.height	=	lpMemScript->GetAsFloatNumber();
					info.color	=	lpMemScript->GetAsNumber();
					info.AddHP	=	lpMemScript->GetAsNumber();
					info.AddMP	=	lpMemScript->GetAsNumber();
					this->SetInfo(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void cCustomTitle::SetInfo(TITLE_STRUCT info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_RANK_TITLE)
	{
		return;
	}

	this->m_CustomTitle[info.Index] = info;
}

TITLE_STRUCT* cCustomTitle::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_RANK_TITLE)
	{
		return 0;
	}

	return &this->m_CustomTitle[index];
}

