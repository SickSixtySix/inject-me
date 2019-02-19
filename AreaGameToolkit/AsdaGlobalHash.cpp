#pragma warning(push, 0)

// InjectMe
#include "AsdaGlobalHash.hpp"

// IDA
#include "IDA/defs.h"

// C
#include <string.h>

namespace InjectMe::Hook::AsdaGlobal
{
	void sub_A56D60(int a1)
	{
		*(_DWORD *)a1 = 0;
		*(_DWORD *)(a1 + 4) = 0;
		*(_DWORD *)(a1 + 8) = 1732584193;
		*(_DWORD *)(a1 + 12) = -271733879;
		*(_DWORD *)(a1 + 16) = -1732584194;
		*(_DWORD *)(a1 + 20) = 271733878;
	}

	int sub_A56DD0(int a1, int a2)
	{
		int v2;
		int v3;
		int v4;
		int v5;
		int v6;
		int v7;
		int v8;
		int v9;
		int v10;
		int v11;
		int v12;
		int v13;
		int v14;
		int v15;
		int v16;
		int v17;
		int v18;
		int v19;
		int v20;
		unsigned int v21;
		int v22;
		unsigned int v23;
		int v24;
		unsigned int v25;
		int v26;
		unsigned int v27;
		int v28;
		unsigned int v29;
		int v30;
		unsigned int v31;
		int v32;
		unsigned int v33;
		int v34;
		unsigned int v35;
		int v36;
		unsigned int v37;
		int v38;
		unsigned int v39;
		int v40;
		unsigned int v41;
		int v42;
		unsigned int v43;
		int v44;
		unsigned int v45;
		int v46;
		unsigned int v47;
		int v48;
		unsigned int v49;
		int v50;
		unsigned int v51;
		int v52;
		unsigned int v53;
		int v54;
		unsigned int v55;
		int v56;
		unsigned int v57;
		int v58;
		unsigned int v59;
		int v60;
		unsigned int v61;
		int v62;
		unsigned int v63;
		int v64;
		unsigned int v65;
		int v66;
		unsigned int v67;
		int v68;
		unsigned int v69;
		int v70;
		unsigned int v71;
		int v72;
		unsigned int v73;
		int v74;
		unsigned int v75;
		int v76;
		unsigned int v77;
		int v78;
		unsigned int v79;
		int v80;
		unsigned int v81;
		int v82;
		unsigned int v83;
		int v84;
		unsigned int v85;
		int v86;
		unsigned int v87;
		int v88;
		unsigned int v89;
		int v90;
		unsigned int v91;
		int v92;
		unsigned int v93;
		int v94;
		unsigned int v95;
		int v96;
		unsigned int v97;
		int v98;
		unsigned int v99;
		int v100;
		unsigned int v101;
		int v102;
		unsigned int v103;
		int v104;
		unsigned int v105;
		int v106;
		unsigned int v107;
		int v108;
		unsigned int v109;
		int v110;
		unsigned int v111;
		int v112;
		unsigned int v113;
		int v114;
		unsigned int v115;
		int v116;
		unsigned int v117;
		int v118;
		unsigned int v119;
		int v120;
		unsigned int v121;
		int v122;
		unsigned int v123;
		int v124;
		unsigned int v125;
		int v126;
		unsigned int v127;
		int v128;
		unsigned int v129;
		int v130;
		unsigned int v131;
		int v132;
		unsigned int v133;
		int v134;
		unsigned int v135;
		int v136;
		unsigned int v137;
		int v138;
		unsigned int v139;
		int v140;
		unsigned int v141;
		int v142;
		unsigned int v143;
		int v144;
		unsigned int v145;
		int v146;
		unsigned int v147;
		int result;

		v2 = (*(_BYTE *)(a2 + 3) << 24) | (*(_BYTE *)(a2 + 2) << 16) | (*(_BYTE *)(a2 + 1) << 8) | *(_BYTE *)a2;
		v3 = (*(_BYTE *)(a2 + 7) << 24) | (*(_BYTE *)(a2 + 6) << 16) | (*(_BYTE *)(a2 + 5) << 8) | *(_BYTE *)(a2 + 4);
		v4 = (*(_BYTE *)(a2 + 11) << 24) | (*(_BYTE *)(a2 + 10) << 16) | (*(_BYTE *)(a2 + 9) << 8) | *(_BYTE *)(a2 + 8);
		v5 = (*(_BYTE *)(a2 + 15) << 24) | (*(_BYTE *)(a2 + 14) << 16) | (*(_BYTE *)(a2 + 13) << 8) | *(_BYTE *)(a2 + 12);
		v6 = (*(_BYTE *)(a2 + 19) << 24) | (*(_BYTE *)(a2 + 18) << 16) | (*(_BYTE *)(a2 + 17) << 8) | *(_BYTE *)(a2 + 16);
		v7 = (*(_BYTE *)(a2 + 23) << 24) | (*(_BYTE *)(a2 + 22) << 16) | (*(_BYTE *)(a2 + 21) << 8) | *(_BYTE *)(a2 + 20);
		v8 = (*(_BYTE *)(a2 + 27) << 24) | (*(_BYTE *)(a2 + 26) << 16) | (*(_BYTE *)(a2 + 25) << 8) | *(_BYTE *)(a2 + 24);
		v9 = (*(_BYTE *)(a2 + 31) << 24) | (*(_BYTE *)(a2 + 30) << 16) | (*(_BYTE *)(a2 + 29) << 8) | *(_BYTE *)(a2 + 28);
		v10 = (*(_BYTE *)(a2 + 35) << 24) | (*(_BYTE *)(a2 + 34) << 16) | (*(_BYTE *)(a2 + 33) << 8) | *(_BYTE *)(a2 + 32);
		v11 = (*(_BYTE *)(a2 + 39) << 24) | (*(_BYTE *)(a2 + 38) << 16) | (*(_BYTE *)(a2 + 37) << 8) | *(_BYTE *)(a2 + 36);
		v12 = (*(_BYTE *)(a2 + 43) << 24) | (*(_BYTE *)(a2 + 42) << 16) | (*(_BYTE *)(a2 + 41) << 8) | *(_BYTE *)(a2 + 40);
		v13 = (*(_BYTE *)(a2 + 47) << 24) | (*(_BYTE *)(a2 + 46) << 16) | (*(_BYTE *)(a2 + 45) << 8) | *(_BYTE *)(a2 + 44);
		v14 = (*(_BYTE *)(a2 + 51) << 24) | (*(_BYTE *)(a2 + 50) << 16) | (*(_BYTE *)(a2 + 49) << 8) | *(_BYTE *)(a2 + 48);
		v15 = (*(_BYTE *)(a2 + 55) << 24) | (*(_BYTE *)(a2 + 54) << 16) | (*(_BYTE *)(a2 + 53) << 8) | *(_BYTE *)(a2 + 52);
		v16 = (*(_BYTE *)(a2 + 59) << 24) | (*(_BYTE *)(a2 + 58) << 16) | (*(_BYTE *)(a2 + 57) << 8) | *(_BYTE *)(a2 + 56);
		v17 = (*(_BYTE *)(a2 + 63) << 24) | (*(_BYTE *)(a2 + 62) << 16) | (*(_BYTE *)(a2 + 61) << 8) | *(_BYTE *)(a2 + 60);
		v18 = *(_DWORD *)(a1 + 12);
		v19 = *(_DWORD *)(a1 + 16);
		v20 = *(_DWORD *)(a1 + 20);
		v21 = *(_DWORD *)(a1 + 8) + v2 + (v20 ^ v18 & (v20 ^ v19)) - 680876936;
		v22 = v18 + ((v21 >> 25) | (v21 << 7));
		v23 = v20 + v3 + (v19 ^ v22 & (v19 ^ v18)) - 389564586;
		v24 = v22 + ((v23 >> 20) | (v23 << 12));
		v25 = v19 + v4 + (v18 ^ v24 & (v18 ^ v22)) + 606105819;
		v26 = v24 + ((v25 >> 15) | (v25 << 17));
		v27 = v18 + v5 + (v22 ^ v26 & (v22 ^ v24)) - 1044525330;
		v28 = v26 + ((v27 >> 10) | (v27 << 22));
		v29 = v22 + v6 + (v24 ^ v28 & (v24 ^ v26)) - 176418897;
		v30 = v28 + ((v29 >> 25) | (v29 << 7));
		v31 = v24 + v7 + (v26 ^ v30 & (v26 ^ v28)) + 1200080426;
		v32 = v30 + ((v31 >> 20) | (v31 << 12));
		v33 = v26 + v8 + (v28 ^ v32 & (v28 ^ v30)) - 1473231341;
		v34 = v32 + ((v33 >> 15) | (v33 << 17));
		v35 = v28 + v9 + (v30 ^ v34 & (v30 ^ v32)) - 45705983;
		v36 = v34 + ((v35 >> 10) | (v35 << 22));
		v37 = v30 + v10 + (v32 ^ v36 & (v32 ^ v34)) + 1770035416;
		v38 = v36 + ((v37 >> 25) | (v37 << 7));
		v39 = v32 + v11 + (v34 ^ v38 & (v34 ^ v36)) - 1958414417;
		v40 = v38 + ((v39 >> 20) | (v39 << 12));
		v41 = v34 + v12 + (v36 ^ v40 & (v36 ^ v38)) - 42063;
		v42 = v40 + ((v41 >> 15) | (v41 << 17));
		v43 = v36 + v13 + (v38 ^ v42 & (v38 ^ v40)) - 1990404162;
		v44 = v42 + ((v43 >> 10) | (v43 << 22));
		v45 = v38 + v14 + (v40 ^ v44 & (v40 ^ v42)) + 1804603682;
		v46 = v44 + ((v45 >> 25) | (v45 << 7));
		v47 = v40 + v15 + (v42 ^ v46 & (v42 ^ v44)) - 40341101;
		v48 = v46 + ((v47 >> 20) | (v47 << 12));
		v49 = v42 + v16 + (v44 ^ v48 & (v44 ^ v46)) - 1502002290;
		v50 = v48 + ((v49 >> 15) | (v49 << 17));
		v51 = v44 + v17 + (v46 ^ v50 & (v46 ^ v48)) + 1236535329;
		v52 = v50 + ((v51 >> 10) | (v51 << 22));
		v53 = v46 + v3 + (v50 ^ v48 & (v50 ^ v52)) - 165796510;
		v54 = v52 + ((v53 >> 27) | 32 * v53);
		v55 = v48 + v8 + (v52 ^ v50 & (v52 ^ v54)) - 1069501632;
		v56 = v54 + ((v55 >> 23) | (v55 << 9));
		v57 = v50 + v13 + (v54 ^ v52 & (v54 ^ v56)) + 643717713;
		v58 = v56 + ((v57 >> 18) | (v57 << 14));
		v59 = v52 + v2 + (v56 ^ v54 & (v56 ^ v58)) - 373897302;
		v60 = v58 + ((v59 >> 12) | (v59 << 20));
		v61 = v54 + v7 + (v58 ^ v56 & (v58 ^ v60)) - 701558691;
		v62 = v60 + ((v61 >> 27) | 32 * v61);
		v63 = (unsigned int)((char*)0x02441453 + v56 + v12 + (v60 ^ v58 & (v60 ^ v62)));
		v64 = v62 + ((v63 >> 23) | (v63 << 9));
		v65 = v58 + v17 + (v62 ^ v60 & (v62 ^ v64)) - 660478335;
		v66 = v64 + ((v65 >> 18) | (v65 << 14));
		v67 = v60 + v6 + (v64 ^ v62 & (v64 ^ v66)) - 405537848;
		v68 = v66 + ((v67 >> 12) | (v67 << 20));
		v69 = v62 + v11 + (v66 ^ v64 & (v66 ^ v68)) + 568446438;
		v70 = v68 + ((v69 >> 27) | 32 * v69);
		v71 = v64 + v16 + (v68 ^ v66 & (v68 ^ v70)) - 1019803690;
		v72 = v70 + ((v71 >> 23) | (v71 << 9));
		v73 = v66 + v5 + (v70 ^ v68 & (v70 ^ v72)) - 187363961;
		v74 = v72 + ((v73 >> 18) | (v73 << 14));
		v75 = v68 + v10 + (v72 ^ v70 & (v72 ^ v74)) + 1163531501;
		v76 = v74 + ((v75 >> 12) | (v75 << 20));
		v77 = v70 + v15 + (v74 ^ v72 & (v74 ^ v76)) - 1444681467;
		v78 = v76 + ((v77 >> 27) | 32 * v77);
		v79 = v72 + v4 + (v76 ^ v74 & (v76 ^ v78)) - 51403784;
		v80 = v78 + ((v79 >> 23) | (v79 << 9));
		v81 = v74 + v9 + (v78 ^ v76 & (v78 ^ v80)) + 1735328473;
		v82 = v80 + ((v81 >> 18) | (v81 << 14));
		v83 = v76 + v14 + (v80 ^ v78 & (v80 ^ v82)) - 1926607734;
		v84 = v82 + ((v83 >> 12) | (v83 << 20));
		v85 = v78 + v7 + (v80 ^ v82 ^ v84) - 378558;
		v86 = v84 + ((v85 >> 28) | 16 * v85);
		v87 = v80 + v10 + (v82 ^ v84 ^ v86) - 2022574463;
		v88 = v86 + ((v87 >> 21) | (v87 << 11));
		v89 = v82 + v13 + (v84 ^ v86 ^ v88) + 1839030562;
		v90 = v88 + ((v89 >> 16) | (v89 << 16));
		v91 = v84 + v16 + (v86 ^ v88 ^ v90) - 35309556;
		v92 = v90 + ((v91 >> 9) | (v91 << 23));
		v93 = v86 + v3 + (v88 ^ v90 ^ v92) - 1530992060;
		v94 = v92 + ((v93 >> 28) | 16 * v93);
		v95 = v88 + v6 + (v90 ^ v92 ^ v94) + 1272893353;
		v96 = v94 + ((v95 >> 21) | (v95 << 11));
		v97 = v90 + v9 + (v92 ^ v94 ^ v96) - 155497632;
		v98 = v96 + ((v97 >> 16) | (v97 << 16));
		v99 = v92 + v12 + (v94 ^ v96 ^ v98) - 1094730640;
		v100 = v98 + ((v99 >> 9) | (v99 << 23));
		v101 = v94 + v15 + (v96 ^ v98 ^ v100) + 681279174;
		v102 = v100 + ((v101 >> 28) | 16 * v101);
		v103 = v96 + v2 + (v98 ^ v100 ^ v102) - 358537222;
		v104 = v102 + ((v103 >> 21) | (v103 << 11));
		v105 = v98 + v5 + (v100 ^ v102 ^ v104) - 722521979;
		v106 = v104 + ((v105 >> 16) | (v105 << 16));
		v107 = v100 + v8 + (v102 ^ v104 ^ v106) + 76029189;
		v108 = v106 + ((v107 >> 9) | (v107 << 23));
		v109 = v102 + v11 + (v104 ^ v106 ^ v108) - 640364487;
		v110 = v108 + ((v109 >> 28) | 16 * v109);
		v111 = v104 + v14 + (v106 ^ v108 ^ v110) - 421815835;
		v112 = v110 + ((v111 >> 21) | (v111 << 11));
		v113 = v106 + v17 + (v108 ^ v110 ^ v112) + 530742520;
		v114 = v112 + ((v113 >> 16) | (v113 << 16));
		v115 = v108 + v4 + (v110 ^ v112 ^ v114) - 995338651;
		v116 = v114 + ((v115 >> 9) | (v115 << 23));
		v117 = v110 + v2 + (v114 ^ (v116 | ~v112)) - 198630844;
		v118 = v116 + ((v117 >> 26) | (v117 << 6));
		v119 = v112 + v9 + (v116 ^ (v118 | ~v114)) + 1126891415;
		v120 = v118 + ((v119 >> 22) | (v119 << 10));
		v121 = v114 + v16 + (v118 ^ (v120 | ~v116)) - 1416354905;
		v122 = v120 + ((v121 >> 17) | (v121 << 15));
		v123 = v116 + v7 + (v120 ^ (v122 | ~v118)) - 57434055;
		v124 = v122 + ((v123 >> 11) | (v123 << 21));
		v125 = v118 + v14 + (v122 ^ (v124 | ~v120)) + 1700485571;
		v126 = v124 + ((v125 >> 26) | (v125 << 6));
		v127 = v120 + v5 + (v124 ^ (v126 | ~v122)) - 1894986606;
		v128 = v126 + ((v127 >> 22) | (v127 << 10));
		v129 = v122 + v12 + (v126 ^ (v128 | ~v124)) - 1051523;
		v130 = v128 + ((v129 >> 17) | (v129 << 15));
		v131 = v124 + v3 + (v128 ^ (v130 | ~v126)) - 2054922799;
		v132 = v130 + ((v131 >> 11) | (v131 << 21));
		v133 = v126 + v10 + (v130 ^ (v132 | ~v128)) + 1873313359;
		v134 = v132 + ((v133 >> 26) | (v133 << 6));
		v135 = v128 + v17 + (v132 ^ (v134 | ~v130)) - 30611744;
		v136 = v134 + ((v135 >> 22) | (v135 << 10));
		v137 = v130 + v8 + (v134 ^ (v136 | ~v132)) - 1560198380;
		v138 = v136 + ((v137 >> 17) | (v137 << 15));
		v139 = v132 + v15 + (v136 ^ (v138 | ~v134)) + 1309151649;
		v140 = v138 + ((v139 >> 11) | (v139 << 21));
		v141 = v134 + v6 + (v138 ^ (v140 | ~v136)) - 145523070;
		v142 = v140 + ((v141 >> 26) | (v141 << 6));
		v143 = v136 + v13 + (v140 ^ (v142 | ~v138)) - 1120210379;
		v144 = v142 + ((v143 >> 22) | (v143 << 10));
		v145 = v138 + v4 + (v142 ^ (v144 | ~v140)) + 718787259;
		v146 = v144 + ((v145 >> 17) | (v145 << 15));
		v147 = v140 + v11 + (v144 ^ (v146 | ~v142)) - 343485551;
		*(_DWORD *)(a1 + 8) += v142;
		*(_DWORD *)(a1 + 12) += v146 + ((v147 >> 11) | (v147 << 21));
		*(_DWORD *)(a1 + 16) += v146;
		result = a1;
		*(_DWORD *)(a1 + 20) += v144;
		return result;
	}

	void sub_A580B0(int a1, char *Src, size_t a3)
	{
		size_t Size;
		int v5;

		if (a3)
		{
			v5 = *(_DWORD *)a1 & 63;
			Size = 64 - v5;
			*(_DWORD *)a1 += a3;
			*(_DWORD *)a1 = *(_DWORD *)a1;
			if (*(_DWORD *)a1 < a3)
				++*(_DWORD *)(a1 + 4);
			if (v5)
			{
				if (a3 >= Size)
				{
					memcpy((void *)(a1 + v5 + 24), Src, Size);
					sub_A56DD0(a1, a1 + 24);
					a3 -= Size;
					Src += Size;
					v5 = 0;
				}
			}
			while (a3 >= 64)
			{
				sub_A56DD0(a1, (int)Src);
				a3 -= 64;
				Src += 64;
			}
			if (a3)
				memcpy((void *)(a1 + v5 + 24), Src, a3);
		}
	}

	_BYTE unk_17F8578[] = { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	void sub_A58200(int a2, int a3)
	{
		int v4;
		int v5;
		int v6;
		int v7;
		_QWORD v8;
		char v9;
		char v10;
		__int16 v11;
		char v12;
		char v13;
		int v14;
		unsigned int v15;
		int v16;
		int v17;
		void *v18;
		unsigned int v19;
		int v20;

		v15 = *(_QWORD *)a2 >> 29;
		v14 = 8 * *(_DWORD *)a2;
		v8 = v14;
		v9 = (unsigned int)v14 >> 16;
		v11 = v15;
		v12 = v15 >> 16;
		v17 = *(_DWORD *)a2 & 0x3F;
		if ((unsigned int)v17 >= 0x38)
			v7 = 120 - v17;
		else
			v7 = 56 - v17;
		v16 = v7;
		sub_A580B0(a2, (char *)&unk_17F8578[0], v7);
		sub_A580B0(a2, (char *)&v8, 8u);
		*(_BYTE *)a3 = *(_BYTE *)(a2 + 8);
		*(_BYTE *)(a3 + 1) = *(_WORD *)(a2 + 8) >> 8;
		*(_BYTE *)(a3 + 2) = *(_DWORD *)(a2 + 8) >> 16;
		*(_BYTE *)(a3 + 3) = *(_DWORD *)(a2 + 8) >> 24;
		*(_BYTE *)(a3 + 4) = *(_BYTE *)(a2 + 12);
		*(_BYTE *)(a3 + 5) = *(_WORD *)(a2 + 12) >> 8;
		*(_BYTE *)(a3 + 6) = *(_DWORD *)(a2 + 12) >> 16;
		*(_BYTE *)(a3 + 7) = *(_DWORD *)(a2 + 12) >> 24;
		*(_BYTE *)(a3 + 8) = *(_BYTE *)(a2 + 16);
		*(_BYTE *)(a3 + 9) = *(_WORD *)(a2 + 16) >> 8;
		*(_BYTE *)(a3 + 10) = *(_DWORD *)(a2 + 16) >> 16;
		*(_BYTE *)(a3 + 11) = *(_DWORD *)(a2 + 16) >> 24;
		*(_BYTE *)(a3 + 12) = *(_BYTE *)(a2 + 20);
		*(_BYTE *)(a3 + 13) = *(_WORD *)(a2 + 20) >> 8;
		*(_BYTE *)(a3 + 14) = *(_DWORD *)(a2 + 20) >> 16;
		*(_BYTE *)(a3 + 15) = *(_DWORD *)(a2 + 20) >> 24;
	}

	void AsdaGlobalHash(char *const BUF, const unsigned long HSH_OFS, const unsigned long DAT_LEN, const unsigned long DAT_OFS)
	{
		char tmpBUF[32768];

		auto src = reinterpret_cast<char*>(BUF + DAT_OFS);
		auto hsh = reinterpret_cast<int>(BUF + HSH_OFS);
		auto dst = reinterpret_cast<int>(tmpBUF);

		sub_A56D60(dst);
		sub_A580B0(dst, src, DAT_LEN);
		sub_A58200(dst, hsh);
	}
}

#pragma warning(pop)