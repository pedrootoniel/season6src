// CustomItem.cpp: implementation of the CCustomSmith class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CSmithItem.h"
#include "MemScript.h"
#ifdef NOLOAD
CCustomSmith gCustomSmith;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomSmith::CCustomSmith() // OK
{
	this->Init();
}

CCustomSmith::~CCustomSmith() // OK
{

}

void CCustomSmith::Init() // OK
{
	for(int n=0;n < MAX_SMITH_ITEM;n++)
	{
		this->m_SmithSwordInfo[n].ItemIndex = -1;
		this->m_SmithAxeInfo[n].ItemIndex = -1;
		this->m_SmithMaceInfo[n].ItemIndex = -1;
		this->m_SmithSpearInfo[n].ItemIndex = -1;
		this->m_SmithBowInfo[n].ItemIndex = -1;
		this->m_SmithStaffInfo[n].ItemIndex = -1;
		this->m_SmithShieldInfo[n].ItemIndex = -1;
		this->m_SmithHelmInfo[n].ItemIndex = -1;
		this->m_SmithArmorInfo[n].ItemIndex = -1;
		this->m_SmithPantInfo[n].ItemIndex = -1;
		this->m_SmithGloveInfo[n].ItemIndex = -1;
		this->m_SmithBootInfo[n].ItemIndex = -1;
	}
}

void CCustomSmith::Load(char* path) // OK
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

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoSword(info);
				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoAxe(info);
				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoMace(info);
				}
				else if(section == 3)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoSpear(info);
				}
				else if(section == 4)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoBow(info);
				}
				else if(section == 5)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoStaff(info);
				}				
				else if(section == 6)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoShield(info);
				}
				else if(section == 7)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoHelm(info);
				}
				else if(section == 8)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoArmor(info);
				}
				else if(section == 9)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoPant(info);
				}
				else if(section == 10)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoGlove(info);
				}
				else if(section == 11)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_SMITH_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Price1Days = lpMemScript->GetAsNumber();

					info.Price7Days = lpMemScript->GetAsNumber();

					info.Price30Days = lpMemScript->GetAsNumber();

					strcpy_s(info.ItemName,lpMemScript->GetAsString());

					this->SetInfoBoot(info);
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

void CCustomSmith::SetInfoSword(CUSTOM_SMITH_INFO info) // Sword
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithSwordInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoAxe(CUSTOM_SMITH_INFO info) // Axe
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithAxeInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoMace(CUSTOM_SMITH_INFO info) // Mace
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithMaceInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoSpear(CUSTOM_SMITH_INFO info) // Spear
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithSpearInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoBow(CUSTOM_SMITH_INFO info) // Bow
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithBowInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoStaff(CUSTOM_SMITH_INFO info) // Staff
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithStaffInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoShield(CUSTOM_SMITH_INFO info) // Shield
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithShieldInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoHelm(CUSTOM_SMITH_INFO info) // Helm
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithHelmInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoArmor(CUSTOM_SMITH_INFO info) // Armor
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithArmorInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoPant(CUSTOM_SMITH_INFO info) // Pant
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithPantInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoGlove(CUSTOM_SMITH_INFO info) // Glove
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithGloveInfo[info.ItemIndex] = info;
}
void CCustomSmith::SetInfoBoot(CUSTOM_SMITH_INFO info) // Boot
{
	if(info.ItemIndex < 0 || info.ItemIndex >= MAX_SMITH_ITEM)
	{
		return;
	}

	this->m_SmithBootInfo[info.ItemIndex] = info;
}
#endif