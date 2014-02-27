//////////
//
// /libsf/VDebug/VDebug/mc_glob.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//	   Feb.25.2014
//////
// Change log:
//	   Feb.25.2014 - Development on 0.70 begins
//	   Nov.12.2012 - Initial creation
//////
// See devhelp.txt.
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//	   http://www.libsf.org/
//	   http://www.libsf.org/licenses/
//	   http://www.visual-freepro.org
//	   http://www.visual-freepro.org/blog/
//	   http://www.visual-freepro.org/forum/
//	   http://www.visual-freepro.org/wiki/
//	   http://www.visual-freepro.org/wiki/index.php/PBL
//	   http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.	In Jesus' name I pray.	Amen.
//
//




//////////
// Global variables
//////
	HINSTANCE		ghInstance;
	HINSTANCE		ghResourceDll						= NULL;					// Handle to the loaded resource dll instance
	s8				cgcVvmmcEngDll[]					= "vvmmcenu.dll";		// Default resource file
	SStartEnd		gseRootResourceTexts				= { NULL, NULL };


	// Known operators to the system
	SAsciiCompSearcher	cgcKeywordOperators[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "_azAZ__\000\000",		1,			true,		_MC_ICODE_ALPHA,						false,				NULL },
		{ "_09\000\000",			1,			true,		_MC_ICODE_NUMERIC,						false,				NULL },
		{ " ",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL },
		{ "\t",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL },
		{ "___",					1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL },
		{ "(",						1,			false,		_MC_ICODE_LEFT_PARENTHESIS,				false,				NULL },
		{ ")",						1,			false,		_MC_ICODE_RIGHT_PARENTHESIS,			false,				NULL },
		{ "[",						1,			false,		_MC_ICODE_LEFT_BRACKET,					false,				NULL },
		{ "]",						1,			false,		_MC_ICODE_RIGHT_BRACKET,				false,				NULL },
		{ "{",						1,			false,		_MC_ICODE_LEFT_BRACE,					false,				NULL },
		{ "}",						1,			false,		_MC_ICODE_RIGHT_BRACE,					false,				NULL },
		{ "+",						1,			false,		_MC_ICODE_PLUS,							false,				NULL },
		{ "-",						1,			false,		_MC_ICODE_MINU,							false,				NULL },
		{ "*",						1,			true,		_MC_ICODE_ASTERISK,						false,				NULL },
		{ "\\",						1,			true,		_MC_ICODE_SLASH,						false,				NULL },
		{ "/",						1,			true,		_MC_ICODE_BACKSLASH,					false,				NULL },
		{ "\"",						1,			false,		_MC_ICODE_DOUBLE_QUOTE,					false,				NULL },
		{ "'",						1,			false,		_MC_ICODE_SINGLE_QUOTE,					false,				NULL },
		{ ".",						1,			false,		_MC_ICODE_PERIOD,						false,				NULL },
		{ ",",						1,			false,		_MC_ICODE_COMMA,						false,				NULL },
		{ ":",						1,			false,		_MC_ICODE_COLON,						false,				NULL },
		{ "_",						1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL },
		{ "~",						1,			false,		_MC_ICODE_TILDE,						false,				NULL },
		{ "@",						1,			false,		_MC_ICODE_AT_SIGN,						false,				NULL },
		{ "?",						1,			false,		_MC_ICODE_QUESTION_MARK,				false,				NULL },
		{ "!",						1,			false,		_MC_ICODE_EXCLAMATION_MARK,				false,				NULL },
		{ "#",						1,			false,		_MC_ICODE_POUND_SIGN,					false,				NULL },
		{ "$",						1,			false,		_MC_ICODE_DOLLAR_SIGN,					false,				NULL },
		{ "%",						1,			false,		_MC_ICODE_PERCENT_SIGN,					false,				NULL },
		{ "^",						1,			false,		_MC_ICODE_CARET,						false,				NULL },
		{ "&",						1,			false,		_MC_ICODE_AMPERSAND,					false,				NULL },
		{ "=",						1,			false,		_MC_ICODE_EQUAL_SIGN,					false,				NULL },
		{ "|",						1,			false,		_MC_ICODE_PIPE_SIGN,					false,				NULL },
		{ "`",						1,			false,		_MC_ICODE_REVERSE_QUOTE,				false,				NULL },
		{ ";",						1,			false,		_MC_ICODE_SEMICOLON,					false,				NULL },
		{ ">",						1,			false,		_MC_ICODE_GREATER_THAN,					false,				NULL },
		{ "<",						1,			false,		_MC_ICODE_LESS_THAN,					false,				NULL },
		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */
		{ "_\000\377\000\000",		1,			true,		_MC_ICODE_UNKNOWN,						false,				NULL },
		{ 0,						0,			0,			0,										0,					0 }
	};




	// Pre-zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywordsPre[] =
	{
		// keyword					length		repeats?	extra (type)								first on line?		custom handler
		{ "include",				7,			false,		_MC_ICODE_INCLUDE,						true,				NULL },
		{ "define",					6,			false,		_MC_ICODE_DEFINE,						true,				NULL },
		{ "//",						2,			true,		_MC_ICODE_COMMENT,						true,				NULL },
		{ 0,						0,			0,			0,										0,					0 }
	};




	// Zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords0[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "dsnip_bxml",				10,			false,		_MC_ICODE_DSNIP_BXML_DEFINITION,		true,				NULL },
		{ "dsnip_dll",				9,			false,		_MC_ICODE_DSNIP_DLL_DEFINITION,			true,				NULL },
		{ "dsnip",					5,			false,		_MC_ICODE_DSNIP_DEFINITION,				true,				NULL },
		{ "snip",					4,			false,		_MC_ICODE_SNIP_DEFINITION,				true,				NULL },
		{ "function",				8,			false,		_MC_ICODE_SNIP_DEFINITION,				true,				NULL },
		{ "dll_function",			12,			false,		_MC_ICODE_DLL_FUNCTION_DEFINITION,		true,				NULL },
		{ "end",					3,			false,		_MC_ICODE_END,							true,				NULL },
		{ "prototype",				9,			false,		_MC_ICODE_PROTOTYPE,					true,				NULL },

		{ "params",					6,			false,		_MC_ICODE_PARAMS_DEFINITION,			false,				NULL },
		{ "returns",				7,			false,		_MC_ICODE_RETURN_DEFINITION,			false,				NULL },
		{ "locals",					6,			false,		_MC_ICODE_LOCALS_DEFINITION,			false,				NULL },

		{ "u8",						2,			false,		_MC_ICODE_U8_DEFINITION,				true,				NULL },
		{ "u16",					3,			false,		_MC_ICODE_U16_DEFINITION,				true,				NULL },
		{ "u32",					3,			false,		_MC_ICODE_U32_DEFINITION,				true,				NULL },
		{ "u64",					3,			false,		_MC_ICODE_U64_DEFINITION,				true,				NULL },
		{ "s8",						2,			false,		_MC_ICODE_S8_DEFINITION,				true,				NULL },
		{ "s16",					3,			false,		_MC_ICODE_S16_DEFINITION,				true,				NULL },
		{ "s32",					3,			false,		_MC_ICODE_S32_DEFINITION,				true,				NULL },
		{ "s64",					3,			false,		_MC_ICODE_S64_DEFINITION,				true,				NULL },
		{ "f32",					3,			false,		_MC_ICODE_F32_DEFINITION,				true,				NULL },
		{ "f64",					3,			false,		_MC_ICODE_F64_DEFINITION,				true,				NULL },
		{ "bni",					3,			false,		_MC_ICODE_BNI_DEFINITION,				true,				NULL },
		{ "bnf",					3,			false,		_MC_ICODE_BNF_DEFINITION,				true,				NULL },

		{ "u8",						2,			false,		_MC_ICODE_U8,							false,				NULL },
		{ "u16",					3,			false,		_MC_ICODE_U16,							false,				NULL },
		{ "u32",					3,			false,		_MC_ICODE_U32,							false,				NULL },
		{ "u64",					3,			false,		_MC_ICODE_U64,							false,				NULL },
		{ "s8",						2,			false,		_MC_ICODE_S8,							false,				NULL },
		{ "s16",					3,			false,		_MC_ICODE_S16,							false,				NULL },
		{ "s32",					3,			false,		_MC_ICODE_S32,							false,				NULL },
		{ "s64",					3,			false,		_MC_ICODE_S64,							false,				NULL },
		{ "f32",					3,			false,		_MC_ICODE_F32,							false,				NULL },
		{ "f64",					3,			false,		_MC_ICODE_F64,							false,				NULL },
		{ "bni",					3,			false,		_MC_ICODE_BNI,							false,				NULL },
		{ "bnf",					3,			false,		_MC_ICODE_BNF,							false,				NULL },

		{ "snip",					4,			false,		_MC_ICODE_SNIP,							false,				NULL },
		{ "ip",						2,			false,		_MC_ICODE_IP,							false,				NULL },
		{ "sp",						2,			false,		_MC_ICODE_SP,							false,				NULL },
		{ "bp",						2,			false,		_MC_ICODE_BP,							false,				NULL },
		{ "ready",					5,			false,		_MC_ICODE_READY,						false,				NULL },
		{ "ready.offset",			12,			false,		_MC_ICODE_READY_OFFSET,					false,				NULL },
		{ "flags",					5,			false,		_MC_ICODE_FLAGS,						false,				NULL },
		{ "pred",					4,			false,		_MC_ICODE_PRED,							false,				NULL },
		{ "pred.count",				10,			false,		_MC_ICODE_PREDCOUNT,					false,				NULL },
		{ "exsnip",					6,			false,		_MC_ICODE_EXSNIP,						false,				NULL },
		{ "error",					5,			false,		_MC_ICODE_ERROR,						false,				NULL },

		{ "a",						1,			false,		_MC_ICODE_A,							false,				NULL },
		{ "b",						1,			false,		_MC_ICODE_B,							false,				NULL },
		{ "c",						1,			false,		_MC_ICODE_C,							false,				NULL },
		{ "d",						1,			false,		_MC_ICODE_D,							false,				NULL },
		{ "e",						1,			false,		_MC_ICODE_E,							false,				NULL },
		{ "f",						1,			false,		_MC_ICODE_F,							false,				NULL },
		{ "g",						1,			false,		_MC_ICODE_G,							false,				NULL },
		{ "h",						1,			false,		_MC_ICODE_H,							false,				NULL },
		{ "i",						1,			false,		_MC_ICODE_I,							false,				NULL },
		{ "j",						1,			false,		_MC_ICODE_J,							false,				NULL },
		{ "k",						1,			false,		_MC_ICODE_K,							false,				NULL },
		{ "l",						1,			false,		_MC_ICODE_L,							false,				NULL },
		{ "m",						1,			false,		_MC_ICODE_M,							false,				NULL },
		{ "n",						1,			false,		_MC_ICODE_N,							false,				NULL },
		{ "o",						1,			false,		_MC_ICODE_O,							false,				NULL },
		{ "p",						1,			false,		_MC_ICODE_P,							false,				NULL },

		{ "fa",						2,			false,		_MC_ICODE_FA,							false,				NULL },
		{ "fb",						2,			false,		_MC_ICODE_FB,							false,				NULL },
		{ "fc",						2,			false,		_MC_ICODE_FC,							false,				NULL },
		{ "fd",						2,			false,		_MC_ICODE_FD,							false,				NULL },
		{ "fe",						2,			false,		_MC_ICODE_FE,							false,				NULL },
		{ "ff",						2,			false,		_MC_ICODE_FF,							false,				NULL },
		{ "fg",						2,			false,		_MC_ICODE_FG,							false,				NULL },
		{ "fh",						2,			false,		_MC_ICODE_FH,							false,				NULL },
		{ "fi",						2,			false,		_MC_ICODE_FI,							false,				NULL },
		{ "fj",						2,			false,		_MC_ICODE_FJ,							false,				NULL },
		{ "fk",						2,			false,		_MC_ICODE_FK,							false,				NULL },
		{ "fl",						2,			false,		_MC_ICODE_FL,							false,				NULL },
		{ "fm",						2,			false,		_MC_ICODE_FM,							false,				NULL },
		{ "fn",						2,			false,		_MC_ICODE_FN,							false,				NULL },
		{ "fo",						2,			false,		_MC_ICODE_FO,							false,				NULL },
		{ "fp",						2,			false,		_MC_ICODE_FP,							false,				NULL },

		{ "result2",				7,			false,		_MC_ICODE_RESULT2,						false,				NULL },
		{ "result",					6,			false,		_MC_ICODE_RESULT,						false,				NULL },

		{ 0,						0,			0,			0,										0,					0 }
	};




	// First-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "uadd64",					6,			false,		_MC_ICODE_UADD64,						true,				 NULL },
		{ "uadd32",					6,			false,		_MC_ICODE_UADD32,						true,				 NULL },
		{ "uadd16",					6,			false,		_MC_ICODE_UADD16,						true,				 NULL },
		{ "uadd8",					5,			false,		_MC_ICODE_UADD8,						true,				 NULL },
		{ "usub64",					6,			false,		_MC_ICODE_USUB64,						true,				 NULL },
		{ "usub32",					6,			false,		_MC_ICODE_USUB32,						true,				 NULL },
		{ "usub16",					6,			false,		_MC_ICODE_USUB16,						true,				 NULL },
		{ "usub8",					5,			false,		_MC_ICODE_USUB8,						true,				 NULL },
		{ "umul64",					6,			false,		_MC_ICODE_UMUL64,						true,				 NULL },
		{ "umul32",					6,			false,		_MC_ICODE_UMUL32,						true,				 NULL },
		{ "umul16",					6,			false,		_MC_ICODE_UMUL16,						true,				 NULL },
		{ "umul8",					5,			false,		_MC_ICODE_UMUL8,						true,				 NULL },
		{ "udiv64",					6,			false,		_MC_ICODE_UDIV64,						true,				 NULL },
		{ "udiv32",					6,			false,		_MC_ICODE_UDIV32,						true,				 NULL },
		{ "udiv16",					6,			false,		_MC_ICODE_UDIV16,						true,				 NULL },
		{ "udiv8",					5,			false,		_MC_ICODE_UDIV8,						true,				 NULL },
		{ "ucomp64",				7,			false,		_MC_ICODE_UCOMP64,						true,				 NULL },
		{ "ucomp32",				7,			false,		_MC_ICODE_UCOMP32,						true,				 NULL },
		{ "ucomp16",				7,			false,		_MC_ICODE_UCOMP16,						true,				 NULL },
		{ "ucomp8",					6,			false,		_MC_ICODE_UCOMP8,						true,				 NULL },
		{ "saddf64",				7,			false,		_MC_ICODE_SADDF64,						true,				 NULL },
		{ "saddf32",				7,			false,		_MC_ICODE_SADDF32,						true,				 NULL },
		{ "sadd64",					6,			false,		_MC_ICODE_SADD64,						true,				 NULL },
		{ "sadd32",					6,			false,		_MC_ICODE_SADD32,						true,				 NULL },
		{ "sadd16",					6,			false,		_MC_ICODE_SADD16,						true,				 NULL },
		{ "sadd8",					5,			false,		_MC_ICODE_SADD8,						true,				 NULL },
		{ "ssubf64",				7,			false,		_MC_ICODE_SSUBF64,						true,				 NULL },
		{ "ssubf32",				7,			false,		_MC_ICODE_SSUBF32,						true,				 NULL },
		{ "ssub64",					6,			false,		_MC_ICODE_SSUB64,						true,				 NULL },
		{ "ssub32",					6,			false,		_MC_ICODE_SSUB32,						true,				 NULL },
		{ "ssub16",					6,			false,		_MC_ICODE_SSUB16,						true,				 NULL },
		{ "ssub8",					5,			false,		_MC_ICODE_SSUB8,						true,				 NULL },
		{ "smulf64",				7,			false,		_MC_ICODE_SMULF64,						true,				 NULL },
		{ "smulf32",				7,			false,		_MC_ICODE_SMULF32,						true,				 NULL },
		{ "smul64",					6,			false,		_MC_ICODE_SMUL64,						true,				 NULL },
		{ "smul32",					6,			false,		_MC_ICODE_SMUL32,						true,				 NULL },
		{ "smul16",					6,			false,		_MC_ICODE_SMUL16,						true,				 NULL },
		{ "smul8",					5,			false,		_MC_ICODE_SMUL8,						true,				 NULL },
		{ "sdivf64",				7,			false,		_MC_ICODE_SDIVF64,						true,				 NULL },
		{ "sdivf32",				7,			false,		_MC_ICODE_SDIVF32,						true,				 NULL },
		{ "sdiv64",					6,			false,		_MC_ICODE_SDIV64,						true,				 NULL },
		{ "sdiv32",					6,			false,		_MC_ICODE_SDIV32,						true,				 NULL },
		{ "sdiv16",					6,			false,		_MC_ICODE_SDIV16,						true,				 NULL },
		{ "sdiv8",					5,			false,		_MC_ICODE_SDIV8,						true,				 NULL },
		{ "scompf64",				8,			false,		_MC_ICODE_SCOMPF64,						true,				 NULL },
		{ "scompf32",				8,			false,		_MC_ICODE_SCOMPF32,						true,				 NULL },
		{ "scomp64",				7,			false,		_MC_ICODE_SCOMP64,						true,				 NULL },
		{ "scomp32",				7,			false,		_MC_ICODE_SCOMP32,						true,				 NULL },
		{ "scomp16",				7,			false,		_MC_ICODE_SCOMP16,						true,				 NULL },
		{ "scomp8",					6,			false,		_MC_ICODE_SCOMP8,						true,				 NULL },
		{ "copyf64",				7,			false,		_MC_ICODE_COPYF64,						true,				 NULL },
		{ "copyf32",				7,			false,		_MC_ICODE_COPYF32,						true,				 NULL },
		{ "copy64",					6,			false,		_MC_ICODE_COPY64,						true,				 NULL },
		{ "copy32",					6,			false,		_MC_ICODE_COPY32,						true,				 NULL },
		{ "copy16",					6,			false,		_MC_ICODE_COPY16,						true,				 NULL },
		{ "copy8",					5,			false,		_MC_ICODE_COPY8,						true,				 NULL },
		{ "copy8x",					6,			false,		_MC_ICODE_COPY8X,						true,				 NULL },
		{ "movef64",				7,			false,		_MC_ICODE_MOVEF64,						true,				 NULL },
		{ "movef32",				7,			false,		_MC_ICODE_MOVEF32,						true,				 NULL },
		{ "move64",					6,			false,		_MC_ICODE_MOVE64,						true,				 NULL },
		{ "move32",					6,			false,		_MC_ICODE_MOVE32,						true,				 NULL },
		{ "move16",					6,			false,		_MC_ICODE_MOVE16,						true,				 NULL },
		{ "move8",					5,			false,		_MC_ICODE_MOVE8,						true,				 NULL },
		{ "xchf64",					6,			false,		_MC_ICODE_XCHF64,						true,				 NULL },
		{ "xchf32",					6,			false,		_MC_ICODE_XCHF32,						true,				 NULL },
		{ "xch64",					5,			false,		_MC_ICODE_XCH64,						true,				 NULL },
		{ "xch32",					5,			false,		_MC_ICODE_XCH32,						true,				 NULL },
		{ "xch16",					5,			false,		_MC_ICODE_XCH16,						true,				 NULL },
		{ "xch8",					4,			false,		_MC_ICODE_XCH8,							true,				 NULL },
		{ "xchuadd64",				9,			false,		_MC_ICODE_XCHUADD64,					true,				 NULL },
		{ "xchuadd32",				9,			false,		_MC_ICODE_XCHUADD32,					true,				 NULL },
		{ "xchuadd16",				9,			false,		_MC_ICODE_XCHUADD16,					true,				 NULL },
		{ "xchuadd8",				8,			false,		_MC_ICODE_XCHUADD8,						true,				 NULL },
		{ "xchumul64",				9,			false,		_MC_ICODE_XCHUMUL64,					true,				 NULL },
		{ "xchumul32",				9,			false,		_MC_ICODE_XCHUMUL32,					true,				 NULL },
		{ "xchumul16",				9,			false,		_MC_ICODE_XCHUMUL16,					true,				 NULL },
		{ "xchumul8",				8,			false,		_MC_ICODE_XCHUMUL8,						true,				 NULL },
		{ "xchsaddf64",				10,			false,		_MC_ICODE_XCHSADDF64,					true,				 NULL },
		{ "xchsaddf32",				10,			false,		_MC_ICODE_XCHSADDF32,					true,				 NULL },
		{ "xchsadd64",				9,			false,		_MC_ICODE_XCHSADD64,					true,				 NULL },
		{ "xchsadd32",				9,			false,		_MC_ICODE_XCHSADD32,					true,				 NULL },
		{ "xchsadd16",				9,			false,		_MC_ICODE_XCHSADD16,					true,				 NULL },
		{ "xchsadd8",				8,			false,		_MC_ICODE_XCHSADD8,						true,				 NULL },
		{ "xchsmulf64",				10,			false,		_MC_ICODE_XCHSMULF64,					true,				 NULL },
		{ "xchsmulf32",				10,			false,		_MC_ICODE_XCHSMULF32,					true,				 NULL },
		{ "xchsmul64",				9,			false,		_MC_ICODE_XCHSMUL64,					true,				 NULL },
		{ "xchsmul32",				9,			false,		_MC_ICODE_XCHSMUL32,					true,				 NULL },
		{ "xchsmul16",				9,			false,		_MC_ICODE_XCHSMUL16,					true,				 NULL },
		{ "xchsmul8",				8,			false,		_MC_ICODE_XCHSMUL8,						true,				 NULL },
		{ "and64",					5,			false,		_MC_ICODE_AND64,						true,				 NULL },
		{ "and32",					5,			false,		_MC_ICODE_AND32,						true,				 NULL },
		{ "and16",					5,			false,		_MC_ICODE_AND16,						true,				 NULL },
		{ "and8",					4,			false,		_MC_ICODE_AND8,							true,				 NULL },
		{ "or64",					4,			false,		_MC_ICODE_OR64,							true,				 NULL },
		{ "or32",					4,			false,		_MC_ICODE_OR32,							true,				 NULL },
		{ "or16",					4,			false,		_MC_ICODE_OR16,							true,				 NULL },
		{ "or8",					3,			false,		_MC_ICODE_OR8,							true,				 NULL },
		{ "not64",					5,			false,		_MC_ICODE_NOT64,						true,				 NULL },
		{ "not32",					5,			false,		_MC_ICODE_NOT32,						true,				 NULL },
		{ "not16",					5,			false,		_MC_ICODE_NOT16,						true,				 NULL },
		{ "not8",					4,			false,		_MC_ICODE_NOT8,							true,				 NULL },
		{ "xor64",					5,			false,		_MC_ICODE_XOR64,						true,				 NULL },
		{ "xor32",					5,			false,		_MC_ICODE_XOR32,						true,				 NULL },
		{ "xor16",					5,			false,		_MC_ICODE_XOR16,						true,				 NULL },
		{ "xor8",					4,			false,		_MC_ICODE_XOR8,							true,				 NULL },
		{ "chgsf64",				7,			false,		_MC_ICODE_CHGSF64,						true,				 NULL },
		{ "chgsf32",				7,			false,		_MC_ICODE_CHGSF32,						true,				 NULL },
		{ "neg64",					5,			false,		_MC_ICODE_NEG64,						true,				 NULL },
		{ "neg32",					5,			false,		_MC_ICODE_NEG32,						true,				 NULL },
		{ "neg16",					5,			false,		_MC_ICODE_NEG16,						true,				 NULL },
		{ "neg8",					4,			false,		_MC_ICODE_NEG8,							true,				 NULL },
		{ "incf64",					6,			false,		_MC_ICODE_INCF64,						true,				 NULL },
		{ "incf32",					6,			false,		_MC_ICODE_INCF32,						true,				 NULL },
		{ "inc64",					5,			false,		_MC_ICODE_INC64,						true,				 NULL },
		{ "inc32",					5,			false,		_MC_ICODE_INC32,						true,				 NULL },
		{ "inc16",					5,			false,		_MC_ICODE_INC16,						true,				 NULL },
		{ "inc8",					4,			false,		_MC_ICODE_INC8,							true,				 NULL },
		{ "decf64",					6,			false,		_MC_ICODE_DECF64,						true,				 NULL },
		{ "decf32",					6,			false,		_MC_ICODE_DECF32,						true,				 NULL },
		{ "dec64",					5,			false,		_MC_ICODE_DEC64,						true,				 NULL },
		{ "dec32",					5,			false,		_MC_ICODE_DEC32,						true,				 NULL },
		{ "dec16",					5,			false,		_MC_ICODE_DEC16,						true,				 NULL },
		{ "dec8",					4,			false,		_MC_ICODE_DEC8,							true,				 NULL },
		{ "shl64",					5,			false,		_MC_ICODE_SHL64,						true,				 NULL },
		{ "shl32",					5,			false,		_MC_ICODE_SHL32,						true,				 NULL },
		{ "shl16",					5,			false,		_MC_ICODE_SHL16,						true,				 NULL },
		{ "shl8",					4,			false,		_MC_ICODE_SHL8,							true,				 NULL },
		{ "shru64",					6,			false,		_MC_ICODE_SHRU64,						true,				 NULL },
		{ "shru32",					6,			false,		_MC_ICODE_SHRU32,						true,				 NULL },
		{ "shru16",					6,			false,		_MC_ICODE_SHRU16,						true,				 NULL },
		{ "shru8",					5,			false,		_MC_ICODE_SHRU8,						true,				 NULL },
		{ "shrs64",					6,			false,		_MC_ICODE_SHRS64,						true,				 NULL },
		{ "shrs32",					6,			false,		_MC_ICODE_SHRS32,						true,				 NULL },
		{ "shrs16",					6,			false,		_MC_ICODE_SHRS16,						true,				 NULL },
		{ "shrs8",					5,			false,		_MC_ICODE_SHRS8,						true,				 NULL },
		{ "rol64",					5,			false,		_MC_ICODE_ROL64,						true,				 NULL },
		{ "rol32",					5,			false,		_MC_ICODE_ROL32,						true,				 NULL },
		{ "rol16",					5,			false,		_MC_ICODE_ROL16,						true,				 NULL },
		{ "rol8",					4,			false,		_MC_ICODE_ROL8,							true,				 NULL },
		{ "ror64",					5,			false,		_MC_ICODE_ROR64,						true,				 NULL },
		{ "ror32",					5,			false,		_MC_ICODE_ROR32,						true,				 NULL },
		{ "ror16",					5,			false,		_MC_ICODE_ROR16,						true,				 NULL },
		{ "ror8",					4,			false,		_MC_ICODE_ROR8,							true,				 NULL },
		{ "cnvobj",					6,			false,		_MC_ICODE_CNVOBJ,						true,				 NULL },
		{ "copyf32i32",				10,			false,		_MC_ICODE_COPYF32I32,					true,				 NULL },
		{ "copyi32f32",				10,			false,		_MC_ICODE_COPYI32F32,					true,				 NULL },
		{ "copyf64i64",				10,			false,		_MC_ICODE_COPYF64I64,					true,				 NULL },
		{ "copyi64f64",				10,			false,		_MC_ICODE_COPYI64F64,					true,				 NULL },
		{ "copyf32i64",				10,			false,		_MC_ICODE_COPYF32I64,					true,				 NULL },
		{ "copyi32f64",				10,			false,		_MC_ICODE_COPYI32F64,					true,				 NULL },
		{ "copyf64i32",				10,			false,		_MC_ICODE_COPYF64I32,					true,				 NULL },
		{ "copyi64f32",				10,			false,		_MC_ICODE_COPYI64F32,					true,				 NULL },
		{ "copyf264",				8,			false,		_MC_ICODE_COPYF264,						true,				 NULL },
		{ "copy642f",				8,			false,		_MC_ICODE_COPY642F,						true,				 NULL },
		{ "copy",					4,			false,		_MC_ICODE_COPY,							true,				 NULL },
		{ "allocs",					6,			false,		_MC_ICODE_ALLOCS,						true,				 NULL },
		{ "deallocs",				8,			false,		_MC_ICODE_DEALLOCS,						true,				 NULL },
		{ "debug",					5,			false,		_MC_ICODE_DEBUG,						true,				 NULL },
		{ "halt",					4,			false,		_MC_ICODE_HALT,							true,				 NULL },
		{ "nop",					3,			false,		_MC_ICODE_NOP,							true,				 NULL },
		{ "lenobj",					6,			false,		_MC_ICODE_LENOBJ,						true,				 NULL },
		{ "numobja",				7,			false,		_MC_ICODE_NUMOBJA,						true,				 NULL },
		{ "numobju",				7,			false,		_MC_ICODE_NUMOBJU,						true,				 NULL },
		{ "nua",					3,			false,		_MC_ICODE_NUA,							true,				 NULL },
		{ "nun",					3,			false,		_MC_ICODE_NUN,							true,				 NULL },
		{ "setips",					6,			false,		_MC_ICODE_SETIPS,						true,				 NULL },
		{ "setip",					5,			false,		_MC_ICODE_SETIP,						true,				 NULL },
		{ "adjip64",				7,			false,		_MC_ICODE_ADJIP64,						true,				 NULL },
		{ "adjip32",				7,			false,		_MC_ICODE_ADJIP32,						true,				 NULL },
		{ "adjip16",				7,			false,		_MC_ICODE_ADJIP16,						true,				 NULL },
		{ "adjip8",					6,			false,		_MC_ICODE_ADJIP8,						true,				 NULL },
		{ "callsn",					6,			false,		_MC_ICODE_CALLSN,						true,				 NULL },
		{ "callsna",				7,			false,		_MC_ICODE_CALLSNA,						true,				 NULL },
		{ "callsnu",				7,			false,		_MC_ICODE_CALLSNU,						true,				 NULL },
		{ "calldsn",				7,			false,		_MC_ICODE_CALLDSN,						true,				 NULL },
		{ "calldsna",				8,			false,		_MC_ICODE_CALLDSNA,						true,				 NULL },
		{ "calldsnu",				8,			false,		_MC_ICODE_CALLDSNU,						true,				 NULL },
		{ "callhn",					6,			false,		_MC_ICODE_CALLHN,						true,				 NULL },
		{ "callhna",				7,			false,		_MC_ICODE_CALLHNA,						true,				 NULL },
		{ "push64",					6,			false,		_MC_ICODE_PUSH64,						true,				 NULL },
		{ "pop64",					5,			false,		_MC_ICODE_POP64,						true,				 NULL },
		{ "push32",					6,			false,		_MC_ICODE_PUSH32,						true,				 NULL },
		{ "pop32",					5,			false,		_MC_ICODE_POP32,						true,				 NULL },
		{ "stackcpy32",				10,			false,		_MC_ICODE_STACKCPY32,					true,				 NULL },
		{ "return",					6,			false,		_MC_ICODE_RETURN,						true,				 NULL },
		{ "rettonam",				8,			false,		_MC_ICODE_RETTONAM,						true,				 NULL },
		{ "rettonum",				8,			false,		_MC_ICODE_RETTONUM,						true,				 NULL },
		{ "sflag",					5,			false,		_MC_ICODE_SFLAG,						true,				 NULL },
		{ "cflag",					5,			false,		_MC_ICODE_CFLAG,						true,				 NULL },
		{ "tflag",					5,			false,		_MC_ICODE_TFLAG,						true,				 NULL },
		{ "inflag",					6,			false,		_MC_ICODE_INFLAG,						true,				 NULL },
		{ "outflag",				7,			false,		_MC_ICODE_OUTFLAG,						true,				 NULL },
		{ "setc",					4,			false,		_MC_ICODE_SETC,							true,				 NULL },
		{ "seto",					4,			false,		_MC_ICODE_SETO,							true,				 NULL },
		{ "setu",					4,			false,		_MC_ICODE_SETU,							true,				 NULL },
		{ "sete",					4,			false,		_MC_ICODE_SETE,							true,				 NULL },
		{ "setz",					4,			false,		_MC_ICODE_SETZ,							true,				 NULL },
		{ "setn",					4,			false,		_MC_ICODE_SETN,							true,				 NULL },
		{ "setp",					4,			false,		_MC_ICODE_SETP,							true,				 NULL },
		{ "seta",					4,			false,		_MC_ICODE_SETA,							true,				 NULL },
		{ "setan",					5,			false,		_MC_ICODE_SETAN,						true,				 NULL },
		{ "clra",					4,			false,		_MC_ICODE_CLRA,							true,				 NULL },
		{ "toga",					4,			false,		_MC_ICODE_TOGA,							true,				 NULL },
		{ "loadtheme",				9,			false,		_MC_ICODE_LOADTHEME,					true,				 NULL },
		{ "renderstart",			11,			false,		_MC_ICODE_RENDERSTART,					true,				 NULL },
		{ "renderregion",			12,			false,		_MC_ICODE_RENDERREGION,					true,				 NULL },
		{ "rendercanvas",			12,			false,		_MC_ICODE_RENDERCANVAS,					true,				 NULL },
		{ "renderscreen",			12,			false,		_MC_ICODE_RENDERSCREEN,					true,				 NULL },
		{ "renderstop",				10,			false,		_MC_ICODE_RENDERSTOP,					true,				 NULL },
		{ "appoapa",				7,			false,		_MC_ICODE_APPOAPA,						true,				 NULL },
		{ "appoach",				7,			false,		_MC_ICODE_APPOACH,						true,				 NULL },
		{ "appoapr",				7,			false,		_MC_ICODE_APPOAPR,						true,				 NULL },
		{ "appoane",				7,			false,		_MC_ICODE_APPOANE,						true,				 NULL },
		{ "delofo",					6,			false,		_MC_ICODE_DELOFO,						true,				 NULL },
		{ "destroy",				7,			false,		_MC_ICODE_DESTROY,						true,				 NULL },
		{ "iscatter",				8,			false,		_MC_ICODE_ISCATTER,						true,				 NULL },
		{ "igather",				7,			false,		_MC_ICODE_IGATHER,						true,				 NULL },
		{ "fscatter",				8,			false,		_MC_ICODE_FSCATTER,						true,				 NULL },
		{ "fgather",				7,			false,		_MC_ICODE_FGATHER,						true,				 NULL },
		{ "tmraddg",				7,			false,		_MC_ICODE_TMRADDG,						true,				 NULL },
		{ "tmrdelg",				7,			false,		_MC_ICODE_TMRDELG,						true,				 NULL },
		{ "tmrenag",				7,			false,		_MC_ICODE_TMRENAG,						true,				 NULL },
		{ "tmrdisg",				7,			false,		_MC_ICODE_TMRDISG,						true,				 NULL },
		{ "tmraddt",				7,			false,		_MC_ICODE_TMRADDT,						true,				 NULL },
		{ "tmrdelt",				7,			false,		_MC_ICODE_TMRDELT,						true,				 NULL },
		{ "tmrenat",				7,			false,		_MC_ICODE_TMRENAT,						true,				 NULL },
		{ "tmrdist",				7,			false,		_MC_ICODE_TMRDIST,						true,				 NULL },
		{ "passive",				7,			false,		_MC_ICODE_PASSIVE,						true,				 NULL },
		{ "active",					6,			false,		_MC_ICODE_ACTIVE,						true,				 NULL },
		{ "setexs",					6,			false,		_MC_ICODE_SETEXS,						true,				 NULL },
		{ "exceps",					6,			false,		_MC_ICODE_EXCEPS,						true,				 NULL },
		{ "thrap",					5,			false,		_MC_ICODE_THRAP,						true,				 NULL },
		{ "thraps",					6,			false,		_MC_ICODE_THRAPS,						true,				 NULL },
		{ "thras",					5,			false,		_MC_ICODE_THRAS,						true,				 NULL },
		{ "thraf",					5,			false,		_MC_ICODE_THRAF,						true,				 NULL },
		{ "thrst",					5,			false,		_MC_ICODE_THRST,						true,				 NULL },
		{ "thrsp",					5,			false,		_MC_ICODE_THRSP,						true,				 NULL },
		{ "thrxt",					5,			false,		_MC_ICODE_THRXT,						true,				 NULL },
		{ "thrxp",					5,			false,		_MC_ICODE_THRXP,						true,				 NULL },
		{ "thrxr",					5,			false,		_MC_ICODE_THRXR,						true,				 NULL },
		{ "thrxrs",					6,			false,		_MC_ICODE_THRXRS,						true,				 NULL },
		{ "thrxj",					5,			false,		_MC_ICODE_THRXJ,						true,				 NULL },
		{ "screate",				7,			false,		_MC_ICODE_SCREATE,						true,				 NULL },
		{ "slock",					5,			false,		_MC_ICODE_SLOCK,						true,				 NULL },
		{ "sunlock",				7,			false,		_MC_ICODE_SUNLOCK,						true,				 NULL },
		{ "sdelete",				7,			false,		_MC_ICODE_SDELETE,						true,				 NULL },
		{ "predicate",				9,			false,		_MC_ICODE_PREDICATE,					true,				 NULL },
		{ "copypred",				8,			false,		_MC_ICODE_COPYPRED,						true,				 NULL },

		{ 0,						0,			0,			0,										0,					0 }
	};
