#pragma warning(push, 0)

// AddonEmu
#include "AsdaGlobalSync.hpp"

// IDA
#include "IDA/defs.h"

// WinAPI
#include <Windows.h>

namespace InjectMe::Hook::AsdaGlobal
{
	//int __thiscall sub_A12F40(int this)
	int sub_A12F40(int _this)
	{
		//return *(_DWORD *)(this + 28);
		return *(_DWORD *)(_this + 28);
	}

	//int __thiscall sub_9E66E7(int this)
	int sub_9E66E7(int _this)
	{
		//return sub_A12F40(this);
		return sub_A12F40(_this);
	}

	//__int64 __thiscall sub_1481500(void *this, int a2)
	__int64 sub_1481500(void *_this, int a2)
	{
		signed int v2; // esi@1
		__int64 result; // qax@1

		//v2 = *((_DWORD *)this + a2 + 1);
		v2 = *((_DWORD *)_this + a2 + 1);
		LODWORD(result) = v2++;
		result = (signed int)result;
		//*((_DWORD *)this + a2 + 1) = v2;
		*((_DWORD *)_this + a2 + 1) = v2;
		if (v2 > 1073741823)
			//*((_DWORD *)this + a2 + 1) = 0;
			*((_DWORD *)_this + a2 + 1) = 0;
		return result;
	}

	//__int64 __thiscall sub_9CB20C(void *this, int a2)
	__int64 sub_9CB20C(void *_this, int a2)
	{
		//return sub_1481500(this, a2);
		return sub_1481500(_this, a2);
	}

	//int __usercall sub_1140540<eax>(__int64 a1<edx:eax>, unsigned __int8 a2<cl>)
	__int64 sub_1140540(__int64 a1, unsigned __int8 a2)
	{
		__int64 v2; // qax@3

		__int32 edx = HIDWORD(a1);
		__int32 eax = LODWORD(a1);
		__int64 qax = a1;
		__int8	cl = a2;

		if (a2 >= 64u)
		{
			//LODWORD(v2) = 0;
			v2 = 0;
		}
		else
		{
			/*if (a2 >= 32u)
				LODWORD(v2) = 0;
			else
				v2 = a1 << (a2 & 0x1F);*/
			if (a2 >= 32u) {
				edx = eax;
				eax ^= eax;
				cl &= 0x1F;
				edx <<= cl;
				HIDWORD(v2) = edx;
				LODWORD(v2) = eax;
			}
			else {
				qax <<= cl;
				v2 = qax;
			}
		}

		return v2;
	}

	//int __usercall sub_9D45DC<eax>(__int64 a1<edx:eax>, unsigned __int8 a2<cl>)
	__int64 sub_9D45DC(__int64 a1, unsigned __int8 a2)
	{
		return sub_1140540(a1, a2);
	}

	//int __usercall sub_1140510<eax>(signed __int64 a1<edx:eax>, unsigned __int8 a2<cl>)
	int sub_1140510(signed __int64 a1, unsigned __int8 a2)
	{
		signed __int64 v2; // qax@3

		if (a2 >= 0x40u)
		{
			LODWORD(v2) = SHIDWORD(a1) >> 31;
		}
		else
		{
			if (a2 >= 0x20u)
				LODWORD(v2) = SHIDWORD(a1) >> (a2 & 0x1F);
			else
				v2 = a1 >> (a2 & 0x1F);
		}
		return v2;
	}

	int sub_9D4622(signed __int64 a1, unsigned __int8 a2)
	{
		return sub_1140510(a1, a2);
	}

	void sub_AECC20(char *BUF, const AsdaGlobalData &data)
	{
		int v4; // eax@2
		int v5; // edx@2
		int v6; // eax@3
		__int64 v7; // qax@5
		__int64 v8; // qax@9
		int v9; // eax@11
		int v11; // [sp+0h] [bp-99Ch]@0
		int v12; // [sp+4h] [bp-998h]@0
		int v13; // [sp+8h] [bp-994h]@0
		char v14; // [sp+Ch] [bp-990h]@0
		char v15; // [sp+50h] [bp-94Ch]@11
		char Dst; // [sp+51h] [bp-94Bh]@11
		int v17; // [sp+58h] [bp-944h]@11
		int v18; // [sp+68h] [bp-934h]@11
		int i; // [sp+850h] [bp-14Ch]@3
		//LARGE_INTEGER PerformanceCount; // [sp+854h] [bp-148h]@3
		LARGE_INTEGER PerformanceCount; // [sp+854h] [bp-148h]@3
		__int64 v21; // [sp+85Ch] [bp-140h]@3
		int arr[60];
		int& v22 = arr[0]; // [sp+864h] [bp-138h]@3
		int& v23 = arr[1]; // [sp+868h] [bp-134h]@3
		int& v24 = arr[2]; // [sp+86Ch] [bp-130h]@3
		int& v25 = arr[3]; // [sp+870h] [bp-12Ch]@3
		int& v26 = arr[4]; // [sp+874h] [bp-128h]@3
		int& v27 = arr[5]; // [sp+878h] [bp-124h]@3
		int& v28 = arr[6]; // [sp+87Ch] [bp-120h]@3
		int& v29 = arr[7]; // [sp+880h] [bp-11Ch]@3
		int& v30 = arr[8]; // [sp+884h] [bp-118h]@3
		int& v31 = arr[9]; // [sp+888h] [bp-114h]@3
		int& v32 = arr[10]; // [sp+88Ch] [bp-110h]@3
		int& v33 = arr[11]; // [sp+890h] [bp-10Ch]@3
		int& v34 = arr[12]; // [sp+894h] [bp-108h]@3
		int& v35 = arr[13]; // [sp+898h] [bp-104h]@3
		int& v36 = arr[14]; // [sp+89Ch] [bp-100h]@3
		int& v37 = arr[15]; // [sp+8A0h] [bp-FCh]@3
		int& v38 = arr[16]; // [sp+8A4h] [bp-F8h]@3
		int& v39 = arr[17]; // [sp+8A8h] [bp-F4h]@3
		int& v40 = arr[18]; // [sp+8ACh] [bp-F0h]@3
		int& v41 = arr[19]; // [sp+8B0h] [bp-ECh]@3
		int& v42 = arr[20]; // [sp+8B4h] [bp-E8h]@3
		int& v43 = arr[21]; // [sp+8B8h] [bp-E4h]@3
		int& v44 = arr[22]; // [sp+8BCh] [bp-E0h]@3
		int& v45 = arr[23]; // [sp+8C0h] [bp-DCh]@3
		int& v46 = arr[24]; // [sp+8C4h] [bp-D8h]@3
		int& v47 = arr[25]; // [sp+8C8h] [bp-D4h]@3
		int& v48 = arr[26]; // [sp+8CCh] [bp-D0h]@3
		int& v49 = arr[27]; // [sp+8D0h] [bp-CCh]@3
		int& v50 = arr[28]; // [sp+8D4h] [bp-C8h]@3
		int& v51 = arr[29]; // [sp+8D8h] [bp-C4h]@3
		int& v52 = arr[30]; // [sp+8DCh] [bp-C0h]@3
		int& v53 = arr[31]; // [sp+8E0h] [bp-BCh]@3
		int& v54 = arr[32]; // [sp+8E4h] [bp-B8h]@3
		int& v55 = arr[33]; // [sp+8E8h] [bp-B4h]@3
		int& v56 = arr[34]; // [sp+8ECh] [bp-B0h]@3
		int& v57 = arr[35]; // [sp+8F0h] [bp-ACh]@3
		int& v58 = arr[36]; // [sp+8F4h] [bp-A8h]@3
		int& v59 = arr[37]; // [sp+8F8h] [bp-A4h]@3
		int& v60 = arr[38]; // [sp+8FCh] [bp-A0h]@3
		int& v61 = arr[39]; // [sp+900h] [bp-9Ch]@3
		int& v62 = arr[40]; // [sp+904h] [bp-98h]@3
		int& v63 = arr[41]; // [sp+908h] [bp-94h]@3
		int& v64 = arr[42]; // [sp+90Ch] [bp-90h]@3
		int& v65 = arr[43]; // [sp+910h] [bp-8Ch]@3
		int& v66 = arr[44]; // [sp+914h] [bp-88h]@3
		int& v67 = arr[45]; // [sp+918h] [bp-84h]@3
		int& v68 = arr[46]; // [sp+91Ch] [bp-80h]@3
		int& v69 = arr[47]; // [sp+920h] [bp-7Ch]@3
		int& v70 = arr[48]; // [sp+924h] [bp-78h]@3
		int& v71 = arr[49]; // [sp+928h] [bp-74h]@3
		int& v72 = arr[50]; // [sp+92Ch] [bp-70h]@3
		int& v73 = arr[51]; // [sp+930h] [bp-6Ch]@3
		int& v74 = arr[52]; // [sp+934h] [bp-68h]@3
		int& v75 = arr[53]; // [sp+938h] [bp-64h]@3
		int& v76 = arr[54]; // [sp+93Ch] [bp-60h]@3
		int& v77 = arr[55]; // [sp+940h] [bp-5Ch]@3
		int& v78 = arr[56]; // [sp+944h] [bp-58h]@3
		int& v79 = arr[57]; // [sp+948h] [bp-54h]@3
		int& v80 = arr[58]; // [sp+94Ch] [bp-50h]@3
		int& v81 = arr[59]; // [sp+950h] [bp-4Ch]@3
		__int64 v82; // [sp+954h] [bp-48h]@3
		int v83; // [sp+95Ch] [bp-40h]@3
		int v84; // [sp+960h] [bp-3Ch]@3
		__int64 v85; // [sp+964h] [bp-38h]@3
		LARGE_INTEGER Src; // [sp+96Ch] [bp-30h]@3
		__int64 v87; // [sp+974h] [bp-28h]@3
		char v88; // [sp+97Ch] [bp-20h]@3
		int v89; // [sp+97Dh] [bp-1Fh]@3
		int v90; // [sp+981h] [bp-1Bh]@3
		int v91; // [sp+985h] [bp-17h]@3
		__int16 v92; // [sp+989h] [bp-13h]@3
		char v93; // [sp+98Bh] [bp-11h]@3
		int v94; // [sp+98Ch] [bp-10h]@3
		__int16 v95; // [sp+990h] [bp-Ch]@3
		__int16 v96; // [sp+992h] [bp-Ah]@3
		__int16 v97; // [sp+994h] [bp-8h]@3
		__int16 v98; // [sp+996h] [bp-6h]@3
		unsigned int v99; // [sp+998h] [bp-4h]@1
		int v100; // [sp+99Ch] [bp+0h]@1

		if (false) {}
		else
		{
			v88 = 0;
			v89 = 0;
			v90 = 0;
			v91 = 0;
			v92 = 0;
			v93 = 0;
			LODWORD(v87) = 0x0057A7A5;
			HIDWORD(v87) = 0;
			Src.QuadPart = 0i64;
			v85 = 0i64;
			v83 = 0;
			v84 = 0;
			v82 = 1i64;
			v22 = 3;
			v23 = 0;
			v24 = 4;
			v25 = 0;
			v26 = 8;
			v27 = 0;
			v28 = 11;
			v29 = 0;
			v30 = 12;
			v31 = 0;
			v32 = 14;
			v33 = 0;
			v34 = 15;
			v35 = 0;
			v36 = 16;
			v37 = 0;
			v38 = 18;
			v39 = 0;
			v40 = 20;
			v41 = 0;
			v42 = 21;
			v43 = 0;
			v44 = 25;
			v45 = 0;
			v46 = 26;
			v47 = 0;
			v48 = 27;
			v49 = 0;
			v50 = 28;
			v51 = 0;
			v52 = 30;
			v53 = 0;
			v54 = 32;
			v55 = 0;
			v56 = 33;
			v57 = 0;
			v58 = 36;
			v59 = 0;
			v60 = 42;
			v61 = 0;
			v62 = 43;
			v63 = 0;
			v64 = 45;
			v65 = 0;
			v66 = 47;
			v67 = 0;
			v68 = 50;
			v69 = 0;
			v70 = 52;
			v71 = 0;
			v72 = 53;
			v73 = 0;
			v74 = 54;
			v75 = 0;
			v76 = 57;
			v77 = 0;
			v78 = 60;
			v79 = 0;
			v80 = 62;
			v81 = 0;
			v6 = sub_9E66E7(data.GetAddress3());
			v21 = v87 + sub_9CB20C((void*)data.GetAddress4(), v6);
			QueryPerformanceCounter(&PerformanceCount);
			Src = PerformanceCount;
			for (i = 0; ; ++i)
			{
				if (i < 30)
				{
					v7 = sub_9D45DC(v82, *(&v22 + 2 * i));
					v85 = v7;
					v83 = v21 & 1;
					v84 = 0;
					if (v83 != 1 || v84)
					{
						v85 = ~v85;
						Src.QuadPart = v85 & *(_QWORD *)&Src;
					}
					else
					{
						Src.QuadPart = v85 | *(_QWORD *)&Src;
					}
					LODWORD(v8) = sub_9D4622(v21, 1u);
					v21 = v8;
					if (v8)
						continue;
				}
				break;
			}
			v15 = 0;
			memcpy_s(BUF, 8u, &Src, 8u);
		}
	}

	void AsdaGlobalSync(char *const BUF, const unsigned long OFS, const AsdaGlobalData &data)
	{
		sub_AECC20(BUF + OFS, data);
	}
}

#pragma warning(pop)