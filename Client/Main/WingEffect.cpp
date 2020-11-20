#include "stdafx.h"
#include "Item.h"
#include "WingEffect.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "Object.h"


WingEffect gWingEffect;

DWORD	AddWingsEffect_Buff;
//float	Color[3];
vec3_t Color;
vec3_t Bone;
LPVOID	F1_This;
DWORD	F1_Arg1;
DWORD	F1_Arg11;
DWORD	F1_Arg2;
DWORD	F2_Arg5;
DWORD	F3_Arg3;
//
LPVOID  F1_Thisv1;
DWORD   F1_Arg1v1;
DWORD   F1_Arg11v1;
DWORD   F1_Arg2v1;
DWORD   F2_Arg5v1;
DWORD   F3_Arg3v1;
//
LPVOID  F1_Thisv2;
DWORD   F1_Arg1v2;
DWORD   F1_Arg11v2;
DWORD   F1_Arg2v2;
DWORD   F2_Arg5v2;
DWORD   F3_Arg3v2;
//
LPVOID  F1_Thisv3;
DWORD   F1_Arg1v3;
DWORD   F1_Arg11v3;
DWORD   F1_Arg2v3;
DWORD   F2_Arg5v3;
DWORD   F3_Arg3v3;
//
LPVOID  F1_Thisv4;
DWORD   F1_Arg1v4;
DWORD   F1_Arg11v4;
DWORD   F1_Arg2v4;
DWORD   F2_Arg5v4;
DWORD   F3_Arg3v4;
//
LPVOID  F1_Thisv5;
DWORD   F1_Arg1v5;
DWORD   F1_Arg11v5;
DWORD   F1_Arg2v5;
DWORD   F2_Arg5v5;
DWORD   F3_Arg3v5;
//
LPVOID  F1_Thisv6;
DWORD   F1_Arg1v6;
DWORD   F1_Arg11v6;
DWORD   F1_Arg2v6;
DWORD   F2_Arg5v6;
DWORD   F3_Arg3v6;
//
LPVOID  F1_Thisv7;
DWORD   F1_Arg1v7;
DWORD   F1_Arg11v7;
DWORD   F1_Arg2v7;
DWORD   F2_Arg5v7;
DWORD   F3_Arg3v7;
//
LPVOID  F1_Thisv8;
DWORD   F1_Arg1v8;
DWORD   F1_Arg11v8;
DWORD   F1_Arg2v8;
DWORD   F2_Arg5v8;
DWORD   F3_Arg3v8;
//
LPVOID  F1_Thisv9;
DWORD   F1_Arg1v9;
DWORD   F1_Arg11v9;
DWORD   F1_Arg2v9;
DWORD   F2_Arg5v9;
DWORD   F3_Arg3v9;
//
LPVOID  F1_Thisv10;
DWORD   F1_Arg1v10;
DWORD   F1_Arg11v10;
DWORD   F1_Arg2v10;
DWORD   F2_Arg5v10;
DWORD   F3_Arg3v10;
//
LPVOID  F1_Thisv11;
DWORD   F1_Arg1v11;
DWORD   F1_Arg11v11;
DWORD   F1_Arg2v11;
DWORD   F2_Arg5v11;
DWORD   F3_Arg3v11;
//
LPVOID  F1_Thisv12;
DWORD   F1_Arg1v12;
DWORD   F1_Arg11v12;
DWORD   F1_Arg2v12;
DWORD   F2_Arg5v12;
DWORD   F3_Arg3v12;
//
LPVOID  F1_Thisv13;
DWORD   F1_Arg1v13;
DWORD   F1_Arg11v13;
DWORD   F1_Arg2v13;
DWORD   F2_Arg5v13;
DWORD   F3_Arg3v13;
//
LPVOID  F1_Thisv14;
DWORD   F1_Arg1v14;
DWORD   F1_Arg11v14;
DWORD   F1_Arg2v14;
DWORD   F2_Arg5v14;
DWORD   F3_Arg3v14;
//
LPVOID  F1_Thisv15;
DWORD   F1_Arg1v15;
DWORD   F1_Arg11v15;
DWORD   F1_Arg2v15;
DWORD   F2_Arg5v15;
DWORD   F3_Arg3v15;
//
LPVOID  F1_Thisv16;
DWORD   F1_Arg1v16;
DWORD   F1_Arg11v16;
DWORD   F1_Arg2v16;
DWORD   F2_Arg5v16;
DWORD   F3_Arg3v16;
//
LPVOID  F1_Thisv17;
DWORD   F1_Arg1v17;
DWORD   F1_Arg11v17;
DWORD   F1_Arg2v17;
DWORD   F2_Arg5v17;
DWORD   F3_Arg3v17;
//
LPVOID  F1_Thisv18;
DWORD   F1_Arg1v18;
DWORD   F1_Arg11v18;
DWORD   F1_Arg2v18;
DWORD   F2_Arg5v18;
DWORD   F3_Arg3v18;
//
LPVOID  F1_Thisv19;
DWORD   F1_Arg1v19;
DWORD   F1_Arg11v19;
DWORD   F1_Arg2v19;
DWORD   F2_Arg5v19;
DWORD   F3_Arg3v19;
//
LPVOID  F1_Thisv20;
DWORD   F1_Arg1v20;
DWORD   F1_Arg11v20;
DWORD   F1_Arg2v20;
DWORD   F2_Arg5v20;
DWORD   F3_Arg3v20;
//
LPVOID  F1_Thisv21;
DWORD   F1_Arg1v21;
DWORD   F1_Arg11v21;
DWORD   F1_Arg2v21;
DWORD   F2_Arg5v21;
DWORD   F3_Arg3v21;
//
LPVOID  F1_Thisv22;
DWORD   F1_Arg1v22;
DWORD   F1_Arg11v22;
DWORD   F1_Arg2v22;
DWORD   F2_Arg5v22;
DWORD   F3_Arg3v22;
//
LPVOID  F1_Thisv23;
DWORD   F1_Arg1v23;
DWORD   F1_Arg11v23;
DWORD   F1_Arg2v23;
DWORD   F2_Arg5v23;
DWORD   F3_Arg3v23;
//
LPVOID  F1_Thisv24;
DWORD   F1_Arg1v24;
DWORD   F1_Arg11v24;
DWORD   F1_Arg2v24;
DWORD   F2_Arg5v24;
DWORD   F3_Arg3v24;
//
LPVOID  F1_Thisv25;
DWORD   F1_Arg1v25;
DWORD   F1_Arg11v25;
DWORD   F1_Arg2v25;
DWORD   F2_Arg5v25;
DWORD   F3_Arg3v25;
//
LPVOID  F1_Thisv26;
DWORD   F1_Arg1v26;
DWORD   F1_Arg11v26;
DWORD   F1_Arg2v26;
DWORD   F2_Arg5v26;
DWORD   F3_Arg3v26;
//
LPVOID  F1_Thisv27;
DWORD   F1_Arg1v27;
DWORD   F1_Arg11v27;
DWORD   F1_Arg2v27;
DWORD   F2_Arg5v27;
DWORD   F3_Arg3v27;
//
LPVOID  F1_Thisv28;
DWORD   F1_Arg1v28;
DWORD   F1_Arg11v28;
DWORD   F1_Arg2v28;
DWORD   F2_Arg5v28;
DWORD   F3_Arg3v28;
//
LPVOID  F1_Thisv29;
DWORD   F1_Arg1v29;
DWORD   F1_Arg11v29;
DWORD   F1_Arg2v29;
DWORD   F2_Arg5v29;
DWORD   F3_Arg3v29;
//
LPVOID  F1_Thisv30;
DWORD   F1_Arg1v30;
DWORD   F1_Arg11v30;
DWORD   F1_Arg2v30;
DWORD   F2_Arg5v30;
DWORD   F3_Arg3v30;
//
LPVOID  F1_Thisv31;
DWORD   F1_Arg1v31;
DWORD   F1_Arg11v31;
DWORD   F1_Arg2v31;
DWORD   F2_Arg5v31;
DWORD   F3_Arg3v31;
//
LPVOID  F1_Thisv32;
DWORD   F1_Arg1v32;
DWORD   F1_Arg11v32;
DWORD   F1_Arg2v32;
DWORD   F2_Arg5v32;
DWORD   F3_Arg3v32;
//
LPVOID  F1_Thisv33;
DWORD   F1_Arg1v33;
DWORD   F1_Arg11v33;
DWORD   F1_Arg2v33;
DWORD   F2_Arg5v33;
DWORD   F3_Arg3v33;
//
LPVOID  F1_Thisv34;
DWORD   F1_Arg1v34;
DWORD   F1_Arg11v34;
DWORD   F1_Arg2v34;
DWORD   F2_Arg5v34;
DWORD   F3_Arg3v34;
//
LPVOID  F1_Thisv35;
DWORD   F1_Arg1v35;
DWORD   F1_Arg11v35;
DWORD   F1_Arg2v35;
DWORD   F2_Arg5v35;
DWORD   F3_Arg3v35;
//
LPVOID  F1_Thisv36;
DWORD   F1_Arg1v36;
DWORD   F1_Arg11v36;
DWORD   F1_Arg2v36;
DWORD   F2_Arg5v36;
DWORD   F3_Arg3v36;
//
LPVOID  F1_Thisv37;
DWORD   F1_Arg1v37;
DWORD   F1_Arg11v37;
DWORD   F1_Arg2v37;
DWORD   F2_Arg5v37;
DWORD   F3_Arg3v37;
//
LPVOID  F1_Thisv38;
DWORD   F1_Arg1v38;
DWORD   F1_Arg11v38;
DWORD   F1_Arg2v38;
DWORD   F2_Arg5v38;
DWORD   F3_Arg3v38;
//
LPVOID  F1_Thisv39;
DWORD   F1_Arg1v39;
DWORD   F1_Arg11v39;
DWORD   F1_Arg2v39;
DWORD   F2_Arg5v39;
DWORD   F3_Arg3v39;
//
LPVOID  F1_Thisv40;
DWORD   F1_Arg1v40;
DWORD   F1_Arg11v40;
DWORD   F1_Arg2v40;
DWORD   F2_Arg5v40;
DWORD   F3_Arg3v40;
//
LPVOID  F1_Thisv41;
DWORD   F1_Arg1v41;
DWORD   F1_Arg11v41;
DWORD   F1_Arg2v41;
DWORD   F2_Arg5v41;
DWORD   F3_Arg3v41;
//
LPVOID  F1_Thisv42;
DWORD   F1_Arg1v42;
DWORD   F1_Arg11v42;
DWORD   F1_Arg2v42;
DWORD   F2_Arg5v42;
DWORD   F3_Arg3v42;
//
LPVOID  F1_Thisv43;
DWORD   F1_Arg1v43;
DWORD   F1_Arg11v43;
DWORD   F1_Arg2v43;
DWORD   F2_Arg5v43;
DWORD   F3_Arg3v43;
//
LPVOID  F1_Thisv44;
DWORD   F1_Arg1v44;
DWORD  F1_Arg11v44;
DWORD   F1_Arg2v44;
DWORD   F2_Arg5v44;
DWORD   F3_Arg3v44;
//
LPVOID  F1_Thisv45;
DWORD   F1_Arg1v45;
DWORD  F1_Arg11v45;
DWORD   F1_Arg2v45;
DWORD   F2_Arg5v45;
DWORD   F3_Arg3v45;
//
LPVOID  F1_Thisv46;
DWORD   F1_Arg1v46;
DWORD  F1_Arg11v46;
DWORD   F1_Arg2v46;
DWORD   F2_Arg5v46;
DWORD   F3_Arg3v46;
//
LPVOID  F1_Thisv47;
DWORD   F1_Arg1v47;
DWORD  F1_Arg11v47;
DWORD   F1_Arg2v47;
DWORD   F2_Arg5v47;
DWORD   F3_Arg3v47;

__declspec(naked) void AddWingsEffect()
{
	_asm
	{
		mov AddWingsEffect_Buff, edx
			mov edx, dword ptr ss : [ebp - 0x68]
			mov F1_Thisv1, edx
			mov F1_Thisv2, edx
			mov F1_Thisv3, edx
			mov F1_Thisv4, edx
			mov F1_Thisv5, edx
			mov F1_Thisv6, edx
			mov F1_Thisv7, edx
			mov F1_Thisv8, edx
			mov F1_Thisv9, edx
			mov F1_Thisv10, edx
			mov F1_Thisv11, edx
			mov F1_Thisv12, edx
			mov F1_Thisv13, edx
			mov F1_Thisv14, edx
			mov F1_Thisv15, edx
			mov F1_Thisv16, edx
			mov F1_Thisv17, edx
			mov F1_Thisv18, edx
			mov F1_Thisv19, edx
			mov F1_Thisv20, edx
			mov F1_Thisv21, edx
			mov F1_Thisv22, edx
			mov F1_Thisv23, edx
			mov F1_Thisv24, edx
			mov F1_Thisv25, edx
			mov F1_Thisv26, edx
			mov F1_Thisv27, edx
			mov F1_Thisv28, edx
			mov F1_Thisv29, edx
			mov F1_Thisv30, edx
			mov F1_Thisv31, edx
			mov F1_Thisv32, edx
			mov F1_Thisv33, edx
			mov F1_Thisv34, edx
			mov F1_Thisv35, edx
			mov F1_Thisv36, edx
			mov F1_Thisv37, edx
			mov F1_Thisv38, edx
			mov F1_Thisv39, edx
			mov F1_Thisv40, edx
			mov F1_Thisv41, edx
			mov F1_Thisv42, edx
			mov F1_Thisv43, edx
			mov F1_Thisv44, edx
			mov F1_Thisv45, edx
			mov F1_Thisv46, edx
			mov F1_Thisv47, edx
			lea edx, [ebp - 0x58]
			mov F1_Arg1v1, edx
			mov F1_Arg1v2, edx
			mov F1_Arg1v3, edx
			mov F1_Arg1v4, edx
			mov F1_Arg1v5, edx
			mov F1_Arg1v6, edx
			mov F1_Arg1v7, edx
			mov F1_Arg1v8, edx
			mov F1_Arg1v9, edx
			mov F1_Arg1v10, edx
			mov F1_Arg1v11, edx
			mov F1_Arg1v12, edx
			mov F1_Arg1v13, edx
			mov F1_Arg1v14, edx
			mov F1_Arg1v15, edx
			mov F1_Arg1v16, edx
			mov F1_Arg1v17, edx
			mov F1_Arg1v18, edx
			mov F1_Arg1v19, edx
			mov F1_Arg1v20, edx
			mov F1_Arg1v21, edx
			mov F1_Arg1v22, edx
			mov F1_Arg1v23, edx
			mov F1_Arg1v24, edx
			mov F1_Arg1v25, edx
			mov F1_Arg1v26, edx
			mov F1_Arg1v27, edx
			mov F1_Arg1v28, edx
			mov F1_Arg1v29, edx
			mov F1_Arg1v30, edx
			mov F1_Arg1v31, edx
			mov F1_Arg1v32, edx
			mov F1_Arg1v33, edx
			mov F1_Arg1v34, edx
			mov F1_Arg1v35, edx
			mov F1_Arg1v36, edx
			mov F1_Arg1v37, edx
			mov F1_Arg1v38, edx
			mov F1_Arg1v39, edx
			mov F1_Arg1v40, edx
			mov F1_Arg1v41, edx
			mov F1_Arg1v42, edx
			mov F1_Arg1v43, edx
			mov F1_Arg1v44, edx
			mov F1_Arg1v45, edx
			mov F1_Arg1v46, edx
			mov F1_Arg1v47, edx
			lea edx, [ebp - 0x18]
			mov F1_Arg11v1, edx
			mov F1_Arg11v2, edx
			mov F1_Arg11v3, edx
			mov F1_Arg11v4, edx
			mov F1_Arg11v5, edx
			mov F1_Arg11v6, edx
			mov F1_Arg11v7, edx
			mov F1_Arg11v8, edx
			mov F1_Arg11v9, edx
			mov F1_Arg11v10, edx
			mov F1_Arg11v11, edx
			mov F1_Arg11v12, edx
			mov F1_Arg11v13, edx
			mov F1_Arg11v14, edx
			mov F1_Arg11v15, edx
			mov F1_Arg11v16, edx
			mov F1_Arg11v17, edx
			mov F1_Arg11v18, edx
			mov F1_Arg11v19, edx
			mov F1_Arg11v20, edx
			mov F1_Arg11v21, edx
			mov F1_Arg11v22, edx
			mov F1_Arg11v23, edx
			mov F1_Arg11v24, edx
			mov F1_Arg11v25, edx
			mov F1_Arg11v26, edx
			mov F1_Arg11v27, edx
			mov F1_Arg11v28, edx
			mov F1_Arg11v29, edx
			mov F1_Arg11v30, edx
			mov F1_Arg11v31, edx
			mov F1_Arg11v32, edx
			mov F1_Arg11v33, edx
			mov F1_Arg11v34, edx
			mov F1_Arg11v35, edx
			mov F1_Arg11v36, edx
			mov F1_Arg11v37, edx
			mov F1_Arg11v38, edx
			mov F1_Arg11v39, edx
			mov F1_Arg11v40, edx
			mov F1_Arg11v41, edx
			mov F1_Arg11v42, edx
			mov F1_Arg11v43, edx
			mov F1_Arg11v44, edx
			mov F1_Arg11v45, edx
			mov F1_Arg11v46, edx
			mov F1_Arg11v47, edx
			mov edx, dword ptr ss : [ebp - 0x6c]
			mov F1_Arg2v1, edx
			mov F1_Arg2v2, edx
			mov F1_Arg2v3, edx
			mov F1_Arg2v4, edx
			mov F1_Arg2v5, edx
			mov F1_Arg2v6, edx
			mov F1_Arg2v7, edx
			mov F1_Arg2v8, edx
			mov F1_Arg2v9, edx
			mov F1_Arg2v10, edx
			mov F1_Arg2v11, edx
			mov F1_Arg2v12, edx
			mov F1_Arg2v13, edx
			mov F1_Arg2v14, edx
			mov F1_Arg2v15, edx
			mov F1_Arg2v16, edx
			mov F1_Arg2v17, edx
			mov F1_Arg2v18, edx
			mov F1_Arg2v19, edx
			mov F1_Arg2v20, edx
			mov F1_Arg2v21, edx
			mov F1_Arg2v22, edx
			mov F1_Arg2v23, edx
			mov F1_Arg2v24, edx
			mov F1_Arg2v25, edx
			mov F1_Arg2v26, edx
			mov F1_Arg2v27, edx
			mov F1_Arg2v28, edx
			mov F1_Arg2v29, edx
			mov F1_Arg2v30, edx
			mov F1_Arg2v31, edx
			mov F1_Arg2v32, edx
			mov F1_Arg2v33, edx
			mov F1_Arg2v34, edx
			mov F1_Arg2v35, edx
			mov F1_Arg2v36, edx
			mov F1_Arg2v37, edx
			mov F1_Arg2v38, edx
			mov F1_Arg2v39, edx
			mov F1_Arg2v40, edx
			mov F1_Arg2v41, edx
			mov F1_Arg2v42, edx
			mov F1_Arg2v43, edx
			mov F1_Arg2v44, edx
			mov F1_Arg2v45, edx
			mov F1_Arg2v46, edx
			mov F1_Arg2v47, edx

			fldz
			fstp dword ptr ss : [esp]
			mov edx, dword ptr ss : [ebp - 0x70]
			mov F2_Arg5v1, edx
			mov F2_Arg5v2, edx
			mov F2_Arg5v3, edx
			mov F2_Arg5v4, edx
			mov F2_Arg5v5, edx
			mov F2_Arg5v6, edx
			mov F2_Arg5v7, edx
			mov F2_Arg5v8, edx
			mov F2_Arg5v9, edx
			mov F2_Arg5v10, edx
			mov F2_Arg5v11, edx
			mov F2_Arg5v12, edx
			mov F2_Arg5v13, edx
			mov F2_Arg5v14, edx
			mov F2_Arg5v15, edx
			mov F2_Arg5v16, edx
			mov F2_Arg5v17, edx
			mov F2_Arg5v18, edx
			mov F2_Arg5v19, edx
			mov F2_Arg5v20, edx
			mov F2_Arg5v21, edx
			mov F2_Arg5v22, edx
			mov F2_Arg5v23, edx
			mov F2_Arg5v24, edx
			mov F2_Arg5v25, edx
			mov F2_Arg5v26, edx
			mov F2_Arg5v27, edx
			mov F2_Arg5v28, edx
			mov F2_Arg5v29, edx
			mov F2_Arg5v30, edx
			mov F2_Arg5v31, edx
			mov F2_Arg5v32, edx
			mov F2_Arg5v33, edx
			mov F2_Arg5v34, edx
			mov F2_Arg5v35, edx
			mov F2_Arg5v36, edx
			mov F2_Arg5v37, edx
			mov F2_Arg5v38, edx
			mov F2_Arg5v39, edx
			mov F2_Arg5v40, edx
			mov F2_Arg5v41, edx
			mov F2_Arg5v42, edx
			mov F2_Arg5v43, edx
			mov F2_Arg5v44, edx
			mov F2_Arg5v45, edx
			mov F2_Arg5v46, edx
			mov F2_Arg5v47, edx
			mov edx, AddWingsEffect_Buff
	}
	// ----

	if (IsCustomItem((WORD)AddWingsEffect_Buff, true))
	{
		if (AddWingsEffect_Buff == ITEM2(0, 47)) //blessed
		{
			Color[0] = 0.2f;
			Color[1] = 0.2f;
			Color[2] = 0.2f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 5, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 7, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 9, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 11, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 13, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 15, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 17, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 19, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 21, 0);
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 23, 0);
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 26, 0);
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 28, 0);
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 30, 0);
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 31, 0);
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 32, 0);
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 33, 0);
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 34, 0);
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 35, 0);
			pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 36, 0);
			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 37, 0);
			pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 38, 0);
			pAllowStaticEffect(F1_Thisv25, &F1_Arg11v25, F1_Arg2v25, 39, 0);
			pAllowStaticEffect(F1_Thisv26, &F1_Arg11v26, F1_Arg2v26, 40, 0);
			pAllowStaticEffect(F1_Thisv27, &F1_Arg11v27, F1_Arg2v27, 41, 0);
			pAllowStaticEffect(F1_Thisv28, &F1_Arg11v28, F1_Arg2v28, 42, 0);
			pAllowStaticEffect(F1_Thisv29, &F1_Arg11v29, F1_Arg2v29, 43, 0);
			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 44, 0);
			pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 45, 0);
			pAllowStaticEffect(F1_Thisv32, &F1_Arg11v32, F1_Arg2v32, 46, 0);
			pAllowStaticEffect(F1_Thisv33, &F1_Arg11v33, F1_Arg2v33, 47, 0);
			pAllowStaticEffect(F1_Thisv34, &F1_Arg11v34, F1_Arg2v34, 48, 0);
			pAllowStaticEffect(F1_Thisv35, &F1_Arg11v35, F1_Arg2v35, 49, 0);
			pAllowStaticEffect(F1_Thisv36, &F1_Arg11v36, F1_Arg2v36, 50, 0);
			pAllowStaticEffect(F1_Thisv37, &F1_Arg11v37, F1_Arg2v37, 51, 0);
			pAllowStaticEffect(F1_Thisv38, &F1_Arg11v38, F1_Arg2v38, 52, 0);
			pAllowStaticEffect(F1_Thisv39, &F1_Arg11v39, F1_Arg2v39, 53, 0);
			pAllowStaticEffect(F1_Thisv40, &F1_Arg11v40, F1_Arg2v40, 54, 0);
			pAllowStaticEffect(F1_Thisv41, &F1_Arg11v41, F1_Arg2v41, 55, 0);
			pAllowStaticEffect(F1_Thisv42, &F1_Arg11v42, F1_Arg2v42, 56, 0);
			pAllowStaticEffect(F1_Thisv43, &F1_Arg11v43, F1_Arg2v43, 57, 0);
			pAllowStaticEffect(F1_Thisv44, &F1_Arg11v44, F1_Arg2v44, 58, 0);
			pAllowStaticEffect(F1_Thisv45, &F1_Arg11v45, F1_Arg2v45, 59, 0);
			pAllowStaticEffect(F1_Thisv46, &F1_Arg11v46, F1_Arg2v46, 60, 0);
			pAllowStaticEffect(F1_Thisv47, &F1_Arg11v47, F1_Arg2v47, 61, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5f, Color, F2_Arg5v1, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 0.5f, Color, F2_Arg5v3, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 0.5f, Color, F2_Arg5v4, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 0.5f, Color, F2_Arg5v5, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 0.5f, Color, F2_Arg5v6, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 0.5f, Color, F2_Arg5v7, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 0.5f, Color, F2_Arg5v8, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 0.5f, Color, F2_Arg5v9, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 0.5f,Color, F2_Arg5v10, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 0.5f, Color, F2_Arg5v11, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 0.5f, Color, F2_Arg5v12, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 0.5f, Color, F2_Arg5v13, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 0.5f, Color, F2_Arg5v14, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 0.5f, Color, F2_Arg5v15, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 0.5f, Color, F2_Arg5v16, 0.0f, 0);
			Color[0] = 0.3f;
			Color[1] = 0.5f;
			Color[2] = 0.3f;
			pPlayStaticEffect(32002, &F1_Arg11v17, 1.0f, Color, F2_Arg5v17, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 1.0f, Color, F2_Arg5v18, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19, 1.0f, Color, F2_Arg5v19, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 1.0f, Color, F2_Arg5v20, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21, 1.0f, Color, F2_Arg5v21, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v22, 1.0f, Color, F2_Arg5v22, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v23, 1.0f, Color, F2_Arg5v23, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v24, 1.0f, Color, F2_Arg5v24, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v25, 1.0f, Color, F2_Arg5v25, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v26, 1.0f, Color, F2_Arg5v26, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v27, 1.0f, Color, F2_Arg5v27, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v28, 1.0f, Color, F2_Arg5v28, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v29, 1.0f, Color, F2_Arg5v29, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v30, 1.0f, Color, F2_Arg5v30, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v31, 1.0f, Color, F2_Arg5v31, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v32, 1.0f, Color, F2_Arg5v32, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v33, 1.0f, Color, F2_Arg5v33, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v34, 1.0f, Color, F2_Arg5v34, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v35, 1.0f, Color, F2_Arg5v35, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v36, 1.0f, Color, F2_Arg5v36, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v37, 1.0f, Color, F2_Arg5v37, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v38, 1.0f, Color, F2_Arg5v38, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v39, 1.0f, Color, F2_Arg5v39, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v40, 1.0f, Color, F2_Arg5v40, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v41, 1.0f, Color, F2_Arg5v41, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v42, 1.0f, Color, F2_Arg5v42, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v43, 1.0f, Color, F2_Arg5v43, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v44, 1.0f, Color, F2_Arg5v44, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v45, 1.0f, Color, F2_Arg5v45, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v46, 1.0f, Color, F2_Arg5v46, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v47, 1.0f, Color, F2_Arg5v47, 0.0f, 0);
			Color[0] = 0.1f;
			Color[1] = 0.5f;
			Color[2] = 1.0f;
			pPlayDynamicEffect(32072, &F1_Arg11v1, F1_Arg2v1, Color, -1, 1.5f, 10);
		}
		else if (AddWingsEffect_Buff == ITEM2(0, 30)||AddWingsEffect_Buff == ITEM2(0, 37)) //Cyclone - Sonic
		{
			Color[0] = 0.7f;
			Color[1] = 0.7f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 1, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			//--
			pPlayStaticEffect(32002, &F1_Arg11v1, 1.0f, Color, F2_Arg5v1, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 1.0f, Color, F2_Arg5v2, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 0.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0f, Color, F2_Arg5v7, 0.0f, 0);
			// --														 
			pPlayDynamicEffect(32396, &F1_Arg11v1, F1_Arg2v1, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v2, F1_Arg2v2, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v3, F1_Arg2v3, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v4, F1_Arg2v4, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v5, F1_Arg2v5, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v6, F1_Arg2v6, Color, 2, 0.4f, 0);
			pPlayDynamicEffect(32396, &F1_Arg11v7, F1_Arg2v7, Color, 2, 0.4f, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(3, 17))//MagmaSpear
		{
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 1, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);			
			// --														 
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			//--
			pPlayStaticEffect(32002, &F1_Arg11v1, 1.4f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 1.4f, Color, F2_Arg5v2, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.4f, Color, F2_Arg5v3, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.4f, Color, F2_Arg5v4, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.4f, Color, F2_Arg5v5, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.4f, Color, F2_Arg5v6, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.4f, Color, F2_Arg5v7, 1.0f, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(5, 37)) //miracle staff
		{
				Color[0] = 1.0f;
				Color[1] = 1.0f;
				Color[2] = 1.0f;
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                
                Color[0] = 0.69999999f;
                Color[1] = 0.1f;
                Color[2] = 0.2f;

                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                Color[0] = 0.89999998f;
                Color[1] = 0.30000001f;
                Color[2] = 0.5f;
                pPlayStaticEffect(32119, &F1_Arg11v2, 0.80000001f, Color, F2_Arg5v2, 0.0f, 0);
                float v271 = (rand() % 15) / 20.0f + 1.0f;
                pPlayStaticEffect(32114,  &F1_Arg11v2, v271, Color, F2_Arg5v2, 0.0f, 0);
                float v93 = v271 - 0.3f;
                pPlayStaticEffect(32114, &F1_Arg11v2, v93, Color, F2_Arg5v2, 90.0f, 0);
                pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);
           
                Color[0] = 0.7f;
                Color[1] = 0.7f;
                Color[2] = 0.7f;
                pPlayStaticEffect(32115, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
               
		}
		/*
		else if (AddWingsEffect_Buff == ITEM2(2, 25)) //emperor
		{
				Color[0] = 1.0f;
				Color[1] = 1.0f;
				Color[2] = 1.0f;
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 5, 0);
                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                
                Color[0] = 0.69999999f;
                Color[1] = 0.1f;
                Color[2] = 0.2f;

                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                Color[0] = 0.89999998f;
                Color[1] = 0.30000001f;
                Color[2] = 0.5f;
                pPlayStaticEffect(32119, &F1_Arg11v2, 0.80000001f, Color, F2_Arg5v2, 0.0f, 0);
                float v271 = (rand() % 15) / 20.0f + 1.0f;
                pPlayStaticEffect(32114,  &F1_Arg11v2, v271, Color, F2_Arg5v2, 0.0f, 0);
                float v93 = v271 - 0.3f;
                pPlayStaticEffect(32114, &F1_Arg11v2, v93, Color, F2_Arg5v2, 90.0f, 0);
                pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);
           
                Color[0] = 0.7f;
                Color[1] = 0.7f;
                Color[2] = 0.7f;
                pPlayStaticEffect(32115, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
               
		}
		*/
		else if (AddWingsEffect_Buff == ITEM2(2, 19)) //bolt
		{
				Color[0] = 1.0f;
				Color[1] = 1.0f;
				Color[2] = 1.0f;
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);

				Color[0] = 0.4f;
                Color[1] = 0.6f;
                Color[2] = 1.0f;

                pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 0.0f, 0);
                
                Color[0] = 0.2f;
                Color[1] = 0.6f;
                Color[2] = 1.0f;

                pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 0.0f, 0);
                Color[0] = 0.4f;
                Color[1] = 0.7f;
                Color[2] = 1.0f;
                pPlayStaticEffect(32119, &F1_Arg11v2, 0.80000001f, Color, F2_Arg5v2, 0.0f, 0);
                float v271 = (rand() % 15) / 20.0f + 1.0f;
                pPlayStaticEffect(32114,  &F1_Arg11v2, v271, Color, F2_Arg5v2, 0.0f, 0);
                float v93 = v271 - 0.3f;
                pPlayStaticEffect(32114, &F1_Arg11v2, v93, Color, F2_Arg5v2, 90.0f, 0);
                              
                Color[0] = 0.4f;
                Color[1] = 0.5f;
                Color[2] = 0.6f;
                pPlayStaticEffect(32115, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 0.0f, 0);
               
		}
		else if (AddWingsEffect_Buff == ITEM2(5, 41)) //spite staff
		{
			
				Color[0] = 0.1f;
                Color[1] = 1.0f;
                Color[2] = 0.2f;
				
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
				
                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                
                Color[0] = 0.7f;
                Color[1] = 1.0f;
                Color[2] = 0.8f;
				
                pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);
                Color[0] = 0.3f;
                Color[1] = 0.5f;
                Color[2] = 0.9f;
                pPlayStaticEffect(32119, &F1_Arg11v2, 0.80000001f, Color, F2_Arg5v2, 0.0f, 0);
                float v271 = (rand() % 15) / 20.0f + 1.0f;
                pPlayStaticEffect(32114,  &F1_Arg11v2, v271, Color, F2_Arg5v2, 0.0f, 0);
                float v93 = v271 - 0.3f;
                pPlayStaticEffect(32114, &F1_Arg11v2, v93, Color, F2_Arg5v2, 90.0f, 0);
                //pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);		
                Color[0] = 0.3f;
                Color[1] = 0.9f;
                Color[2] = 0.7f;
				
				pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);
           		
                Color[0] = 0.5f;
                Color[1] = 1.0f;
                Color[2] = 0.5f;
                pPlayStaticEffect(32115, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 0.0f, 0);			  
		}
		else if (AddWingsEffect_Buff == ITEM2(2, 24))
		{
			Color[0] = 0.3f;
			Color[1] = 0.4f;
			Color[2] = 0.8f;
			// --
												 
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 0.5f, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 41, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 0.5f, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 63, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 0.5f, 0);
			// --														 
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 44, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 0.5f, 0);
			//--
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0f, Color, F2_Arg5v16, 0.5f, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 32, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 2.0f, Color, F2_Arg5v17, 0.5f, 0);
			// --

			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v30, 0.5f, Color, F2_Arg5v30, 0.5f, 0);
			pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 16, 0);
			pPlayStaticEffect(32002, &F1_Arg11v31, 0.5f, Color, F2_Arg5v31, 0.5f, 0);
			pAllowStaticEffect(F1_Thisv32, &F1_Arg11v32, F1_Arg2v32, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v32, 0.5f, Color, F2_Arg5v32, 0.5f, 0);
			pAllowStaticEffect(F1_Thisv33, &F1_Arg11v33, F1_Arg2v33, 18, 0);
			pPlayStaticEffect(32002, &F1_Arg11v33, 0.5f, Color, F2_Arg5v33, 0.5f, 0);

			Color[0] = 0.0f;
			Color[1] = 0.3f;
			Color[2] = 1.0f;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 5, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 8, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1, 1.0f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 1.0f, Color, F2_Arg5v2, 1.0f, 0);
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.0f;

			pAllowStaticEffect(F1_Thisv34, &F1_Arg11v34, F1_Arg2v34, 57, 0);
			Color[0] = 0.69999999f;
            Color[1] = 0.1f;
            Color[2] = 0.2f;

            pPlayStaticEffect(32002, &F1_Arg11v34, 2.0f, Color, F2_Arg5v34, 0.0f, 0);
            Color[0] = 0.89999998f;
            Color[1] = 0.30000001f;
            Color[2] = 0.5f;
            pPlayStaticEffect(32119, &F1_Arg11v34, 0.80000001f, Color, F2_Arg5v34, 0.0f, 0);
            float v271 = (rand() % 15) / 20.0f + 1.0f;
            pPlayStaticEffect(32114,  &F1_Arg11v34, v271, Color, F2_Arg5v34, 0.0f, 0);
            float v93 = v271 - 0.3f;
            pPlayStaticEffect(32114, &F1_Arg11v34, v93, Color, F2_Arg5v34, 90.0f, 0);
            pPlayDynamicEffect(32049, &F1_Arg11v34, F1_Arg2v34, Color, 11, 2.0f, 0);          
            Color[0] = 0.7f;
            Color[1] = 0.7f;
            Color[2] = 0.7f;
            pPlayStaticEffect(32115, &F1_Arg11v34, 2.0f, Color, F2_Arg5v34, 0.0f, 0);		
		}		
		else if (AddWingsEffect_Buff == ITEM2(5, 44)||AddWingsEffect_Buff == ITEM2(5, 200))//Blessed Divine Staff of Archa
		{
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 25, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5f, Color, F2_Arg5v1, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 26, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 27, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 28, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 40, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 41, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0f, Color, F2_Arg5v7, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 43, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.4f, Color, F2_Arg5v8, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 44, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1.4f, Color, F2_Arg5v9, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 72, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 2.6f, Color, F2_Arg5v10, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 73, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 2.6f, Color, F2_Arg5v11, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 74, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 1.4f, Color, F2_Arg5v12, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 75, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1.4f, Color, F2_Arg5v13, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 76, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 2.0f, Color, F2_Arg5v14, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 2.0f, Color, F2_Arg5v15, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0f, Color, F2_Arg5v16, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 26, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 2.0f, Color, F2_Arg5v17, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 28, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 2.0f, Color, F2_Arg5v18, 1.0f, 0);
			//// --
			Color[0] = 0.4f;
			Color[1] = 0.4f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 53, 0);
			if ( !(rand() % 10) )
			pPlayDynamicEffect(32279, &F1_Arg11v23, F1_Arg2v23,Color,3, 0.6f, 0);

			pPlayStaticEffect(32501, &F1_Arg11v23, 1.0f, Color, F2_Arg5v23, 1.0f, 0);

            pPlayStaticEffect(32119, &F1_Arg11v23, 0.8f, Color, F2_Arg5v23, 0.0f, 0);
            float v271 = (rand() % 15) / 20.0f + 1.0f;
            pPlayStaticEffect(32114,  &F1_Arg11v23, v271, Color, F2_Arg5v23, 0.0f, 0);
				
			pPlayDynamicEffect(32049, &F1_Arg11v23, F1_Arg2v23, Color, 11, 2.0f, 0);
          		
		}
		else if (AddWingsEffect_Buff == ITEM2(5, 45))//Blessed Divine Arch Stick
		{
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 25, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5f, Color, F2_Arg5v1, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 27, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 29, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 31, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 33, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 34, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 36, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0f, Color, F2_Arg5v7, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 38, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.4f, Color, F2_Arg5v8, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 40, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1.4f, Color, F2_Arg5v9, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 1, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 2.6f, Color, F2_Arg5v10, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 4, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 2.6f, Color, F2_Arg5v11, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 1.4f, Color, F2_Arg5v12, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1.4f, Color, F2_Arg5v13, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 2.0f, Color, F2_Arg5v14, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 2.0f, Color, F2_Arg5v15, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 20, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0f, Color, F2_Arg5v16, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 23, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 2.0f, Color, F2_Arg5v17, 1.0f, 0);
			//// --          		
		}
		else if (AddWingsEffect_Buff == ITEM2(4, 30))//Blessed Divine Crossbow
		{
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 2, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5f, Color, F2_Arg5v1, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 4, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 5, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0f, Color, F2_Arg5v7, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.4f, Color, F2_Arg5v8, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1.4f, Color, F2_Arg5v9, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 2.6f, Color, F2_Arg5v10, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 2.6f, Color, F2_Arg5v11, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 1.4f, Color, F2_Arg5v12, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 14, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1.4f, Color, F2_Arg5v13, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 2.0f, Color, F2_Arg5v14, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 16, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 2.0f, Color, F2_Arg5v15, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0f, Color, F2_Arg5v16, 1.0f, 0);
			// --
			
			//
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 1, 0);
			pPlayStaticEffect(32131, &F1_Arg11v23, 0.8f, Color, F2_Arg5v23, 0, 0);
						//
			Color[0] = 1.0f;
			Color[1] = 0.2f;
			Color[2] = 0.3f;
				pPlayDynamicEffect(32002,  &F1_Arg11v2, F1_Arg2v2, Color,0, -1, 0);
				pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);
				pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);
			Color[0] = 0.1f;
			Color[1] = 0.2f;
			Color[2] = 0.5f;
				pPlayDynamicEffect(32002,  &F1_Arg11v2, F1_Arg2v2, Color,0, -1, 0);
				pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);
				pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(4, 28))//BloodAngel Bow
		{
			Color[0] = 1.0f;
			Color[1] = 0.2f;
			Color[2] = 0.3f;

			pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 37, 0);

			pPlayStaticEffect(32119, &F1_Arg11v31, 0.8f, Color, F2_Arg5v31, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v31, v271, Color, F2_Arg5v31, 0.0f, 0);
			float v93 = v271 - 0.3f;
			pPlayStaticEffect(32114, &F1_Arg11v31, v93, Color, F2_Arg5v31, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v31, F1_Arg2v31, Color, 11, 2.0f, 0);
						   
			Color[0] = 0.7f;
			Color[1] = 0.7f;
			Color[2] = 0.7f;
			pPlayStaticEffect(32115, &F1_Arg11v31, 2.0f, Color, F2_Arg5v31, 0.0f, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(0, 45))//Bloodangel Magic Sword
		{
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);


			pPlayStaticEffect(32002, &F1_Arg11v1, 1.5f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 1.5f, Color, F2_Arg5v2, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.5f, Color, F2_Arg5v3, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.5f, Color, F2_Arg5v4, 1.0f, 0);

			//
			Color[0] = 0.3f;
			Color[1] = 0.3f;
			Color[2] = 1.0f;
			pPlayStaticEffect(32131, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 0, 0);
						//
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;

			pPlayStaticEffect(32119, &F1_Arg11v4, 0.8f, Color, F2_Arg5v4, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v4, v271, Color, F2_Arg5v4, 0.0f, 0);
			float v93 = v271 - 0.3f;
			pPlayStaticEffect(32114, &F1_Arg11v4, v93, Color, F2_Arg5v4, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v4, F1_Arg2v4, Color, 11, 2.0f, 0);
						   
			Color[0] = 0.7f;
			Color[1] = 0.7f;
			Color[2] = 0.7f;
			pPlayStaticEffect(32115, &F1_Arg11v4, 2.0f, Color, F2_Arg5v4, 0.0f, 0);


		}
		else if (AddWingsEffect_Buff == ITEM2(2, 23)) //Bloodangel Scepter
		{
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;
			// --
		
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);


			pPlayStaticEffect(32002, &F1_Arg11v1, 2.0f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2.0f, Color, F2_Arg5v3, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2.0f, Color, F2_Arg5v4, 1.0f, 0);

			//
			Color[0] = 0.3f;
			Color[1] = 0.3f;
			Color[2] = 1.0f;
			pPlayStaticEffect(32131, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 0, 0);
						//
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;

			pPlayStaticEffect(32119, &F1_Arg11v3, 0.80000001f, Color, F2_Arg5v3, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v3, v271, Color, F2_Arg5v3, 0.0f, 0);
			float v93 = v271 - 0.300000011920929f;
			pPlayStaticEffect(32114, &F1_Arg11v3, v93, Color, F2_Arg5v3, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v3, F1_Arg2v3, Color, 11, 2.0f, 0);
						   
			Color[0] = 0.69999999f;
			Color[1] = 0.69999999f;
			Color[2] = 0.69999999f;
			pPlayStaticEffect(32115, &F1_Arg11v3, 2.0f, Color, F2_Arg5v3, 0.0f, 0);


		}
		else if (AddWingsEffect_Buff == ITEM2(0, 37)) //Cyclone Sword
		{
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;
			// --
		
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);


			pPlayStaticEffect(32002, &F1_Arg11v1, 2.0f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2.0f, Color, F2_Arg5v3, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2.0f, Color, F2_Arg5v4, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 2.0f, Color, F2_Arg5v5, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 2.0f, Color, F2_Arg5v6, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 2.0f, Color, F2_Arg5v7, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 2.0f, Color, F2_Arg5v8, 1.0f, 0);

			//
			Color[0] = 0.3f;
			Color[1] = 0.3f;
			Color[2] = 1.0f;
			pPlayStaticEffect(32131, &F1_Arg11v8, 1.0f, Color, F2_Arg5v8, 0, 0);
						//
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;

			pPlayStaticEffect(32119, &F1_Arg11v8, 0.80000001f, Color, F2_Arg5v8, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v8, v271, Color, F2_Arg5v8, 0.0f, 0);
			float v93 = v271 - 0.300000011920929f;
			pPlayStaticEffect(32114, &F1_Arg11v8, v93, Color, F2_Arg5v8, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v8, F1_Arg2v8, Color, 11, 2.0f, 0);
						   
			Color[0] = 0.69999999f;
			Color[1] = 0.69999999f;
			Color[2] = 0.69999999f;
			pPlayStaticEffect(32115, &F1_Arg11v8, 2.0f, Color, F2_Arg5v8, 0.0f, 0);


		}
		else if (AddWingsEffect_Buff == ITEM2(5, 42)) // blood angel staff
		{
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;
			// --
		
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);


			pPlayStaticEffect(32002, &F1_Arg11v1, 2.0f, Color, F2_Arg5v1, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2.0f, Color, F2_Arg5v2, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2.0f, Color, F2_Arg5v3, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2.0f, Color, F2_Arg5v4, 1.0f, 0);

			//
			Color[0] = 0.3f;
			Color[1] = 0.3f;
			Color[2] = 1.0f;
			pPlayStaticEffect(32131, &F1_Arg11v2, 1.0f, Color, F2_Arg5v2, 0, 0);
						//
			Color[0] = 1.0f;
			Color[1] = 0.3f;
			Color[2] = 0.3f;

							pPlayDynamicEffect(0x7E83, &F1_Arg11v1, F1_Arg2v1,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v3, F1_Arg2v3,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v4, F1_Arg2v4,Color,0, -1, 0);
							 pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);
			Color[0] = 0.1f;
			Color[1] = 0.2f;
			Color[2] = 0.5f;
							pPlayDynamicEffect(0x7E83, &F1_Arg11v1, F1_Arg2v1,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v3, F1_Arg2v3,Color,0, -1, 0);
							pPlayDynamicEffect(0x7E83, &F1_Arg11v4, F1_Arg2v4,Color,0, -1, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(0,51)) //holyangel sword
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 10, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 11, 0);
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 13, 0);
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 14, 0);
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 15, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11,	0.6f, Color, F2_Arg5v11,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12,	0.6f, Color, F2_Arg5v12,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13,	0.6f, Color, F2_Arg5v13,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14,	0.6f, Color, F2_Arg5v14,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15,	0.6f, Color, F2_Arg5v15,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16,	0.6f, Color, F2_Arg5v16,0.5f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v11, F1_Arg2v11	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v12, F1_Arg2v12	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v13, F1_Arg2v13	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v14, F1_Arg2v14	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v15, F1_Arg2v15	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v16, F1_Arg2v16	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice

		}
		else if (AddWingsEffect_Buff == ITEM2(0,52)) //holyangel magic sword
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 10, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 11, 0);
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 13, 0);
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 14, 0);
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 15, 0);
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 16, 0);
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 17, 0);
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 18, 0);
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 19, 0);
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 20, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11,	0.6f, Color, F2_Arg5v11,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12,	0.6f, Color, F2_Arg5v12,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13,	0.6f, Color, F2_Arg5v13,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14,	0.6f, Color, F2_Arg5v14,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15,	0.6f, Color, F2_Arg5v15,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16,	0.6f, Color, F2_Arg5v16,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17,	0.6f, Color, F2_Arg5v17,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18,	0.6f, Color, F2_Arg5v18,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19,	0.6f, Color, F2_Arg5v19,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20,	0.6f, Color, F2_Arg5v20,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21,	0.6f, Color, F2_Arg5v21,0.5f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v11, F1_Arg2v11	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v12, F1_Arg2v12	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v13, F1_Arg2v13	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v14, F1_Arg2v14	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v15, F1_Arg2v15	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v16, F1_Arg2v16	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v17, F1_Arg2v17	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v18, F1_Arg2v18	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v19, F1_Arg2v19	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v20, F1_Arg2v20	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v21, F1_Arg2v21	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice

		}
		else if (AddWingsEffect_Buff == ITEM2(2,26)) //holyangel scepter
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);

			pPlayStaticEffect(32119, &F1_Arg11v4, 0.80000001f, Color, F2_Arg5v4, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v4, v271, Color, F2_Arg5v4, 0.0f, 0);
			float v93 = v271 - 0.300000011920929f;
			pPlayStaticEffect(32114, &F1_Arg11v4, v93, Color, F2_Arg5v4, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v4, F1_Arg2v4, Color, 11, 2.0f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice

		}
		else if (AddWingsEffect_Buff == ITEM2(4,31)) //holyangel bow
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 10, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 11, 0);
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 13, 0);
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 14, 0);
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 15, 0);
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 16, 0);
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 17, 0);
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 18, 0);
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 19, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11,	0.6f, Color, F2_Arg5v11,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12,	0.6f, Color, F2_Arg5v12,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13,	0.6f, Color, F2_Arg5v13,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14,	0.6f, Color, F2_Arg5v14,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15,	0.6f, Color, F2_Arg5v15,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16,	0.6f, Color, F2_Arg5v16,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17,	0.6f, Color, F2_Arg5v17,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18,	0.6f, Color, F2_Arg5v18,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19,	0.6f, Color, F2_Arg5v19,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20,	0.6f, Color, F2_Arg5v20,0.5f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v11, F1_Arg2v11	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v12, F1_Arg2v12	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v13, F1_Arg2v13	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v14, F1_Arg2v14	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v15, F1_Arg2v15	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v16, F1_Arg2v16	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v17, F1_Arg2v17	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v18, F1_Arg2v18	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v19, F1_Arg2v19	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v20, F1_Arg2v20	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice

		}
		else if (AddWingsEffect_Buff == ITEM2(5,48)) //holyangel staff
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 10, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 11, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11,	0.6f, Color, F2_Arg5v11,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12,	0.6f, Color, F2_Arg5v12,0.5f, 0);

			pPlayStaticEffect(32119, &F1_Arg11v9, 0.80000001f, Color, F2_Arg5v9, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v9, v271, Color, F2_Arg5v9, 0.0f, 0);
			float v93 = v271 - 0.300000011920929f;
			pPlayStaticEffect(32114, &F1_Arg11v9, v93, Color, F2_Arg5v9, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v9, F1_Arg2v9, Color, 11, 2.0f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v11, F1_Arg2v11	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v12, F1_Arg2v12	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice

		}
		else if (AddWingsEffect_Buff == ITEM2(5,49)) //holyangel stick
		{
			Color[0] = 0.1f;
			Color[1] = 0.8f;
			Color[2] = 1.0f;

			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 2, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 3, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 4, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 5, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 6, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 7, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 8, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 9, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 10, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,	0.6f, Color, F2_Arg5v1,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,	0.6f, Color, F2_Arg5v2,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,	0.6f, Color, F2_Arg5v3,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,	0.6f, Color, F2_Arg5v4,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,	0.6f, Color, F2_Arg5v5,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,	0.6f, Color, F2_Arg5v6,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,	0.6f, Color, F2_Arg5v7,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,	0.6f, Color, F2_Arg5v8,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,	0.6f, Color, F2_Arg5v9,	0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10,	0.6f, Color, F2_Arg5v10,0.5f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11,	0.6f, Color, F2_Arg5v11,0.5f, 0);

			pPlayStaticEffect(32119, &F1_Arg11v11, 0.80000001f, Color, F2_Arg5v11, 0.0f, 0);
			float v271 = (rand() % 15) / 20.0f + 1.0f;
			pPlayStaticEffect(32114,  &F1_Arg11v11, v271, Color, F2_Arg5v11, 0.0f, 0);
			float v93 = v271 - 0.300000011920929f;
			pPlayStaticEffect(32114, &F1_Arg11v11, v93, Color, F2_Arg5v11, 90.0f, 0);
			pPlayDynamicEffect(32049, &F1_Arg11v11, F1_Arg2v11, Color, 11, 2.0f, 0);

			Color[0] = 0.5f;
			Color[1] = 0.5f;
			Color[2] = 0.5f;

			pPlayDynamicEffect(0x7D65, &F1_Arg11v1,	 F1_Arg2v1	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v2,	 F1_Arg2v2	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v3,	 F1_Arg2v3	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v4,	 F1_Arg2v4	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v5,	 F1_Arg2v5	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v6,	 F1_Arg2v6	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v7,	 F1_Arg2v7	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v8,	 F1_Arg2v8	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v9,	 F1_Arg2v9	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v10, F1_Arg2v10	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
			pPlayDynamicEffect(0x7D65, &F1_Arg11v11, F1_Arg2v11	,Color,	17,	0.1f, 56);		//0x7D65 | 17 Nice
		}
		/* 
            0x7d83    // ~ Lights (1-5)             
            ------   ---------------------------------- 
            0x7d7E    // ~ Flower 1 
            0x7d7F    // ~ Flower 2 
            0x7d80    // ~ Flower 3 
            ------   ---------------------------------- 
            0x7d4d    // ~ Flame (0 / 1+) 
            0x7e73    // ~ Flame Type 2 
            0x7eaf    // ~ Flame Type 3   
            ------   ---------------------------------- 
            0x7e35    // ~ Snow Type 1 
            0x7e36    // ~ Snow Type 2 
            ------   ---------------------------------- 
            0x7e63    // ~ Heart (0 / 1) 
            ------   ---------------------------------- 
            0x7E1F    // ~ Blue Effect  
            ------   ---------------------------------- 
            0x7d30    // ~ Some Balls 
            ------   ---------------------------------- 
            0x7D65    // ~ Basic Smoke(phun khoi) 
            0x7D65    // ~ Smoke (17, )
            0x7D65    // ~ Smoke Up-Right 
            0x7D65    // ~ Smoke Type (3 / 4+) 
            0x7E04    // ~ Smoke Ball (0 / 5+) 
            ------   ---------------------------------- 
            0x7e22    // ~ Some effect 
            ------   ---------------------------------- 
            0x7e7c    // ~ Static Light 
            ------   ---------------------------------- 
            0x7d36    // ~ Blue Dynamic Light (0+) 
            ------   ---------------------------------- 
            0x7d71    // ~ Stars (id 4 like w3 elf) 
            */ 
	}
	if (IsCustomWings((WORD)AddWingsEffect_Buff, true))
	{
		DWORD Model = sub_969C50(sub_4CDA10(), AddWingsEffect_Buff);

		if (AddWingsEffect_Buff == ITEM2(12, 180))
		{
			//----	
			{
				Color[0] = 0.8f;
				Color[1] = 0.4f;
				Color[2] = 0.0f;
			}
				// ----
				pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 47, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6f, Color, F2_Arg5v1, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 24, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v2, 0.6f, Color, F2_Arg5v2, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 31, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v3, 0.6f, Color, F2_Arg5v3, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 40, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v4, 0.6f, Color, F2_Arg5v4, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 8, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v5, 0.6f, Color, F2_Arg5v5, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 17, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v6, 0.6f, Color, F2_Arg5v6, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 46, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v7, 0.6f, Color, F2_Arg5v7, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 23, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v8, 0.6f, Color, F2_Arg5v8, 1.0f, 0);
				// --
				Color[0] = 0.8f;
				Color[1] = 0.1f;
				Color[2] = 0.0f;
				// --
				pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 35, 0);
				pPlayStaticEffect(32002, &F1_Arg11v9, 1.8f, Color, F2_Arg5v9, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 39, 0);
				pPlayStaticEffect(32002, &F1_Arg11v10, 1.8f, Color, F2_Arg5v10, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 44, 0);
				pPlayStaticEffect(32002, &F1_Arg11v11, 1.8f, Color, F2_Arg5v11, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 45, 0);
				pPlayStaticEffect(32002, &F1_Arg11v12, 1.8f, Color, F2_Arg5v12, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
				pPlayStaticEffect(32002, &F1_Arg11v13, 1.8f, Color, F2_Arg5v13, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 16, 0);
				pPlayStaticEffect(32002, &F1_Arg11v14, 1.8f, Color, F2_Arg5v14, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 21, 0);
				pPlayStaticEffect(32002, &F1_Arg11v15, 1.8f, Color, F2_Arg5v15, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 22, 0);
				pPlayStaticEffect(32002, &F1_Arg11v16, 1.8f, Color, F2_Arg5v16, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 61, 0);
				pPlayStaticEffect(32002, &F1_Arg11v17, 1.8f, Color, F2_Arg5v17, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 60, 0);
				pPlayStaticEffect(32002, &F1_Arg11v18, 1.8f, Color, F2_Arg5v18, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 59, 0);
				pPlayStaticEffect(32002, &F1_Arg11v19, 1.8f, Color, F2_Arg5v19, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 62, 0);
				pPlayStaticEffect(32002, &F1_Arg11v20, 1.8f, Color, F2_Arg5v20, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 55, 0);
				pPlayStaticEffect(32002, &F1_Arg11v21, 1.8f, Color, F2_Arg5v21, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 52, 0);
				pPlayStaticEffect(32002, &F1_Arg11v22, 1.8f, Color, F2_Arg5v22, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 53, 0);
				pPlayStaticEffect(32002, &F1_Arg11v23, 1.8f, Color, F2_Arg5v23, 1.0f, 0);
				// --
				pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 54, 0);
				pPlayStaticEffect(32002, &F1_Arg11v24, 1.8f, Color, F2_Arg5v24, 1.0f, 0);
				//----

				// ---- 
				pAllowStaticEffect(F1_Thisv25, &F1_Arg11v25, F1_Arg2v25, 4, 0);
				pPlayStaticEffect(32002, &F1_Arg11v25, 1.8f, Color, F2_Arg5v25, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv26, &F1_Arg11v26, F1_Arg2v26, 42, 0);
				pPlayStaticEffect(32002, &F1_Arg11v26, 1.8f, Color, F2_Arg5v26, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv27, &F1_Arg11v27, F1_Arg2v27, 27, 0);
				pPlayStaticEffect(32002, &F1_Arg11v27, 1.8f, Color, F2_Arg5v27, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv28, &F1_Arg11v28, F1_Arg2v28, 21, 0);
				pPlayStaticEffect(32002, &F1_Arg11v28, 1.8f, Color, F2_Arg5v28, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv29, &F1_Arg11v29, F1_Arg2v29, 53, 0);
				pPlayStaticEffect(32002, &F1_Arg11v29, 1.8f, Color, F2_Arg5v29, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 59, 0);
				pPlayStaticEffect(32002, &F1_Arg11v30, 1.8f, Color, F2_Arg5v30, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 5, 0);
				pPlayStaticEffect(32002, &F1_Arg11v31, 1.8f, Color, F2_Arg5v31, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv32, &F1_Arg11v32, F1_Arg2v32, 28, 0);
				pPlayStaticEffect(32002, &F1_Arg11v32, 1.8f, Color, F2_Arg5v32, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv33, &F1_Arg11v33, F1_Arg2v33, 10, 0);
				pPlayStaticEffect(32002, &F1_Arg11v33, 1.8f, Color, F2_Arg5v33, 2.0f, 0);
				// - 
				pAllowStaticEffect(F1_Thisv34, &F1_Arg11v34, F1_Arg2v34, 33, 0);
				pPlayStaticEffect(32002, &F1_Arg11v34, 1.8f, Color, F2_Arg5v34, 2.0f, 0);

			if ( !(rand() %20) )
			{
              pCreateEffect(388, &F1_Arg11v34, F1_Arg2v34, Color, 1, 0, -1, 1, 0, 0, 0.0f, -1);
            }

		}
	else if (AddWingsEffect_Buff == ITEM2(12, 181)||AddWingsEffect_Buff == ITEM2(12, 200)) //angel & devil
		{
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 61, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5f, Color, F2_Arg5v1, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 42, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5f, Color, F2_Arg5v2, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0f, Color, F2_Arg5v3, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 41, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0f, Color, F2_Arg5v4, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 63, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0f, Color, F2_Arg5v5, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 44, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0f, Color, F2_Arg5v6, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0f, Color, F2_Arg5v7, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 59, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.4f, Color, F2_Arg5v8, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 40, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1.4f, Color, F2_Arg5v9, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 62, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 2.6f, Color, F2_Arg5v10, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 43, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 2.6f, Color, F2_Arg5v11, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 65, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 1.4f, Color, F2_Arg5v12, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 46, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1.4f, Color, F2_Arg5v13, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 58, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 2.0f, Color, F2_Arg5v14, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 39, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 2.0f, Color, F2_Arg5v15, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0f, Color, F2_Arg5v16, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 32, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 2.0f, Color, F2_Arg5v17, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 2.0f, Color, F2_Arg5v18, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19, 2.0f, Color, F2_Arg5v19, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 25, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 2.0f, Color, F2_Arg5v20, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 27, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21, 2.0f, Color, F2_Arg5v21, 1.0f, 0);
			// --
			pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v22, 0.5f, Color, F2_Arg5v22, 1.0f, 0);
			//
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 0.55f;
			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 3, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v23, 0, Color, F2_Arg5v23, 1.0f, 0);
			int ran = rand() % 100;
			if(ran  < 10)
			{
			pPlayDynamicEffect(0x7e63, &F1_Arg11v23, F1_Arg2v23, Color, 1, 0.3f, 2);
			}

		}
		else if (AddWingsEffect_Buff == ITEM2(12, 187))
		{
			
				Color[0] = 1.0f;
				Color[1] = 0.6f;
				Color[2] = 0.0f;
				pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 8, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v5, 0.4f, Color, F2_Arg5v5, 1.0f, 0);

				pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 16, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v14, 0.4f, Color, F2_Arg5v14, 1.0f, 0);

				//----
				Color[0] = 1.0f;
				Color[1] = 0.3f;
				Color[2] = 0.0f;

				pPlayStaticEffect(32002, &F1_Arg11v5,  2.6f, Color, F2_Arg5v5, 1.0f, 0);
				pPlayStaticEffect(32002, &F1_Arg11v14, 2.6f, Color, F2_Arg5v14, 1.0f, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(12, 186))
		{			
				Color[0] = 0.0f;
				Color[1] = 0.6f;
				Color[2] = 1.0f;
				pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 43, 0);
				pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 49, 0);
				pPlayStaticEffect(32131, &F1_Arg11v5, 0.8f, Color, F2_Arg5v5,  0, 0);
				pPlayStaticEffect(32131, &F1_Arg11v14,0.8f, Color, F2_Arg5v14, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 185))
		{
				Color[0] = 1.0f;
				Color[1] = 0.0f;
				Color[2] = 0.0f;

				pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 3, 0);
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 20, 0);
		
				pPlayStaticEffect(32002, &F1_Arg11v1, 3.6f, Color, F2_Arg5v1, 1.0f, 0);
				pPlayStaticEffect(32002, &F1_Arg11v2, 3.6f, Color, F2_Arg5v2, 1.0f, 0);

		}
		/*
		else if (AddWingsEffect_Buff == ITEM2(12, 192)||AddWingsEffect_Buff == ITEM2(12, 193)||AddWingsEffect_Buff == ITEM2(12, 196))
		{
	
			Color[0] = 1.0f;
			Color[1] = 1.0f;
			Color[2] = 1.0f;
		
			int RANDOM  = rand() %61;
			int RANDOM2 = rand() %61;
			
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, RANDOM, 0);
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, RANDOM2, 0);
		
			if ( !(rand() %20) )
			{
              pCreateEffect(388, &F1_Arg11v3, F1_Arg2v3, Color, 1, 0, -1, 1, 0, 0, 0.0f, -1);
            }

			if ( !(rand() %20) )
			{
              pCreateEffect(388, &F1_Arg11v1, F1_Arg2v1, Color, 1, 0, -1, 1, 0, 0, 0.0f, -1);
            }

		}
		else if (AddWingsEffect_Buff == ITEM2(12, 194))
		{	
			 Color[0] = 0.7f;
			 Color[1] = 0.7f;
			 Color[2] = 1.0f;
			
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 35, 0);
		
			if ( !(rand() %20) )
			{
              pCreateEffect(388, &F1_Arg11v3, F1_Arg2v3, Color, 1, F2_Arg5v3, -1, 0, 0, 0, 0.0f, -1);
              pCreateEffect(388, &F1_Arg11v3, F1_Arg2v3, Color, 1, F2_Arg5v3, -1, 0, 0, 0, 0.0f, -1);
            }
			if ( !(rand() %20) )
			{
              pCreateEffect(388, &F1_Arg11v1, F1_Arg2v1, Color, 1, F2_Arg5v1, -1, 0, 0, 0, 0.0f, -1);
              pCreateEffect(388, &F1_Arg11v1, F1_Arg2v1, Color, 1, F2_Arg5v1, -1, 0, 0, 0, 0.0f, -1);
            }
			int GetRand = rand() %61;
			if(GetRand!=3 && GetRand != 35)
			{
				pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, GetRand, 0);
				if ( !(rand() %20) )
				{
				pCreateEffect(388, &F1_Arg11v4, F1_Arg2v4, Color, 1, F2_Arg5v4, -1, 0, 0, 0, 0.0f, -1);
				}
			}
		}
		
		else if (AddWingsEffect_Buff == ITEM2(12, 187))
		{
				Color[0] = 1.0f;
				Color[1] = 1.0f;
				Color[2] = 1.0f;
			
				int RANDOM = rand() %60;
				int RANDOM2 = rand() %60;
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, RANDOM, 0);
				if(RANDOM2<10)
				{
				pPlayDynamicEffect(0x7E2D, &F1_Arg11v2, F1_Arg2v2, Color, 0, 0.5f, 4);
				}

                Color[0] = 0.9f;
                Color[1] = 0.3f;
                Color[2] = 0.5;
                
                pPlayDynamicEffect(32049, &F1_Arg11v2, F1_Arg2v2, Color, 11, 2.0f, 0);                            
		}
		
		else if (AddWingsEffect_Buff == ITEM2(12, 186)||AddWingsEffect_Buff == ITEM2(12, 201)) // Wing Grow Lancer
		{
			Color[0] = 0.34f;
			Color[1] = 0.25f;
			Color[2] = 1.0f;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 13, 0);
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 14, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 15, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 16, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 17, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 18, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 19, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 20, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 21, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 22, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 23, 0);
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 24, 0);
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 25, 0);

			pPlayStaticEffect(32002, &F1_Arg11v1,  0.8f, Color, F2_Arg5v1,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2,  0.8f, Color, F2_Arg5v2,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3,  0.8f, Color, F2_Arg5v3,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4,  0.8f, Color, F2_Arg5v4,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5,  0.8f, Color, F2_Arg5v5,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6,  0.8f, Color, F2_Arg5v6,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7,  0.8f, Color, F2_Arg5v7,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8,  0.8f, Color, F2_Arg5v8,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9,  0.8f, Color, F2_Arg5v9,  1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 0.8f, Color, F2_Arg5v10, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 0.8f, Color, F2_Arg5v11, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 0.8f, Color, F2_Arg5v12, 1.0f, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 0.8f, Color, F2_Arg5v13, 1.0f, 0);
	
			Color[0] = 0.4f;
			Color[1] = 0.4f;
			Color[2] = 0.8f;

			int ran = rand() % 100;
			if(ran < 5)
			{
				pPlayDynamicEffect(32049, &F1_Arg11v1,  F1_Arg2v1,  Color, 11, 1.0f, 0);
				pPlayDynamicEffect(32049, &F1_Arg11v3,  F1_Arg2v3,  Color, 11, 1.0f, 0);
				pPlayDynamicEffect(32049, &F1_Arg11v11, F1_Arg2v11, Color, 11, 1.0f, 0);
				pPlayDynamicEffect(32049, &F1_Arg11v12, F1_Arg2v12, Color, 11, 1.0f, 0);
			}
		}*/
		else if (AddWingsEffect_Buff == ITEM2(12, 221)) //Fake Cape DL Lvl 4
		{		
			Vector(0.85f, 0.82f, 1.0f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 25, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 26, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 27, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 28, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 29, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 30, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 31, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			Vector(1.0f, 0.95f, 0.49f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 32, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 33, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 34, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			Vector(0.85f, 0.82f, 1.0f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 35, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 190)) //Wing lvl4 SM
		{
			Vector(1.0f, 0.95f, 0.49f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 13, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 14, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 16, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 23, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 33, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 38, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 39, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			Vector(1.0f, 1.0f, 1.0f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 15, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 21, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 22, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 6, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 9, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 29, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 32, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 34, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 44, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 45, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 190)) //Wing lvl4 BK
		{
			Vector(0.96f, 0.31f, 0.35f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 6, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 7, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 8, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 9, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 16, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 17, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 21, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 22, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 23, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 24, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 25, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			for (int i = 29; i <= 38; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 44, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 45, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 46, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 47, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 52, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 53, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 54, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 55, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 56, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 59, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			if (rand() % 20 < 2)
				pCreateEffect3(388, Bone, F1_Arg2v1, Color, 0, F2_Arg5v1, -1, 0, 0, 0, 0.0f, -1);

			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 60, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 61, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 62, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 65, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 66, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 67, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 68, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 76, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 77, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 78, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 79, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 86, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 87, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			for (int i = 91; i <= 95; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			for (int i = 99; i <= 108; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			for (int i = 114; i <= 118; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 122, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 123, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 124, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 125, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 129, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 130, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 131, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 132, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 135, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 136, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 137, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 138, 0);
			sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			//if (rand() % 20 < 2) 
			//	pCreateEffect3(388, Bone, F1_Arg2v1, Color, 0, F2_Arg5v1, -1, 0, 0, 0, 0.0f, -1);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 192)) //Wing lvl4 FE
		{
			Vector(1.0f, 0.95f, 0.49f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 9, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 23, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 65, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 93, 0);
			sub_771310_(32002, Bone, 1.5f, Color, F2_Arg5v1, 0, 0);
			Vector(0.71f, 0.61f, 1.0f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 38, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 80, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 7, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 24, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 63, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 93, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 240)) //Wing lvl4 MG
		{
			Vector(0.85f, 0.82f, 1.0f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 72, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 79, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 9, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 17, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 25, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 33, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 41, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 49, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 57, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 65, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 195)) //Wing lvl 4 SU
		{
			Vector(1.0f, 0.95f, 0.49f, Color);
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 7, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			for (int i = 8; i <= 17; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			for (int i = 46; i <= 73; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.3f, Color, F2_Arg5v1, 0, 0);
			}
			for (int i = 98; i <= 107; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.5f, Color, F2_Arg5v1, 0, 0);
			}
			sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, 108, 0);
			sub_771310_(32002, Bone, 1.0f, Color, F2_Arg5v1, 0, 0);
			for (int i = 138; i <= 165; i++)
			{
				sub_544E60((LPVOID)Model, Bone, F1_Arg2v1, i, 0);
				sub_771310_(32002, Bone, 0.3f, Color, F2_Arg5v1, 0, 0);
			}
		}
		_asm
		{
			mov AddWingsEffect_Buff, 0x0056CA63
				jmp AddWingsEffect_Buff
		}
	}
	if (AddWingsEffect_Buff > 0x0A9D)
	{
		_asm
		{
			mov AddWingsEffect_Buff, 0x005667BB
				jmp AddWingsEffect_Buff
		}
	}
	_asm
	{
		mov AddWingsEffect_Buff, 0x00566707
			jmp AddWingsEffect_Buff
	}
}

void WingEffect::Load()
{
	SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
	SetOp((LPVOID)0x005666F7, (LPVOID)AddWingsEffect, ASM::JMP);
}
/* 
            0x7d83    // ~ Lights (1-5)             
            ------   ---------------------------------- 
            0x7d7E    // ~ Flower 1 
            0x7d7F    // ~ Flower 2 
            0x7d80    // ~ Flower 3 
            ------   ---------------------------------- 
            0x7d4d    // ~ Flame (0 / 1+) 
            0x7e73    // ~ Flame Type 2 
            0x7eaf    // ~ Flame Type 3   
            ------   ---------------------------------- 
            0x7E35    // ~ Snow Type 1 
            0x7E36    // ~ Snow Type 2 
            ------   ---------------------------------- 
            0x7E63    // ~ Heart (0 / 1) 
            ------   ---------------------------------- 
            0x7E1F    // ~ Blue Effect  
            ------   ---------------------------------- 
            0x7d30    // ~ Some Balls 
            ------   ---------------------------------- 
            0x7d65    // ~ Basic Smoke(phun khoi) 
            0x7d65    // ~ Green Smoke 
            0x7d65    // ~ Smoke Up-Right 
            0x7d65    // ~ Smoke Type (3 / 4+) 
            0x7e04    // ~ Smoke Ball (0 / 5+) 
            ------   ---------------------------------- 
            0x7e22    // ~ Some effect 
            ------   ---------------------------------- 
            0x7e7c    // ~ Static Light 
            ------   ---------------------------------- 
            0x7d36    // ~ Blue Dynamic Light (0+) 
            ------   ---------------------------------- 
            0x7d71    // ~ Stars (id 4 like w3 elf) 
			------	----------------------------------
			32291	  // Rain

			sub_72D1B0(322, (int)&v214, (int)&v214, (int)&v217, 6, SLODWORD(a2), 170.0, -1, 0, 0, -1, 0, -1); //WTF

			sub_6D9070(239, (int)&BMD, (int)&SkillPos, Color, 3, 0, -1, 0, 0, 0, 0.0, -1);
            */ 
