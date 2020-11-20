#include "stdafx.h"
#include "EncDec.h"
#pragma optimize("g", on)

CEncDec* g_EncDec = new CEncDec;

DWORD __fastcall CEncDec::ComputeCRC(BYTE* data, int size)
{
	int crc, i;

	crc = 0;

	BYTE* ptr = data;
	int count = size;

	while(--count >= 0)
	{
		crc = crc ^ (int)*ptr++ << 8;
		for(i = 0; i < 8; ++i)
			if(crc & 0x8000)
				crc = crc << 1 ^ 0x10213465;
			else
				crc = crc << 1;
	}

	return (crc & 0xFFFFFFFF);
}

DWORD __fastcall CEncDec::ComputeFileCRC(char* file)
{
	FILE* hFile = fopen(file, "rb");

	if(!hFile)
		return 0;

	fseek(hFile, 0, SEEK_END);
	long size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	BYTE* buff = new BYTE[size];
	fread(buff, 1, size, hFile);

	DWORD crc = ComputeCRC(buff, size);

	fclose(hFile);
	delete [] buff;

	return crc;
}
#pragma optimize("g", off)