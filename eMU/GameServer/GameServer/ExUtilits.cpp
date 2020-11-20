#include "StdAfx.h"

int ExcOpt(int amount)
{
	if (amount > 6) amount = 6;
	if (amount < 1) amount = 1;

	srand(time(NULL));

	amount = rand() % amount + 1;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	int opt_done[6] = { 0 };

	for(int n=0; n < amount; n++)
	{
		int SearchExc = 0;

		srand(time(NULL));

		if( n == 0 )
		{
			SearchExc = opt_db[rand()%6];
			opt_done[n] = SearchExc;
		}
		else
		{
			while(true)
			{
				SearchExc = opt_db[rand()%6];
				bool bOpt = true;

				for(int i=0; i<amount; i++)
				{
					if(SearchExc == opt_done[i])
					{
						bOpt = false;
					}
				}

				if(bOpt == true)
				{
					opt_done[n] = SearchExc;
					break;
				}
			}
		}

		exc += SearchExc;
	}

	return exc;
}

bool Ex_IsBadFileLine(char *FileLine, int *Flag)
{
	if(*Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			*Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(*Flag < 0 || *Flag > 9)
	{
		*Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		*Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}

int Ex_GetInt(int Min, int Max, int Default, LPCTSTR BlockName, LPCTSTR ConfigName, LPCSTR FolderName)
{
	int Result;

	WIN32_FIND_DATAA wfd;
	if (FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{
		char errorStr[256];
		sprintf(errorStr, "Can't find %s config file!\n Taken default value in [%s] section for %s = %d", FolderName, BlockName, ConfigName, Default);
		MessageBox(NULL, errorStr, "Configs error", MB_OK | MB_ICONERROR);
		Result = Default;
	}
	else
		Result = GetPrivateProfileInt(BlockName, ConfigName, -100500, FolderName);

	if (Result == -100500)
	{
		char errorStr[256];
		sprintf(errorStr, "In %s file [%s] section can't find %s config line!\n Taken default value %d", FolderName, BlockName, ConfigName, Default);
		MessageBox(NULL, errorStr, "Configs error", MB_OK | MB_ICONERROR);
		Result = Default;
	}

	if (Result < Min || Result > Max)
	{
		char errorStr[256];
		sprintf(errorStr, "In %s file [%s] section, %s config is out of range!\nMin = %d Max = %d\tTaken default value %d", FolderName, BlockName, ConfigName, Min, Max, Default);
		MessageBox(NULL, errorStr, "Configs error", MB_OK | MB_ICONERROR);
		Result = Default;
	}
	return Result;
}

int GetNumberByPercent(int Proc, int Min, int Max)
{
	int Random = rand() % 100;

	if (Proc == 0 || Max == Min)
	{
		return Min;
	}

	if (Random <= Proc)
	{
		return Max;
	}
	if (Proc > 50)
	{
		return GetNumberByPercent(Proc / 2, Min, Max - 1);
	}
	else if (Proc < 30)
	{
		return GetNumberByPercent(Proc * 3 / 2, Min, Max - 1);
	}
	else
	{
		return GetNumberByPercent(Proc, Min, Max - 1);
	}
}