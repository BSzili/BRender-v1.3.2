/*
 * Copyright (c) 1992,1993-1995 Argonaut Technologies Limited. All rights reserved.
 *
 * $Id: fixed.c 1.1 1997/12/10 16:41:21 jon Exp $
 * $Locker: $
 *
 * Various fixed point support functions
 */
#if defined(__WATCOMC__) && defined(__TARGET_MSC__)

#pragma aux sqrt "_*" parm caller [] modify [eax ecx edx] ;
#pragma aux pow "_*" parm caller [] modify [eax ecx edx] ;
#endif

#include "brender.h"
#include "brmath.h"

BR_RCS_ID("$Id: fixed.c 1.1 1997/12/10 16:41:21 jon Exp $")

br_fixed_ls BR_PUBLIC_ENTRY BrFixedSqrt(br_fixed_ls a)
{
	return BrFloatToFixed(BrFloatSqrt(BrFixedToFloat(a)));
}

br_fixed_ls BR_PUBLIC_ENTRY BrFixedPow(br_fixed_ls a, br_fixed_ls b)
{
	return BrFloatToFixed(BrFloatPow(BrFixedToFloat(a),BrFixedToFloat(b)));
}

br_fixed_ls BR_PUBLIC_ENTRY BrFixedDiv(br_fixed_ls numerator, br_fixed_ls denominator)
{
    br_scalar n = BrFixedToScalar(numerator);
    br_scalar d = BrFixedToScalar(denominator);
    return BrScalarToFixed(n / d);
}

#if 0
/*
 * Reciprocal table
 *
 * 0x8000000/x from 0 2048
 */
unsigned long BR_ASM_DATA _reciprocal[2048] = {
	0x00010000,0x000010000,0x000008000,0x000005555,0x000004000,0x000003333,0x000002AAA,0x000002492,
	0x00002000,0x000001C71,0x000001999,0x000001745,0x000001555,0x0000013B1,0x000001249,0x000001111,
	0x00001000,0x000000F0F,0x000000E38,0x000000D79,0x000000CCC,0x000000C30,0x000000BA2,0x000000B21,
	0x00000AAA,0x000000A3D,0x0000009D8,0x00000097B,0x000000924,0x0000008D3,0x000000888,0x000000842,
	0x00000800,0x0000007C1,0x000000787,0x000000750,0x00000071C,0x0000006EB,0x0000006BC,0x000000690,
	0x00000666,0x00000063E,0x000000618,0x0000005F4,0x0000005D1,0x0000005B0,0x000000590,0x000000572,
	0x00000555,0x000000539,0x00000051E,0x000000505,0x0000004EC,0x0000004D4,0x0000004BD,0x0000004A7,
	0x00000492,0x00000047D,0x000000469,0x000000456,0x000000444,0x000000432,0x000000421,0x000000410,
	0x00000400,0x0000003F0,0x0000003E0,0x0000003D2,0x0000003C3,0x0000003B5,0x0000003A8,0x00000039B,
	0x0000038E,0x000000381,0x000000375,0x000000369,0x00000035E,0x000000353,0x000000348,0x00000033D,
	0x00000333,0x000000329,0x00000031F,0x000000315,0x00000030C,0x000000303,0x0000002FA,0x0000002F1,
	0x000002E8,0x0000002E0,0x0000002D8,0x0000002D0,0x0000002C8,0x0000002C0,0x0000002B9,0x0000002B1,
	0x000002AA,0x0000002A3,0x00000029C,0x000000295,0x00000028F,0x000000288,0x000000282,0x00000027C,
	0x00000276,0x000000270,0x00000026A,0x000000264,0x00000025E,0x000000259,0x000000253,0x00000024E,
	0x00000249,0x000000243,0x00000023E,0x000000239,0x000000234,0x000000230,0x00000022B,0x000000226,
	0x00000222,0x00000021D,0x000000219,0x000000214,0x000000210,0x00000020C,0x000000208,0x000000204,
	0x00000200,0x0000001FC,0x0000001F8,0x0000001F4,0x0000001F0,0x0000001EC,0x0000001E9,0x0000001E5,
	0x000001E1,0x0000001DE,0x0000001DA,0x0000001D7,0x0000001D4,0x0000001D0,0x0000001CD,0x0000001CA,
	0x000001C7,0x0000001C3,0x0000001C0,0x0000001BD,0x0000001BA,0x0000001B7,0x0000001B4,0x0000001B2,
	0x000001AF,0x0000001AC,0x0000001A9,0x0000001A6,0x0000001A4,0x0000001A1,0x00000019E,0x00000019C,
	0x00000199,0x000000197,0x000000194,0x000000192,0x00000018F,0x00000018D,0x00000018A,0x000000188,
	0x00000186,0x000000183,0x000000181,0x00000017F,0x00000017D,0x00000017A,0x000000178,0x000000176,
	0x00000174,0x000000172,0x000000170,0x00000016E,0x00000016C,0x00000016A,0x000000168,0x000000166,
	0x00000164,0x000000162,0x000000160,0x00000015E,0x00000015C,0x00000015A,0x000000158,0x000000157,
	0x00000155,0x000000153,0x000000151,0x000000150,0x00000014E,0x00000014C,0x00000014A,0x000000149,
	0x00000147,0x000000146,0x000000144,0x000000142,0x000000141,0x00000013F,0x00000013E,0x00000013C,
	0x0000013B,0x000000139,0x000000138,0x000000136,0x000000135,0x000000133,0x000000132,0x000000130,
	0x0000012F,0x00000012E,0x00000012C,0x00000012B,0x000000129,0x000000128,0x000000127,0x000000125,
	0x00000124,0x000000123,0x000000121,0x000000120,0x00000011F,0x00000011E,0x00000011C,0x00000011B,
	0x0000011A,0x000000119,0x000000118,0x000000116,0x000000115,0x000000114,0x000000113,0x000000112,
	0x00000111,0x00000010F,0x00000010E,0x00000010D,0x00000010C,0x00000010B,0x00000010A,0x000000109,
	0x00000108,0x000000107,0x000000106,0x000000105,0x000000104,0x000000103,0x000000102,0x000000101,
	0x00000100,0x0000000FF,0x0000000FE,0x0000000FD,0x0000000FC,0x0000000FB,0x0000000FA,0x0000000F9,
	0x000000F8,0x0000000F7,0x0000000F6,0x0000000F5,0x0000000F4,0x0000000F3,0x0000000F2,0x0000000F1,
	0x000000F0,0x0000000F0,0x0000000EF,0x0000000EE,0x0000000ED,0x0000000EC,0x0000000EB,0x0000000EA,
	0x000000EA,0x0000000E9,0x0000000E8,0x0000000E7,0x0000000E6,0x0000000E5,0x0000000E5,0x0000000E4,
	0x000000E3,0x0000000E2,0x0000000E1,0x0000000E1,0x0000000E0,0x0000000DF,0x0000000DE,0x0000000DE,
	0x000000DD,0x0000000DC,0x0000000DB,0x0000000DB,0x0000000DA,0x0000000D9,0x0000000D9,0x0000000D8,
	0x000000D7,0x0000000D6,0x0000000D6,0x0000000D5,0x0000000D4,0x0000000D4,0x0000000D3,0x0000000D2,
	0x000000D2,0x0000000D1,0x0000000D0,0x0000000D0,0x0000000CF,0x0000000CE,0x0000000CE,0x0000000CD,
	0x000000CC,0x0000000CC,0x0000000CB,0x0000000CA,0x0000000CA,0x0000000C9,0x0000000C9,0x0000000C8,
	0x000000C7,0x0000000C7,0x0000000C6,0x0000000C5,0x0000000C5,0x0000000C4,0x0000000C4,0x0000000C3,
	0x000000C3,0x0000000C2,0x0000000C1,0x0000000C1,0x0000000C0,0x0000000C0,0x0000000BF,0x0000000BF,
	0x000000BE,0x0000000BD,0x0000000BD,0x0000000BC,0x0000000BC,0x0000000BB,0x0000000BB,0x0000000BA,
	0x000000BA,0x0000000B9,0x0000000B9,0x0000000B8,0x0000000B8,0x0000000B7,0x0000000B7,0x0000000B6,
	0x000000B6,0x0000000B5,0x0000000B5,0x0000000B4,0x0000000B4,0x0000000B3,0x0000000B3,0x0000000B2,
	0x000000B2,0x0000000B1,0x0000000B1,0x0000000B0,0x0000000B0,0x0000000AF,0x0000000AF,0x0000000AE,
	0x000000AE,0x0000000AD,0x0000000AD,0x0000000AC,0x0000000AC,0x0000000AC,0x0000000AB,0x0000000AB,
	0x000000AA,0x0000000AA,0x0000000A9,0x0000000A9,0x0000000A8,0x0000000A8,0x0000000A8,0x0000000A7,
	0x000000A7,0x0000000A6,0x0000000A6,0x0000000A5,0x0000000A5,0x0000000A5,0x0000000A4,0x0000000A4,
	0x000000A3,0x0000000A3,0x0000000A3,0x0000000A2,0x0000000A2,0x0000000A1,0x0000000A1,0x0000000A1,
	0x000000A0,0x0000000A0,0x00000009F,0x00000009F,0x00000009F,0x00000009E,0x00000009E,0x00000009D,
	0x0000009D,0x00000009D,0x00000009C,0x00000009C,0x00000009C,0x00000009B,0x00000009B,0x00000009A,
	0x0000009A,0x00000009A,0x000000099,0x000000099,0x000000099,0x000000098,0x000000098,0x000000098,
	0x00000097,0x000000097,0x000000097,0x000000096,0x000000096,0x000000095,0x000000095,0x000000095,
	0x00000094,0x000000094,0x000000094,0x000000093,0x000000093,0x000000093,0x000000092,0x000000092,
	0x00000092,0x000000091,0x000000091,0x000000091,0x000000090,0x000000090,0x000000090,0x000000090,
	0x0000008F,0x00000008F,0x00000008F,0x00000008E,0x00000008E,0x00000008E,0x00000008D,0x00000008D,
	0x0000008D,0x00000008C,0x00000008C,0x00000008C,0x00000008C,0x00000008B,0x00000008B,0x00000008B,
	0x0000008A,0x00000008A,0x00000008A,0x000000089,0x000000089,0x000000089,0x000000089,0x000000088,
	0x00000088,0x000000088,0x000000087,0x000000087,0x000000087,0x000000087,0x000000086,0x000000086,
	0x00000086,0x000000086,0x000000085,0x000000085,0x000000085,0x000000084,0x000000084,0x000000084,
	0x00000084,0x000000083,0x000000083,0x000000083,0x000000083,0x000000082,0x000000082,0x000000082,
	0x00000082,0x000000081,0x000000081,0x000000081,0x000000081,0x000000080,0x000000080,0x000000080,
	0x00000080,0x00000007F,0x00000007F,0x00000007F,0x00000007F,0x00000007E,0x00000007E,0x00000007E,
	0x0000007E,0x00000007D,0x00000007D,0x00000007D,0x00000007D,0x00000007C,0x00000007C,0x00000007C,
	0x0000007C,0x00000007B,0x00000007B,0x00000007B,0x00000007B,0x00000007A,0x00000007A,0x00000007A,
	0x0000007A,0x00000007A,0x000000079,0x000000079,0x000000079,0x000000079,0x000000078,0x000000078,
	0x00000078,0x000000078,0x000000078,0x000000077,0x000000077,0x000000077,0x000000077,0x000000076,
	0x00000076,0x000000076,0x000000076,0x000000076,0x000000075,0x000000075,0x000000075,0x000000075,
	0x00000075,0x000000074,0x000000074,0x000000074,0x000000074,0x000000073,0x000000073,0x000000073,
	0x00000073,0x000000073,0x000000072,0x000000072,0x000000072,0x000000072,0x000000072,0x000000071,
	0x00000071,0x000000071,0x000000071,0x000000071,0x000000070,0x000000070,0x000000070,0x000000070,
	0x00000070,0x000000070,0x00000006F,0x00000006F,0x00000006F,0x00000006F,0x00000006F,0x00000006E,
	0x0000006E,0x00000006E,0x00000006E,0x00000006E,0x00000006D,0x00000006D,0x00000006D,0x00000006D,
	0x0000006D,0x00000006D,0x00000006C,0x00000006C,0x00000006C,0x00000006C,0x00000006C,0x00000006B,
	0x0000006B,0x00000006B,0x00000006B,0x00000006B,0x00000006B,0x00000006A,0x00000006A,0x00000006A,
	0x0000006A,0x00000006A,0x00000006A,0x000000069,0x000000069,0x000000069,0x000000069,0x000000069,
	0x00000069,0x000000068,0x000000068,0x000000068,0x000000068,0x000000068,0x000000068,0x000000067,
	0x00000067,0x000000067,0x000000067,0x000000067,0x000000067,0x000000066,0x000000066,0x000000066,
	0x00000066,0x000000066,0x000000066,0x000000065,0x000000065,0x000000065,0x000000065,0x000000065,
	0x00000065,0x000000064,0x000000064,0x000000064,0x000000064,0x000000064,0x000000064,0x000000064,
	0x00000063,0x000000063,0x000000063,0x000000063,0x000000063,0x000000063,0x000000062,0x000000062,
	0x00000062,0x000000062,0x000000062,0x000000062,0x000000062,0x000000061,0x000000061,0x000000061,
	0x00000061,0x000000061,0x000000061,0x000000061,0x000000060,0x000000060,0x000000060,0x000000060,
	0x00000060,0x000000060,0x000000060,0x00000005F,0x00000005F,0x00000005F,0x00000005F,0x00000005F,
	0x0000005F,0x00000005F,0x00000005E,0x00000005E,0x00000005E,0x00000005E,0x00000005E,0x00000005E,
	0x0000005E,0x00000005E,0x00000005D,0x00000005D,0x00000005D,0x00000005D,0x00000005D,0x00000005D,
	0x0000005D,0x00000005C,0x00000005C,0x00000005C,0x00000005C,0x00000005C,0x00000005C,0x00000005C,
	0x0000005C,0x00000005B,0x00000005B,0x00000005B,0x00000005B,0x00000005B,0x00000005B,0x00000005B,
	0x0000005B,0x00000005A,0x00000005A,0x00000005A,0x00000005A,0x00000005A,0x00000005A,0x00000005A,
	0x0000005A,0x000000059,0x000000059,0x000000059,0x000000059,0x000000059,0x000000059,0x000000059,
	0x00000059,0x000000058,0x000000058,0x000000058,0x000000058,0x000000058,0x000000058,0x000000058,
	0x00000058,0x000000057,0x000000057,0x000000057,0x000000057,0x000000057,0x000000057,0x000000057,
	0x00000057,0x000000057,0x000000056,0x000000056,0x000000056,0x000000056,0x000000056,0x000000056,
	0x00000056,0x000000056,0x000000056,0x000000055,0x000000055,0x000000055,0x000000055,0x000000055,
	0x00000055,0x000000055,0x000000055,0x000000055,0x000000054,0x000000054,0x000000054,0x000000054,
	0x00000054,0x000000054,0x000000054,0x000000054,0x000000054,0x000000053,0x000000053,0x000000053,
	0x00000053,0x000000053,0x000000053,0x000000053,0x000000053,0x000000053,0x000000052,0x000000052,
	0x00000052,0x000000052,0x000000052,0x000000052,0x000000052,0x000000052,0x000000052,0x000000052,
	0x00000051,0x000000051,0x000000051,0x000000051,0x000000051,0x000000051,0x000000051,0x000000051,
	0x00000051,0x000000051,0x000000050,0x000000050,0x000000050,0x000000050,0x000000050,0x000000050,
	0x00000050,0x000000050,0x000000050,0x000000050,0x00000004F,0x00000004F,0x00000004F,0x00000004F,
	0x0000004F,0x00000004F,0x00000004F,0x00000004F,0x00000004F,0x00000004F,0x00000004E,0x00000004E,
	0x0000004E,0x00000004E,0x00000004E,0x00000004E,0x00000004E,0x00000004E,0x00000004E,0x00000004E,
	0x0000004E,0x00000004D,0x00000004D,0x00000004D,0x00000004D,0x00000004D,0x00000004D,0x00000004D,
	0x0000004D,0x00000004D,0x00000004D,0x00000004D,0x00000004C,0x00000004C,0x00000004C,0x00000004C,
	0x0000004C,0x00000004C,0x00000004C,0x00000004C,0x00000004C,0x00000004C,0x00000004C,0x00000004B,
	0x0000004B,0x00000004B,0x00000004B,0x00000004B,0x00000004B,0x00000004B,0x00000004B,0x00000004B,
	0x0000004B,0x00000004B,0x00000004A,0x00000004A,0x00000004A,0x00000004A,0x00000004A,0x00000004A,
	0x0000004A,0x00000004A,0x00000004A,0x00000004A,0x00000004A,0x00000004A,0x000000049,0x000000049,
	0x00000049,0x000000049,0x000000049,0x000000049,0x000000049,0x000000049,0x000000049,0x000000049,
	0x00000049,0x000000049,0x000000048,0x000000048,0x000000048,0x000000048,0x000000048,0x000000048,
	0x00000048,0x000000048,0x000000048,0x000000048,0x000000048,0x000000048,0x000000048,0x000000047,
	0x00000047,0x000000047,0x000000047,0x000000047,0x000000047,0x000000047,0x000000047,0x000000047,
	0x00000047,0x000000047,0x000000047,0x000000047,0x000000046,0x000000046,0x000000046,0x000000046,
	0x00000046,0x000000046,0x000000046,0x000000046,0x000000046,0x000000046,0x000000046,0x000000046,
	0x00000046,0x000000045,0x000000045,0x000000045,0x000000045,0x000000045,0x000000045,0x000000045,
	0x00000045,0x000000045,0x000000045,0x000000045,0x000000045,0x000000045,0x000000044,0x000000044,
	0x00000044,0x000000044,0x000000044,0x000000044,0x000000044,0x000000044,0x000000044,0x000000044,
	0x00000044,0x000000044,0x000000044,0x000000044,0x000000043,0x000000043,0x000000043,0x000000043,
	0x00000043,0x000000043,0x000000043,0x000000043,0x000000043,0x000000043,0x000000043,0x000000043,
	0x00000043,0x000000043,0x000000043,0x000000042,0x000000042,0x000000042,0x000000042,0x000000042,
	0x00000042,0x000000042,0x000000042,0x000000042,0x000000042,0x000000042,0x000000042,0x000000042,
	0x00000042,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,
	0x00000041,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,0x000000041,
	0x00000041,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,
	0x00000040,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,0x000000040,
	0x00000040,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,
	0x0000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,0x00000003F,
	0x0000003F,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,
	0x0000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,0x00000003E,
	0x0000003E,0x00000003E,0x00000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,
	0x0000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,0x00000003D,
	0x0000003D,0x00000003D,0x00000003D,0x00000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,
	0x0000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,
	0x0000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003C,0x00000003B,0x00000003B,0x00000003B,
	0x0000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,
	0x0000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003B,0x00000003A,
	0x0000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,
	0x0000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,0x00000003A,
	0x0000003A,0x00000003A,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,
	0x00000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,
	0x00000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000039,0x000000038,0x000000038,
	0x00000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,
	0x00000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,0x000000038,
	0x00000038,0x000000038,0x000000038,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,
	0x00000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,
	0x00000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,0x000000037,
	0x00000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,
	0x00000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,
	0x00000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000036,0x000000035,0x000000035,
	0x00000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,
	0x00000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000035,
	0x00000035,0x000000035,0x000000035,0x000000035,0x000000035,0x000000034,0x000000034,0x000000034,
	0x00000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,
	0x00000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000034,
	0x00000034,0x000000034,0x000000034,0x000000034,0x000000034,0x000000033,0x000000033,0x000000033,
	0x00000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,
	0x00000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,
	0x00000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000033,0x000000032,0x000000032,
	0x00000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,
	0x00000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,
	0x00000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000032,0x000000031,
	0x00000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,
	0x00000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,
	0x00000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,0x000000031,
	0x00000031,0x000000031,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,
	0x00000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,
	0x00000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,
	0x00000030,0x000000030,0x000000030,0x000000030,0x000000030,0x000000030,0x00000002F,0x00000002F,
	0x0000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,
	0x0000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,
	0x0000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,0x00000002F,
	0x0000002F,0x00000002F,0x00000002F,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,
	0x0000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,
	0x0000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,
	0x0000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,0x00000002E,
	0x0000002E,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,
	0x0000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,
	0x0000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,
	0x0000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,0x00000002D,
	0x0000002D,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,
	0x0000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,
	0x0000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,
	0x0000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,0x00000002C,
	0x0000002C,0x00000002C,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,
	0x0000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,
	0x0000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,
	0x0000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,
	0x0000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002B,0x00000002A,0x00000002A,0x00000002A,
	0x0000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,
	0x0000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,
	0x0000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,
	0x0000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,0x00000002A,
	0x0000002A,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,
	0x00000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,
	0x00000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,
	0x00000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,
	0x00000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000029,0x000000028,
	0x00000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,
	0x00000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,
	0x00000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,
	0x00000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,
	0x00000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000028,0x000000027,
	0x00000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,
	0x00000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,
	0x00000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,
	0x00000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,
	0x00000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,0x000000027,
	0x00000027,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,
	0x00000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,
	0x00000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,
	0x00000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,
	0x00000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000026,
	0x00000026,0x000000026,0x000000026,0x000000026,0x000000026,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,0x000000025,
	0x00000025,0x000000025,0x000000025,0x000000025,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000024,
	0x00000024,0x000000024,0x000000024,0x000000024,0x000000024,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,0x000000023,
	0x00000023,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,0x000000022,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,0x000000021,
	0x00000021,0x000000021,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
	0x00000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,0x000000020,
};
#endif
