/*
** Parsed from DerivedCoreProperties.txt, version 11.0.
** For more information, see https://www.unicode.org/reports/tr31/.
*/

/* #define CHECK_BINARY_SEARCH */
#ifdef CHECK_BINARY_SEARCH
#include <stdio.h>
#endif
#include <stddef.h> /* size_t */

#define MAXUNICODE  0x10FFFF

#define IN_RANGES(ranges, code_point) \
  is_in_ranges((ranges), sizeof (ranges) / sizeof (ranges)[0], (code_point))

typedef struct {
  const unsigned int low, high;
} code_point_range;

static const code_point_range XID_Start[] = {
  { 0x00041, 0x0005A },
  { 0x00061, 0x0007A },
  { 0x000AA, 0x000AA },
  { 0x000B5, 0x000B5 },
  { 0x000BA, 0x000BA },
  { 0x000C0, 0x000D6 },
  { 0x000D8, 0x000F6 },
  { 0x000F8, 0x002C1 },
  { 0x002C6, 0x002D1 },
  { 0x002E0, 0x002E4 },
  { 0x002EC, 0x002EC },
  { 0x002EE, 0x002EE },
  { 0x00370, 0x00374 },
  { 0x00376, 0x00377 },
  { 0x0037B, 0x0037D },
  { 0x0037F, 0x0037F },
  { 0x00386, 0x00386 },
  { 0x00388, 0x0038A },
  { 0x0038C, 0x0038C },
  { 0x0038E, 0x003A1 },
  { 0x003A3, 0x003F5 },
  { 0x003F7, 0x00481 },
  { 0x0048A, 0x0052F },
  { 0x00531, 0x00556 },
  { 0x00559, 0x00559 },
  { 0x00560, 0x00588 },
  { 0x005D0, 0x005EA },
  { 0x005EF, 0x005F2 },
  { 0x00620, 0x0064A },
  { 0x0066E, 0x0066F },
  { 0x00671, 0x006D3 },
  { 0x006D5, 0x006D5 },
  { 0x006E5, 0x006E6 },
  { 0x006EE, 0x006EF },
  { 0x006FA, 0x006FC },
  { 0x006FF, 0x006FF },
  { 0x00710, 0x00710 },
  { 0x00712, 0x0072F },
  { 0x0074D, 0x007A5 },
  { 0x007B1, 0x007B1 },
  { 0x007CA, 0x007EA },
  { 0x007F4, 0x007F5 },
  { 0x007FA, 0x007FA },
  { 0x00800, 0x00815 },
  { 0x0081A, 0x0081A },
  { 0x00824, 0x00824 },
  { 0x00828, 0x00828 },
  { 0x00840, 0x00858 },
  { 0x00860, 0x0086A },
  { 0x008A0, 0x008B4 },
  { 0x008B6, 0x008BD },
  { 0x00904, 0x00939 },
  { 0x0093D, 0x0093D },
  { 0x00950, 0x00950 },
  { 0x00958, 0x00961 },
  { 0x00971, 0x00980 },
  { 0x00985, 0x0098C },
  { 0x0098F, 0x00990 },
  { 0x00993, 0x009A8 },
  { 0x009AA, 0x009B0 },
  { 0x009B2, 0x009B2 },
  { 0x009B6, 0x009B9 },
  { 0x009BD, 0x009BD },
  { 0x009CE, 0x009CE },
  { 0x009DC, 0x009DD },
  { 0x009DF, 0x009E1 },
  { 0x009F0, 0x009F1 },
  { 0x009FC, 0x009FC },
  { 0x00A05, 0x00A0A },
  { 0x00A0F, 0x00A10 },
  { 0x00A13, 0x00A28 },
  { 0x00A2A, 0x00A30 },
  { 0x00A32, 0x00A33 },
  { 0x00A35, 0x00A36 },
  { 0x00A38, 0x00A39 },
  { 0x00A59, 0x00A5C },
  { 0x00A5E, 0x00A5E },
  { 0x00A72, 0x00A74 },
  { 0x00A85, 0x00A8D },
  { 0x00A8F, 0x00A91 },
  { 0x00A93, 0x00AA8 },
  { 0x00AAA, 0x00AB0 },
  { 0x00AB2, 0x00AB3 },
  { 0x00AB5, 0x00AB9 },
  { 0x00ABD, 0x00ABD },
  { 0x00AD0, 0x00AD0 },
  { 0x00AE0, 0x00AE1 },
  { 0x00AF9, 0x00AF9 },
  { 0x00B05, 0x00B0C },
  { 0x00B0F, 0x00B10 },
  { 0x00B13, 0x00B28 },
  { 0x00B2A, 0x00B30 },
  { 0x00B32, 0x00B33 },
  { 0x00B35, 0x00B39 },
  { 0x00B3D, 0x00B3D },
  { 0x00B5C, 0x00B5D },
  { 0x00B5F, 0x00B61 },
  { 0x00B71, 0x00B71 },
  { 0x00B83, 0x00B83 },
  { 0x00B85, 0x00B8A },
  { 0x00B8E, 0x00B90 },
  { 0x00B92, 0x00B95 },
  { 0x00B99, 0x00B9A },
  { 0x00B9C, 0x00B9C },
  { 0x00B9E, 0x00B9F },
  { 0x00BA3, 0x00BA4 },
  { 0x00BA8, 0x00BAA },
  { 0x00BAE, 0x00BB9 },
  { 0x00BD0, 0x00BD0 },
  { 0x00C05, 0x00C0C },
  { 0x00C0E, 0x00C10 },
  { 0x00C12, 0x00C28 },
  { 0x00C2A, 0x00C39 },
  { 0x00C3D, 0x00C3D },
  { 0x00C58, 0x00C5A },
  { 0x00C60, 0x00C61 },
  { 0x00C80, 0x00C80 },
  { 0x00C85, 0x00C8C },
  { 0x00C8E, 0x00C90 },
  { 0x00C92, 0x00CA8 },
  { 0x00CAA, 0x00CB3 },
  { 0x00CB5, 0x00CB9 },
  { 0x00CBD, 0x00CBD },
  { 0x00CDE, 0x00CDE },
  { 0x00CE0, 0x00CE1 },
  { 0x00CF1, 0x00CF2 },
  { 0x00D05, 0x00D0C },
  { 0x00D0E, 0x00D10 },
  { 0x00D12, 0x00D3A },
  { 0x00D3D, 0x00D3D },
  { 0x00D4E, 0x00D4E },
  { 0x00D54, 0x00D56 },
  { 0x00D5F, 0x00D61 },
  { 0x00D7A, 0x00D7F },
  { 0x00D85, 0x00D96 },
  { 0x00D9A, 0x00DB1 },
  { 0x00DB3, 0x00DBB },
  { 0x00DBD, 0x00DBD },
  { 0x00DC0, 0x00DC6 },
  { 0x00E01, 0x00E30 },
  { 0x00E32, 0x00E32 },
  { 0x00E40, 0x00E46 },
  { 0x00E81, 0x00E82 },
  { 0x00E84, 0x00E84 },
  { 0x00E87, 0x00E88 },
  { 0x00E8A, 0x00E8A },
  { 0x00E8D, 0x00E8D },
  { 0x00E94, 0x00E97 },
  { 0x00E99, 0x00E9F },
  { 0x00EA1, 0x00EA3 },
  { 0x00EA5, 0x00EA5 },
  { 0x00EA7, 0x00EA7 },
  { 0x00EAA, 0x00EAB },
  { 0x00EAD, 0x00EB0 },
  { 0x00EB2, 0x00EB2 },
  { 0x00EBD, 0x00EBD },
  { 0x00EC0, 0x00EC4 },
  { 0x00EC6, 0x00EC6 },
  { 0x00EDC, 0x00EDF },
  { 0x00F00, 0x00F00 },
  { 0x00F40, 0x00F47 },
  { 0x00F49, 0x00F6C },
  { 0x00F88, 0x00F8C },
  { 0x01000, 0x0102A },
  { 0x0103F, 0x0103F },
  { 0x01050, 0x01055 },
  { 0x0105A, 0x0105D },
  { 0x01061, 0x01061 },
  { 0x01065, 0x01066 },
  { 0x0106E, 0x01070 },
  { 0x01075, 0x01081 },
  { 0x0108E, 0x0108E },
  { 0x010A0, 0x010C5 },
  { 0x010C7, 0x010C7 },
  { 0x010CD, 0x010CD },
  { 0x010D0, 0x010FA },
  { 0x010FC, 0x01248 },
  { 0x0124A, 0x0124D },
  { 0x01250, 0x01256 },
  { 0x01258, 0x01258 },
  { 0x0125A, 0x0125D },
  { 0x01260, 0x01288 },
  { 0x0128A, 0x0128D },
  { 0x01290, 0x012B0 },
  { 0x012B2, 0x012B5 },
  { 0x012B8, 0x012BE },
  { 0x012C0, 0x012C0 },
  { 0x012C2, 0x012C5 },
  { 0x012C8, 0x012D6 },
  { 0x012D8, 0x01310 },
  { 0x01312, 0x01315 },
  { 0x01318, 0x0135A },
  { 0x01380, 0x0138F },
  { 0x013A0, 0x013F5 },
  { 0x013F8, 0x013FD },
  { 0x01401, 0x0166C },
  { 0x0166F, 0x0167F },
  { 0x01681, 0x0169A },
  { 0x016A0, 0x016EA },
  { 0x016EE, 0x016F8 },
  { 0x01700, 0x0170C },
  { 0x0170E, 0x01711 },
  { 0x01720, 0x01731 },
  { 0x01740, 0x01751 },
  { 0x01760, 0x0176C },
  { 0x0176E, 0x01770 },
  { 0x01780, 0x017B3 },
  { 0x017D7, 0x017D7 },
  { 0x017DC, 0x017DC },
  { 0x01820, 0x01878 },
  { 0x01880, 0x018A8 },
  { 0x018AA, 0x018AA },
  { 0x018B0, 0x018F5 },
  { 0x01900, 0x0191E },
  { 0x01950, 0x0196D },
  { 0x01970, 0x01974 },
  { 0x01980, 0x019AB },
  { 0x019B0, 0x019C9 },
  { 0x01A00, 0x01A16 },
  { 0x01A20, 0x01A54 },
  { 0x01AA7, 0x01AA7 },
  { 0x01B05, 0x01B33 },
  { 0x01B45, 0x01B4B },
  { 0x01B83, 0x01BA0 },
  { 0x01BAE, 0x01BAF },
  { 0x01BBA, 0x01BE5 },
  { 0x01C00, 0x01C23 },
  { 0x01C4D, 0x01C4F },
  { 0x01C5A, 0x01C7D },
  { 0x01C80, 0x01C88 },
  { 0x01C90, 0x01CBA },
  { 0x01CBD, 0x01CBF },
  { 0x01CE9, 0x01CEC },
  { 0x01CEE, 0x01CF1 },
  { 0x01CF5, 0x01CF6 },
  { 0x01D00, 0x01DBF },
  { 0x01E00, 0x01F15 },
  { 0x01F18, 0x01F1D },
  { 0x01F20, 0x01F45 },
  { 0x01F48, 0x01F4D },
  { 0x01F50, 0x01F57 },
  { 0x01F59, 0x01F59 },
  { 0x01F5B, 0x01F5B },
  { 0x01F5D, 0x01F5D },
  { 0x01F5F, 0x01F7D },
  { 0x01F80, 0x01FB4 },
  { 0x01FB6, 0x01FBC },
  { 0x01FBE, 0x01FBE },
  { 0x01FC2, 0x01FC4 },
  { 0x01FC6, 0x01FCC },
  { 0x01FD0, 0x01FD3 },
  { 0x01FD6, 0x01FDB },
  { 0x01FE0, 0x01FEC },
  { 0x01FF2, 0x01FF4 },
  { 0x01FF6, 0x01FFC },
  { 0x02071, 0x02071 },
  { 0x0207F, 0x0207F },
  { 0x02090, 0x0209C },
  { 0x02102, 0x02102 },
  { 0x02107, 0x02107 },
  { 0x0210A, 0x02113 },
  { 0x02115, 0x02115 },
  { 0x02118, 0x0211D },
  { 0x02124, 0x02124 },
  { 0x02126, 0x02126 },
  { 0x02128, 0x02128 },
  { 0x0212A, 0x02139 },
  { 0x0213C, 0x0213F },
  { 0x02145, 0x02149 },
  { 0x0214E, 0x0214E },
  { 0x02160, 0x02188 },
  { 0x02C00, 0x02C2E },
  { 0x02C30, 0x02C5E },
  { 0x02C60, 0x02CE4 },
  { 0x02CEB, 0x02CEE },
  { 0x02CF2, 0x02CF3 },
  { 0x02D00, 0x02D25 },
  { 0x02D27, 0x02D27 },
  { 0x02D2D, 0x02D2D },
  { 0x02D30, 0x02D67 },
  { 0x02D6F, 0x02D6F },
  { 0x02D80, 0x02D96 },
  { 0x02DA0, 0x02DA6 },
  { 0x02DA8, 0x02DAE },
  { 0x02DB0, 0x02DB6 },
  { 0x02DB8, 0x02DBE },
  { 0x02DC0, 0x02DC6 },
  { 0x02DC8, 0x02DCE },
  { 0x02DD0, 0x02DD6 },
  { 0x02DD8, 0x02DDE },
  { 0x03005, 0x03007 },
  { 0x03021, 0x03029 },
  { 0x03031, 0x03035 },
  { 0x03038, 0x0303C },
  { 0x03041, 0x03096 },
  { 0x0309D, 0x0309F },
  { 0x030A1, 0x030FA },
  { 0x030FC, 0x030FF },
  { 0x03105, 0x0312F },
  { 0x03131, 0x0318E },
  { 0x031A0, 0x031BA },
  { 0x031F0, 0x031FF },
  { 0x03400, 0x04DB5 },
  { 0x04E00, 0x09FEF },
  { 0x0A000, 0x0A48C },
  { 0x0A4D0, 0x0A4FD },
  { 0x0A500, 0x0A60C },
  { 0x0A610, 0x0A61F },
  { 0x0A62A, 0x0A62B },
  { 0x0A640, 0x0A66E },
  { 0x0A67F, 0x0A69D },
  { 0x0A6A0, 0x0A6EF },
  { 0x0A717, 0x0A71F },
  { 0x0A722, 0x0A788 },
  { 0x0A78B, 0x0A7B9 },
  { 0x0A7F7, 0x0A801 },
  { 0x0A803, 0x0A805 },
  { 0x0A807, 0x0A80A },
  { 0x0A80C, 0x0A822 },
  { 0x0A840, 0x0A873 },
  { 0x0A882, 0x0A8B3 },
  { 0x0A8F2, 0x0A8F7 },
  { 0x0A8FB, 0x0A8FB },
  { 0x0A8FD, 0x0A8FE },
  { 0x0A90A, 0x0A925 },
  { 0x0A930, 0x0A946 },
  { 0x0A960, 0x0A97C },
  { 0x0A984, 0x0A9B2 },
  { 0x0A9CF, 0x0A9CF },
  { 0x0A9E0, 0x0A9E4 },
  { 0x0A9E6, 0x0A9EF },
  { 0x0A9FA, 0x0A9FE },
  { 0x0AA00, 0x0AA28 },
  { 0x0AA40, 0x0AA42 },
  { 0x0AA44, 0x0AA4B },
  { 0x0AA60, 0x0AA76 },
  { 0x0AA7A, 0x0AA7A },
  { 0x0AA7E, 0x0AAAF },
  { 0x0AAB1, 0x0AAB1 },
  { 0x0AAB5, 0x0AAB6 },
  { 0x0AAB9, 0x0AABD },
  { 0x0AAC0, 0x0AAC0 },
  { 0x0AAC2, 0x0AAC2 },
  { 0x0AADB, 0x0AADD },
  { 0x0AAE0, 0x0AAEA },
  { 0x0AAF2, 0x0AAF4 },
  { 0x0AB01, 0x0AB06 },
  { 0x0AB09, 0x0AB0E },
  { 0x0AB11, 0x0AB16 },
  { 0x0AB20, 0x0AB26 },
  { 0x0AB28, 0x0AB2E },
  { 0x0AB30, 0x0AB5A },
  { 0x0AB5C, 0x0AB65 },
  { 0x0AB70, 0x0ABE2 },
  { 0x0AC00, 0x0D7A3 },
  { 0x0D7B0, 0x0D7C6 },
  { 0x0D7CB, 0x0D7FB },
  { 0x0F900, 0x0FA6D },
  { 0x0FA70, 0x0FAD9 },
  { 0x0FB00, 0x0FB06 },
  { 0x0FB13, 0x0FB17 },
  { 0x0FB1D, 0x0FB1D },
  { 0x0FB1F, 0x0FB28 },
  { 0x0FB2A, 0x0FB36 },
  { 0x0FB38, 0x0FB3C },
  { 0x0FB3E, 0x0FB3E },
  { 0x0FB40, 0x0FB41 },
  { 0x0FB43, 0x0FB44 },
  { 0x0FB46, 0x0FBB1 },
  { 0x0FBD3, 0x0FC5D },
  { 0x0FC64, 0x0FD3D },
  { 0x0FD50, 0x0FD8F },
  { 0x0FD92, 0x0FDC7 },
  { 0x0FDF0, 0x0FDF9 },
  { 0x0FE71, 0x0FE71 },
  { 0x0FE73, 0x0FE73 },
  { 0x0FE77, 0x0FE77 },
  { 0x0FE79, 0x0FE79 },
  { 0x0FE7B, 0x0FE7B },
  { 0x0FE7D, 0x0FE7D },
  { 0x0FE7F, 0x0FEFC },
  { 0x0FF21, 0x0FF3A },
  { 0x0FF41, 0x0FF5A },
  { 0x0FF66, 0x0FF9D },
  { 0x0FFA0, 0x0FFBE },
  { 0x0FFC2, 0x0FFC7 },
  { 0x0FFCA, 0x0FFCF },
  { 0x0FFD2, 0x0FFD7 },
  { 0x0FFDA, 0x0FFDC },
  { 0x10000, 0x1000B },
  { 0x1000D, 0x10026 },
  { 0x10028, 0x1003A },
  { 0x1003C, 0x1003D },
  { 0x1003F, 0x1004D },
  { 0x10050, 0x1005D },
  { 0x10080, 0x100FA },
  { 0x10140, 0x10174 },
  { 0x10280, 0x1029C },
  { 0x102A0, 0x102D0 },
  { 0x10300, 0x1031F },
  { 0x1032D, 0x1034A },
  { 0x10350, 0x10375 },
  { 0x10380, 0x1039D },
  { 0x103A0, 0x103C3 },
  { 0x103C8, 0x103CF },
  { 0x103D1, 0x103D5 },
  { 0x10400, 0x1049D },
  { 0x104B0, 0x104D3 },
  { 0x104D8, 0x104FB },
  { 0x10500, 0x10527 },
  { 0x10530, 0x10563 },
  { 0x10600, 0x10736 },
  { 0x10740, 0x10755 },
  { 0x10760, 0x10767 },
  { 0x10800, 0x10805 },
  { 0x10808, 0x10808 },
  { 0x1080A, 0x10835 },
  { 0x10837, 0x10838 },
  { 0x1083C, 0x1083C },
  { 0x1083F, 0x10855 },
  { 0x10860, 0x10876 },
  { 0x10880, 0x1089E },
  { 0x108E0, 0x108F2 },
  { 0x108F4, 0x108F5 },
  { 0x10900, 0x10915 },
  { 0x10920, 0x10939 },
  { 0x10980, 0x109B7 },
  { 0x109BE, 0x109BF },
  { 0x10A00, 0x10A00 },
  { 0x10A10, 0x10A13 },
  { 0x10A15, 0x10A17 },
  { 0x10A19, 0x10A35 },
  { 0x10A60, 0x10A7C },
  { 0x10A80, 0x10A9C },
  { 0x10AC0, 0x10AC7 },
  { 0x10AC9, 0x10AE4 },
  { 0x10B00, 0x10B35 },
  { 0x10B40, 0x10B55 },
  { 0x10B60, 0x10B72 },
  { 0x10B80, 0x10B91 },
  { 0x10C00, 0x10C48 },
  { 0x10C80, 0x10CB2 },
  { 0x10CC0, 0x10CF2 },
  { 0x10D00, 0x10D23 },
  { 0x10F00, 0x10F1C },
  { 0x10F27, 0x10F27 },
  { 0x10F30, 0x10F45 },
  { 0x11003, 0x11037 },
  { 0x11083, 0x110AF },
  { 0x110D0, 0x110E8 },
  { 0x11103, 0x11126 },
  { 0x11144, 0x11144 },
  { 0x11150, 0x11172 },
  { 0x11176, 0x11176 },
  { 0x11183, 0x111B2 },
  { 0x111C1, 0x111C4 },
  { 0x111DA, 0x111DA },
  { 0x111DC, 0x111DC },
  { 0x11200, 0x11211 },
  { 0x11213, 0x1122B },
  { 0x11280, 0x11286 },
  { 0x11288, 0x11288 },
  { 0x1128A, 0x1128D },
  { 0x1128F, 0x1129D },
  { 0x1129F, 0x112A8 },
  { 0x112B0, 0x112DE },
  { 0x11305, 0x1130C },
  { 0x1130F, 0x11310 },
  { 0x11313, 0x11328 },
  { 0x1132A, 0x11330 },
  { 0x11332, 0x11333 },
  { 0x11335, 0x11339 },
  { 0x1133D, 0x1133D },
  { 0x11350, 0x11350 },
  { 0x1135D, 0x11361 },
  { 0x11400, 0x11434 },
  { 0x11447, 0x1144A },
  { 0x11480, 0x114AF },
  { 0x114C4, 0x114C5 },
  { 0x114C7, 0x114C7 },
  { 0x11580, 0x115AE },
  { 0x115D8, 0x115DB },
  { 0x11600, 0x1162F },
  { 0x11644, 0x11644 },
  { 0x11680, 0x116AA },
  { 0x11700, 0x1171A },
  { 0x11800, 0x1182B },
  { 0x118A0, 0x118DF },
  { 0x118FF, 0x118FF },
  { 0x11A00, 0x11A00 },
  { 0x11A0B, 0x11A32 },
  { 0x11A3A, 0x11A3A },
  { 0x11A50, 0x11A50 },
  { 0x11A5C, 0x11A83 },
  { 0x11A86, 0x11A89 },
  { 0x11A9D, 0x11A9D },
  { 0x11AC0, 0x11AF8 },
  { 0x11C00, 0x11C08 },
  { 0x11C0A, 0x11C2E },
  { 0x11C40, 0x11C40 },
  { 0x11C72, 0x11C8F },
  { 0x11D00, 0x11D06 },
  { 0x11D08, 0x11D09 },
  { 0x11D0B, 0x11D30 },
  { 0x11D46, 0x11D46 },
  { 0x11D60, 0x11D65 },
  { 0x11D67, 0x11D68 },
  { 0x11D6A, 0x11D89 },
  { 0x11D98, 0x11D98 },
  { 0x11EE0, 0x11EF2 },
  { 0x12000, 0x12399 },
  { 0x12400, 0x1246E },
  { 0x12480, 0x12543 },
  { 0x13000, 0x1342E },
  { 0x14400, 0x14646 },
  { 0x16800, 0x16A38 },
  { 0x16A40, 0x16A5E },
  { 0x16AD0, 0x16AED },
  { 0x16B00, 0x16B2F },
  { 0x16B40, 0x16B43 },
  { 0x16B63, 0x16B77 },
  { 0x16B7D, 0x16B8F },
  { 0x16E40, 0x16E7F },
  { 0x16F00, 0x16F44 },
  { 0x16F50, 0x16F50 },
  { 0x16F93, 0x16F9F },
  { 0x16FE0, 0x16FE1 },
  { 0x17000, 0x187F1 },
  { 0x18800, 0x18AF2 },
  { 0x1B000, 0x1B11E },
  { 0x1B170, 0x1B2FB },
  { 0x1BC00, 0x1BC6A },
  { 0x1BC70, 0x1BC7C },
  { 0x1BC80, 0x1BC88 },
  { 0x1BC90, 0x1BC99 },
  { 0x1D400, 0x1D454 },
  { 0x1D456, 0x1D49C },
  { 0x1D49E, 0x1D49F },
  { 0x1D4A2, 0x1D4A2 },
  { 0x1D4A5, 0x1D4A6 },
  { 0x1D4A9, 0x1D4AC },
  { 0x1D4AE, 0x1D4B9 },
  { 0x1D4BB, 0x1D4BB },
  { 0x1D4BD, 0x1D4C3 },
  { 0x1D4C5, 0x1D505 },
  { 0x1D507, 0x1D50A },
  { 0x1D50D, 0x1D514 },
  { 0x1D516, 0x1D51C },
  { 0x1D51E, 0x1D539 },
  { 0x1D53B, 0x1D53E },
  { 0x1D540, 0x1D544 },
  { 0x1D546, 0x1D546 },
  { 0x1D54A, 0x1D550 },
  { 0x1D552, 0x1D6A5 },
  { 0x1D6A8, 0x1D6C0 },
  { 0x1D6C2, 0x1D6DA },
  { 0x1D6DC, 0x1D6FA },
  { 0x1D6FC, 0x1D714 },
  { 0x1D716, 0x1D734 },
  { 0x1D736, 0x1D74E },
  { 0x1D750, 0x1D76E },
  { 0x1D770, 0x1D788 },
  { 0x1D78A, 0x1D7A8 },
  { 0x1D7AA, 0x1D7C2 },
  { 0x1D7C4, 0x1D7CB },
  { 0x1E800, 0x1E8C4 },
  { 0x1E900, 0x1E943 },
  { 0x1EE00, 0x1EE03 },
  { 0x1EE05, 0x1EE1F },
  { 0x1EE21, 0x1EE22 },
  { 0x1EE24, 0x1EE24 },
  { 0x1EE27, 0x1EE27 },
  { 0x1EE29, 0x1EE32 },
  { 0x1EE34, 0x1EE37 },
  { 0x1EE39, 0x1EE39 },
  { 0x1EE3B, 0x1EE3B },
  { 0x1EE42, 0x1EE42 },
  { 0x1EE47, 0x1EE47 },
  { 0x1EE49, 0x1EE49 },
  { 0x1EE4B, 0x1EE4B },
  { 0x1EE4D, 0x1EE4F },
  { 0x1EE51, 0x1EE52 },
  { 0x1EE54, 0x1EE54 },
  { 0x1EE57, 0x1EE57 },
  { 0x1EE59, 0x1EE59 },
  { 0x1EE5B, 0x1EE5B },
  { 0x1EE5D, 0x1EE5D },
  { 0x1EE5F, 0x1EE5F },
  { 0x1EE61, 0x1EE62 },
  { 0x1EE64, 0x1EE64 },
  { 0x1EE67, 0x1EE6A },
  { 0x1EE6C, 0x1EE72 },
  { 0x1EE74, 0x1EE77 },
  { 0x1EE79, 0x1EE7C },
  { 0x1EE7E, 0x1EE7E },
  { 0x1EE80, 0x1EE89 },
  { 0x1EE8B, 0x1EE9B },
  { 0x1EEA1, 0x1EEA3 },
  { 0x1EEA5, 0x1EEA9 },
  { 0x1EEAB, 0x1EEBB },
  { 0x20000, 0x2A6D6 },
  { 0x2A700, 0x2B734 },
  { 0x2B740, 0x2B81D },
  { 0x2B820, 0x2CEA1 },
  { 0x2CEB0, 0x2EBE0 },
  { 0x2F800, 0x2FA1D }
};

static const code_point_range XID_Continue[] = {
  { 0x00030, 0x00039 },
  { 0x00041, 0x0005A },
  { 0x0005F, 0x0005F },
  { 0x00061, 0x0007A },
  { 0x000AA, 0x000AA },
  { 0x000B5, 0x000B5 },
  { 0x000B7, 0x000B7 },
  { 0x000BA, 0x000BA },
  { 0x000C0, 0x000D6 },
  { 0x000D8, 0x000F6 },
  { 0x000F8, 0x002C1 },
  { 0x002C6, 0x002D1 },
  { 0x002E0, 0x002E4 },
  { 0x002EC, 0x002EC },
  { 0x002EE, 0x002EE },
  { 0x00300, 0x00374 },
  { 0x00376, 0x00377 },
  { 0x0037B, 0x0037D },
  { 0x0037F, 0x0037F },
  { 0x00386, 0x0038A },
  { 0x0038C, 0x0038C },
  { 0x0038E, 0x003A1 },
  { 0x003A3, 0x003F5 },
  { 0x003F7, 0x00481 },
  { 0x00483, 0x00487 },
  { 0x0048A, 0x0052F },
  { 0x00531, 0x00556 },
  { 0x00559, 0x00559 },
  { 0x00560, 0x00588 },
  { 0x00591, 0x005BD },
  { 0x005BF, 0x005BF },
  { 0x005C1, 0x005C2 },
  { 0x005C4, 0x005C5 },
  { 0x005C7, 0x005C7 },
  { 0x005D0, 0x005EA },
  { 0x005EF, 0x005F2 },
  { 0x00610, 0x0061A },
  { 0x00620, 0x00669 },
  { 0x0066E, 0x006D3 },
  { 0x006D5, 0x006DC },
  { 0x006DF, 0x006E8 },
  { 0x006EA, 0x006FC },
  { 0x006FF, 0x006FF },
  { 0x00710, 0x0074A },
  { 0x0074D, 0x007B1 },
  { 0x007C0, 0x007F5 },
  { 0x007FA, 0x007FA },
  { 0x007FD, 0x007FD },
  { 0x00800, 0x0082D },
  { 0x00840, 0x0085B },
  { 0x00860, 0x0086A },
  { 0x008A0, 0x008B4 },
  { 0x008B6, 0x008BD },
  { 0x008D3, 0x008E1 },
  { 0x008E3, 0x00963 },
  { 0x00966, 0x0096F },
  { 0x00971, 0x00983 },
  { 0x00985, 0x0098C },
  { 0x0098F, 0x00990 },
  { 0x00993, 0x009A8 },
  { 0x009AA, 0x009B0 },
  { 0x009B2, 0x009B2 },
  { 0x009B6, 0x009B9 },
  { 0x009BC, 0x009C4 },
  { 0x009C7, 0x009C8 },
  { 0x009CB, 0x009CE },
  { 0x009D7, 0x009D7 },
  { 0x009DC, 0x009DD },
  { 0x009DF, 0x009E3 },
  { 0x009E6, 0x009F1 },
  { 0x009FC, 0x009FC },
  { 0x009FE, 0x009FE },
  { 0x00A01, 0x00A03 },
  { 0x00A05, 0x00A0A },
  { 0x00A0F, 0x00A10 },
  { 0x00A13, 0x00A28 },
  { 0x00A2A, 0x00A30 },
  { 0x00A32, 0x00A33 },
  { 0x00A35, 0x00A36 },
  { 0x00A38, 0x00A39 },
  { 0x00A3C, 0x00A3C },
  { 0x00A3E, 0x00A42 },
  { 0x00A47, 0x00A48 },
  { 0x00A4B, 0x00A4D },
  { 0x00A51, 0x00A51 },
  { 0x00A59, 0x00A5C },
  { 0x00A5E, 0x00A5E },
  { 0x00A66, 0x00A75 },
  { 0x00A81, 0x00A83 },
  { 0x00A85, 0x00A8D },
  { 0x00A8F, 0x00A91 },
  { 0x00A93, 0x00AA8 },
  { 0x00AAA, 0x00AB0 },
  { 0x00AB2, 0x00AB3 },
  { 0x00AB5, 0x00AB9 },
  { 0x00ABC, 0x00AC5 },
  { 0x00AC7, 0x00AC9 },
  { 0x00ACB, 0x00ACD },
  { 0x00AD0, 0x00AD0 },
  { 0x00AE0, 0x00AE3 },
  { 0x00AE6, 0x00AEF },
  { 0x00AF9, 0x00AFF },
  { 0x00B01, 0x00B03 },
  { 0x00B05, 0x00B0C },
  { 0x00B0F, 0x00B10 },
  { 0x00B13, 0x00B28 },
  { 0x00B2A, 0x00B30 },
  { 0x00B32, 0x00B33 },
  { 0x00B35, 0x00B39 },
  { 0x00B3C, 0x00B44 },
  { 0x00B47, 0x00B48 },
  { 0x00B4B, 0x00B4D },
  { 0x00B56, 0x00B57 },
  { 0x00B5C, 0x00B5D },
  { 0x00B5F, 0x00B63 },
  { 0x00B66, 0x00B6F },
  { 0x00B71, 0x00B71 },
  { 0x00B82, 0x00B83 },
  { 0x00B85, 0x00B8A },
  { 0x00B8E, 0x00B90 },
  { 0x00B92, 0x00B95 },
  { 0x00B99, 0x00B9A },
  { 0x00B9C, 0x00B9C },
  { 0x00B9E, 0x00B9F },
  { 0x00BA3, 0x00BA4 },
  { 0x00BA8, 0x00BAA },
  { 0x00BAE, 0x00BB9 },
  { 0x00BBE, 0x00BC2 },
  { 0x00BC6, 0x00BC8 },
  { 0x00BCA, 0x00BCD },
  { 0x00BD0, 0x00BD0 },
  { 0x00BD7, 0x00BD7 },
  { 0x00BE6, 0x00BEF },
  { 0x00C00, 0x00C0C },
  { 0x00C0E, 0x00C10 },
  { 0x00C12, 0x00C28 },
  { 0x00C2A, 0x00C39 },
  { 0x00C3D, 0x00C44 },
  { 0x00C46, 0x00C48 },
  { 0x00C4A, 0x00C4D },
  { 0x00C55, 0x00C56 },
  { 0x00C58, 0x00C5A },
  { 0x00C60, 0x00C63 },
  { 0x00C66, 0x00C6F },
  { 0x00C80, 0x00C83 },
  { 0x00C85, 0x00C8C },
  { 0x00C8E, 0x00C90 },
  { 0x00C92, 0x00CA8 },
  { 0x00CAA, 0x00CB3 },
  { 0x00CB5, 0x00CB9 },
  { 0x00CBC, 0x00CC4 },
  { 0x00CC6, 0x00CC8 },
  { 0x00CCA, 0x00CCD },
  { 0x00CD5, 0x00CD6 },
  { 0x00CDE, 0x00CDE },
  { 0x00CE0, 0x00CE3 },
  { 0x00CE6, 0x00CEF },
  { 0x00CF1, 0x00CF2 },
  { 0x00D00, 0x00D03 },
  { 0x00D05, 0x00D0C },
  { 0x00D0E, 0x00D10 },
  { 0x00D12, 0x00D44 },
  { 0x00D46, 0x00D48 },
  { 0x00D4A, 0x00D4E },
  { 0x00D54, 0x00D57 },
  { 0x00D5F, 0x00D63 },
  { 0x00D66, 0x00D6F },
  { 0x00D7A, 0x00D7F },
  { 0x00D82, 0x00D83 },
  { 0x00D85, 0x00D96 },
  { 0x00D9A, 0x00DB1 },
  { 0x00DB3, 0x00DBB },
  { 0x00DBD, 0x00DBD },
  { 0x00DC0, 0x00DC6 },
  { 0x00DCA, 0x00DCA },
  { 0x00DCF, 0x00DD4 },
  { 0x00DD6, 0x00DD6 },
  { 0x00DD8, 0x00DDF },
  { 0x00DE6, 0x00DEF },
  { 0x00DF2, 0x00DF3 },
  { 0x00E01, 0x00E3A },
  { 0x00E40, 0x00E4E },
  { 0x00E50, 0x00E59 },
  { 0x00E81, 0x00E82 },
  { 0x00E84, 0x00E84 },
  { 0x00E87, 0x00E88 },
  { 0x00E8A, 0x00E8A },
  { 0x00E8D, 0x00E8D },
  { 0x00E94, 0x00E97 },
  { 0x00E99, 0x00E9F },
  { 0x00EA1, 0x00EA3 },
  { 0x00EA5, 0x00EA5 },
  { 0x00EA7, 0x00EA7 },
  { 0x00EAA, 0x00EAB },
  { 0x00EAD, 0x00EB9 },
  { 0x00EBB, 0x00EBD },
  { 0x00EC0, 0x00EC4 },
  { 0x00EC6, 0x00EC6 },
  { 0x00EC8, 0x00ECD },
  { 0x00ED0, 0x00ED9 },
  { 0x00EDC, 0x00EDF },
  { 0x00F00, 0x00F00 },
  { 0x00F18, 0x00F19 },
  { 0x00F20, 0x00F29 },
  { 0x00F35, 0x00F35 },
  { 0x00F37, 0x00F37 },
  { 0x00F39, 0x00F39 },
  { 0x00F3E, 0x00F47 },
  { 0x00F49, 0x00F6C },
  { 0x00F71, 0x00F84 },
  { 0x00F86, 0x00F97 },
  { 0x00F99, 0x00FBC },
  { 0x00FC6, 0x00FC6 },
  { 0x01000, 0x01049 },
  { 0x01050, 0x0109D },
  { 0x010A0, 0x010C5 },
  { 0x010C7, 0x010C7 },
  { 0x010CD, 0x010CD },
  { 0x010D0, 0x010FA },
  { 0x010FC, 0x01248 },
  { 0x0124A, 0x0124D },
  { 0x01250, 0x01256 },
  { 0x01258, 0x01258 },
  { 0x0125A, 0x0125D },
  { 0x01260, 0x01288 },
  { 0x0128A, 0x0128D },
  { 0x01290, 0x012B0 },
  { 0x012B2, 0x012B5 },
  { 0x012B8, 0x012BE },
  { 0x012C0, 0x012C0 },
  { 0x012C2, 0x012C5 },
  { 0x012C8, 0x012D6 },
  { 0x012D8, 0x01310 },
  { 0x01312, 0x01315 },
  { 0x01318, 0x0135A },
  { 0x0135D, 0x0135F },
  { 0x01369, 0x01371 },
  { 0x01380, 0x0138F },
  { 0x013A0, 0x013F5 },
  { 0x013F8, 0x013FD },
  { 0x01401, 0x0166C },
  { 0x0166F, 0x0167F },
  { 0x01681, 0x0169A },
  { 0x016A0, 0x016EA },
  { 0x016EE, 0x016F8 },
  { 0x01700, 0x0170C },
  { 0x0170E, 0x01714 },
  { 0x01720, 0x01734 },
  { 0x01740, 0x01753 },
  { 0x01760, 0x0176C },
  { 0x0176E, 0x01770 },
  { 0x01772, 0x01773 },
  { 0x01780, 0x017D3 },
  { 0x017D7, 0x017D7 },
  { 0x017DC, 0x017DD },
  { 0x017E0, 0x017E9 },
  { 0x0180B, 0x0180D },
  { 0x01810, 0x01819 },
  { 0x01820, 0x01878 },
  { 0x01880, 0x018AA },
  { 0x018B0, 0x018F5 },
  { 0x01900, 0x0191E },
  { 0x01920, 0x0192B },
  { 0x01930, 0x0193B },
  { 0x01946, 0x0196D },
  { 0x01970, 0x01974 },
  { 0x01980, 0x019AB },
  { 0x019B0, 0x019C9 },
  { 0x019D0, 0x019DA },
  { 0x01A00, 0x01A1B },
  { 0x01A20, 0x01A5E },
  { 0x01A60, 0x01A7C },
  { 0x01A7F, 0x01A89 },
  { 0x01A90, 0x01A99 },
  { 0x01AA7, 0x01AA7 },
  { 0x01AB0, 0x01ABD },
  { 0x01B00, 0x01B4B },
  { 0x01B50, 0x01B59 },
  { 0x01B6B, 0x01B73 },
  { 0x01B80, 0x01BF3 },
  { 0x01C00, 0x01C37 },
  { 0x01C40, 0x01C49 },
  { 0x01C4D, 0x01C7D },
  { 0x01C80, 0x01C88 },
  { 0x01C90, 0x01CBA },
  { 0x01CBD, 0x01CBF },
  { 0x01CD0, 0x01CD2 },
  { 0x01CD4, 0x01CF9 },
  { 0x01D00, 0x01DF9 },
  { 0x01DFB, 0x01F15 },
  { 0x01F18, 0x01F1D },
  { 0x01F20, 0x01F45 },
  { 0x01F48, 0x01F4D },
  { 0x01F50, 0x01F57 },
  { 0x01F59, 0x01F59 },
  { 0x01F5B, 0x01F5B },
  { 0x01F5D, 0x01F5D },
  { 0x01F5F, 0x01F7D },
  { 0x01F80, 0x01FB4 },
  { 0x01FB6, 0x01FBC },
  { 0x01FBE, 0x01FBE },
  { 0x01FC2, 0x01FC4 },
  { 0x01FC6, 0x01FCC },
  { 0x01FD0, 0x01FD3 },
  { 0x01FD6, 0x01FDB },
  { 0x01FE0, 0x01FEC },
  { 0x01FF2, 0x01FF4 },
  { 0x01FF6, 0x01FFC },
  { 0x0203F, 0x02040 },
  { 0x02054, 0x02054 },
  { 0x02071, 0x02071 },
  { 0x0207F, 0x0207F },
  { 0x02090, 0x0209C },
  { 0x020D0, 0x020DC },
  { 0x020E1, 0x020E1 },
  { 0x020E5, 0x020F0 },
  { 0x02102, 0x02102 },
  { 0x02107, 0x02107 },
  { 0x0210A, 0x02113 },
  { 0x02115, 0x02115 },
  { 0x02118, 0x0211D },
  { 0x02124, 0x02124 },
  { 0x02126, 0x02126 },
  { 0x02128, 0x02128 },
  { 0x0212A, 0x02139 },
  { 0x0213C, 0x0213F },
  { 0x02145, 0x02149 },
  { 0x0214E, 0x0214E },
  { 0x02160, 0x02188 },
  { 0x02C00, 0x02C2E },
  { 0x02C30, 0x02C5E },
  { 0x02C60, 0x02CE4 },
  { 0x02CEB, 0x02CF3 },
  { 0x02D00, 0x02D25 },
  { 0x02D27, 0x02D27 },
  { 0x02D2D, 0x02D2D },
  { 0x02D30, 0x02D67 },
  { 0x02D6F, 0x02D6F },
  { 0x02D7F, 0x02D96 },
  { 0x02DA0, 0x02DA6 },
  { 0x02DA8, 0x02DAE },
  { 0x02DB0, 0x02DB6 },
  { 0x02DB8, 0x02DBE },
  { 0x02DC0, 0x02DC6 },
  { 0x02DC8, 0x02DCE },
  { 0x02DD0, 0x02DD6 },
  { 0x02DD8, 0x02DDE },
  { 0x02DE0, 0x02DFF },
  { 0x03005, 0x03007 },
  { 0x03021, 0x0302F },
  { 0x03031, 0x03035 },
  { 0x03038, 0x0303C },
  { 0x03041, 0x03096 },
  { 0x03099, 0x0309A },
  { 0x0309D, 0x0309F },
  { 0x030A1, 0x030FA },
  { 0x030FC, 0x030FF },
  { 0x03105, 0x0312F },
  { 0x03131, 0x0318E },
  { 0x031A0, 0x031BA },
  { 0x031F0, 0x031FF },
  { 0x03400, 0x04DB5 },
  { 0x04E00, 0x09FEF },
  { 0x0A000, 0x0A48C },
  { 0x0A4D0, 0x0A4FD },
  { 0x0A500, 0x0A60C },
  { 0x0A610, 0x0A62B },
  { 0x0A640, 0x0A66F },
  { 0x0A674, 0x0A67D },
  { 0x0A67F, 0x0A6F1 },
  { 0x0A717, 0x0A71F },
  { 0x0A722, 0x0A788 },
  { 0x0A78B, 0x0A7B9 },
  { 0x0A7F7, 0x0A827 },
  { 0x0A840, 0x0A873 },
  { 0x0A880, 0x0A8C5 },
  { 0x0A8D0, 0x0A8D9 },
  { 0x0A8E0, 0x0A8F7 },
  { 0x0A8FB, 0x0A8FB },
  { 0x0A8FD, 0x0A92D },
  { 0x0A930, 0x0A953 },
  { 0x0A960, 0x0A97C },
  { 0x0A980, 0x0A9C0 },
  { 0x0A9CF, 0x0A9D9 },
  { 0x0A9E0, 0x0A9FE },
  { 0x0AA00, 0x0AA36 },
  { 0x0AA40, 0x0AA4D },
  { 0x0AA50, 0x0AA59 },
  { 0x0AA60, 0x0AA76 },
  { 0x0AA7A, 0x0AAC2 },
  { 0x0AADB, 0x0AADD },
  { 0x0AAE0, 0x0AAEF },
  { 0x0AAF2, 0x0AAF6 },
  { 0x0AB01, 0x0AB06 },
  { 0x0AB09, 0x0AB0E },
  { 0x0AB11, 0x0AB16 },
  { 0x0AB20, 0x0AB26 },
  { 0x0AB28, 0x0AB2E },
  { 0x0AB30, 0x0AB5A },
  { 0x0AB5C, 0x0AB65 },
  { 0x0AB70, 0x0ABEA },
  { 0x0ABEC, 0x0ABED },
  { 0x0ABF0, 0x0ABF9 },
  { 0x0AC00, 0x0D7A3 },
  { 0x0D7B0, 0x0D7C6 },
  { 0x0D7CB, 0x0D7FB },
  { 0x0F900, 0x0FA6D },
  { 0x0FA70, 0x0FAD9 },
  { 0x0FB00, 0x0FB06 },
  { 0x0FB13, 0x0FB17 },
  { 0x0FB1D, 0x0FB28 },
  { 0x0FB2A, 0x0FB36 },
  { 0x0FB38, 0x0FB3C },
  { 0x0FB3E, 0x0FB3E },
  { 0x0FB40, 0x0FB41 },
  { 0x0FB43, 0x0FB44 },
  { 0x0FB46, 0x0FBB1 },
  { 0x0FBD3, 0x0FC5D },
  { 0x0FC64, 0x0FD3D },
  { 0x0FD50, 0x0FD8F },
  { 0x0FD92, 0x0FDC7 },
  { 0x0FDF0, 0x0FDF9 },
  { 0x0FE00, 0x0FE0F },
  { 0x0FE20, 0x0FE2F },
  { 0x0FE33, 0x0FE34 },
  { 0x0FE4D, 0x0FE4F },
  { 0x0FE71, 0x0FE71 },
  { 0x0FE73, 0x0FE73 },
  { 0x0FE77, 0x0FE77 },
  { 0x0FE79, 0x0FE79 },
  { 0x0FE7B, 0x0FE7B },
  { 0x0FE7D, 0x0FE7D },
  { 0x0FE7F, 0x0FEFC },
  { 0x0FF10, 0x0FF19 },
  { 0x0FF21, 0x0FF3A },
  { 0x0FF3F, 0x0FF3F },
  { 0x0FF41, 0x0FF5A },
  { 0x0FF66, 0x0FFBE },
  { 0x0FFC2, 0x0FFC7 },
  { 0x0FFCA, 0x0FFCF },
  { 0x0FFD2, 0x0FFD7 },
  { 0x0FFDA, 0x0FFDC },
  { 0x10000, 0x1000B },
  { 0x1000D, 0x10026 },
  { 0x10028, 0x1003A },
  { 0x1003C, 0x1003D },
  { 0x1003F, 0x1004D },
  { 0x10050, 0x1005D },
  { 0x10080, 0x100FA },
  { 0x10140, 0x10174 },
  { 0x101FD, 0x101FD },
  { 0x10280, 0x1029C },
  { 0x102A0, 0x102D0 },
  { 0x102E0, 0x102E0 },
  { 0x10300, 0x1031F },
  { 0x1032D, 0x1034A },
  { 0x10350, 0x1037A },
  { 0x10380, 0x1039D },
  { 0x103A0, 0x103C3 },
  { 0x103C8, 0x103CF },
  { 0x103D1, 0x103D5 },
  { 0x10400, 0x1049D },
  { 0x104A0, 0x104A9 },
  { 0x104B0, 0x104D3 },
  { 0x104D8, 0x104FB },
  { 0x10500, 0x10527 },
  { 0x10530, 0x10563 },
  { 0x10600, 0x10736 },
  { 0x10740, 0x10755 },
  { 0x10760, 0x10767 },
  { 0x10800, 0x10805 },
  { 0x10808, 0x10808 },
  { 0x1080A, 0x10835 },
  { 0x10837, 0x10838 },
  { 0x1083C, 0x1083C },
  { 0x1083F, 0x10855 },
  { 0x10860, 0x10876 },
  { 0x10880, 0x1089E },
  { 0x108E0, 0x108F2 },
  { 0x108F4, 0x108F5 },
  { 0x10900, 0x10915 },
  { 0x10920, 0x10939 },
  { 0x10980, 0x109B7 },
  { 0x109BE, 0x109BF },
  { 0x10A00, 0x10A03 },
  { 0x10A05, 0x10A06 },
  { 0x10A0C, 0x10A13 },
  { 0x10A15, 0x10A17 },
  { 0x10A19, 0x10A35 },
  { 0x10A38, 0x10A3A },
  { 0x10A3F, 0x10A3F },
  { 0x10A60, 0x10A7C },
  { 0x10A80, 0x10A9C },
  { 0x10AC0, 0x10AC7 },
  { 0x10AC9, 0x10AE6 },
  { 0x10B00, 0x10B35 },
  { 0x10B40, 0x10B55 },
  { 0x10B60, 0x10B72 },
  { 0x10B80, 0x10B91 },
  { 0x10C00, 0x10C48 },
  { 0x10C80, 0x10CB2 },
  { 0x10CC0, 0x10CF2 },
  { 0x10D00, 0x10D27 },
  { 0x10D30, 0x10D39 },
  { 0x10F00, 0x10F1C },
  { 0x10F27, 0x10F27 },
  { 0x10F30, 0x10F50 },
  { 0x11000, 0x11046 },
  { 0x11066, 0x1106F },
  { 0x1107F, 0x110BA },
  { 0x110D0, 0x110E8 },
  { 0x110F0, 0x110F9 },
  { 0x11100, 0x11134 },
  { 0x11136, 0x1113F },
  { 0x11144, 0x11146 },
  { 0x11150, 0x11173 },
  { 0x11176, 0x11176 },
  { 0x11180, 0x111C4 },
  { 0x111C9, 0x111CC },
  { 0x111D0, 0x111DA },
  { 0x111DC, 0x111DC },
  { 0x11200, 0x11211 },
  { 0x11213, 0x11237 },
  { 0x1123E, 0x1123E },
  { 0x11280, 0x11286 },
  { 0x11288, 0x11288 },
  { 0x1128A, 0x1128D },
  { 0x1128F, 0x1129D },
  { 0x1129F, 0x112A8 },
  { 0x112B0, 0x112EA },
  { 0x112F0, 0x112F9 },
  { 0x11300, 0x11303 },
  { 0x11305, 0x1130C },
  { 0x1130F, 0x11310 },
  { 0x11313, 0x11328 },
  { 0x1132A, 0x11330 },
  { 0x11332, 0x11333 },
  { 0x11335, 0x11339 },
  { 0x1133B, 0x11344 },
  { 0x11347, 0x11348 },
  { 0x1134B, 0x1134D },
  { 0x11350, 0x11350 },
  { 0x11357, 0x11357 },
  { 0x1135D, 0x11363 },
  { 0x11366, 0x1136C },
  { 0x11370, 0x11374 },
  { 0x11400, 0x1144A },
  { 0x11450, 0x11459 },
  { 0x1145E, 0x1145E },
  { 0x11480, 0x114C5 },
  { 0x114C7, 0x114C7 },
  { 0x114D0, 0x114D9 },
  { 0x11580, 0x115B5 },
  { 0x115B8, 0x115C0 },
  { 0x115D8, 0x115DD },
  { 0x11600, 0x11640 },
  { 0x11644, 0x11644 },
  { 0x11650, 0x11659 },
  { 0x11680, 0x116B7 },
  { 0x116C0, 0x116C9 },
  { 0x11700, 0x1171A },
  { 0x1171D, 0x1172B },
  { 0x11730, 0x11739 },
  { 0x11800, 0x1183A },
  { 0x118A0, 0x118E9 },
  { 0x118FF, 0x118FF },
  { 0x11A00, 0x11A3E },
  { 0x11A47, 0x11A47 },
  { 0x11A50, 0x11A83 },
  { 0x11A86, 0x11A99 },
  { 0x11A9D, 0x11A9D },
  { 0x11AC0, 0x11AF8 },
  { 0x11C00, 0x11C08 },
  { 0x11C0A, 0x11C36 },
  { 0x11C38, 0x11C40 },
  { 0x11C50, 0x11C59 },
  { 0x11C72, 0x11C8F },
  { 0x11C92, 0x11CA7 },
  { 0x11CA9, 0x11CB6 },
  { 0x11D00, 0x11D06 },
  { 0x11D08, 0x11D09 },
  { 0x11D0B, 0x11D36 },
  { 0x11D3A, 0x11D3A },
  { 0x11D3C, 0x11D3D },
  { 0x11D3F, 0x11D47 },
  { 0x11D50, 0x11D59 },
  { 0x11D60, 0x11D65 },
  { 0x11D67, 0x11D68 },
  { 0x11D6A, 0x11D8E },
  { 0x11D90, 0x11D91 },
  { 0x11D93, 0x11D98 },
  { 0x11DA0, 0x11DA9 },
  { 0x11EE0, 0x11EF6 },
  { 0x12000, 0x12399 },
  { 0x12400, 0x1246E },
  { 0x12480, 0x12543 },
  { 0x13000, 0x1342E },
  { 0x14400, 0x14646 },
  { 0x16800, 0x16A38 },
  { 0x16A40, 0x16A5E },
  { 0x16A60, 0x16A69 },
  { 0x16AD0, 0x16AED },
  { 0x16AF0, 0x16AF4 },
  { 0x16B00, 0x16B36 },
  { 0x16B40, 0x16B43 },
  { 0x16B50, 0x16B59 },
  { 0x16B63, 0x16B77 },
  { 0x16B7D, 0x16B8F },
  { 0x16E40, 0x16E7F },
  { 0x16F00, 0x16F44 },
  { 0x16F50, 0x16F7E },
  { 0x16F8F, 0x16F9F },
  { 0x16FE0, 0x16FE1 },
  { 0x17000, 0x187F1 },
  { 0x18800, 0x18AF2 },
  { 0x1B000, 0x1B11E },
  { 0x1B170, 0x1B2FB },
  { 0x1BC00, 0x1BC6A },
  { 0x1BC70, 0x1BC7C },
  { 0x1BC80, 0x1BC88 },
  { 0x1BC90, 0x1BC99 },
  { 0x1BC9D, 0x1BC9E },
  { 0x1D165, 0x1D169 },
  { 0x1D16D, 0x1D172 },
  { 0x1D17B, 0x1D182 },
  { 0x1D185, 0x1D18B },
  { 0x1D1AA, 0x1D1AD },
  { 0x1D242, 0x1D244 },
  { 0x1D400, 0x1D454 },
  { 0x1D456, 0x1D49C },
  { 0x1D49E, 0x1D49F },
  { 0x1D4A2, 0x1D4A2 },
  { 0x1D4A5, 0x1D4A6 },
  { 0x1D4A9, 0x1D4AC },
  { 0x1D4AE, 0x1D4B9 },
  { 0x1D4BB, 0x1D4BB },
  { 0x1D4BD, 0x1D4C3 },
  { 0x1D4C5, 0x1D505 },
  { 0x1D507, 0x1D50A },
  { 0x1D50D, 0x1D514 },
  { 0x1D516, 0x1D51C },
  { 0x1D51E, 0x1D539 },
  { 0x1D53B, 0x1D53E },
  { 0x1D540, 0x1D544 },
  { 0x1D546, 0x1D546 },
  { 0x1D54A, 0x1D550 },
  { 0x1D552, 0x1D6A5 },
  { 0x1D6A8, 0x1D6C0 },
  { 0x1D6C2, 0x1D6DA },
  { 0x1D6DC, 0x1D6FA },
  { 0x1D6FC, 0x1D714 },
  { 0x1D716, 0x1D734 },
  { 0x1D736, 0x1D74E },
  { 0x1D750, 0x1D76E },
  { 0x1D770, 0x1D788 },
  { 0x1D78A, 0x1D7A8 },
  { 0x1D7AA, 0x1D7C2 },
  { 0x1D7C4, 0x1D7CB },
  { 0x1D7CE, 0x1D7FF },
  { 0x1DA00, 0x1DA36 },
  { 0x1DA3B, 0x1DA6C },
  { 0x1DA75, 0x1DA75 },
  { 0x1DA84, 0x1DA84 },
  { 0x1DA9B, 0x1DA9F },
  { 0x1DAA1, 0x1DAAF },
  { 0x1E000, 0x1E006 },
  { 0x1E008, 0x1E018 },
  { 0x1E01B, 0x1E021 },
  { 0x1E023, 0x1E024 },
  { 0x1E026, 0x1E02A },
  { 0x1E800, 0x1E8C4 },
  { 0x1E8D0, 0x1E8D6 },
  { 0x1E900, 0x1E94A },
  { 0x1E950, 0x1E959 },
  { 0x1EE00, 0x1EE03 },
  { 0x1EE05, 0x1EE1F },
  { 0x1EE21, 0x1EE22 },
  { 0x1EE24, 0x1EE24 },
  { 0x1EE27, 0x1EE27 },
  { 0x1EE29, 0x1EE32 },
  { 0x1EE34, 0x1EE37 },
  { 0x1EE39, 0x1EE39 },
  { 0x1EE3B, 0x1EE3B },
  { 0x1EE42, 0x1EE42 },
  { 0x1EE47, 0x1EE47 },
  { 0x1EE49, 0x1EE49 },
  { 0x1EE4B, 0x1EE4B },
  { 0x1EE4D, 0x1EE4F },
  { 0x1EE51, 0x1EE52 },
  { 0x1EE54, 0x1EE54 },
  { 0x1EE57, 0x1EE57 },
  { 0x1EE59, 0x1EE59 },
  { 0x1EE5B, 0x1EE5B },
  { 0x1EE5D, 0x1EE5D },
  { 0x1EE5F, 0x1EE5F },
  { 0x1EE61, 0x1EE62 },
  { 0x1EE64, 0x1EE64 },
  { 0x1EE67, 0x1EE6A },
  { 0x1EE6C, 0x1EE72 },
  { 0x1EE74, 0x1EE77 },
  { 0x1EE79, 0x1EE7C },
  { 0x1EE7E, 0x1EE7E },
  { 0x1EE80, 0x1EE89 },
  { 0x1EE8B, 0x1EE9B },
  { 0x1EEA1, 0x1EEA3 },
  { 0x1EEA5, 0x1EEA9 },
  { 0x1EEAB, 0x1EEBB },
  { 0x20000, 0x2A6D6 },
  { 0x2A700, 0x2B734 },
  { 0x2B740, 0x2B81D },
  { 0x2B820, 0x2CEA1 },
  { 0x2CEB0, 0x2EBE0 },
  { 0x2F800, 0x2FA1D },
  { 0xE0100, 0xE01EF }
};


int is_in_ranges (const code_point_range *const ranges, const size_t length,
                  const unsigned int code_point) {
  size_t low = 0, mid, high = length - 1;
  while (low <= high) {
    mid = (high + low) / 2;
#ifdef CHECK_BINARY_SEARCH
    printf("U+%04X <= U+%04X <= U+%04X? (%d, %d)\n",
      ranges[mid].low, code_point, ranges[mid].high, (int) low, (int) high);
#endif
    if (code_point < ranges[mid].low)
      high = mid - 1;
    else if (code_point <= ranges[mid].high)
      return 1;
    else
      low = mid + 1;
  }
  return 0;
}

/*
** Assumes that ASCII characters (0x00-0x7F) have already been validated,
** and that there are no invalid bytes (0xC0, 0xC1, 0xF5-0xFF).
*/
static const char *check_utf8_identifier(const char *const ident, const size_t len) {
  size_t i;
  static const unsigned int limits[] = {0xFF, 0x7F, 0x7FF, 0xFFFF};
  for (i = 0; i < len; i++) {
    unsigned int c = ident[i];
    if (c > 0x7F) {
      /* based on utf8_decode in lutf8lib.c */
      unsigned int code_point = 0;
      int count = 0;  /* to count number of continuation bytes */
      while (c & 0x40) {  /* still have continuation bytes? */
        int cc;
        if (++count + i >= len /* have reached end of string */
            || (cc = ident[i + count], /* read next byte */
            (cc & 0xC0) != 0x80)) { /* not a continuation byte? */
          return "missing continuation byte";
        }
        code_point = (code_point << 6) | (cc & 0x3F);  /* add lower 6 bits from cont. byte */
        c <<= 1;  /* to test next bit */
      }
      code_point |= ((c & 0x7F) << (count * 5));  /* add first byte */
      if (count > 3 || code_point > MAXUNICODE || code_point <= limits[count])
        return "invalid UTF-8"
			else if (!(i == 0 ? IN_RANGES(XID_Start, code_point)
                        : IN_RANGES(XID_CONTINUE, code_point))
        return "disallowed code point in identifier";
      i += count;  /* skip continuation bytes read */
    }
  }
  return NULL;
}
