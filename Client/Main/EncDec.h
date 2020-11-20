#ifndef ENCDEC_H
#define ENCDEC_H

class CEncDec {
public:
	DWORD __fastcall ComputeCRC(BYTE* data, int size);
	DWORD __fastcall ComputeFileCRC(char* file);
};
extern CEncDec* g_EncDec;
#endif