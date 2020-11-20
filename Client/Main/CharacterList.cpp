#include "stdafx.h"
#include "CharacterList.h"


cCharacterList gCharacterList;

void cCharacterList::ClearCharacterList()
{
	for(int i=0;i<25;i++)
	{
		CharList[i].Exist = 0;
		memset(CharList[i].Name, 0, sizeof(CharList[i].Name));
		CharList[i].Reset = -1;
	}
}

void cCharacterList::SetList(PMSG_CHARACTER_INFO_DATA* lpMsg)
{
	this->ClearCharacterList();

	for (int n=0;n<lpMsg->Count;n++)
	{
		PMSG_CHARACTER_INFO* lpInfo = (PMSG_CHARACTER_INFO*)(((BYTE*)lpMsg)+sizeof(PMSG_CHARACTER_INFO_DATA)+(sizeof(PMSG_CHARACTER_INFO)*n));

		this->CharList[n].Exist = 1;

		memcpy(CharList[n].Name, lpInfo->Name, sizeof(lpInfo->Name));

		this->CharList[n].Reset = lpInfo->Reset;

		////console.Log("","Name = %s",this->CharList[n].Name);
	}
}

int cCharacterList::GetResetByName(char* Name)
{
	for(int i=0;i<25;i++)
	{
		if (this->CharList[i].Exist != 1)
		{
			continue;
		}

		if (_stricmp(this->CharList[i].Name,Name) == 0)
		{
			return this->CharList[i].Reset; 
		}
	}

	return 0;
}

void cCharacterList::GetInfo(char* Name, int *Reset)
{
	for(int i=0;i<25;i++)
	{
		if (this->CharList[i].Exist != 1)
		{
			continue;
		}

		////console.Log("","GR = %d",CharList[i].GReset);
		if (_stricmp(this->CharList[i].Name,Name) == 0)
		{
			//return this->CharList[i].GReset; 
			*Reset = this->CharList[i].Reset;
		}
	}
}
