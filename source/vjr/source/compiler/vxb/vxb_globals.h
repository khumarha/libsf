//////////
//
// /libsf/source/vjr/source/compiler/vxb/vxb_globals.h
//
//////
//    _     _ _     _____ _____ 
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____  
//   \ \   / /  ___| __|  _ \ 
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/ 
//      \_/  |_|  |_|  |_|
//
//////
// Version 0.54
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//	   Jun.29.2014
//////
// Change log:
//	   Jun.29.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//   ___      ___   ___  ___    _______
//  |"  \    /"  | |"  \/"  |  |   _  "\
//   \   \  //  /   \   \  /   (. |_)  :)
//    \\  \/. ./     \\  \/    |:     \/
//     \.    //      /\.  \    (|  _  \\
//      \\   /      /  \   \   |: |_)  :)
//       \__/      |___/\___|  (_______/
//     Visual FreePro, Jr. XBase Compiler
//
//////////









//////////
//
//	CREATE TABLE somename.dbf
//		[ALIAS whatever]
//		[IN [cAlias|nWorkArea]]
//		[SHARED|EXLCUSIVE]
//		[CLOSE]
//		[IGNORESAFETY]
//		[FROM cAlias|cPathname]
//		[ATOP cPathname]
//
//		ALIAS whatever			-- Allow the created table to have whatever alias you desire at creation
//		IN cAlias|nWorkArea		-- Allow it to be created at a specific place
//		SHARED|EXCLUSIVE		-- Allow it to be opened with explicit SHARED or EXCLUSIVE access
//		CLOSE					-- Allow it to be created, but not opened for use.
//		IGNORESAFETY			-- Ignore the SET SAFETY setting, and always create the table
//		FROM cAlias|cPathname	-- Allow the structure definition to come from another alias, or pathname
//		ATOP cPathname			-- Creates a logical table that does not exist as a .DBF on disk, but rather operates atop the SDF data on disk as though it were a DBF, allowing for all normal disk operations without having to bring it in to the DBF, then writing it back out. Useful for parsing text files, or old style Hollerith-format data files with control and data portions in the same file, because multiple tables can be used which sit ATOP the same data set (same cPathname on disk), allowing multi-access to a single data source.
//
//////
//
// New commands:
//			REDIMENSION laArray[x,y,z]		-- Resizes array and keeps [2,2] data in those positions when resizing to [3,3] for example, can also be used as DIMENSION laArray[x,y,z] RESIZE
//			ON ANYDIALOG ...				-- Whenever any dialog window is about to be displayed to the user, it allows for interception, redirection, automation, recording of system commands, etc.
//			ON ANYDIALOGRESPONSE ...		-- Whenever a user chooses an option on a dialog, this is called
//			ON WARNING ...
//
//////
//
// New functions:
//			ABOVE			(xVal, xTest)
//			BELOW			(xVal, xTest)
//			OUTSIDE			(xVal, xMin, xMax)
//			FOUNDIN			(cHaystack, cNeedle1, cNeedle2, cNeedle3...)[.ignorecase]
//			ALINESTOSTR		(laArray)
//			ALINESTOFILE	(laArray, lcPathname)
//
//		BROWSE FOR ABOVE(nValue, nAmount)
//		Equivalent:		BROWSE FOR nValue >= nAmount
//
//		BROWSE FOR BELOW(nValue, nAmount)
//		Equivalent:		BROWSE FOR nValue <= nAmount
//
//		BROWSE FOR OUTSIDE(nVal, 10, 100)
//		Equivalent:		BROWSE FOR nValue < 10 AND nValue > 100
//		Equivalent:		BROWSE FOR NOT BETWEEN(nValue, 10, 100)
//
//		BROWSE FOR FOUNDIN(cName, "Fred", "Ethyl").ignorecase
//		Equivalent:		BROWSE FOR LOWER("Fred") $ LOWER(cName) OR LOWER("Ethyl") $ LOWER(cName)
//
//		BROWSE FOR FOUNDIN(cName, "Fred", "Ethyl").and.ignorecase
//		Equivalent:		BROWSE FOR LOWER("Fred") $ LOWER(cName) AND LOWER("Ethyl") $ LOWER(cName)
//
//////
//
// "Vector" functions:
//			VABOVE		(xMax, xTest1, xTest2, xTest3...)[.and][.ignorecase]
//			VBELOW		(xMin, xTest1, xTest2, xTest3...)[.and][.ignorecase]
//			VBETWEEN	(xMin, xMax, xTest1, xTest2, xTest3...)[.and][.ignorecase]
//			VOUTSIDE	(xMin, xMax, xTest1, xTest2, xTest3...)[.and][.ignorecase]
//			VFOUNDIN	(cNeedle, cHaystack1, cHaystack2, cHaystack3...)[.and][.ignorecase]
//
//		BROWSE FOR VABOVE(1000, nVal1, nVal2, nVal3)
//		Equivalent:		BROWSE FOR nVal1 >= 1000 OR nVal2 >= 1000 OR nVal3 >= 1000
//
//		BROWSE FOR VABOVE(1000, nVal1, nVal2, nVal3).and
//		Equivalent:		BROWSE FOR nVal1 >= 1000 AND nVal2 >= 1000 AND nVal3 >= 1000
//	
//		BROWSE FOR VBELOW(50, nVal1, nVal2, nVal3)
//		Equivalent:		BROWSE FOR nVal1 <= 50 OR nVal2 <= 50 OR nVal3 <= 50
//	
//		BROWSE FOR VBETWEEN(50, 1000, nVal1, nVal2, nVal3)
//		Equivalent:		BROWSE FOR BETWEEN(nVal1, 50, 1000) OR BETWEEN(nVal2, 50, 1000) OR BETWEEN(nVal3, 50, 1000)
//	
//		BROWSE FOR VOUTSIDE(50, 1000, nVal1, nVal2, nVal3)
//		Equivalent:		BROWSE FOR NOT BETWEEN(nVal1, 50, 1000) OR NOT BETWEEN(nVal2, 50, 1000) OR NOT BETWEEN(nVal3, 50, 1000)
//	
//		BROWSE FOR VFOUNDIN(cNeedle, cHay1, cHay2, cHay3).ignorecase
//		Equivalent:		BROWSE FOR LOWER(cNeedle) $ LOWER(cHay1) OR LOWER(cNeedle) $ LOWER(cHay2) OR LOWER(cNeedle) $ LOWER(cHay3)...
//	
//		BROWSE FOR VFOUNDIN(cNeedle, cHay1, cHay2, cHay3).and.ignorecase
//		Equivalent:		BROWSE FOR LOWER(cNeedle) $ LOWER(cHay1) AND LOWER(cNeedle) $ LOWER(cHay2) AND LOWER(cNeedle) $ LOWER(cHay3)...
//	
//////////



//////////
// Syntax highlight colors for VXB
//////
	SBgra			colorSynHi_dotVariable				= { rgba(0, 128, 192, 255) };			// Cyanish
	SBgra			colorSynHi_exclamationMarkVariable	= { rgba(0, 128, 192, 255) };			// Cyanish
	SBgra			colorSynHi_flag						= { rgba(164, 128, 0, 255) };			// Golden




//////////
// Keywords for VXB
//////
	SAsciiCompSearcher	cgcKeywordsVxb[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		category			syntax highlight color		syntax highlight bold		onFind()	compilerDictionaryLookup()
		// Reinterpret previously parsed forms to others
		{ cgc_asterisk,				1,			true,		_ICODE_COMMENT,							true,				_ICAT_GENERIC,		&colorSynHi_comment1,		false,						null0,		null0 },
		{ cgc_ampersandComment,		2,			false,		_ICODE_LINE_COMMENT,					false,				_ICAT_GENERIC,		&colorSynHi_comment2,		false,						null0,		null0 },
		{ cgc_dollarSign,			1,			false,		_ICODE_FOUND_IN,						false,				_ICAT_GENERIC,		&colorSynHi_operator,		false,						null0,		null0 },
		{ cgc_notFoundIn,			2,			false,		_ICODE_NOT_FOUND_IN,					false,				_ICAT_GENERIC,		&colorSynHi_operator,		true,						null0,		null0 },
		{ cgc_notEqual1,			1,			false,		_ICODE_NOT_EQUAL,						false,				_ICAT_GENERIC,		&colorSynHi_operator,		false,						null0,		null0 },
		{ cgc_notEqual2,			2,			false,		_ICODE_NOT_EQUAL,						false,				_ICAT_GENERIC,		&colorSynHi_operator,		false,						null0,		null0 },

		// Functions
		{ cgc_abs,					3,			false,		_ICODE_ABS,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aclass,				6,			false,		_ICODE_ACLASS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_acopy,				5,			false,		_ICODE_ACOPY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_acos,					4,			false,		_ICODE_ACOS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adatabases,			10,			false,		_ICODE_ADATABASES,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adbobjects,			10,			false,		_ICODE_ADBOBJECTS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_addbs,				5,			false,		_ICODE_ADDBS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_addobject,			9,			false,		_ICODE_ADDOBJECT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_addproperty,			11,			false,		_ICODE_ADDPROPERTY,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adel,					4,			false,		_ICODE_ADEL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adir,					4,			false,		_ICODE_ADIR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adlls,				5,			false,		_ICODE_ADLLS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_adockstate,			10,			false,		_ICODE_ADOCKSTATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aelement,				8,			false,		_ICODE_AELEMENT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aerror,				6,			false,		_ICODE_AERROR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aevents,				7,			false,		_ICODE_AEVENTS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_afields,				7,			false,		_ICODE_AFIELDS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_afont,				5,			false,		_ICODE_AFONT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_again,				5,			false,		_ICODE_AGAIN,							false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_agetclass,			9,			false,		_ICODE_AGETCLASS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_agetfileversion,		15,			false,		_ICODE_AGETFILEVERSION,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ainstance,			9,			false,		_ICODE_AINSTANCE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ains,					4,			false,		_ICODE_AINS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_alanguage,			9,			false,		_ICODE_ALANGUAGE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_alen,					4,			false,		_ICODE_ALEN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_alias,				5,			false,		_ICODE_ALIAS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_alines,				6,			false,		_ICODE_ALINES,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_alltrim,				7,			false,		_ICODE_ALLTRIM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_amembers,				8,			false,		_ICODE_AMEMBERS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_amouseobj,			9,			false,		_ICODE_AMOUSEOBJ,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_anetresources,		13,			false,		_ICODE_ANETRESOURCES,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aprinters,			9,			false,		_ICODE_APRINTERS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aprocinfo,			9,			false,		_ICODE_APROCINFO,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ascan,				5,			false,		_ICODE_ASCAN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asc,					3,			false,		_ICODE_ASC,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ascending,			9,			false,		_ICODE_ASCENDING,						false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_aselobj,				7,			false,		_ICODE_ASELOBJ,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asessions,			9,			false,		_ICODE_ASESSIONS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asin,					4,			false,		_ICODE_ASIN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asort,				5,			false,		_ICODE_ASORT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asqlhandles,			11,			false,		_ICODE_ASQLHANDLES,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_astackinfo,			10,			false,		_ICODE_ASTACKINFO,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_asubscript,			10,			false,		_ICODE_ASUBSCRIPT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_at_c,					4,			false,		_ICODE_AT_C,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_at,					2,			false,		_ICODE_AT,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ataginfo,				8,			false,		_ICODE_ATAGINFO,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atan,					4,			false,		_ICODE_ATAN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atcline,				7,			false,		_ICODE_ATCLINE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atcc,					4,			false,		_ICODE_ATCC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atc,					3,			false,		_ICODE_ATC,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atline,				6,			false,		_ICODE_ATLINE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_atn2,					4,			false,		_ICODE_ATN2,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_aused,				5,			false,		_ICODE_AUSED,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_avcxclasses,			11,			false,		_ICODE_AVCXCLASSES,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_barprompt,			9,			false,		_ICODE_BARPROMPT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_barcount,				8,			false,		_ICODE_BARCOUNT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bar,					3,			false,		_ICODE_BAR,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_between,				7,			false,		_ICODE_BETWEEN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bindevent,			9,			false,		_ICODE_BINDEVENT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bintoc,				6,			false,		_ICODE_BINTOC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitand,				6,			false,		_ICODE_BITAND,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitclear,				8,			false,		_ICODE_BITCLEAR,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitlshift,			9,			false,		_ICODE_BITLSHIFT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitnot,				6,			false,		_ICODE_BITNOT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitor,				5,			false,		_ICODE_BITOR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitrshift,			9,			false,		_ICODE_BITRSHIFT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitset,				6,			false,		_ICODE_BITSET,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bittest,				7,			false,		_ICODE_BITTEST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bitxor,				6,			false,		_ICODE_BITXOR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_bof,					3,			false,		_ICODE_BOF,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_candidate,			9,			false,		_ICODE_CANDIDATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_capslock,				8,			false,		_ICODE_CAPSLOCK,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cast,					4,			false,		_ICODE_CAST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cdow,					4,			false,		_ICODE_CDOW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cdx,					3,			false,		_ICODE_CDX,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ceiling,				7,			false,		_ICODE_CEILING,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_chr,					3,			false,		_ICODE_CHR,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_chrsaw,				6,			false,		_ICODE_CHRSAW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_chrtranc,				8,			false,		_ICODE_CHRTRANC,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_chrtran,				7,			false,		_ICODE_CHRTRAN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_clearresultset,		14,			false,		_ICODE_CLEARRESULTSET,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cmonth,				6,			false,		_ICODE_CMONTH,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cntbar,				6,			false,		_ICODE_CNTBAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cntpad,				6,			false,		_ICODE_CNTPAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_col,					3,			false,		_ICODE_COL,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_comarray,				8,			false,		_ICODE_COMARRAY,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_comclassinfo,			12,			false,		_ICODE_COMCLASSINFO,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_command,				7,			false,		_ICODE_COMMAND,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_compobj,				7,			false,		_ICODE_COMPOBJ,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_comprop,				7,			false,		_ICODE_COMPROP,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_comreturnerror,		14,			false,		_ICODE_COMRETURNERROR,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_coms,					4,			false,		_ICODE_COMS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_connstring,			10,			false,		_ICODE_CONNSTRING,						false,				_ICAT_OPTION,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cos,					3,			false,		_ICODE_COS,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cpconvert,			9,			false,		_ICODE_CPCONVERT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cpcurrent,			9,			false,		_ICODE_CPCURRENT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cpdbf,				5,			false,		_ICODE_CPDBF,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_createbinary,			12,			false,		_ICODE_CREATEBINARY,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_createobject,			12,			false,		_ICODE_CREATEOBJECT,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_createobjectex,		14,			false,		_ICODE_CREATEOBJECTEX,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_createoffline,		13,			false,		_ICODE_CREATEOFFLINE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ctobin,				6,			false,		_ICODE_CTOBIN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ctod,					4,			false,		_ICODE_CTOD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ctot,					4,			false,		_ICODE_CTOT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_curdir,				6,			false,		_ICODE_CURDIR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cursorgetprop,		13,			false,		_ICODE_CURSORGETPROP,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cursorsetprop,		13,			false,		_ICODE_CURSORSETPROP,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_cursortoxml,			11,			false,		_ICODE_CURSORTOXML,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_curval,				6,			false,		_ICODE_CURVAL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_datetime,				8,			false,		_ICODE_DATETIME,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_date,					4,			false,		_ICODE_DATE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_day,					3,			false,		_ICODE_DAY,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dbc,					3,			false,		_ICODE_DBC,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dbf,					3,			false,		_ICODE_DBF,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dbgetprop,			9,			false,		_ICODE_DBGETPROP,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dbsetprop,			9,			false,		_ICODE_DBSETPROP,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dbused,				6,			false,		_ICODE_DBUSED,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeaborttrans,		13,			false,		_ICODE_DDEABORTTRANS,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeadvise,			9,			false,		_ICODE_DDEADVISE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeenabled,			10,			false,		_ICODE_DDEENABLED,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeexecute,			10,			false,		_ICODE_DDEEXECUTE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeinitiate,			11,			false,		_ICODE_DDEINITIATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddelasterror,			12,			false,		_ICODE_DDELASTERROR,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddepoke,				7,			false,		_ICODE_DDEPOKE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dderequest,			10,			false,		_ICODE_DDEREQUEST,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddes,					4,			false,		_ICODE_DDES,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddesetoption,			12,			false,		_ICODE_DDESETOPTION,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddesetservice,		13,			false,		_ICODE_DDESETSERVICE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddesettopic,			11,			false,		_ICODE_DDESETTOPIC,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ddeterminate,			12,			false,		_ICODE_DDETERMINATE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_defaultext,			10,			false,		_ICODE_DEFAULTEXT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_deleted,				7,			false,		_ICODE_DELETED,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_descending,			10,			false,		_ICODE_DESCENDING,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_difference,			10,			false,		_ICODE_DIFFERENCE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_directory,			9,			false,		_ICODE_DIRECTORY,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_diskspace,			9,			false,		_ICODE_DISKSPACE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_displaypath,			11,			false,		_ICODE_DISPLAYPATH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dmy,					3,			false,		_ICODE_DMY,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dodefault,			9,			false,		_ICODE_DODEFAULT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dow,					3,			false,		_ICODE_DOW,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_drivetype,			9,			false,		_ICODE_DRIVETYPE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dropoffline,			11,			false,		_ICODE_DROPOFFLINE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dtoc,					4,			false,		_ICODE_DTOC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dtor,					4,			false,		_ICODE_DTOR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dtos,					4,			false,		_ICODE_DTOS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_dtot,					4,			false,		_ICODE_DTOT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_editsource,			10,			false,		_ICODE_EDITSOURCE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_empty,				5,			false,		_ICODE_EMPTY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_eof,					3,			false,		_ICODE_EOF,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_error,				5,			false,		_ICODE_ERROR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_evaluate,				8,			false,		_ICODE_EVALUATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_eventhandler,			12,			false,		_ICODE_EVENTHANDLER,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_evl,					3,			false,		_ICODE_EVL,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_execscript,			10,			false,		_ICODE_EXECSCRIPT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_exp,					3,			false,		_ICODE_EXP,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fchsize,				7,			false,		_ICODE_FCHSIZE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fclose,				6,			false,		_ICODE_FCLOSE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fcount,				6,			false,		_ICODE_FCOUNT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fcreate,				7,			false,		_ICODE_FCREATE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fdate,				5,			false,		_ICODE_FDATE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_feof,					4,			false,		_ICODE_FEOF,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ferror,				6,			false,		_ICODE_FERROR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fflush,				6,			false,		_ICODE_FFLUSH,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fgets,				5,			false,		_ICODE_FGETS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_field,				5,			false,		_ICODE_FIELD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_filetostr,			9,			false,		_ICODE_FILETOSTR,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_file,					4,			false,		_ICODE_FILE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_filter,				6,			false,		_ICODE_FILTER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fklabel,				7,			false,		_ICODE_FKLABEL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fkmax,				5,			false,		_ICODE_FKMAX,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fldlist,				7,			false,		_ICODE_FLDLIST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_flock,				5,			false,		_ICODE_FLOCK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_floor,				5,			false,		_ICODE_FLOOR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fontmetric,			10,			false,		_ICODE_FONTMETRIC,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fopen,				5,			false,		_ICODE_FOPEN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
//		{ cgc_for,					3,			false,		_ICODE_FOR,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_forceext,				8,			false,		_ICODE_FORCEEXT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_forcepath,			9,			false,		_ICODE_FORCEPATH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_found,				5,			false,		_ICODE_FOUND,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fputs,				5,			false,		_ICODE_FPUTS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fread,				5,			false,		_ICODE_FREAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fseek,				5,			false,		_ICODE_FSEEK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fsize,				5,			false,		_ICODE_FSIZE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ftime,				5,			false,		_ICODE_FTIME,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fullpath,				8,			false,		_ICODE_FULLPATH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fv,					2,			false,		_ICODE_FV,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_fwrite,				6,			false,		_ICODE_FWRITE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getautoincvalue,		15,			false,		_ICODE_GETAUTOINCVALUE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getbar,				6,			false,		_ICODE_GETBAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getcolor,				8,			false,		_ICODE_GETCOLOR,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getcp,				5,			false,		_ICODE_GETCP,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getcursoradapter,		16,			false,		_ICODE_GETCURSORADAPTER,				false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getdir,				6,			false,		_ICODE_GETDIR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getenv,				6,			false,		_ICODE_GETENV,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getfile,				7,			false,		_ICODE_GETFILE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getfldstate,			11,			false,		_ICODE_GETFLDSTATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getfont,				7,			false,		_ICODE_GETFONT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getinterface,			12,			false,		_ICODE_GETINTERFACE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getnextmodified,		15,			false,		_ICODE_GETNEXTMODIFIED,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getobject,			9,			false,		_ICODE_GETOBJECT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getpad,				6,			false,		_ICODE_GETPAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getpem,				6,			false,		_ICODE_GETPEM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getpict,				7,			false,		_ICODE_GETPICT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getprinter,			10,			false,		_ICODE_GETPRINTER,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getresultset,			12,			false,		_ICODE_GETRESULTSET,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getwordcount,			12,			false,		_ICODE_GETWORDCOUNT,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_getwordnum,			10,			false,		_ICODE_GETWORDNUM,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_gomonth,				7,			false,		_ICODE_GOMONTH,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_header,				6,			false,		_ICODE_HEADER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_home,					4,			false,		_ICODE_HOME,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_hour,					4,			false,		_ICODE_HOUR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_icase,				5,			false,		_ICODE_ICASE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_idxcollate,			10,			false,		_ICODE_IDXCOLLATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_iif,					3,			false,		_ICODE_IIF,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_imestatus,			9,			false,		_ICODE_IMESTATUS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_in,					2,			false,		_ICODE_IN,								false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_indbc,				5,			false,		_ICODE_INDBC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_indexseek,			9,			false,		_ICODE_INDEXSEEK,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_inkey,				5,			false,		_ICODE_INKEY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_inlist,				6,			false,		_ICODE_INLIST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_inputbox,				8,			false,		_ICODE_INPUTBOX,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_insmode,				7,			false,		_ICODE_INSMODE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_int,					3,			false,		_ICODE_INT,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isalpha,				7,			false,		_ICODE_ISALPHA,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isblank,				7,			false,		_ICODE_ISBLANK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_iscolor,				7,			false,		_ICODE_ISCOLOR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isdigit,				7,			false,		_ICODE_ISDIGIT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isexclusive,			11,			false,		_ICODE_ISEXCLUSIVE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isflocked,			9,			false,		_ICODE_ISFLOCKED,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isleadbyte,			10,			false,		_ICODE_ISLEADBYTE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_islower,				7,			false,		_ICODE_ISLOWER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ismemofetched,		13,			false,		_ICODE_ISMEMOFETCHED,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ismouse,				7,			false,		_ICODE_ISMOUSE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isnull,				6,			false,		_ICODE_ISNULL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ispen,				5,			false,		_ICODE_ISPEN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isreadonly,			10,			false,		_ICODE_ISREADONLY,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isrlocked,			9,			false,		_ICODE_ISRLOCKED,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_istransactable,		14,			false,		_ICODE_ISTRANSACTABLE,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_isupper,				7,			false,		_ICODE_ISUPPER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_justdrive,			9,			false,		_ICODE_JUSTDRIVE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_justext,				7,			false,		_ICODE_JUSTEXT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_justfname,			9,			false,		_ICODE_JUSTFNAME,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_justpath,				8,			false,		_ICODE_JUSTPATH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_juststem,				8,			false,		_ICODE_JUSTSTEM,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_keymatch,				8,			false,		_ICODE_KEYMATCH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_key,					3,			false,		_ICODE_KEY,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lastkey,				7,			false,		_ICODE_LASTKEY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_leftc,				5,			false,		_ICODE_LEFTC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_left,					4,			false,		_ICODE_LEFT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lenc,					4,			false,		_ICODE_LENC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_len,					3,			false,		_ICODE_LEN,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_likec,				5,			false,		_ICODE_LIKEC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_like,					4,			false,		_ICODE_LIKE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lineno,				6,			false,		_ICODE_LINENO,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_loadpicture,			11,			false,		_ICODE_LOADPICTURE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_locfile,				7,			false,		_ICODE_LOCFILE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lock,					4,			false,		_ICODE_LOCK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_log10,				5,			false,		_ICODE_LOG10,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_log,					3,			false,		_ICODE_LOG,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lookup,				6,			false,		_ICODE_LOOKUP,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lower,				5,			false,		_ICODE_LOWER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ltrim,				5,			false,		_ICODE_LTRIM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lupdate,				7,			false,		_ICODE_LUPDATE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_maketransactable,		16,			false,		_ICODE_MAKETRANSACTABLE,				false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_max,					3,			false,		_ICODE_MAX,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mcol,					4,			false,		_ICODE_MCOL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mdown,				5,			false,		_ICODE_MDOWN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mdx,					3,			false,		_ICODE_MDX,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mdy,					3,			false,		_ICODE_MDY,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_memlines,				8,			false,		_ICODE_MEMLINES,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_memory,				6,			false,		_ICODE_MEMORY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_menu,					4,			false,		_ICODE_MENU,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_messagebox,			10,			false,		_ICODE_MESSAGEBOX,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_message,				7,			false,		_ICODE_MESSAGE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_minute,				6,			false,		_ICODE_MINUTE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_min,					3,			false,		_ICODE_MIN,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mline,				5,			false,		_ICODE_MLINE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mod,					3,			false,		_ICODE_MOD,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_month,				5,			false,		_ICODE_MONTH,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mrkbar,				6,			false,		_ICODE_MRKBAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mrkpad,				6,			false,		_ICODE_MRKPAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mrow,					4,			false,		_ICODE_MROW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mton,					4,			false,		_ICODE_MTON,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mwindow,				7,			false,		_ICODE_MWINDOW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ndx,					3,			false,		_ICODE_NDX,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_newobject,			9,			false,		_ICODE_NEWOBJECT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_nodata,				6,			false,		_ICODE_NODATA,							false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_norequery,			9,			false,		_ICODE_NOREQUERY,						false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_normalize,			9,			false,		_ICODE_NORMALIZE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_noupdate,				8,			false,		_ICODE_NOUPDATE,						false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_ntom,					4,			false,		_ICODE_NTOM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_numlock,				7,			false,		_ICODE_NUMLOCK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_nvl,					3,			false,		_ICODE_NVL,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_objnum,				6,			false,		_ICODE_OBJNUM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_objtoclient,			11,			false,		_ICODE_OBJTOCLIENT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_objvar,				6,			false,		_ICODE_OBJVAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_occursc,				7,			false,		_ICODE_OCCURSC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_occurs,				6,			false,		_ICODE_OCCURS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_oemtoansi,			9,			false,		_ICODE_OEMTOANSI,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_oldval,				6,			false,		_ICODE_OLDVAL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_on,					2,			false,		_ICODE_ON,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_order,				5,			false,		_ICODE_ORDER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_os,					2,			false,		_ICODE_OS,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_overview,				8,			false,		_ICODE_OVERVIEW,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_padc,					4,			false,		_ICODE_PADC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_padl,					4,			false,		_ICODE_PADL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_padr,					4,			false,		_ICODE_PADR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pad,					3,			false,		_ICODE_PAD,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_parameters,			10,			false,		_ICODE_PARAMETERS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_payment,				7,			false,		_ICODE_PAYMENT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pcol,					4,			false,		_ICODE_PCOL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pcount,				6,			false,		_ICODE_PCOUNT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pemstatus,			9,			false,		_ICODE_PEMSTATUS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pi,					2,			false,		_ICODE_PI,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_popup,				5,			false,		_ICODE_POPUP,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_primary,				7,			false,		_ICODE_PRIMARY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_printstatus,			11,			false,		_ICODE_PRINTSTATUS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_prmbar,				6,			false,		_ICODE_PRMBAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_prmpad,				6,			false,		_ICODE_PRMPAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_program,				7,			false,		_ICODE_PROGRAM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_prompt,				6,			false,		_ICODE_PROMPT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_proper,				6,			false,		_ICODE_PROPER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_prow,					4,			false,		_ICODE_PROW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_prtinfo,				7,			false,		_ICODE_PRTINFO,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_putfile,				7,			false,		_ICODE_PUTFILE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_pv,					2,			false,		_ICODE_PV,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_quarter,				7,			false,		_ICODE_QUARTER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_raiseevent,			10,			false,		_ICODE_RAISEEVENT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rand,					4,			false,		_ICODE_RAND,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ratc,					4,			false,		_ICODE_RATC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rat,					3,			false,		_ICODE_RAT,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ratline,				7,			false,		_ICODE_RATLINE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rdlevel,				7,			false,		_ICODE_RDLEVEL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_readkey,				7,			false,		_ICODE_READKEY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_reccount,				8,			false,		_ICODE_RECCOUNT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_recno,				5,			false,		_ICODE_RECNO,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_recsize,				7,			false,		_ICODE_RECSIZE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_refresh,				7,			false,		_ICODE_REFRESH,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_relation,				8,			false,		_ICODE_RELATION,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_replicate,			9,			false,		_ICODE_REPLICATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_requery,				7,			false,		_ICODE_REQUERY,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rgb,					3,			false,		_ICODE_RGB,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rgbscheme,			9,			false,		_ICODE_RGBSCHEME,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_right,				5,			false,		_ICODE_RIGHT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rightc,				6,			false,		_ICODE_RIGHTC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rlock,				5,			false,		_ICODE_RLOCK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_round,				5,			false,		_ICODE_ROUND,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_row,					3,			false,		_ICODE_ROW,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rtod,					4,			false,		_ICODE_RTOD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_rtrim,				5,			false,		_ICODE_RTRIM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_savepicture,			11,			false,		_ICODE_SAVEPICTURE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_scheme,				6,			false,		_ICODE_SCHEME,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_scols,				5,			false,		_ICODE_SCOLS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_seconds,				7,			false,		_ICODE_SECONDS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sec,					3,			false,		_ICODE_SEC,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_seek,					4,			false,		_ICODE_SEEK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_select,				6,			false,		_ICODE_SELECT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_set,					3,			false,		_ICODE_SET,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_setfldstate,			11,			false,		_ICODE_SETFLDSTATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_setresultset,			12,			false,		_ICODE_SETRESULTSET,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_shared,				6,			false,		_ICODE_SHARED,							false,				_ICAT_OPTION,		&colorSynHi_flag,			false,						null0,		null0 },
		{ cgc_sign,					4,			false,		_ICODE_SIGN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sin,					3,			false,		_ICODE_SIN,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_skpbar,				6,			false,		_ICODE_SKPBAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_skppad,				6,			false,		_ICODE_SKPPAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_soundex,				7,			false,		_ICODE_SOUNDEX,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_space,				5,			false,		_ICODE_SPACE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlcancel,			9,			false,		_ICODE_SQLCANCEL,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlcolumns,			10,			false,		_ICODE_SQLCOLUMNS,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlcommit,			9,			false,		_ICODE_SQLCOMMIT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlconnect,			10,			false,		_ICODE_SQLCONNECT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqldisconnect,		13,			false,		_ICODE_SQLDISCONNECT,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlexec,				7,			false,		_ICODE_SQLEXEC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlgetprop,			10,			false,		_ICODE_SQLGETPROP,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlidledisconnect,	17,			false,		_ICODE_SQLIDLEDISCONNECT,				false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlmoreresults,		14,			false,		_ICODE_SQLMORERESULTS,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlprepare,			10,			false,		_ICODE_SQLPREPARE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlrollback,			11,			false,		_ICODE_SQLROLLBACK,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlsetprop,			10,			false,		_ICODE_SQLSETPROP,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqlstringconnect,		16,			false,		_ICODE_SQLSTRINGCONNECT,				false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqltables,			9,			false,		_ICODE_SQLTABLES,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sqrt,					4,			false,		_ICODE_SQRT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_srows,				5,			false,		_ICODE_SROWS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_strconv,				7,			false,		_ICODE_STRCONV,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_strextract,			10,			false,		_ICODE_STREXTRACT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_strtofile,			9,			false,		_ICODE_STRTOFILE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_strtranc,				8,			false,		_ICODE_STRTRANC,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_strtran,				7,			false,		_ICODE_STRTRAN,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_str,					3,			false,		_ICODE_STR,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_stuffc,				6,			false,		_ICODE_STUFFC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_stuff,				5,			false,		_ICODE_STUFF,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_substrc,				7,			false,		_ICODE_SUBSTRC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_substr,				6,			false,		_ICODE_SUBSTR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sysmetric,			9,			false,		_ICODE_SYSMETRIC,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sys,					3,			false,		_ICODE_SYS,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tablerevert,			11,			false,		_ICODE_TABLEREVERT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tableupdate,			11,			false,		_ICODE_TABLEUPDATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tag,					3,			false,		_ICODE_TAG,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tagcount,				8,			false,		_ICODE_TAGCOUNT,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tagno,				5,			false,		_ICODE_TAGNO,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_tan,					3,			false,		_ICODE_TAN,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_target,				6,			false,		_ICODE_TARGET,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_textmerge,			9,			false,		_ICODE_TEXTMERGE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_time,					4,			false,		_ICODE_TIME,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_transform,			9,			false,		_ICODE_TRANSFORM,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_trim,					4,			false,		_ICODE_TRIM,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ttoc,					4,			false,		_ICODE_TTOC,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_ttod,					4,			false,		_ICODE_TTOD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_txnlevel,				8,			false,		_ICODE_TXNLEVEL,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_txtwidth,				8,			false,		_ICODE_TXTWIDTH,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_type,					4,			false,		_ICODE_TYPE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_unbindevents,			12,			false,		_ICODE_UNBINDEVENTS,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_unique,				6,			false,		_ICODE_UNIQUE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_updated,				7,			false,		_ICODE_UPDATED,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_upper,				5,			false,		_ICODE_UPPER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_used,					4,			false,		_ICODE_USED,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_val,					3,			false,		_ICODE_VAL,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_varread,				7,			false,		_ICODE_VARREAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_vartype,				7,			false,		_ICODE_VARTYPE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_version,				7,			false,		_ICODE_VERSION,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wborder,				7,			false,		_ICODE_WBORDER,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wchild,				6,			false,		_ICODE_WCHILD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wcols,				5,			false,		_ICODE_WCOLS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wdockable,			9,			false,		_ICODE_WDOCKABLE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_week,					4,			false,		_ICODE_WEEK,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wexist,				6,			false,		_ICODE_WEXIST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wfont,				5,			false,		_ICODE_WFONT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wlast,				5,			false,		_ICODE_WLAST,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wlcol,				5,			false,		_ICODE_WLCOL,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wlrow,				5,			false,		_ICODE_WLROW,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wmaximum,				8,			false,		_ICODE_WMAXIMUM,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wminimum,				8,			false,		_ICODE_WMINIMUM,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wontop,				6,			false,		_ICODE_WONTOP,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_woutput,				7,			false,		_ICODE_WOUTPUT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wparent,				7,			false,		_ICODE_WPARENT,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wread,				5,			false,		_ICODE_WREAD,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wrows,				5,			false,		_ICODE_WROWS,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wtitle,				6,			false,		_ICODE_WTITLE,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_wvisible,				8,			false,		_ICODE_WVISIBLE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_xmltocursor,			11,			false,		_ICODE_XMLTOCURSOR,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_xmlupdategram,		13,			false,		_ICODE_XMLUPDATEGRAM,					false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_year,					4,			false,		_ICODE_YEAR,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },

// Temporarily added until the processing engine is completed
		{ cgc_concatenate,			11,			false,		_ICODE_CONCATENATE,						false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_add,					3,			false,		_ICODE_ADD,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_sub,					3,			false,		_ICODE_SUB,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_mul,					3,			false,		_ICODE_MUL,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_div,					3,			false,		_ICODE_DIV,								false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },

		// Commands
		{ cgc_activate,				8,			false,		_ICODE_ACTIVATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
//		{ cgc_add,					3,			false,		_ICODE_ADD,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_alter,				5,			false,		_ICODE_ALTER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_alternate,			9,			false,		_ICODE_ALTERNATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_ansi,					4,			false,		_ICODE_ANSI,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_app,					3,			false,		_ICODE_APP,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_append,				6,			false,		_ICODE_APPEND,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_array,				5,			false,		_ICODE_ARRAY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_asserts,				7,			false,		_ICODE_ASSERTS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_assert,				6,			false,		_ICODE_ASSERT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_assist,				6,			false,		_ICODE_ASSIST,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_autoincerror,			12,			false,		_ICODE_AUTOINCERROR,					false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_autosave,				8,			false,		_ICODE_AUTOSAVE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_average,				7,			false,		_ICODE_AVERAGE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_bar,					3,			false,		_ICODE_BAR,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_begin,				5,			false,		_ICODE_BEGIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_bell,					4,			false,		_ICODE_BELL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_blank,				5,			false,		_ICODE_BLANK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_blocksize,			9,			false,		_ICODE_BLOCKSIZE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_border,				6,			false,		_ICODE_BORDER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_box,					3,			false,		_ICODE_BOX,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_browse,				6,			false,		_ICODE_BROWSE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_browseime,			9,			false,		_ICODE_BROWSEIME,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_brstatus,				8,			false,		_ICODE_BRSTATUS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_build,				5,			false,		_ICODE_BUILD,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_calculate,			9,			false,		_ICODE_CALCULATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_call,					4,			false,		_ICODE_CALL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cancel,				6,			false,		_ICODE_CANCEL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_carry,				5,			false,		_ICODE_CARRY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_case,					4,			false,		_ICODE_CASE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_catch,				5,			false,		_ICODE_CATCH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cd,					2,			false,		_ICODE_CD,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_century,				7,			false,		_ICODE_CENTURY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_change,				6,			false,		_ICODE_CHANGE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_chdir,				5,			false,		_ICODE_CHDIR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_class,				5,			false,		_ICODE_CLASS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_classlib,				8,			false,		_ICODE_CLASSLIB,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_clear,				5,			false,		_ICODE_CLEAR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_clears,				6,			false,		_ICODE_CLEARS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_clock,				5,			false,		_ICODE_CLOCK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_close,				5,			false,		_ICODE_CLOSE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_closes,				6,			false,		_ICODE_CLOSES,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_collate,				7,			false,		_ICODE_COLLATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_color,				5,			false,		_ICODE_COLOR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_compatible,			10,			false,		_ICODE_COMPATIBLE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_compile,				7,			false,		_ICODE_COMPILE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_confirm,				7,			false,		_ICODE_CONFIRM,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_connection,			10,			false,		_ICODE_CONNECTION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_connections,			11,			false,		_ICODE_CONNECTIONS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_console,				7,			false,		_ICODE_CONSOLE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_continue,				8,			false,		_ICODE_CONTINUE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_copy,					4,			false,		_ICODE_COPY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_count,				5,			false,		_ICODE_COUNT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_coverage,				8,			false,		_ICODE_COVERAGE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cpcompile,			9,			false,		_ICODE_CPCOMPILE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cpdialog,				8,			false,		_ICODE_CPDIALOG,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_create,				6,			false,		_ICODE_CREATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_currency,				8,			false,		_ICODE_CURRENCY,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_cursor,				6,			false,		_ICODE_CURSOR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_database,				8,			false,		_ICODE_DATABASE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_datasession,			11,			false,		_ICODE_DATASESSION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_date,					4,			false,		_ICODE_DATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_deactivate,			10,			false,		_ICODE_DEACTIVATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_debug,				5,			false,		_ICODE_DEBUG,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_debugout,				8,			false,		_ICODE_DEBUGOUT,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_decimals,				8,			false,		_ICODE_DECIMALS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_declare,				7,			false,		_ICODE_DECLARE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_default,				7,			false,		_ICODE_DEFAULT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_define,				6,			false,		_ICODE_DEFINE_PRAGMA,					false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_delete,				6,			false,		_ICODE_DELETE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_deleted,				7,			false,		_ICODE_DELETED,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_delimiters,			10,			false,		_ICODE_DELIMITERS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_development,			11,			false,		_ICODE_DEVELOPMENT,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_device,				6,			false,		_ICODE_DEVICE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dimension,			9,			false,		_ICODE_DIMENSION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dir,					3,			false,		_ICODE_DIR,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_directory,			9,			false,		_ICODE_DIRECTORY,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_display,				7,			false,		_ICODE_DISPLAY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dlls,					4,			false,		_ICODE_DLLS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dll,					3,			false,		_ICODE_DLL,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_do,					2,			false,		_ICODE_DOWHILE,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dock,					4,			false,		_ICODE_DOCK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_doevents,				8,			false,		_ICODE_DOEVENTS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_dohistory,			9,			false,		_ICODE_DOHISTORY,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_drop,					4,			false,		_ICODE_DROP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_each,					4,			false,		_ICODE_EACH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_echo,					4,			false,		_ICODE_ECHO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_edit,					4,			false,		_ICODE_EDIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_eject,				5,			false,		_ICODE_EJECT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_else,					4,			false,		_ICODE_ELSE,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_end,					3,			false,		_ICODE_END,								false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endcase,				7,			false,		_ICODE_ENDCASE,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_enddo,				5,			false,		_ICODE_ENDDO,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endfor,				6,			false,		_ICODE_ENDFOR,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endfunction,			11,			false,		_ICODE_ENDFUNCTION,						false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endif,				5,			false,		_ICODE_ENDIF,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
//		{ cgc_endprintjob,			11,			false,		_ICODE_ENDPRINTJOB,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endprocedure,			12,			false,		_ICODE_ENDPROCEDURE,					false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endscan,				7,			false,		_ICODE_ENDSCAN,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endtext,				7,			false,		_ICODE_ENDTEXT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_endwith,				7,			false,		_ICODE_ENDWITH,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_enginebehavior,		14,			false,		_ICODE_ENGINEBEHAVIOR,					false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_erase,				5,			false,		_ICODE_ERASE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_error,				5,			false,		_ICODE_ERROR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_escape,				6,			false,		_ICODE_ESCAPE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_eventlist,			9,			false,		_ICODE_EVENTLIST,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_events,				6,			false,		_ICODE_EVENTS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_eventtracking,		13,			false,		_ICODE_EVENTTRACKING,					false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_exact,				5,			false,		_ICODE_EXACT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_exclusive,			9,			false,		_ICODE_EXCLUSIVE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_exe,					3,			false,		_ICODE_EXE,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_exit,					4,			false,		_ICODE_EXIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_export,				6,			false,		_ICODE_EXPORT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_extended,				8,			false,		_ICODE_EXTENDED,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_external,				8,			false,		_ICODE_EXTERNAL,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fdow,					4,			false,		_ICODE_FDOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fields,				6,			false,		_ICODE_FIELDS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_files,				5,			false,		_ICODE_FILES,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_file,					4,			false,		_ICODE_FILE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fill,					4,			false,		_ICODE_FILL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_filter,				6,			false,		_ICODE_FILTER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_finally,				7,			false,		_ICODE_FINALLY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_find,					4,			false,		_ICODE_FIND,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fixed,				5,			false,		_ICODE_FIXED,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_flush,				5,			false,		_ICODE_FLUSH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_format,				6,			false,		_ICODE_FORMAT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_form,					4,			false,		_ICODE_FORM,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_for,					3,			false,		_ICODE_FOR,								false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_free,					4,			false,		_ICODE_FREE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_from,					4,			false,		_ICODE_FROM,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fullpath,				8,			false,		_ICODE_FULLPATH,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_function,				8,			false,		_ICODE_FUNCTION,						false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_fweek,				5,			false,		_ICODE_FWEEK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_gather,				6,			false,		_ICODE_GATHER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_general,				7,			false,		_ICODE_GENERAL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_getexpr,				7,			false,		_ICODE_GETEXPR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_gets,					4,			false,		_ICODE_GETS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_get,					3,			false,		_ICODE_GET,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_go,					2,			false,		_ICODE_GO,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_goto,					4,			false,		_ICODE_GOTO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_headings,				8,			false,		_ICODE_HEADINGS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_help,					4,			false,		_ICODE_HELP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_hide,					4,			false,		_ICODE_HIDE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_hours,				5,			false,		_ICODE_HOURS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_id,					2,			false,		_ICODE_ID,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_if,					2,			false,		_ICODE_IF,								false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_import,				6,			false,		_ICODE_IMPORT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_indexes,				7,			false,		_ICODE_INDEXES,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_index,				5,			false,		_ICODE_INDEX,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_input,				5,			false,		_ICODE_INPUT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_insert,				6,			false,		_ICODE_INSERT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_intensity,			9,			false,		_ICODE_INTENSITY,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_join,					4,			false,		_ICODE_JOIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_key,					3,			false,		_ICODE_KEY,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_keyboard,				8,			false,		_ICODE_KEYBOARD,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_keycomp,				7,			false,		_ICODE_KEYCOMP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_label,				5,			false,		_ICODE_LABEL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_lelse,				5,			false,		_ICODE_LELSE,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_library,				7,			false,		_ICODE_LIBRARY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_lif,					3,			false,		_ICODE_LIF,								false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_lists,				5,			false,		_ICODE_LISTS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_list,					4,			false,		_ICODE_LIST,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_load,					4,			false,		_ICODE_LOAD,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_local,				5,			false,		_ICODE_LOCAL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_locate,				6,			false,		_ICODE_LOCATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_lock,					4,			false,		_ICODE_LOCK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_logerrors,			9,			false,		_ICODE_LOGERRORS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_loop,					4,			false,		_ICODE_LOOP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_lparameters,			11,			false,		_ICODE_LPARAMETERS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_mackey,				6,			false,		_ICODE_MACKEY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_macros,				6,			false,		_ICODE_MACROS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_macro,				5,			false,		_ICODE_MACRO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_margin,				6,			false,		_ICODE_MARGIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_mark,					4,			false,		_ICODE_MARK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_md,					2,			false,		_ICODE_MD,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_memowidth,			9,			false,		_ICODE_MEMOWIDTH,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_memory,				6,			false,		_ICODE_MEMORY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_memo,					4,			false,		_ICODE_MEMO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_menus,				5,			false,		_ICODE_MENUS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_menu,					4,			false,		_ICODE_MENU,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_message,				7,			false,		_ICODE_MESSAGE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_mkdir,				5,			false,		_ICODE_MKDIR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_modify,				6,			false,		_ICODE_MODIFY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_mouse,				5,			false,		_ICODE_MOUSE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_move,					4,			false,		_ICODE_MOVE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_mtdll,				5,			false,		_ICODE_MTDLL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_multilocks,			10,			false,		_ICODE_MULTILOCKS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_near,					4,			false,		_ICODE_NEAR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_next,					4,			false,		_ICODE_ENDFOR,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_nocptrans,			9,			false,		_ICODE_NOCPTRANS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_note,					4,			false,		_ICODE_NOTE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_notify,				6,			false,		_ICODE_NOTIFY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_nulldisplay,			11,			false,		_ICODE_NULLDISPLAY,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_objects,				7,			false,		_ICODE_OBJECTS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_object,				6,			false,		_ICODE_OBJECT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_odometer,				8,			false,		_ICODE_ODOMETER,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_off,					3,			false,		_ICODE_OFF,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_of,					2,			false,		_ICODE_OF,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_oleobject,			9,			false,		_ICODE_OLEOBJECT,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_on,					2,			false,		_ICODE_ON,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_open,					4,			false,		_ICODE_OPEN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_optimize,				8,			false,		_ICODE_OPTIMIZE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_order,				5,			false,		_ICODE_ORDER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_or,					2,			false,		_ICODE_OR,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_overview,				8,			false,		_ICODE_OVERVIEW,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_pack,					4,			false,		_ICODE_PACK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_pad,					3,			false,		_ICODE_PAD,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_page,					4,			false,		_ICODE_PAGE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_palette,				7,			false,		_ICODE_PALETTE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_parameters,			10,			false,		_ICODE_PARAMETERS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_path,					4,			false,		_ICODE_PATH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_pdsetup,				7,			false,		_ICODE_PDSETUP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_play,					4,			false,		_ICODE_PLAY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_point,				5,			false,		_ICODE_POINT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_pop,					3,			false,		_ICODE_POP,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_popups,				6,			false,		_ICODE_POPUPS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_popup,				5,			false,		_ICODE_POPUP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_printer,				7,			false,		_ICODE_PRINTER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
//		{ cgc_printjob,				8,			false,		_ICODE_PRINTJOB,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_private,				7,			false,		_ICODE_PRIVATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_procedures,			10,			false,		_ICODE_PROCEDURES,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_procedure,			9,			false,		_ICODE_PROCEDURE,						false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_project,				7,			false,		_ICODE_PROJECT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_prompt,				6,			false,		_ICODE_PROMPT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_public,				6,			false,		_ICODE_PUBLIC,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_push,					4,			false,		_ICODE_PUSH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_query,				5,			false,		_ICODE_QUERY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_quit,					4,			false,		_ICODE_QUIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_rd,					2,			false,		_ICODE_RD,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_read,					4,			false,		_ICODE_READ,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_readborder,			10,			false,		_ICODE_READBORDER,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_readerror,			9,			false,		_ICODE_READERROR,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_recall,				6,			false,		_ICODE_RECALL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_recover,				7,			false,		_ICODE_RECOVER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_refresh,				7,			false,		_ICODE_REFRESH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_reindex,				7,			false,		_ICODE_REINDEX,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_relation,				8,			false,		_ICODE_RELATION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_release,				7,			false,		_ICODE_RELEASE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_remove,				6,			false,		_ICODE_REMOVE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_rename,				6,			false,		_ICODE_RENAME,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_replace,				7,			false,		_ICODE_REPLACE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_report,				6,			false,		_ICODE_REPORT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_reprocessattempts,	17,			false,		_ICODE_REPROCESS_ATTEMPTS,				false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_reprocess,			9,			false,		_ICODE_REPROCESS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_resource,				8,			false,		_ICODE_RESOURCE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_restore,				7,			false,		_ICODE_RESTORE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_resume,				6,			false,		_ICODE_RESUME,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_retry,				5,			false,		_ICODE_RETRY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_return,				6,			false,		_ICODE_RETURN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_rmdir,				5,			false,		_ICODE_RMDIR,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_rollback,				8,			false,		_ICODE_ROLLBACK,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_run,					3,			false,		_ICODE_RUN,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_safety,				6,			false,		_ICODE_SAFETY,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_save,					4,			false,		_ICODE_SAVE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_say,					3,			false,		_ICODE_SAY,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_scan,					4,			false,		_ICODE_SCAN,							false,				_ICAT_FLOW,			&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_scatter,				7,			false,		_ICODE_SCATTER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_scheme,				6,			false,		_ICODE_SCHEME,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_screen,				6,			false,		_ICODE_SCREEN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_scroll,				6,			false,		_ICODE_SCROLL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_seconds,				7,			false,		_ICODE_SECONDS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_seek,					4,			false,		_ICODE_SEEK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_select,				6,			false,		_ICODE_SELECT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_selection,			9,			false,		_ICODE_SELECTION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_separator,			9,			false,		_ICODE_SEPARATOR,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_set,					3,			false,		_ICODE_SET,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_show,					4,			false,		_ICODE_SHOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_shutdown,				8,			false,		_ICODE_SHUTDOWN,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_size,					4,			false,		_ICODE_SIZE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_skip,					4,			false,		_ICODE_SKIP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sort,					4,			false,		_ICODE_SORT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_space,				5,			false,		_ICODE_SPACE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sql,					3,			false,		_ICODE_SQL,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_status,				6,			false,		_ICODE_STATUS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_step,					4,			false,		_ICODE_STEP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_store,				5,			false,		_ICODE_STORE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_strictdate,			10,			false,		_ICODE_STRICTDATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_structure,			9,			false,		_ICODE_STRUCTURE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sum,					3,			false,		_ICODE_SUM,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_suspend,				7,			false,		_ICODE_SUSPEND,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sysformats,			10,			false,		_ICODE_SYSFORMATS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sysmenu,				7,			false,		_ICODE_SYSMENU,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_system,				6,			false,		_ICODE_SYSTEM,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_sys,					3,			false,		_ICODE_SYS,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_tablevalidate,		13,			false,		_ICODE_TABLEVALIDATE,					false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_tables,				6,			false,		_ICODE_TABLES,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_table,				5,			false,		_ICODE_TABLE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_tag,					3,			false,		_ICODE_TAG,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_talk,					4,			false,		_ICODE_TALK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_textmerge,			9,			false,		_ICODE_TEXTMERGE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_text,					4,			false,		_ICODE_TEXT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_to,					2,			false,		_ICODE_TO,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_topic,				5,			false,		_ICODE_TOPIC,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_total,				5,			false,		_ICODE_TOTAL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_transaction,			11,			false,		_ICODE_TRANSACTION,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_trbetween,			9,			false,		_ICODE_TRBETWEEN,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_trigger,				7,			false,		_ICODE_TRIGGER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_try,					3,			false,		_ICODE_TRY,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_type,					4,			false,		_ICODE_TYPE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_typeahead,			9,			false,		_ICODE_TYPEAHEAD,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_udfparms,				8,			false,		_ICODE_UDFPARMS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_unique,				6,			false,		_ICODE_UNIQUE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_unlock,				6,			false,		_ICODE_UNLOCK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_update,				6,			false,		_ICODE_UPDATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_use,					3,			false,		_ICODE_USE,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		(uptr)&compilerDictionary_command_use	},
		{ cgc_validate,				8,			false,		_ICODE_VALIDATE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_views,				5,			false,		_ICODE_VIEWS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_view,					4,			false,		_ICODE_VIEW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_wait,					4,			false,		_ICODE_WAIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_while,				5,			false,		_ICODE_WHILE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_windows,				7,			false,		_ICODE_WINDOWS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_window,				6,			false,		_ICODE_WINDOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_with,					4,			false,		_ICODE_WITH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_zap,					3,			false,		_ICODE_ZAP,								false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },

		// keyword					length		repeats?	extra (type)							first on line?		category
		{ cgc_not_dots,				5,			false,		_ICODE_NOT,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_not,					3,			false,		_ICODE_NOT,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_and_dots,				5,			false,		_ICODE_AND,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_and,					3,			false,		_ICODE_AND,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_or_dots,				4,			false,		_ICODE_OR,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_or,					2,			false,		_ICODE_OR,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },

		// Relatives
		{ cgc_thiscode,				8,			false,		_ICODE_THISCODE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_thisclass,			9,			false,		_ICODE_THISCLASS,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_thisform,				8,			false,		_ICODE_THISFORM,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_parent,				6,			false,		_ICODE_PARENT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },

		// Stand-alones
		{ cgc_null_dots,			6,			false,		_ICODE_NULL,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_null,					4,			false,		_ICODE_NULL,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_t_dots,				3,			false,		_ICODE_TRUE,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_true,					4,			false,		_ICODE_TRUE,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_f_dots,				3,			false,		_ICODE_FALSE,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_false,				5,			false,		_ICODE_FALSE,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_yes,					3,			false,		_ICODE_YES,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_no,					2,			false,		_ICODE_NO,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_up,					2,			false,		_ICODE_UP,								false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_down,					4,			false,		_ICODE_DOWN,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_o_dots,				3,			false,		_ICODE_OTHER,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_p_dots,				3,			false,		_ICODE_PARTIAL,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_x_dots,				3,			false,		_ICODE_EXTRA,							false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_y_dots,				3,			false,		_ICODE_YET_ANOTHER,						false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },
		{ cgc_z_dots,				3,			false,		_ICODE_ZATS_ALL_FOLKS,					false,				_ICAT_GENERIC,		&colorSynHi_logical,		true,						null0,		null0 },

		// VXB specific
		{ cgc__screen,				7,			false,		_ICODE_SCREEN,							false,				_ICAT_GENERIC,		&colorSynHi_variable,		true,						null0,		null0 },
		{ cgc__vjr,					4,			false,		_ICODE_VJR,								false,				_ICAT_GENERIC,		&colorSynHi_variable,		true,						null0,		null0 },
		{ cgc__jdebi,				6,			false,		_ICODE_JDEBI,							false,				_ICAT_GENERIC,		&colorSynHi_variable,		true,						null0,		null0 },
		{ cgc__cmd,					4,			false,		_ICODE_CMD,								false,				_ICAT_GENERIC,		&colorSynHi_variable,		true,						null0,		null0 },
		{ cgc__settings,			9,			false,		_ICODE_SETTINGS,						false,				_ICAT_GENERIC,		&colorSynHi_variable,		true,						null0,		null0 },
		{ cgc_protected,			9,			false,		_ICODE_PROTECTED,						false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_main,					4,			false,		_ICODE_MAIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ cgc_loadlastfromvjruserdbf, 22,		false,		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF,		false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_flags,				5,			false,		_ICODE_FLAGS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_metaicase,			9,			false,		_ICODE_METAICASE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_mefaicase,			9,			false,		_ICODE_MEFAICASE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_meiaicase,			9,			false,		_ICODE_MEIAICASE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_memaicase,			9,			false,		_ICODE_MEMAICASE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_meta,					4,			false,		_ICODE_META,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_mefa,					4,			false,		_ICODE_MEFA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_meia,					4,			false,		_ICODE_MEIA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_mema,					4,			false,		_ICODE_MEMA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_flowof,				6,			false,		_ICODE_FLOWOF,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_flowout,				7,			false,		_ICODE_FLOWOUT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_flowto,				6,			false,		_ICODE_FLOWTO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_flow,					4,			false,		_ICODE_FLOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_subflow,				7,			false,		_ICODE_SUBFLOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_rgba,					4,			false,		_ICODE_RGBA,							false,				_ICAT_FUNCTION,		&colorSynHi_function,		false,						null0,		null0 },
		{ cgc_lobject,				7,			false,		_ICODE_LOBJECT,							true,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_params,				7,			false,		_ICODE_PARAMS,							true,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_returns,				7,			false,		_ICODE_RETURNS,							true,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_as,					2,			false,		_ICODE_AS,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_character,			9,			false,		_ICODE_CHARACTER,						false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_integer,				7,			false,		_ICODE_INTEGER,							false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_float,				5,			false,		_ICODE_FLOAT,							false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_double,				6,			false,		_ICODE_DOUBLE,							false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_logical,				7,			false,		_ICODE_LOGICAL,							false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
//		{ cgc_date,					4,			false,		_ICODE_DATE,							false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
//		{ cgc_datetime,				8,			false,		_ICODE_DATETIME,						false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
//		{ cgc_currency,				8,			false,		_ICODE_CURRENCY,						false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_s32,					3,			false,		_ICODE_S32,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_s64,					3,			false,		_ICODE_S64,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_u32,					3,			false,		_ICODE_U32,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_u64,					3,			false,		_ICODE_U64,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_f32,					3,			false,		_ICODE_F32,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_f64,					3,			false,		_ICODE_F64,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_bi,					2,			false,		_ICODE_BI,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_bfp,					3,			false,		_ICODE_BFP,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_s16,					3,			false,		_ICODE_S16,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_s8,					2,			false,		_ICODE_S8,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_u16,					3,			false,		_ICODE_U16,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_u8,					2,			false,		_ICODE_U8,								false,				_ICAT_GENERIC,		null0,						false,						null0,		null0 },
		{ cgc_adhoc,				5,			false,		_ICODE_ADHOC,							true,				_ICAT_FLOW,			&colorSynHi_command,		true,						null0,		null0 },
		{ cgc_endadhoc,				8,			false,		_ICODE_ENDADHOC,						true,				_ICAT_FLOW,			&colorSynHi_command,		true,						null0,		null0 },

		{ 0,						0,			0,			0,										0,					0 }
	};
