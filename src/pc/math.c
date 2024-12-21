#include "../common.h"
#include "../geom.h"
#include "math.h"

uint16_t sin_table[1025] = {
       0,      6,    0xD,   0x13,   0x19,   0x1F,   0x26,   0x2C,
    0x32,   0x39,   0x3F,   0x45,   0x4B,   0x52,   0x58,   0x5E,
    0x65,   0x6B,   0x71,   0x77,   0x7E,   0x84,   0x8A,   0x90,
    0x97,   0x9D,   0xA3,   0xAA,   0xB0,   0xB6,   0xBC,   0xC3,
    0xC9,   0xCF,   0xD6,   0xDC,   0xE2,   0xE8,   0xEF,   0xF5,
    0xFB,  0x101,  0x108,  0x10E,  0x114,  0x11B,  0x121,  0x127,
   0x12D,  0x134,  0x13A,  0x140,  0x146,  0x14D,  0x153,  0x159,
   0x15F,  0x166,  0x16C,  0x172,  0x178,  0x17F,  0x185,  0x18B,
   0x191,  0x198,  0x19E,  0x1A4,  0x1AA,  0x1B1,  0x1B7,  0x1BD,
   0x1C3,  0x1CA,  0x1D0,  0x1D6,  0x1DC,  0x1E3,  0x1E9,  0x1EF,
   0x1F5,  0x1FC,  0x202,  0x208,  0x20E,  0x215,  0x21B,  0x221,
   0x227,  0x22D,  0x234,  0x23A,  0x240,  0x246,  0x24D,  0x253,
   0x259,  0x25F,  0x265,  0x26C,  0x272,  0x278,  0x27E,  0x284,
   0x28B,  0x291,  0x297,  0x29D,  0x2A3,  0x2AA,  0x2B0,  0x2B6,
   0x2BC,  0x2C2,  0x2C9,  0x2CF,  0x2D5,  0x2DB,  0x2E1,  0x2E8,
   0x2EE,  0x2F4,  0x2FA,  0x300,  0x306,  0x30D,  0x313,  0x319,
   0x31F,  0x325,  0x32B,  0x332,  0x338,  0x33E,  0x344,  0x34A,
   0x350,  0x356,  0x35D,  0x363,  0x369,  0x36F,  0x375,  0x37B,
   0x381,  0x388,  0x38E,  0x394,  0x39A,  0x3A0,  0x3A6,  0x3AC,
   0x3B2,  0x3B9,  0x3BF,  0x3C5,  0x3CB,  0x3D1,  0x3D7,  0x3DD,
   0x3E3,  0x3E9,  0x3EF,  0x3F6,  0x3FC,  0x402,  0x408,  0x40E,
   0x414,  0x41A,  0x420,  0x426,  0x42C,  0x432,  0x438,  0x43E,
   0x444,  0x44B,  0x451,  0x457,  0x45D,  0x463,  0x469,  0x46F,
   0x475,  0x47B,  0x481,  0x487,  0x48D,  0x493,  0x499,  0x49F,
   0x4A5,  0x4AB,  0x4B1,  0x4B7,  0x4BD,  0x4C3,  0x4C9,  0x4CF,
   0x4D5,  0x4DB,  0x4E1,  0x4E7,  0x4ED,  0x4F3,  0x4F9,  0x4FF,
   0x505,  0x50B,  0x511,  0x517,  0x51D,  0x523,  0x529,  0x52F,
   0x534,  0x53A,  0x540,  0x546,  0x54C,  0x552,  0x558,  0x55E,
   0x564,  0x56A,  0x570,  0x576,  0x57C,  0x581,  0x587,  0x58D,
   0x593,  0x599,  0x59F,  0x5A5,  0x5AB,  0x5B1,  0x5B6,  0x5BC,
   0x5C2,  0x5C8,  0x5CE,  0x5D4,  0x5DA,  0x5DF,  0x5E5,  0x5EB,
   0x5F1,  0x5F7,  0x5FD,  0x602,  0x608,  0x60E,  0x614,  0x61A,
   0x61F,  0x625,  0x62B,  0x631,  0x637,  0x63C,  0x642,  0x648,
   0x64E,  0x654,  0x659,  0x65F,  0x665,  0x66B,  0x670,  0x676,
   0x67C,  0x682,  0x687,  0x68D,  0x693,  0x699,  0x69E,  0x6A4,
   0x6AA,  0x6AF,  0x6B5,  0x6BB,  0x6C1,  0x6C6,  0x6CC,  0x6D2,
   0x6D7,  0x6DD,  0x6E3,  0x6E8,  0x6EE,  0x6F4,  0x6F9,  0x6FF,
   0x705,  0x70A,  0x710,  0x715,  0x71B,  0x721,  0x726,  0x72C,
   0x732,  0x737,  0x73D,  0x742,  0x748,  0x74E,  0x753,  0x759,
   0x75E,  0x764,  0x76A,  0x76F,  0x775,  0x77A,  0x780,  0x785,
   0x78B,  0x790,  0x796,  0x79B,  0x7A1,  0x7A6,  0x7AC,  0x7B2,
   0x7B7,  0x7BD,  0x7C2,  0x7C8,  0x7CD,  0x7D2,  0x7D8,  0x7DD,
   0x7E3,  0x7E8,  0x7EE,  0x7F3,  0x7F9,  0x7FE,  0x804,  0x809,
   0x80E,  0x814,  0x819,  0x81F,  0x824,  0x82A,  0x82F,  0x834,
   0x83A,  0x83F,  0x845,  0x84A,  0x84F,  0x855,  0x85A,  0x85F,
   0x865,  0x86A,  0x86F,  0x875,  0x87A,  0x87F,  0x885,  0x88A,
   0x88F,  0x895,  0x89A,  0x89F,  0x8A5,  0x8AA,  0x8AF,  0x8B4,
   0x8BA,  0x8BF,  0x8C4,  0x8C9,  0x8CF,  0x8D4,  0x8D9,  0x8DE,
   0x8E4,  0x8E9,  0x8EE,  0x8F3,  0x8F8,  0x8FE,  0x903,  0x908,
   0x90D,  0x912,  0x918,  0x91D,  0x922,  0x927,  0x92C,  0x931,
   0x937,  0x93C,  0x941,  0x946,  0x94B,  0x950,  0x955,  0x95A,
   0x95F,  0x965,  0x96A,  0x96F,  0x974,  0x979,  0x97E,  0x983,
   0x988,  0x98D,  0x992,  0x997,  0x99C,  0x9A1,  0x9A6,  0x9AB,
   0x9B0,  0x9B5,  0x9BA,  0x9BF,  0x9C4,  0x9C9,  0x9CE,  0x9D3,
   0x9D8,  0x9DD,  0x9E2,  0x9E7,  0x9EC,  0x9F1,  0x9F6,  0x9FB,
   0x9FF,  0xA04,  0xA09,  0xA0E,  0xA13,  0xA18,  0xA1D,  0xA22,
   0xA26,  0xA2B,  0xA30,  0xA35,  0xA3A,  0xA3F,  0xA44,  0xA48,
   0xA4D,  0xA52,  0xA57,  0xA5C,  0xA60,  0xA65,  0xA6A,  0xA6F,
   0xA73,  0xA78,  0xA7D,  0xA82,  0xA86,  0xA8B,  0xA90,  0xA95,
   0xA99,  0xA9E,  0xAA3,  0xAA7,  0xAAC,  0xAB1,  0xAB5,  0xABA,
   0xABF,  0xAC3,  0xAC8,  0xACD,  0xAD1,  0xAD6,  0xADB,  0xADF,
   0xAE4,  0xAE8,  0xAED,  0xAF2,  0xAF6,  0xAFB,  0xAFF,  0xB04,
   0xB08,  0xB0D,  0xB11,  0xB16,  0xB1B,  0xB1F,  0xB24,  0xB28,
   0xB2D,  0xB31,  0xB36,  0xB3A,  0xB3E,  0xB43,  0xB47,  0xB4C,
   0xB50,  0xB55,  0xB59,  0xB5E,  0xB62,  0xB66,  0xB6B,  0xB6F,
   0xB74,  0xB78,  0xB7C,  0xB81,  0xB85,  0xB89,  0xB8E,  0xB92,
   0xB97,  0xB9B,  0xB9F,  0xBA3,  0xBA8,  0xBAC,  0xBB0,  0xBB5,
   0xBB9,  0xBBD,  0xBC1,  0xBC6,  0xBCA,  0xBCE,  0xBD2,  0xBD7,
   0xBDB,  0xBDF,  0xBE3,  0xBE8,  0xBEC,  0xBF0,  0xBF4,  0xBF8,
   0xBFC,  0xC01,  0xC05,  0xC09,  0xC0D,  0xC11,  0xC15,  0xC19,
   0xC1E,  0xC22,  0xC26,  0xC2A,  0xC2E,  0xC32,  0xC36,  0xC3A,
   0xC3E,  0xC42,  0xC46,  0xC4A,  0xC4E,  0xC52,  0xC56,  0xC5A,
   0xC5E,  0xC62,  0xC66,  0xC6A,  0xC6E,  0xC72,  0xC76,  0xC7A,
   0xC7E,  0xC82,  0xC86,  0xC8A,  0xC8E,  0xC91,  0xC95,  0xC99,
   0xC9D,  0xCA1,  0xCA5,  0xCA9,  0xCAC,  0xCB0,  0xCB4,  0xCB8,
   0xCBC,  0xCC0,  0xCC3,  0xCC7,  0xCCB,  0xCCF,  0xCD2,  0xCD6,
   0xCDA,  0xCDE,  0xCE1,  0xCE5,  0xCE9,  0xCED,  0xCF0,  0xCF4,
   0xCF8,  0xCFB,  0xCFF,  0xD03,  0xD06,  0xD0A,  0xD0E,  0xD11,
   0xD15,  0xD18,  0xD1C,  0xD20,  0xD23,  0xD27,  0xD2A,  0xD2E,
   0xD32,  0xD35,  0xD39,  0xD3C,  0xD40,  0xD43,  0xD47,  0xD4A,
   0xD4E,  0xD51,  0xD55,  0xD58,  0xD5C,  0xD5F,  0xD62,  0xD66,
   0xD69,  0xD6D,  0xD70,  0xD74,  0xD77,  0xD7A,  0xD7E,  0xD81,
   0xD85,  0xD88,  0xD8B,  0xD8F,  0xD92,  0xD95,  0xD99,  0xD9C,
   0xD9F,  0xDA2,  0xDA6,  0xDA9,  0xDAC,  0xDB0,  0xDB3,  0xDB6,
   0xDB9,  0xDBC,  0xDC0,  0xDC3,  0xDC6,  0xDC9,  0xDCC,  0xDD0,
   0xDD3,  0xDD6,  0xDD9,  0xDDC,  0xDDF,  0xDE3,  0xDE6,  0xDE9,
   0xDEC,  0xDEF,  0xDF2,  0xDF5,  0xDF8,  0xDFB,  0xDFE,  0xE01,
   0xE04,  0xE07,  0xE0A,  0xE0D,  0xE10,  0xE13,  0xE16,  0xE19,
   0xE1C,  0xE1F,  0xE22,  0xE25,  0xE28,  0xE2B,  0xE2E,  0xE31,
   0xE34,  0xE37,  0xE3A,  0xE3C,  0xE3F,  0xE42,  0xE45,  0xE48,
   0xE4B,  0xE4D,  0xE50,  0xE53,  0xE56,  0xE59,  0xE5B,  0xE5E,
   0xE61,  0xE64,  0xE66,  0xE69,  0xE6C,  0xE6F,  0xE71,  0xE74,
   0xE77,  0xE79,  0xE7C,  0xE7F,  0xE81,  0xE84,  0xE87,  0xE89,
   0xE8C,  0xE8F,  0xE91,  0xE94,  0xE96,  0xE99,  0xE9B,  0xE9E,
   0xEA1,  0xEA3,  0xEA6,  0xEA8,  0xEAB,  0xEAD,  0xEB0,  0xEB2,
   0xEB5,  0xEB7,  0xEBA,  0xEBC,  0xEBF,  0xEC1,  0xEC3,  0xEC6,
   0xEC8,  0xECB,  0xECD,  0xECF,  0xED2,  0xED4,  0xED6,  0xED9,
   0xEDB,  0xEDD,  0xEE0,  0xEE2,  0xEE4,  0xEE7,  0xEE9,  0xEEB,
   0xEEE,  0xEF0,  0xEF2,  0xEF4,  0xEF7,  0xEF9,  0xEFB,  0xEFD,
   0xEFF,  0xF02,  0xF04,  0xF06,  0xF08,  0xF0A,  0xF0C,  0xF0E,
   0xF11,  0xF13,  0xF15,  0xF17,  0xF19,  0xF1B,  0xF1D,  0xF1F,
   0xF21,  0xF23,  0xF25,  0xF27,  0xF29,  0xF2B,  0xF2D,  0xF2F,
   0xF31,  0xF33,  0xF35,  0xF37,  0xF39,  0xF3B,  0xF3D,  0xF3F,
   0xF41,  0xF43,  0xF45,  0xF46,  0xF48,  0xF4A,  0xF4C,  0xF4E,
   0xF50,  0xF51,  0xF53,  0xF55,  0xF57,  0xF59,  0xF5A,  0xF5C,
   0xF5E,  0xF60,  0xF61,  0xF63,  0xF65,  0xF67,  0xF68,  0xF6A,
   0xF6C,  0xF6D,  0xF6F,  0xF71,  0xF72,  0xF74,  0xF76,  0xF77,
   0xF79,  0xF7A,  0xF7C,  0xF7D,  0xF7F,  0xF81,  0xF82,  0xF84,
   0xF85,  0xF87,  0xF88,  0xF8A,  0xF8B,  0xF8D,  0xF8E,  0xF90,
   0xF91,  0xF93,  0xF94,  0xF95,  0xF97,  0xF98,  0xF9A,  0xF9B,
   0xF9C,  0xF9E,  0xF9F,  0xFA1,  0xFA2,  0xFA3,  0xFA5,  0xFA6,
   0xFA7,  0xFA8,  0xFAA,  0xFAB,  0xFAC,  0xFAE,  0xFAF,  0xFB0,
   0xFB1,  0xFB3,  0xFB4,  0xFB5,  0xFB6,  0xFB7,  0xFB8,  0xFBA,
   0xFBB,  0xFBC,  0xFBD,  0xFBE,  0xFBF,  0xFC0,  0xFC2,  0xFC3,
   0xFC4,  0xFC5,  0xFC6,  0xFC7,  0xFC8,  0xFC9,  0xFCA,  0xFCB,
   0xFCC,  0xFCD,  0xFCE,  0xFCF,  0xFD0,  0xFD1,  0xFD2,  0xFD3,
   0xFD4,  0xFD5,  0xFD5,  0xFD6,  0xFD7,  0xFD8,  0xFD9,  0xFDA,
   0xFDB,  0xFDC,  0xFDC,  0xFDD,  0xFDE,  0xFDF,  0xFE0,  0xFE0,
   0xFE1,  0xFE2,  0xFE3,  0xFE3,  0xFE4,  0xFE5,  0xFE6,  0xFE6,
   0xFE7,  0xFE8,  0xFE8,  0xFE9,  0xFEA,  0xFEA,  0xFEB,  0xFEC,
   0xFEC,  0xFED,  0xFED,  0xFEE,  0xFEF,  0xFEF,  0xFF0,  0xFF0,
   0xFF1,  0xFF1,  0xFF2,  0xFF2,  0xFF3,  0xFF3,  0xFF4,  0xFF4,
   0xFF5,  0xFF5,  0xFF6,  0xFF6,  0xFF7,  0xFF7,  0xFF8,  0xFF8,
   0xFF8,  0xFF9,  0xFF9,  0xFF9,  0xFFA,  0xFFA,  0xFFA,  0xFFB,
   0xFFB,  0xFFB,  0xFFC,  0xFFC,  0xFFC,  0xFFC,  0xFFD,  0xFFD,
   0xFFD,  0xFFD,  0xFFE,  0xFFE,  0xFFE,  0xFFE,  0xFFE,  0xFFF,
   0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF, 0x1000, 0x1000,
  0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
  0x1000
};

uint16_t atan_table[1024] ={
      0,     1,     2,     2,     3,     3,     4,     5,
      5,     6,     7,     7,     8,     9,     9,   0xA,
    0xA,   0xB,   0xC,   0xC,   0xD,   0xE,   0xE,   0xF,
   0x10,  0x10,  0x11,  0x11,  0x12,  0x13,  0x13,  0x14,
   0x15,  0x15,  0x16,  0x17,  0x17,  0x18,  0x18,  0x19,
   0x1A,  0x1A,  0x1B,  0x1C,  0x1C,  0x1D,  0x1E,  0x1E,
   0x1F,  0x1F,  0x20,  0x21,  0x21,  0x22,  0x23,  0x23,
   0x24,  0x24,  0x25,  0x26,  0x26,  0x27,  0x28,  0x28,
   0x29,  0x2A,  0x2A,  0x2B,  0x2B,  0x2C,  0x2D,  0x2D,
   0x2E,  0x2F,  0x2F,  0x30,  0x31,  0x31,  0x32,  0x32,
   0x33,  0x34,  0x34,  0x35,  0x36,  0x36,  0x37,  0x37,
   0x38,  0x39,  0x39,  0x3A,  0x3B,  0x3B,  0x3C,  0x3D,
   0x3D,  0x3E,  0x3E,  0x3F,  0x40,  0x40,  0x41,  0x42,
   0x42,  0x43,  0x43,  0x44,  0x45,  0x45,  0x46,  0x47,
   0x47,  0x48,  0x49,  0x49,  0x4A,  0x4A,  0x4B,  0x4C,
   0x4C,  0x4D,  0x4E,  0x4E,  0x4F,  0x4F,  0x50,  0x51,
   0x51,  0x52,  0x53,  0x53,  0x54,  0x54,  0x55,  0x56,
   0x56,  0x57,  0x58,  0x58,  0x59,  0x59,  0x5A,  0x5B,
   0x5B,  0x5C,  0x5D,  0x5D,  0x5E,  0x5E,  0x5F,  0x60,
   0x60,  0x61,  0x62,  0x62,  0x63,  0x63,  0x64,  0x65,
   0x65,  0x66,  0x67,  0x67,  0x68,  0x68,  0x69,  0x6A,
   0x6A,  0x6B,  0x6B,  0x6C,  0x6D,  0x6D,  0x6E,  0x6F,
   0x6F,  0x70,  0x70,  0x71,  0x72,  0x72,  0x73,  0x74,
   0x74,  0x75,  0x75,  0x76,  0x77,  0x77,  0x78,  0x78,
   0x79,  0x7A,  0x7A,  0x7B,  0x7C,  0x7C,  0x7D,  0x7D,
   0x7E,  0x7F,  0x7F,  0x80,  0x80,  0x81,  0x82,  0x82,
   0x83,  0x83,  0x84,  0x85,  0x85,  0x86,  0x87,  0x87,
   0x88,  0x88,  0x89,  0x8A,  0x8A,  0x8B,  0x8B,  0x8C,
   0x8D,  0x8D,  0x8E,  0x8E,  0x8F,  0x90,  0x90,  0x91,
   0x91,  0x92,  0x93,  0x93,  0x94,  0x94,  0x95,  0x96,
   0x96,  0x97,  0x98,  0x98,  0x99,  0x99,  0x9A,  0x9B,
   0x9B,  0x9C,  0x9C,  0x9D,  0x9E,  0x9E,  0x9F,  0x9F,
   0xA0,  0xA1,  0xA1,  0xA2,  0xA2,  0xA3,  0xA4,  0xA4,
   0xA5,  0xA5,  0xA6,  0xA6,  0xA7,  0xA8,  0xA8,  0xA9,
   0xA9,  0xAA,  0xAB,  0xAB,  0xAC,  0xAC,  0xAD,  0xAE,
   0xAE,  0xAF,  0xAF,  0xB0,  0xB1,  0xB1,  0xB2,  0xB2,
   0xB3,  0xB4,  0xB4,  0xB5,  0xB5,  0xB6,  0xB6,  0xB7,
   0xB8,  0xB8,  0xB9,  0xB9,  0xBA,  0xBB,  0xBB,  0xBC,
   0xBC,  0xBD,  0xBE,  0xBE,  0xBF,  0xBF,  0xC0,  0xC0,
   0xC1,  0xC2,  0xC2,  0xC3,  0xC3,  0xC4,  0xC5,  0xC5,
   0xC6,  0xC6,  0xC7,  0xC7,  0xC8,  0xC9,  0xC9,  0xCA,
   0xCA,  0xCB,  0xCB,  0xCC,  0xCD,  0xCD,  0xCE,  0xCE,
   0xCF,  0xCF,  0xD0,  0xD1,  0xD1,  0xD2,  0xD2,  0xD3,
   0xD3,  0xD4,  0xD5,  0xD5,  0xD6,  0xD6,  0xD7,  0xD7,
   0xD8,  0xD9,  0xD9,  0xDA,  0xDA,  0xDB,  0xDB,  0xDC,
   0xDD,  0xDD,  0xDE,  0xDE,  0xDF,  0xDF,  0xE0,  0xE1,
   0xE1,  0xE2,  0xE2,  0xE3,  0xE3,  0xE4,  0xE4,  0xE5,
   0xE6,  0xE6,  0xE7,  0xE7,  0xE8,  0xE8,  0xE9,  0xEA,
   0xEA,  0xEB,  0xEB,  0xEC,  0xEC,  0xED,  0xED,  0xEE,
   0xEF,  0xEF,  0xF0,  0xF0,  0xF1,  0xF1,  0xF2,  0xF2,
   0xF3,  0xF4,  0xF4,  0xF5,  0xF5,  0xF6,  0xF6,  0xF7,
   0xF7,  0xF8,  0xF8,  0xF9,  0xFA,  0xFA,  0xFB,  0xFB,
   0xFC,  0xFC,  0xFD,  0xFD,  0xFE,  0xFE,  0xFF, 0x100,
  0x100, 0x101, 0x101, 0x102, 0x102, 0x103, 0x103, 0x104,
  0x104, 0x105, 0x106, 0x106, 0x107, 0x107, 0x108, 0x108,
  0x109, 0x109, 0x10A, 0x10A, 0x10B, 0x10B, 0x10C, 0x10D,
  0x10D, 0x10E, 0x10E, 0x10F, 0x10F, 0x110, 0x110, 0x111,
  0x111, 0x112, 0x112, 0x113, 0x113, 0x114, 0x114, 0x115,
  0x116, 0x116, 0x117, 0x117, 0x118, 0x118, 0x119, 0x119,
  0x11A, 0x11A, 0x11B, 0x11B, 0x11C, 0x11C, 0x11D, 0x11D,
  0x11E, 0x11E, 0x11F, 0x120, 0x120, 0x121, 0x121, 0x122,
  0x122, 0x123, 0x123, 0x124, 0x124, 0x125, 0x125, 0x126,
  0x126, 0x127, 0x127, 0x128, 0x128, 0x129, 0x129, 0x12A,
  0x12A, 0x12B, 0x12B, 0x12C, 0x12C, 0x12D, 0x12D, 0x12E,
  0x12E, 0x12F, 0x12F, 0x130, 0x130, 0x131, 0x131, 0x132,
  0x133, 0x133, 0x134, 0x134, 0x135, 0x135, 0x136, 0x136,
  0x137, 0x137, 0x138, 0x138, 0x139, 0x139, 0x13A, 0x13A,
  0x13B, 0x13B, 0x13C, 0x13C, 0x13D, 0x13D, 0x13E, 0x13E,
  0x13F, 0x13F, 0x140, 0x140, 0x141, 0x141, 0x142, 0x142,
  0x142, 0x143, 0x143, 0x144, 0x144, 0x145, 0x145, 0x146,
  0x146, 0x147, 0x147, 0x148, 0x148, 0x149, 0x149, 0x14A,
  0x14A, 0x14B, 0x14B, 0x14C, 0x14C, 0x14D, 0x14D, 0x14E,
  0x14E, 0x14F, 0x14F, 0x150, 0x150, 0x151, 0x151, 0x152,
  0x152, 0x153, 0x153, 0x154, 0x154, 0x154, 0x155, 0x155,
  0x156, 0x156, 0x157, 0x157, 0x158, 0x158, 0x159, 0x159,
  0x15A, 0x15A, 0x15B, 0x15B, 0x15C, 0x15C, 0x15D, 0x15D,
  0x15D, 0x15E, 0x15E, 0x15F, 0x15F, 0x160, 0x160, 0x161,
  0x161, 0x162, 0x162, 0x163, 0x163, 0x164, 0x164, 0x164,
  0x165, 0x165, 0x166, 0x166, 0x167, 0x167, 0x168, 0x168,
  0x169, 0x169, 0x16A, 0x16A, 0x16A, 0x16B, 0x16B, 0x16C,
  0x16C, 0x16D, 0x16D, 0x16E, 0x16E, 0x16F, 0x16F, 0x170,
  0x170, 0x170, 0x171, 0x171, 0x172, 0x172, 0x173, 0x173,
  0x174, 0x174, 0x174, 0x175, 0x175, 0x176, 0x176, 0x177,
  0x177, 0x178, 0x178, 0x179, 0x179, 0x179, 0x17A, 0x17A,
  0x17B, 0x17B, 0x17C, 0x17C, 0x17D, 0x17D, 0x17D, 0x17E,
  0x17E, 0x17F, 0x17F, 0x180, 0x180, 0x181, 0x181, 0x181,
  0x182, 0x182, 0x183, 0x183, 0x184, 0x184, 0x184, 0x185,
  0x185, 0x186, 0x186, 0x187, 0x187, 0x187, 0x188, 0x188,
  0x189, 0x189, 0x18A, 0x18A, 0x18B, 0x18B, 0x18B, 0x18C,
  0x18C, 0x18D, 0x18D, 0x18E, 0x18E, 0x18E, 0x18F, 0x18F,
  0x190, 0x190, 0x191, 0x191, 0x191, 0x192, 0x192, 0x193,
  0x193, 0x193, 0x194, 0x194, 0x195, 0x195, 0x196, 0x196,
  0x196, 0x197, 0x197, 0x198, 0x198, 0x199, 0x199, 0x199,
  0x19A, 0x19A, 0x19B, 0x19B, 0x19B, 0x19C, 0x19C, 0x19D,
  0x19D, 0x19D, 0x19E, 0x19E, 0x19F, 0x19F, 0x1A0, 0x1A0,
  0x1A0, 0x1A1, 0x1A1, 0x1A2, 0x1A2, 0x1A2, 0x1A3, 0x1A3,
  0x1A4, 0x1A4, 0x1A4, 0x1A5, 0x1A5, 0x1A6, 0x1A6, 0x1A6,
  0x1A7, 0x1A7, 0x1A8, 0x1A8, 0x1A9, 0x1A9, 0x1A9, 0x1AA,
  0x1AA, 0x1AB, 0x1AB, 0x1AB, 0x1AC, 0x1AC, 0x1AD, 0x1AD,
  0x1AD, 0x1AE, 0x1AE, 0x1AF, 0x1AF, 0x1AF, 0x1B0, 0x1B0,
  0x1B0, 0x1B1, 0x1B1, 0x1B2, 0x1B2, 0x1B2, 0x1B3, 0x1B3,
  0x1B4, 0x1B4, 0x1B4, 0x1B5, 0x1B5, 0x1B6, 0x1B6, 0x1B6,
  0x1B7, 0x1B7, 0x1B8, 0x1B8, 0x1B8, 0x1B9, 0x1B9, 0x1B9,
  0x1BA, 0x1BA, 0x1BB, 0x1BB, 0x1BB, 0x1BC, 0x1BC, 0x1BD,
  0x1BD, 0x1BD, 0x1BE, 0x1BE, 0x1BE, 0x1BF, 0x1BF, 0x1C0,
  0x1C0, 0x1C0, 0x1C1, 0x1C1, 0x1C2, 0x1C2, 0x1C2, 0x1C3,
  0x1C3, 0x1C3, 0x1C4, 0x1C4, 0x1C5, 0x1C5, 0x1C5, 0x1C6,
  0x1C6, 0x1C6, 0x1C7, 0x1C7, 0x1C8, 0x1C8, 0x1C8, 0x1C9,
  0x1C9, 0x1C9, 0x1CA, 0x1CA, 0x1CB, 0x1CB, 0x1CB, 0x1CC,
  0x1CC, 0x1CC, 0x1CD, 0x1CD, 0x1CD, 0x1CE, 0x1CE, 0x1CF,
  0x1CF, 0x1CF, 0x1D0, 0x1D0, 0x1D0, 0x1D1, 0x1D1, 0x1D1,
  0x1D2, 0x1D2, 0x1D3, 0x1D3, 0x1D3, 0x1D4, 0x1D4, 0x1D4,
  0x1D5, 0x1D5, 0x1D5, 0x1D6, 0x1D6, 0x1D7, 0x1D7, 0x1D7,
  0x1D8, 0x1D8, 0x1D8, 0x1D9, 0x1D9, 0x1D9, 0x1DA, 0x1DA,
  0x1DA, 0x1DB, 0x1DB, 0x1DC, 0x1DC, 0x1DC, 0x1DD, 0x1DD,
  0x1DD, 0x1DE, 0x1DE, 0x1DE, 0x1DF, 0x1DF, 0x1DF, 0x1E0,
  0x1E0, 0x1E0, 0x1E1, 0x1E1, 0x1E1, 0x1E2, 0x1E2, 0x1E3,
  0x1E3, 0x1E3, 0x1E4, 0x1E4, 0x1E4, 0x1E5, 0x1E5, 0x1E5,
  0x1E6, 0x1E6, 0x1E6, 0x1E7, 0x1E7, 0x1E7, 0x1E8, 0x1E8,
  0x1E8, 0x1E9, 0x1E9, 0x1E9, 0x1EA, 0x1EA, 0x1EA, 0x1EB,
  0x1EB, 0x1EB, 0x1EC, 0x1EC, 0x1EC, 0x1ED, 0x1ED, 0x1ED,
  0x1EE, 0x1EE, 0x1EE, 0x1EF, 0x1EF, 0x1EF, 0x1F0, 0x1F0,
  0x1F0, 0x1F1, 0x1F1, 0x1F1, 0x1F2, 0x1F2, 0x1F2, 0x1F3,
  0x1F3, 0x1F3, 0x1F4, 0x1F4, 0x1F4, 0x1F5, 0x1F5, 0x1F5,
  0x1F6, 0x1F6, 0x1F6, 0x1F7, 0x1F7, 0x1F7, 0x1F8, 0x1F8,
  0x1F8, 0x1F9, 0x1F9, 0x1F9, 0x1FA, 0x1FA, 0x1FA, 0x1FB,
  0x1FB, 0x1FB, 0x1FC, 0x1FC, 0x1FC, 0x1FD, 0x1FD, 0x1FD,
  0x1FE, 0x1FE, 0x1FE, 0x1FF, 0x1FF, 0x1FF, 0x1FF, 0x200
};

uint16_t sqrt_table[192] = {
  0x1000, 0x101F, 0x103F, 0x105E, 0x107E, 0x109C, 0x10BB, 0x10DA,
  0x10F8, 0x1116, 0x1134, 0x1152, 0x116F, 0x118C, 0x11A9, 0x11C6,
  0x11E3, 0x1200, 0x121C, 0x1238, 0x1254, 0x1270, 0x128C, 0x12A7,
  0x12C2, 0x12DE, 0x12F9, 0x1314, 0x132E, 0x1349, 0x1364, 0x137E,
  0x1398, 0x13B2, 0x13CC, 0x13E6, 0x1400, 0x1419, 0x1432, 0x144C,
  0x1465, 0x147E, 0x1497, 0x14B0, 0x14C8, 0x14E1, 0x14F9, 0x1512,
  0x152A, 0x1542, 0x155A, 0x1572, 0x158A, 0x15A2, 0x15B9, 0x15D1,
  0x15E8, 0x1600, 0x1617, 0x162E, 0x1645, 0x165C, 0x1673, 0x1689,
  0x16A0, 0x16B7, 0x16CD, 0x16E4, 0x16FA, 0x1710, 0x1726, 0x173C,
  0x1752, 0x1768, 0x177E, 0x1794, 0x17AA, 0x17BF, 0x17D5, 0x17EA,
  0x1800, 0x1815, 0x182A, 0x183F, 0x1854, 0x1869, 0x187E, 0x1893,
  0x18A8, 0x18BD, 0x18D1, 0x18E6, 0x18FA, 0x190F, 0x1923, 0x1938,
  0x194C, 0x1960, 0x1974, 0x1988, 0x199C, 0x19B0, 0x19C4, 0x19D8,
  0x19EC, 0x1A00, 0x1A13, 0x1A27, 0x1A3A, 0x1A4E, 0x1A61, 0x1A75,
  0x1A88, 0x1A9B, 0x1AAE, 0x1AC2, 0x1AD5, 0x1AE8, 0x1AFB, 0x1B0E,
  0x1B21, 0x1B33, 0x1B46, 0x1B59, 0x1B6C, 0x1B7E, 0x1B91, 0x1BA3,
  0x1BB6, 0x1BC8, 0x1BDB, 0x1BED, 0x1C00, 0x1C12, 0x1C24, 0x1C36,
  0x1C48, 0x1C5A, 0x1C6C, 0x1C7E, 0x1C90, 0x1CA2, 0x1CB4, 0x1CC6,
  0x1CD8, 0x1CE9, 0x1CFB, 0x1D0D, 0x1D1E, 0x1D30, 0x1D41, 0x1D53,
  0x1D64, 0x1D76, 0x1D87, 0x1D98, 0x1DAA, 0x1DBB, 0x1DCC, 0x1DDD,
  0x1DEE, 0x1E00, 0x1E11, 0x1E22, 0x1E33, 0x1E43, 0x1E54, 0x1E65,
  0x1E76, 0x1E87, 0x1E98, 0x1EA8, 0x1EB9, 0x1ECA, 0x1EDA, 0x1EEB,
  0x1EFB, 0x1F0C, 0x1F1C, 0x1F2D, 0x1F3D, 0x1F4E, 0x1F5E, 0x1F6E,
  0x1F7E, 0x1F8F, 0x1F9F, 0x1FAF, 0x1FBF, 0x1FCF, 0x1FDF, 0x1FEF
};

int16_t msin(uint32_t a) {
  a = angle12(a);
  if (a < 0x400)
    return sin_table[a];
  else if (a < 0x800)
    return sin_table[0x800-a];
  else if (a < 0xC00)
    return -sin_table[a-0x800];
  else
    return -sin_table[0x1000-a];
}

int16_t mcos(uint32_t a) {
  a = angle12(a);
  if (a < 0x400)
    return sin_table[0x400-a];
  else if (a < 0x800)
    return -sin_table[a-0x400];
  else if (a < 0xC00)
    return -sin_table[0xC00-a];
  else
    return sin_table[a-0xC00];
}

int32_t matan2(int32_t y, int32_t x) {
  int ny, nx, idx;
  int32_t res;

  nx=0; ny=0;
  if (y<0) { y=-y; ny=1; }
  if (x<0) { x=-x; nx=1; }
  if (!(y|x)) { return 0; }
  if (y >= x) {
    idx = (x>>21)?x/(y>>10):(x<<10)/y;
    res = 0x400 - atan_table[idx];
  }
  else {
    idx = (y>>21)?y/(x>>10):(y<<10)/x;
    res = atan_table[idx];
  }
  if (nx) { res = 0x800 - res; }
  if (ny) { res = -res; }
  return res;
}

int32_t msqrt(int32_t a) {
  int32_t tmp, lzc, res;
  int idx;

  if (a==0) { return 0; }
  tmp = a;
  lzc = 0;
  if (tmp >= 0) { tmp = ~tmp; }
  while (tmp & 0x80000000) {
    lzc++;
    tmp <<= 1;
  }
  lzc &= ~1;
  idx = lzc < 24 ? a >> (24-lzc) : a << (lzc-24);
  res = (sqrt_table[idx-64] << ((31-lzc)/2)) >> 12;
  return res;
}
