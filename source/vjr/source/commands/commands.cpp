//////////
//
// /libsf/source/vjr/commands/commands.cpp
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
// Version 0.56
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
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
//
// To add a new function, see the instructions in command_defs.h.
//
//




//////////
//
// Called to signal an error in the current running program
//
//////
	void iError_signal(SThisCode* thisCode, u32 tnErrorNum, SComp* comp, bool tlInvasive, s8* tcExtraInfo, bool tlFatal)
	{
// TODO:  This will need to potentially break the program execution
		iError_reportByNumber(thisCode, tnErrorNum, comp, tlInvasive);
	}




//////////
//
// Reports an error
//
//////
	void iError_report(cu8* constantErrorText, bool tlInvasive)
	{
		iError_report((u8*)constantErrorText, tlInvasive);
	}

	void iError_report(u8* errorText, bool tlInvasive)
	{
		if (!tlInvasive)
		{
			// Append the error to the EM
			iSEM_appendLine(screenData, errorText, -1, false);
			screen_editbox->isDirtyRender = true;

		} else {
			// Immediate need
			MessageBox(NULL, (cs8*)errorText, (cs8*)cgcVjrError, MB_OK);
		}
	}




//////////
//
// Reports an error by number
//
//////
	void iError_reportByNumber(SThisCode* thisCode, u32 tnErrorNum, SComp* comp, bool tlInvasive)
	{
		switch (tnErrorNum)
		{
			case _ERROR_OUT_OF_MEMORY:						{	iError_report(cgcOutOfMemory, tlInvasive);						break;	}
			case _ERROR_UNEXPECTED_COMMAND:					{	iError_report(cgcUnexpectedCommand, tlInvasive);				break;	}
			case _ERROR_CONTEXT_HAS_CHANGED:				{	iError_report(cgcContextHasChanged, tlInvasive);				break;	}
			case _ERROR_FULL_RECOMPILE_REQUIRED:			{	iError_report(cgcFullRecompileRequired, tlInvasive);			break;	}
			case _ERROR_NOT_A_VARIABLE:						{	iError_report(cgcNotAVariable, tlInvasive);						break;	}
			case _ERROR_NUMERIC_OVERFLOW:					{	iError_report(cgcNumericOverflow, tlInvasive);					break;	}
			case _ERROR_NOT_NUMERIC:						{	iError_report(cgcNotNumeric, tlInvasive);						break;	}
			case _ERROR_EMPTY_STRING:						{	iError_report(cgcEmptyString, tlInvasive);						break;	}
			case _ERROR_SYNTAX:								{	iError_report(cgcSyntaxError, tlInvasive);						break;	}
			case _ERROR_UNRECOGNIZED_PARAMETER:				{	iError_report(cgcUnrecognizedParameter, tlInvasive);			break;	}
			case _ERROR_OUT_OF_RANGE:						{	iError_report(cgcOutOfRange, tlInvasive);						break;	}
			case _ERROR_COMMA_EXPECTED:						{	iError_report(cgcCommaExpected, tlInvasive);					break;	}
			case _ERROR_TOO_MANY_PARAMETERS:				{	iError_report(cgcTooManyParameters, tlInvasive);				break;	}
			case _ERROR_DATA_TYPE_MISMATCH:					{	iError_report(cgcDataTypeMismatch, tlInvasive);					break;	}
			case _ERROR_FEATURE_NOT_AVAILABLE:				{	iError_report(cgcFeatureNotAvailable, tlInvasive);				break;	}
			case _ERROR_P1_IS_INCORRECT:					{	iError_report(cgcP1IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P2_IS_INCORRECT:					{	iError_report(cgcP2IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P3_IS_INCORRECT:					{	iError_report(cgcP3IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P4_IS_INCORRECT:					{	iError_report(cgcP4IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P5_IS_INCORRECT:					{	iError_report(cgcP5IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P6_IS_INCORRECT:					{	iError_report(cgcP6IsIncorrect, tlInvasive);					break;	}
			case _ERROR_P7_IS_INCORRECT:					{	iError_report(cgcP7IsIncorrect, tlInvasive);					break;	}
			case _ERROR_INTERNAL_ERROR:						{	iError_report(cgcInternalError, tlInvasive);					break;	}
			case _ERROR_INVALID_ARGUMENT_TYPE_COUNT:		{	iError_report(cgcInvalidArgumentTypeCountError, tlInvasive);	break;	}
			case _ERROR_VARIABLE_NOT_FOUND:					{	iError_report(cgcVariableNotFoundError, tlInvasive);			break;	}
			case _ERROR_ALIAS_NOT_FOUND:					{	iError_report(cgcAliasNotFoundError, tlInvasive);				break;	}
			case _ERROR_INVALID_WORK_AREA:					{	iError_report(cgcInvalidWorkArea, tlInvasive);					break;	}
			case _ERROR_ALIAS_ALREADY_IN_USE:				{	iError_report(cgcAliasAlreadyInUse, tlInvasive);				break;	}
			case _ERROR_PARENTHESIS_EXPECTED:				{	iError_report(cgcParenthesisExpected, tlInvasive);				break;	}
			case _ERROR_MISSING_PARAMETER:					{	iError_report(cgcMissingParameter, tlInvasive);					break;	}
			case _ERROR_UNABLE_TO_OPEN_TABLE:				{	iError_report(cgcUnableToOpenTable, tlInvasive);				break;	}
			case _ERROR_WORK_AREA_ALREADY_IN_USE:			{	iError_report(cgcWorkAreaAlreadyInUse, tlInvasive);				break;	}
			case _ERROR_ERROR_OPENING_DBC:					{	iError_report(cgcErrorOpeningDbc, tlInvasive);					break;	}
			case _ERROR_CONFLICTING_PARAMETERS:				{	iError_report(cgcConflictingParameters, tlInvasive);			break;	}
			case _ERROR_PARAMETER_IS_INCORRECT:				{	iError_report(cgcParameterIsIncorrect, tlInvasive);				break;	}
			case _ERROR_TABLE_ALREADY_IN_USE:				{	iError_report(cgcTableAlreadyInUse, tlInvasive);				break;	}
			case _ERROR_PARAMETER_TOO_LONG:					{	iError_report(cgcParameterTooLong, tlInvasive);					break;	}
			case _ERROR_UNABLE_TO_OPEN_DBC:					{	iError_report(cgcUnableToOpenDbc, tlInvasive);					break;	}
			case _ERROR_DIVISION_BY_ZERO:					{	iError_report(cgcDivisionByZero, tlInvasive);					break;	}
			case _ERROR_CANNOT_BE_NEGATIVE:					{	iError_report(cgcCannotBeNegative, tlInvasive);					break;	}
			case _ERROR_CANNOT_BE_ZERO_OR_NEGATIVE:			{	iError_report(cgcCannotBeZeroOrNegative, tlInvasive);			break;	}
															

		}

		// Flag the component
		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data && comp->line->sourceCode_populatedLength != 0)
		{
			// Flag it for error
			comp->isError = true;
		}
	}




//////////
//
// Called to signal an error if the f32 value is outside the valid range for the target type
//
//////
	f32 iErrorCandidate_signalOutOfRange_f32(SThisCode* thisCode, f32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (f32)_s8_min || value >= (f32)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (f32)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value <= (f32)_s16_min || value >= (f32)_s16_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (f32)_u16_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S32:
				if (value <= (f32)_s32_min || value >= (f32)_s32_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U32:
				if (value >= (f32)_u32_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S64:
				if (value <= (f32)_s64_min || value >= (f32)_s64_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U64:
				if (value >= (f32)_u64_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the f64 value is outside the valid range for the target type
//
//////
	f64 iErrorCandidate_signalOutOfRange_f64(SThisCode* thisCode, f64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (f64)_s8_min || value >= (f64)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (f64)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value <= (f64)_s16_min || value >= (f64)_s16_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (f64)_u16_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S32:
				if (value <= (f64)_s32_min || value >= (f64)_s32_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U32:
				if (value >= (f64)_u32_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S64:
				if (value <= (f64)_s64_min || value >= (f64)_s64_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U64:
				if (value >= (f64)_u64_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the u16 value is outside the valid range for the target type
//
//////
	u8 iErrorCandidate_signalOutOfRange_u8(SThisCode* thisCode, u8 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u8)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the s16 value is outside the valid range for the target type
//
//////
	s16 iErrorCandidate_signalOutOfRange_s16(SThisCode* thisCode, s16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s16)_s8_min || value >= (s16)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (s16)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the u16 value is outside the valid range for the target type
//
//////
	u16 iErrorCandidate_signalOutOfRange_u16(SThisCode* thisCode, u16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u16)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (u16)_u8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value >= (u16)_s16_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the s32 value is outside the valid range for the target type
//
//////
	s32 iErrorCandidate_signalOutOfRange_s32(SThisCode* thisCode, s32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s32)_s8_min || value >= (s32)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (s32)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value <= (s32)_s16_min || value >= (s32)_s16_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (s32)_u16_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the s32 value is outside the valid range for the target type
//
//////
	u32 iErrorCandidate_signalOutOfRange_u32(SThisCode* thisCode, u32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u32)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (u32)_u8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value >= (u32)_s16_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (u32)_u16_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the s64 value is outside the valid range for the target type
//
//////
	s64 iErrorCandidate_signalOutOfRange_s64(SThisCode* thisCode, s64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s64)_s8_min || value >= (s64)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (s64)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value <= (s64)_s16_min || value >= (s64)_s16_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (s64)_u16_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S32:
				if (value <= (s64)_s32_min || value >= (s64)_s32_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U32:
				if (value >= (s64)_u32_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the s64 value is outside the valid range for the target type
//
//////
	u64 iErrorCandidate_signalOutOfRange_u64(SThisCode* thisCode, u64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u64)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U8:
				if (value >= (u64)_u8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S16:
				if (value >= (u64)_s16_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U16:
				if (value >= (u64)_u16_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S32:
				if (value >= (u64)_s32_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_U32:
				if (value >= (u64)_u32_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;

			case _VAR_TYPE_S64:
				if (value >= (u64)_s64_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
				break;
		}

		// Return the input value
		return(value);
	}




//////////
//
// Called to signal an error if the numeric value is outside the valid range for the target type
//
//////
	f64 iErrorCandidate_signalOutOfRange_numeric(SThisCode* thisCode, SDatum* value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		f64	lfValue;
		s8	buffer[64];


		// Based on the test type, make sure it's in range
		if (value && value->length >= 1 && (u32)value->length <= sizeof(buffer) - 1)
		{
			// Copy text to null-terminate
			memcpy(buffer, value->data, value->length);
			buffer[value->length] = 0;

			// Convert to f64
			lfValue = atof(value->data);

			// Based on the type, check its range
			switch (tnVarType)
			{
				case _VAR_TYPE_S8:
					if (lfValue <= (f64)_s8_min || lfValue >= (f64)_s8_max)			iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_U8:
					if (lfValue >= (f64)_u8_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_S16:
					if (lfValue <= (f64)_s16_min || lfValue >= (f64)_s16_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_U16:
					if (lfValue >= (f64)_u16_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_S32:
					if (lfValue <= (f64) _s32_min || lfValue >= (f64)_s32_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_U32:
					if (lfValue >= (f64)_u32_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_S64:
					if (lfValue <= (f64)_s64_min || lfValue >= (f64)_s64_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_U64:
					if (lfValue >= (f64)_u64_max)									iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;

				case _VAR_TYPE_F32:
					if (lfValue <= (f64)_s32_min || lfValue >= (f64)_s32_max)		iError_signal(thisCode, _ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);
					break;
			}

		} else {
			// Signal the lowest possible value
			lfValue = (f64)_f64_min;
		}

		// Return the input value
		return(lfValue);
	}




//////////
//
// Function: ADDBS()
// Adds a backslash to a path if it needs one
//
//////
// Version 0.56
// Last update:
//	   Dec.26.2014
//////
// Change log:
//     Dec.26.2014 - Initial creation
//////
// Parameters:
//     varString		-- Character, the string that needs to end with a backspace
//////
// Returns:
//     Character		-- The string with a trailing backspace added if need be
//////
	SVariable* function_addbs(SThisCode* thisCode, SVariable* varString)
	{
        SVariable* result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 1)
			{
				// If the last character is not a backslash, add one
				if (varString->value.data_u8[varString->value.length - 1] != '\\')
				{
					// We need to append the string plus a backslash
					iDatum_allocateSpace(&result->value, varString->value.length + 1);
					memcpy(result->value.data_s8, varString->value.data_s8, varString->value.length);
					result->value.data_u8[result->value.length - 1] = '\\';

				} else {
					// We can copy the string as is
					iDatum_duplicate(&result->value, &varString->value);
				}

			} else {
				// Append a trailing backslash
				iDatum_duplicate(&result->value, (u8*)cgcBackslash, 1);
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: ALLTRIM()
// Trims spaces off the start and end of the string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString			-- Character, the string to trim
//     pCaseInsensitive	-- (Optional) Logical,		are the trim characters case insensitive?  Default = .T.
//     pTrimChars1		-- (Optional) Character,	characters to trim
//     pTrimChars2		-- (Optional) Character,	characters to trim
//
//////
// Returns:
//    Character		-- The string with any leading and trailing spaces removed
//////
	SVariable* function_alltrim(SThisCode* thisCode, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2)
	{
		return(ifunction_trim_common(thisCode, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, true, true));
	}




//////////
//
// Logic used for ALLTRIM(), LTRIM(), RTRIM()
//
//////
// Syntax forms supported:
//	    (1)  *TRIM(cString[, cTrimString])
//	    (2)  *TRIM(cString[, nCaseSensitive|lCaseSensitive[, cTrimChar1[, cTrimChar2]]])
//
//////
	SVariable* ifunction_trim_common(SThisCode* thisCode, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2, bool tlTrimTheStart, bool tlTrimTheEnd)
	{
		s32			lnI, lnClipStartPos, lnClipEndPos;
		s8			lc;
		bool		llCaseInsensitive, llSyntaxForm1, llFound;
		s8*			trim1ptr;
		s8*			trim2ptr;
		s32			trim1Length, trim2Length;
        SVariable*	result;


// TODO:  Incomplete function.  Breakpoint, debug, and finish development
//_asm_int3;
		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Initialize
		//////
			llSyntaxForm1		= false;		// Two syntax forms are available
			llCaseInsensitive	= false;		// By default case-sensitive compare
			trim1ptr		= (s8*)cgc_spaceText;
			trim1Length		= 1;
			trim2ptr		= NULL;
			trim2Length		= 0;


		//////////
        // If pCaseInsensitive is present, indicates case-insensitive
		//////
			if (varCaseInsensitive)
			{
				// See what the parameter is
				if (!iVariable_isValid(varCaseInsensitive))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varCaseInsensitive), false);
					return(NULL);

				} else if (iVariable_isTypeNumeric(varCaseInsensitive)) {
					// They are indicating case sensitivity by an integer, should be 1 for case-insensitive, otherwise case-sensitive
					// If 1, case-insensitive
					if (*(s32*)varCaseInsensitive->value.data == 1)
						llCaseInsensitive = true;

				} else if (iVariable_isTypeLogical(varCaseInsensitive)) {
					// They are indicating case sensitivity by a logical flag, should be .t. for case-insensitive, otherwise case-sensitive
					if (varCaseInsensitive->value.data[0] != 0)
						llCaseInsensitive = true;

				} else if (iVariable_isTypeCharacter(varCaseInsensitive)) {
					// They're using the syntax form:
					//		ALLTRIM(cString[, cTrimString])
					trim1ptr		= varCaseInsensitive->value.data;
					trim1Length		= varCaseInsensitive->value.length;
					trim2ptr		= NULL;
					trim2Length		= 0;
					llSyntaxForm1	= true;

				} else {
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varCaseInsensitive), false);
					return(NULL);
				}
			}


		//////////
		// If they specified trimCharss
		//////
			if (varTrimChars1)
			{
				// If they're using syntax form1, then the presence of this parameter is a syntax error
				if (llSyntaxForm1)
				{
					iError_reportByNumber(thisCode, _ERROR_TOO_MANY_PARAMETERS, iVariable_compRelated(thisCode, varTrimChars1), false);
					return(NULL);

				} else if (iVariable_isTypeCharacter(varTrimChars1)) {
					// They specified characters to scan
					trim1ptr	= varTrimChars1->value.data;
					trim1Length	= varTrimChars1->value.length;

				} else {
					iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varTrimChars1), false);
					return(NULL);
				}
			}


		//////////
		// If they specified trimCharss
		//////
			if (varTrimChars2)
			{
				if (iVariable_isTypeCharacter(varTrimChars2))
				{
					// They specified characters to scan
					trim2ptr	= varTrimChars2->value.data;
					trim2Length	= varTrimChars2->value.length;
					if (trim1ptr == (s8*)cgc_spaceText)
					{
						// They gave us the second trim characters, so we'll use it
						trim1ptr		= NULL;
						trim1Length		= 0;
					}

				} else {
					iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_compRelated(thisCode, varTrimChars2), false);
					return(NULL);
				}
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // It must be at least one character long to be adjusted
		//////
			if (varString->value.length >= 1)
			{
				//////////
				// START
				//////
					lnClipStartPos = 0;
					if (tlTrimTheStart)
					{
						// Based on the comparison, we either compare character-by-character, or convert case and compare character-by-character
						if (llCaseInsensitive)
						{
							// Compare character by character exactly as they are
							for ( ; lnClipStartPos < varString->value.length; ++lnClipStartPos)
							{
								// Grab the character
								lc = varString->value.data[lnClipStartPos];

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim1ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim2ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}

						} else {
							// Compare character by character accounting for case
							// Compare character by character exactly as they are
							for ( ; lnClipStartPos < varString->value.length; ++lnClipStartPos)
							{
								// Grab the character
								lc = iLowerCase(varString->value.data[lnClipStartPos]);

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim1ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim2ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}
						}

						// When we get here, we have determined the number of characters on the left
						if (lnClipStartPos >= varString->value.length)
							return(result);		// The entire character string is empty, so we just return the blank string
					}


				//////////
				// END
				//////
					lnClipEndPos = varString->value.length - 1;
					if (tlTrimTheEnd)
					{
						// Based on the comparison, we either compare character-by-character, or convert case and compare character-by-character
						if (llCaseInsensitive)
						{
							// Compare character by character exactly as they are
							for ( ; lnClipEndPos > 0; lnClipEndPos--)
							{
								// Grab the character
								lc = varString->value.data[lnClipEndPos];

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim1ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim2ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}

						} else {
							// Compare character by character accounting for case
							// Compare character by character exactly as they are
							for ( ; lnClipEndPos > 0; lnClipEndPos--)
							{
								// Grab the character
								lc = iLowerCase(varString->value.data[lnClipEndPos]);

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim1ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim2ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}
						}
					}


				//////////
				// Copy the portion of the string
				//////
					iDatum_duplicate(&result->value, varString->value.data_u8 + lnClipStartPos, lnClipEndPos - lnClipStartPos + 1);
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: ALP()
// Retrieves the alpha channel from an RGBA or BGRA color.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Numeric, a color (0..(2^32)-1)
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
	SVariable* function_alp(SThisCode* thisCode, SVariable* varColor)
	{
		return(ifunction_color_common(thisCode, varColor, 0xff000000, 24));
	}




//////////
//
// Function: ASC()
// Takes a character input and converts it to its ASCII value.
//
//////
// Version 0.56
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1		-- Character, must be at least one character long
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
    SVariable* function_asc(SThisCode* thisCode, SVariable* varString)
    {
        u8 			value;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // It must be at least one character long
		//////
			if (varString->value.length == 0)
				iError_reportByNumber(thisCode, _ERROR_EMPTY_STRING, iVariable_compRelated(thisCode, varString), false);


		//////////
		// Extract the first character, and convert it to a number
		//////
			value = varString->value.data_u8[0];


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        *result->value.data_s32 = (s32)value;


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Functions:  AT(), ATC(), RAT(), RATC()
// Takes a character input to search for, an expression to search, and an optional occurrence
// to find, with and optionally with regard to case (trailing "C").
//
// Functions:  OCCURS(), OCCURSC()
// Takes a character input to search for, an expression to search, and determines how many
// times the search string is found, and optionally with regard to case (trailing "C").
//
//////
// Version 0.56
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pNeedle		-- What we're looking for
//     pHaystack	-- Where we're looking
//     pOccurrence	-- An optional instance count within the expression
//
//////
// Returns:
//    u32			-- Location of the find, or 0 if not found
//////
	SVariable* function_at(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence)
	{
		return(ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, varOccurrence, true, false, NULL));
	}

	SVariable* function_atc(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence)
	{
		return(ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, varOccurrence, false, false, NULL));
	}

	SVariable* function_rat(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence)
	{
		return(ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, varOccurrence, true, true, NULL));
	}

	SVariable* function_ratc(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence)
	{
		return(ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, varOccurrence, false, true, NULL));
	}

	SVariable* ifunction_at_occurs_common(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence, bool tlCaseSensitive, bool tlScanBackward, u32* tnFoundCount)
	{
		u32			errorNum;
		s32			lnI, lnStart, lnInc, lnStopper, lnFoundCount, lnOccurrence;
		bool		error;
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varNeedle) || !iVariable_isTypeCharacter(varNeedle))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNeedle), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varHaystack) || !iVariable_isTypeCharacter(varHaystack))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varHaystack), false);
				return(NULL);
			}


		//////////
		// Parameter 3 is optional, but if present...
		//////
			if (iVariable_isValid(varOccurrence))
			{
				// ...it must be numeric
				if (!iVariable_isTypeNumeric(varOccurrence))
				{
					iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varOccurrence), false);
					return(NULL);
				}

				// Grab the occurrence
				lnOccurrence = iiVariable_getAs_s32(thisCode, varOccurrence, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varOccurrence), false);	return(NULL);	}

				// Validate that the occurrence is
				if (lnOccurrence <= 0)
				{
					iError_report((cu8*)"Parameter 3 must be 1 or greater", false);
					return(NULL);
				}

			} else {
				// The first occurrence is what we're after
				lnOccurrence = 1;
			}


		//////////
		// Create the return variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);


		//////////
		// If either string has a zero length, or the needle is bigger than the haystack, we cannot find it
		//////
			if (varNeedle->value.length == 0 || varHaystack->value.length == 0 || varNeedle->value.length > varHaystack->value.length)
				return(result);


		//////////
		// Determine where
		//////
			if (tnFoundCount)
			{
				// They want to find all of the occurrences
				lnStart			= 0;
				lnInc			= 1;
				lnStopper		= varHaystack->value.length - varNeedle->value.length + 1;
				lnOccurrence	= varHaystack->value.length;

			} else if (tlScanBackward) {
				// Scan from the back of the string to the start
				lnStart		= varHaystack->value.length - varNeedle->value.length;
				lnInc		= -1;
				lnStopper	= -1;

			} else {
				// Scan from the front of the string to the end
				lnStart		= 0;
				lnInc		= 1;
				lnStopper	= varHaystack->value.length - varNeedle->value.length + 1;
			}


		//////////
		// Scan through the text
		//////
			for (lnI = lnStart, lnFoundCount = 0; lnI != lnStopper; lnI += lnInc)
			{
				//////////
				// Compare this portion
				//////
					if (tlCaseSensitive)
					{
						// Case-sensitive
						if (memcmp(varNeedle->value.data, varHaystack->value.data + lnI, varNeedle->value.length) == 0)
							++lnFoundCount;		// Here's a match

					} else {
						// Case-insensitive
						if (_memicmp(varNeedle->value.data, varHaystack->value.data + lnI, varNeedle->value.length) == 0)
							++lnFoundCount;		// Here's a match
					}


				//////////
				// See if we're done
				//////
					if (lnFoundCount == lnOccurrence)
					{
						// Store the found location
						*(s32*)result->value.data_s32 = lnI + 1;

						// We're done, exit
						break;
					}
			}


		//////////
		// Update the found count if it was requested
		//////
			if (tnFoundCount)
				*tnFoundCount = lnFoundCount;


		//////////
		// Indicate our status
		//////
			return(result);
	}




//////////
//
// Function: BLU()
// Retrieves the blue channel from an RGBA or BGRA color.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Numeric, a color (0..(2^32)-1)
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
	SVariable* function_blu(SThisCode* thisCode, SVariable* varColor)
	{
		return(ifunction_color_common(thisCode, varColor, 0x00ff0000, 16));
	}




//////////
//
// Function: BGR()
// Returns the BGR() of the three input values.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed system-wide RGBA() integer
//
//////
	SVariable* function_bgr(SThisCode* thisCode, SVariable* varBlu, SVariable* varGrn, SVariable* varRed)
	{
		return(ifunction_rgba_common(thisCode, varRed, varGrn, varBlu, NULL));
	}




//////////
//
// Function: BGRA()
// Returns the BGRA() of the four input values.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pAlp			-- Alpha, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed system-wide RGBA() integer
//
//////
	SVariable* function_bgra(SThisCode* thisCode, SVariable* varBlu, SVariable* varGrn, SVariable* varRed, SVariable* varAlp)
	{
		return(ifunction_rgba_common(thisCode, varRed, varGrn, varBlu, varAlp));
	}




//////////
//
// Function: CEILING()
// Returns the next highest integer that is greater than or equal to the specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    CEILING(n) of the value in p1
//////
// Example:
//    ? CEILING(2.2)		&& Display 3
//////
    SVariable* function_ceiling(SThisCode* thisCode, SVariable* varNumber)
    {
        // Return ceiling

        return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_CEILING, _VAR_TYPE_S64, propGet_settings_ncset_ceilingFloor(_settings)));
	}



//////////
//
// Function: CHR()
// Takes a numeric input in the range 0..255, and converts it to its ASCII character.
//
//////
// Version 0.56
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1			-- Numeric, in the range 0..255
//
//////
// Returns:
//    Character		-- Input number converted to character
//////
    SVariable* function_chr(SThisCode* thisCode, SVariable* varNumer)
    {
        s32			value;
		u32			errorNum;
        bool		error;
        SVariable*	result;
		u8			buffer[16];


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNumer) || !iVariable_isTypeNumeric(varNumer))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNumer), false);
				return(NULL);
			}


		//////////
        // It must be in the range 0..255
		//////
			value = iiVariable_getAs_s32(thisCode, varNumer, false, &error, &errorNum);
			if (error)
			{
				// The iVariable_getAs_s32() function reported an error.
				// This means the user is trying to obtain an integer value from a logical, or something similar.
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumer), false);
				return(NULL);

			} else if (value > 255 || value < 0) {
				// We report our own error
				iError_report((u8*)"Parameter must be in the range 0..255", false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report((u8*)"Internal error.", false);
				return(NULL);
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        buffer[0] = (u8)value;
			buffer[1] = 0;
			iDatum_duplicate(&result->value, buffer, 1);


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Function: CHRTRAN()
// Character transformation
//
//////
// Version 0.56
// Last update:
//     Aug.21.2014
//////
// Change log:
//     Aug.21.2014 - Initial creation
//////
// Parameters:
//     pOriginalString		-- The string being updated
//     pSearch				-- The search characters
//     pReplace             -- The characters to replace when found
//
//////
// Returns:
//    A copy of the pOriginalString with everything converted.
//
//////
	SVariable* function_chrtran(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace)
	{
		return(ifunction_chrtran_common(thisCode, varString, varSearch, varReplace, true));
	}

	SVariable* function_chrtranc(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace)
	{
		return(ifunction_chrtran_common(thisCode, varString, varSearch, varReplace, false));
	}

	SVariable* ifunction_chrtran_common(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace, bool tlCaseSensitive)
	{
		s8			c1, c2;
		s32			lnSrc, lnDst, lnSearch;
		bool		llFound;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varSearch) || !iVariable_isTypeCharacter(varSearch))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varSearch), false);
				return(NULL);
			}


		//////////
		// Parameter 3 is optional, but must be character if present
		//////
			if (!iVariable_isValid(varReplace))
			{
				// They didn't provide a 3rd parameter, so we'll use a pseudo placeholder which is an empty string
				varReplace = varEmptyString;

			} else if (!iVariable_isTypeCharacter(varReplace)) {
				// It is invalid
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varReplace), false);
				return(NULL);
			}


		//////////
		// Allocate a copy of the original string
		//////
			result = iVariable_createAndPopulate(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length);

			// If the original string is empty, or the characters to search for are empty, then we don't need to do anything
			if (varString->value.length == 0 || varSearch->value.length == 0)
				return(result);


		//////////
		// Iterate through the string and update as we go
		//////
			for (lnSrc = 0, lnDst = 0; lnSrc < result->value.length; lnSrc++)
			{
				// Grab this character
				c1 = result->value.data[lnSrc];

				// Adjust the case if need be
				if (!tlCaseSensitive)
				{
					if (c1 >= 'A' && c1 <= 'Z')
						c1 += 0x20;
				}

				// Search the conversion string
				llFound = false;
				for (lnSearch = 0; lnSearch < varSearch->value.length; lnSearch++)
				{
					// Grab this character
					c2 = varSearch->value.data[lnSearch];

					// Adjust the case if necessary
					if (!tlCaseSensitive)
					{
						// Case insensitive, convert if need be
						if (c2 >= 'A' && c2 <= 'Z')
							c2 += 0x20;
					}

					// Is this character a match?
					if (c1 == c2)
					{
						// Indicate we found it
						llFound = true;

						// We need to perform the replace
						if (lnSearch < varReplace->value.length)
						{
							// We replace it with the character that's there
							result->value.data[lnDst] = varReplace->value.data[lnSearch];

						} else {
							// There is no translation character, so we just delete this character
							// To do that, we decrease our lnDst because it will be increased below
							--lnDst;
						}

						// We're done with this one because we found its match
						break;
					}
				}

				// When we get here, we either found the character or not
				if (!llFound && lnSrc != lnDst)
				{
					// We need to copy this character over
					result->value.data[lnDst] = result->value.data[lnSrc];
				}

				// Move our destination forward
				++lnDst;
			}


		//////////
		// When we get here, lnDst indicates how long the output string is
		//////
			result->value.length = lnDst;


		//////////
		// Return our final string
		/////
			return(result);
	}
;




//////////
//
// Function: COLORIZE()
// Colorizes an existing color by blending two colors.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor			-- The original color
//     varColorTarget	-- The color to blend in
//     varPercentage	-- (Optional) How much to blend
//
//////
// Returns:
//    Numeric			-- The resulting colorized color
//
//////
	SVariable* function_colorize(SThisCode* thisCode, SVariable* varColor, SVariable* varColorTarget, SVariable* varPercentage)
	{
		return(ifunction_colorize_common(thisCode, varColor, varColorTarget, varPercentage, true));
	}

	SVariable* ifunction_colorize_common(SThisCode* thisCode, SVariable* varColor, SVariable* varColorTarget, SVariable* varPercentage, bool tlApplyColorTarget)
	{
		u32			lnColor, lnColorTarget, lnColorNew;
		f32			lfRedC, lfGrnC, lfBluC, lfAlpC;		// varColor
		f32			lfRedT, lfGrnT, lfBluT, lfAlpT;		// varColorTarget
		f32			lfAlp, lfMalp, lfGray, lfRedNew, lfGrnNew, lfBluNew, lfAlpNew;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varColor), false);
				return(NULL);
			}


		//////////
		// If present, varColorTarget must be numeric
		//////
			if (tlApplyColorTarget)
			{
				if (!iVariable_isValid(varColorTarget) || !iVariable_isTypeNumeric(varColorTarget))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varColorTarget), false);
					return(NULL);
				}
			}


		//////////
		// Grab the percentage
		//////
			if (varPercentage)
			{
				// Must be floating point
				if (!iVariable_isValid(varPercentage) || !iVariable_isTypeFloatingPoint(varPercentage))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varPercentage), false);
					return(NULL);
				}

				// Grab the value
				lfAlp = iiVariable_getAs_f32(thisCode, varPercentage, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varPercentage), false);	return(NULL);	}

				// Must be in the range 0.0 to 1.0
				if (lfAlp < 0.0f || lfAlp > 1.0f)
				{
					iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varPercentage), false);
					return(NULL);
				}
				// If we get here, we're good

			} else {
				// They didn't specify a percentage, use default values
				if (tlApplyColorTarget)		lfAlp = 0.5f;		// colorize() 50% / 50%
				else						lfAlp = 1.0f;		// grayscale() 100%
			}

			// Compute our malp
			lfMalp = 1.0f - lfAlp;


		//////////
		// Grab the color
		//////
			// Extract the color
			lnColor = iiVariable_getAs_u32(thisCode, varColor, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varColor), false);	return(NULL);	}

			// Extract channels
			lfRedC = (f32)red(lnColor);
			lfGrnC = (f32)grn(lnColor);
			lfBluC = (f32)blu(lnColor);
			lfAlpC = (f32)alp(lnColor);


		//////////
		// Grab the color target
		//////
			if (tlApplyColorTarget)
			{
				// Extract the color target
				lnColorTarget = iiVariable_getAs_u32(thisCode, varColorTarget, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varColor), false);	return(NULL);	}

				// Extract channels
				lfRedT = (f32)red(lnColorTarget);
				lfGrnT = (f32)grn(lnColorTarget);
				lfBluT = (f32)blu(lnColorTarget);
				lfAlpT = (f32)alp(lnColorTarget);


				//////////
				// Generate the combined color (original color * malp) + (color target * alp)
				//////
					lfRedNew	= (lfRedC * lfMalp) + (lfRedT * lfAlp);
					lfGrnNew	= (lfGrnC * lfMalp) + (lfGrnT * lfAlp);
					lfBluNew	= (lfBluC * lfMalp) + (lfBluT * lfAlp);
					lfAlpNew	= (lfAlpC * lfMalp) + (lfAlpT * lfAlp);


			} else {
				// We are grayscaling
				lfGray		= max(min((lfRedC * 0.35f) + (lfGrnC * 0.54f) + (lfBluC * 0.11f), 1.0f), 0.0f);

				// Generate the new grayscaled color (original color * malp) + (grayscale * alp)
				lfRedNew	= (lfRedC * lfMalp) + (lfGray * lfAlp);
				lfGrnNew	= (lfGrnC * lfMalp) + (lfGray * lfAlp);
				lfBluNew	= (lfBluC * lfMalp) + (lfGray * lfAlp);
				lfAlpNew	= (lfAlpC * lfMalp) + (lfGray * lfAlp);
			}


		//////////
		// Construct the new color into an integer
		//////
			lnColorNew = rgba((u32)lfRedNew, (u32)lfGrnNew, (u32)lfBluNew, (u32)lfAlpNew);


		//////////
		// Construct our result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_U32, NULL);
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Populate and return our result
		//////
			*result->value.data_u32 = lnColorNew;
			return(result);
	}




//////////
//
// Function: COS()
// Returns the cosine of a numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.17.2015
//////
// Change log:
//     Mar.17.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    COS(n) of the value in p1
//////
// Example:
//    ? COS(0)		&& Display 1.00
//////
    SVariable* function_cos(SThisCode* thisCode, SVariable* varNumber)
    {
		// Return exp
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_COS, _VAR_TYPE_F64, false));
	}



//////////
//
// Function: CREATEOBJECT()
// Instantiates and instance of the indicated class.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pClassname	-- The name of the class
//     Note:  A future extension will allow parameters passed to the class's init() event
//
//////
// Returns:
//    Object		-- The class instance object is returned
//
//////
	SVariable* function_createobject(SThisCode* thisCode, SVariable* varClass)
	{
		s32			lnObjType;
		SObject*	obj;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varClass) || !iVariable_isTypeCharacter(varClass))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varClass), false);
				return(NULL);
			}


		//////////
        // It must be at least one character long
		//////
			if (varClass->value.length == 0)
				iError_reportByNumber(thisCode, _ERROR_EMPTY_STRING, iVariable_compRelated(thisCode, varClass), false);


		//////////
		// See if we know the class
		//////
			lnObjType = iiObj_getBaseclassType_byName(thisCode, varClass->value.data, varClass->value.length);
			if (lnObjType <= 0)
			{
				iError_report((cu8*)"Unknown class", false);
				return(NULL);
			}

			// Create our object
			obj = iObj_create(thisCode, lnObjType, NULL);
			if (!obj)
			{
				iError_report((cu8*)"Internal error on create object.", false);
				return(NULL);
			}


		//////////
        // Create our return result variable, which is a reference to the new object
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_OBJECT, NULL);
			if (!result)
			{
				iObj_delete(thisCode, &obj, true, true, true);
				iError_report((cu8*)"Internal error on create variable.", false);
				return(NULL);
			}

			// Store the object reference
			result->obj = obj;


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: CURDIR()
// Returns the current directory
//
//////
// Version 0.56
// Last Update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		none
//////
// Returns:
//		Character		-- Current directory
//////
	SVariable* function_curdir(SThisCode* thisCode)
	{
		u8			curdir[_MAX_PATH];
		SVariable*	result;


		// Get the current directory
		memset(curdir, 0, sizeof(curdir));
		GetCurrentDirectory(_MAX_PATH, (s8*)curdir);

		// Create the output variable
		result = iVariable_createAndPopulate(thisCode, _VAR_TYPE_CHARACTER, curdir, (u32)strlen(curdir));
		return(result);
	}




//////////
//
// Function: DATETIME()
// Returns the current local time, or uses the input variables to create the indicated datetime.
//
//////
// Version 0.56
// Last update:
//     Jul.10.2014
//////
// Change log:
//     Jul.10.2014 - Initial creation
//////
// Parameters:
//     pYear		-- (optional) Numeric, in the range 1600..2400
//     pMonth		-- (optional) Numeric, in the range 1..12
//     pDay			-- (optional) Numeric, in the range 1..(varies based on month+year, not more than 31)
//     pHour		-- (optional) Numeric, in the range 0..23
//     pMinute		-- (optional) Numeric, in the range 0..59
//     pSecond		-- (optional) Numeric, in the range 0..59
//     pMillisecond	-- (optional) Numeric, in the range 0..999
//
//////
// Returns:
//    Datetime		-- Current datetime(), or input converted to datetime
//
//////
	SVariable* function_datetime(SThisCode* thisCode, SVariable* varYear, SVariable* varMonth, SVariable* varDay, SVariable* varHour, SVariable* varMinute, SVariable* varSecond, SVariable* varMillisecond)
	{
		SVariable*	result;
		SDateTime*	dt;
		f32			lfJulian;
		u32			errorNum;
		bool		error;
		SYSTEMTIME	lst;


		// Have they provided us with data?
		if (!varYear)
		{
			// Nope, we are creating the current system time
			GetLocalTime(&lst);

		} else {
			// They have provided us datetime parameters.
			// Default to 01/01/1600 00:00:00.000 for any
			lst.wYear			= 1600;
			lst.wMonth			= 1;
			lst.wDay			= 1;
			lst.wHour			= 0;
			lst.wMinute			= 0;
			lst.wSecond			= 0;
			lst.wMilliseconds	= 0;


			//////////
			// pYear must be numeric, and in the range of 1600..2400
			//////
				if (iVariable_isValid(varYear))
				{
					// They gave us a pYear
					if (!iVariable_isTypeNumeric(varYear))
					{
						iError_report((cu8*)"Year must be numeric", false);
						return(NULL);
					}
					lst.wYear = (u16)iiVariable_getAs_s32(thisCode, varYear, false, &error, &errorNum);
					if (!error && (lst.wYear < 1600 || lst.wYear > 2400))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varYear), false);
						return(NULL);
					}
				}


			//////////
			// pMonth must be numeric, and in the range of 1..12
			//////
				if (iVariable_isValid(varMonth))
				{
					// They gave us a pMonth
					if (!iVariable_isTypeNumeric(varMonth))
					{
						iError_report((cu8*)"Month must be numeric", false);
						return(NULL);
					}
					lst.wMonth = (u16)iiVariable_getAs_s32(thisCode, varMonth, false, &error, &errorNum);
					if (!error && (lst.wMonth < 1 || lst.wMonth > 12))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varMonth), false);
						return(NULL);
					}
				}


			//////////
			// pDay must be numeric, and in a valid range for the year and month
			//////
				if (iVariable_isValid(varDay))
				{
					// They gave us a pDay
					if (!iVariable_isTypeNumeric(varDay))
					{
						iError_report((cu8*)"Day must be numeric", false);
						return(NULL);
					}
					lst.wDay = (u16)iiVariable_getAs_s32(thisCode, varDay, false, &error, &errorNum);
					if (!error && !iVariable_isDayValidForDate(lst.wYear, lst.wMonth, lst.wDay))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varDay), false);
						return(NULL);
					}
				}


			//////////
			// pHour must be numeric, and in the range of 0..23
			//////
				if (iVariable_isValid(varHour))
				{
					// They gave us a pHour
					if (!iVariable_isTypeNumeric(varHour))
					{
						iError_report((cu8*)"Hours must be numeric", false);
						return(NULL);
					}
					lst.wHour = (u16)iiVariable_getAs_s32(thisCode, varHour, false, &error, &errorNum);
					if (!error && (lst.wHour < 0 || lst.wHour > 23))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varHour), false);
						return(NULL);
					}
				}


			//////////
			// pMinute must be numeric, and in the range of 0..59
			//////
				if (iVariable_isValid(varMinute))
				{
					// They gave us a pMinute
					if (!iVariable_isTypeNumeric(varMinute))
					{
						iError_report((cu8*)"Minutes must be numeric", false);
						return(NULL);
					}
					lst.wMinute = (u16)iiVariable_getAs_s32(thisCode, varMinute, false, &error, &errorNum);
					if (!error && (lst.wMinute < 0 || lst.wMinute > 59))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varMinute), false);
						return(NULL);
					}
				}


			//////////
			// pSecond must be numeric, and in the range of 0..59
			//////
				if (iVariable_isValid(varSecond))
				{
					// They gave us a pSecond
					if (!iVariable_isTypeNumeric(varSecond))
					{
						iError_report((cu8*)"Seconds must be numeric", false);
						return(NULL);
					}
					lst.wSecond = (u16)iiVariable_getAs_s32(thisCode, varSecond, false, &error, &errorNum);
					if (!error && (lst.wSecond < 0 || lst.wSecond > 59))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varSecond), false);
						return(NULL);
					}
				}


			//////////
			// pMillisecond must be numeric, and in the range of 0..999
			//////
				if (iVariable_isValid(varMillisecond))
				{
					// They gave us a pMillisecond
					if (!iVariable_isTypeNumeric(varMillisecond))
					{
						iError_report((cu8*)"Milliseconds must be numeric", false);
						return(NULL);
					}
					lst.wMilliseconds = (u16)iiVariable_getAs_s32(thisCode, varMillisecond, false, &error, &errorNum);
					if (!error && (lst.wMilliseconds < 0 || lst.wMilliseconds > 999))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varMillisecond), false);
						return(NULL);
					}
				}
		}


		//////////
		// Convert lst.* into a VJr datetime variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_DATETIME, NULL);
			dt = (SDateTime*)result->value.data;

			// Date is stored as julian day number
			dt->julian	= iiVariable_julianDayNumber_fromYyyyMmDd(&lfJulian, lst.wYear, lst.wMonth, lst.wDay);

			// Time is stored as seconds since midnight
			dt->seconds = (f32)(lst.wHour * 60 * 60) + (f32)(lst.wMinute * 60) + (f32)lst.wSecond + ((f32)lst.wMilliseconds / 1000.0f);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: DTOR()
// Converts degrees to radians.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    DTOR(n) of the value in p1
//////
// Example:
//    ? DTOR(180)		&& Display 3.14
//////
    SVariable* function_dtor(SThisCode* thisCode, SVariable* varNumber)
    {
		// Return exp
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_DTOR, _VAR_TYPE_F64, false));
	}



//////////
//
// Function: EXP()
// Returns the value of e^x where x is a specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    EXP(n) of the value in p1
//////
// Example:
//    ? EXP(2)		&& Display 7.39
//////
    SVariable* function_exp(SThisCode* thisCode, SVariable* varNumber)
    {
		// Return exp
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_EXP, _VAR_TYPE_F64, false));
	}

	// Common numeric functions used for EXP(), LOG(), LOG10(), PI(), SQRT(), CEILING(), FLOOR(), DTOR(), RTOD().
    SVariable* ifunction_numbers_common(SThisCode* thisCode, SVariable* varNumber, u32 functionType, const u32 resultType, bool sameInputType)
    {
		f64			lfValue;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		// Is a number required?
		lfValue = 0.0;	// Assume no
		if (varNumber)
		{
			//////////
			// Must be numeric
			//////
				if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varNumber), false);
					return(NULL);
				}


			//////////
			// Convert to f64
			//////
				lfValue = iiVariable_getAs_f64(thisCode, varNumber, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);
					return(NULL);
				}
		}


		//////////
		// Compute numeric function
		//////
			switch (functionType)
			{

// SQRT()
				case _FP_COMMON_SQRT:

					//////////
					// Verify p1 >= 0
					//////
						if (lfValue < 0.0)
						{
							// Oops!
							iError_reportByNumber(thisCode, _ERROR_CANNOT_BE_NEGATIVE, iVariable_compRelated(thisCode, varNumber), false);
							return(NULL);
						}


					//////////
					// Compute sqrt
					//////
						lfValue = sqrt(lfValue);	
						break;

// EXP()
				case _FP_COMMON_EXP:
					lfValue = exp(lfValue);	
					break;

// PI()
				case _FP_COMMON_PI:
					lfValue = _MATH_PI;
					break;

// LOG()
// LOG10()
				case _FP_COMMON_LOG:
				case _FP_COMMON_LOG10:

					//////////
					// Verify p1 > 0
					//////
						if (lfValue <= 0.0)
						{
							// Oops!
							iError_reportByNumber(thisCode, _ERROR_CANNOT_BE_ZERO_OR_NEGATIVE, iVariable_compRelated(thisCode, varNumber), false);
							return(NULL);
						}


					//////////
					// Compute
					//////
						if (functionType == _FP_COMMON_LOG)		lfValue = log(lfValue);	
						else									lfValue = log10(lfValue);	
						break;

// CEILING()
				case _FP_COMMON_CEILING:
					lfValue = ceil(lfValue);
					break;

// FLOOR()
				case _FP_COMMON_FLOOR:
					lfValue = floor(lfValue);
					break;

// DTOR()
				case _FP_COMMON_DTOR:
					lfValue = lfValue * _MATH_PI180;
					break;

// RTOD()
				case _FP_COMMON_RTOD:
					lfValue = lfValue * _MATH_180PI;
					break;

// COS()
				case _FP_COMMON_COS:
					lfValue = cos(lfValue);
					break;

// SIN()
				case _FP_COMMON_SIN:
					lfValue = sin(lfValue);
					break;
				default:
					// Programmer error... this is an internal function and we should never get here
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varNumber), false);
					return(NULL);
			}


		//////////
		// Create output variable
		//////
			if (sameInputType)	result = iVariable_create(thisCode, varNumber->varType, NULL);
			else				result = iVariable_create(thisCode, resultType, NULL); 

			if (!result)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Set the value
		//////
			if (!iVariable_setNumeric_toNumericType(thisCode, result, NULL, &lfValue, NULL, NULL, NULL, NULL))
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);


		//////////
        // Return result
		//////
	        return result;   
	}


//////////
//
// Function: FLOOR()
// Returns the nearest integer that is less than or equal to the specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    FLOOR(n) of the value in p1
//////
// Example:
//    ? FLOOR(2.2)		&& Display 2
//////
    SVariable* function_floor(SThisCode* thisCode, SVariable* varNumber)
    {
        // Return floor
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_FLOOR, _VAR_TYPE_S64, propGet_settings_ncset_ceilingFloor(_settings)));
	}


//////////
//
// Function: FORCEEXT()
// Takes a pathname and forces the file extension to the new value
//
//////
// Version 0.56
// Last update:
//     Mar.12.2015
//////
// Change log:
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewExtension	-- The new file extension to force.
//////
// Returns:
//    The input pathname with the next extension.
//////
	SVariable* function_forceext(SThisCode* thisCode, SVariable* varPathname, SVariable varNewExtension)
	{
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		return(NULL);
	}




//////////
//
// Function: FORCEFNAME()
// Takes a pathname and forces the filename to the new value
//
//////
// Version 0.56
// Last update:
//     Mar.12.2015
//////
// Change log:
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewFilename	-- The new filename to force.
//////
// Returns:
//    The input pathname with the filename.
//////
	SVariable* function_forcefname(SThisCode* thisCode, SVariable* varPathname, SVariable varNewFilename)
	{
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		return(NULL);
	}




//////////
//
// Function: FORCEEXT()
// Takes a pathname and forces the path to the new value
//
//////
// Version 0.56
// Last update:
//     Mar.12.2015
//////
// Change log:
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewPathname	-- The new pathname to force.
//////
// Returns:
//    The input pathname with the new path.
//////
	SVariable* function_forcepath(SThisCode* thisCode, SVariable* varPathname, SVariable varNewPathname)
	{
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		return(NULL);
	}




//////////
//
// Function: FORCESTEM()
// Takes a pathname and forces the stem to the new value
//
//////
// Version 0.56
// Last update:
//     Mar.12.2015
//////
// Change log:
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewStem		-- The new stem to force.
//////
// Returns:
//    The input pathname with the new stem.
//////
	SVariable* function_forcestem(SThisCode* thisCode, SVariable* varPathname, SVariable varNewStem)
	{
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		return(NULL);
	}




//////////
//
// Function: GRAYSCALE()
// Grayscales a color.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor			-- The color to grayscale.
//     varPercentage	-- (Optional) A percentage to grayscale (0.05 leaves almost all the color data, 0.95 is almost completely grayscaled)
//////
// Returns:
//    The input pathname with the new stem.
//////
	SVariable* function_grayscale(SThisCode* thisCode, SVariable* varColor, SVariable* varPercentage)
	{
		return(ifunction_colorize_common(thisCode, varColor, NULL, varPercentage, false));
	}




//////////
//
// Function: GRN()
// Retrieves the green channel from an RGBA or BGRA color.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Numeric, a color (0..(2^32)-1)
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
	SVariable* function_grn(SThisCode* thisCode, SVariable* varColor)
	{
		return(ifunction_color_common(thisCode, varColor, 0x0000ff00, 8));
	}




//////////
//
// Function: INT()
// Takes a value and returns the INT(n) of that value.
//
//////
// Version 0.56
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    INT(n) of the value in p1
//////
    SVariable* function_int(SThisCode* thisCode, SVariable* varNumber)
    {
		f64			fValue;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			if (iVariable_isTypeFloatingPoint(varNumber))
			{
				fValue = iiVariable_getAs_f64(thisCode, varNumber, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);	return(NULL);	}

				// Convert to S64
				result = iVariable_create(thisCode, _VAR_TYPE_S64, NULL);
				*(s64*)result->value.data = (s64)fValue;

			} else {
				// Copy whatever it already is
				result = iVariable_create(thisCode, varNumber->varType, NULL);
				iDatum_duplicate(&result->value, &varNumber->value);
			}


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Function: JUSTDRIVE()
// Returns the drive letter from the input pathname
//
//////
// Version 0.56
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The drive component of the pathname, or the current drive if it wasn't specified, ("c:" of "c:\path\to\sample.txt")
//////
	SVariable* function_justdrive(SThisCode* thisCode, SVariable* varString)
	{
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 2)
			{
				// If it is of the form "x:"... then we return the left two-most characters
				if (varString->value.data_s8[1] == ':')
				{
					// We have a drive
					ptr = varString->value.data_u8;
				}

			} else {
				// It's too short and cannot have a drive, so we'll initialize an empty variable
				ptr = NULL;
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
				iDatum_duplicate(&result->value, ptr, 2);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: JUSTEXT()
// Returns the file extension from the input pathname
//
//////
// Version 0.56
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file extension component, or an empty string if one was not specified, ("txt" of "c:\path\to\sample.txt")
//////
	SVariable* function_justext(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnI, lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr		= NULL;
			result	= iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '.')
					{
						// We found a period
						ptr = varString->value.data_u8 + lnI + 1;
						break;
					}
				}
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
				iDatum_duplicate(&result->value, ptr, lnLength);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: JUSTFNAME()
// Returns the file name from the input pathname
//
//////
// Version 0.56
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file name portion of the pathname ("sample.txt" of "c:\path\to\sample.txt")
//////
	SVariable* function_justfname(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnI, lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr		= NULL;
			result	= iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '\\')
					{
						// We found a backslash
						break;
					}
				}

				// Set our pointer to the filename
				ptr			= varString->value.data_u8 + lnI + ((lnI > 0) ? 1 : 0);
				lnLength	+= ((lnI > 0) ? 0 : 1);
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
				iDatum_duplicate(&result->value, ptr, lnLength);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: JUSTPATH()
// Returns the path from the input pathname
//
//////
// Version 0.56
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file path of the pathname ("c:\path\to" of "c:\path\to\sample.txt")
//////
	SVariable* function_justpath(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr		= NULL;
			result	= iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnLength = varString->value.length - 1; lnLength >= 0; lnLength--)
				{
					if (varString->value.data_u8[lnLength] == '\\')
					{
						// We found a backslash
						ptr = varString->value.data_u8;
						if (lnLength == 0)
							++lnLength;
						break;
					}
				}
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
				iDatum_duplicate(&result->value, ptr, lnLength);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: JUSTSTEM()
// Returns the stem (filename left of dot-extension) from the input pathname
//
//////
// Version 0.56
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//		varPostfixWidth	-- (optional) Numeric, the number of extra spaces to postfix pad the juststem() result with
//////
// Returns:
//		Character		-- The file name portion of the pathname ("sample" of "c:\path\to\sample.txt")
//////
	SVariable* function_juststem(SThisCode* thisCode, SVariable* varString, SVariable* varPostfixWidth)
	{
		s32			lnI, lnLength, lnPostfixWidth;
		u8*			ptr;
		bool		error;
		u32			errorNum;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// If parameter 2 was specified, it must be numeric
		//////
			if (varPostfixWidth)
			{
				if (!iVariable_isValid(varPostfixWidth) || !iVariable_isTypeNumeric(varPostfixWidth))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varPostfixWidth), false);
					return(NULL);
				}
				// Grab the postfix width
				lnPostfixWidth = iiVariable_getAs_s32(thisCode, varPostfixWidth, false, &error, &errorNum);

			} else {
				// No postfix
				lnPostfixWidth = 0;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr		= NULL;
			result	= iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--)
				{
					if (varString->value.data_u8[lnI] == '\\')
					{
						// We found a period
						break;
					}
				}

				// Set our pointer to the filename
				ptr = varString->value.data_u8 + lnI + ((lnI > 0) ? 1 : 0);
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
			{
				// Search forward until we find a period, or the end
				for (lnLength = ((lnI == 0) ? 0 : -1); lnI < varString->value.length; lnI++, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '.')
						break;
				}

				// Copy the stem portion
				iDatum_allocateSpace(&result->value, lnLength + lnPostfixWidth);
				if (result->value.data && result->value.length == lnLength + lnPostfixWidth)
				{
					// Copy the ptr content
					memcpy(result->value.data_s8, ptr, lnLength);

					// Postfix width is populated with spaces
					if (lnPostfixWidth != 0)
						memset(result->value.data_s8 + lnLength, 32, lnPostfixWidth);
				}
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: LEFT()
// Returns the left N characters of a string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//     pCount		-- Numeric, the number of characters to copy
//
//////
// Returns:
//    Character		-- The string of the left N characters
//////
	SVariable* function_left(SThisCode* thisCode, SVariable* varString, SVariable* varCount)
	{
		s32			lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be nmumeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Copy as much of the source string as will fit
		//////
			if (lnLength > 0)
				iDatum_duplicate(&result->value, varString->value.data_u8, min(varString->value.length, lnLength));


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: LEN()
// Returns the length of the string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to return the length from
//
//////
// Returns:
//    Numeric		-- The length of the string
//////
	SVariable* function_len(SThisCode* thisCode, SVariable* varString)
	{
        SVariable* result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
		// Populate based on the length
		//////
			*(s32*)result->value.data = varString->value.length;


		//////////
        // Return our converted result
		//////
	        return result;
	}


//////////
//
// Function: LOG()
// Returns the natural logarithm (base e) of the specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    LOG(n) of the value in p1
//////
// Example:
//    ? LOG(2)		&& Display 0.69
//////
    SVariable* function_log(SThisCode* thisCode, SVariable* varNumber)
    {
        // Return log
		return ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_LOG, _VAR_TYPE_F64, false);   
	}




//////////
//
// Function: LOG10()
// Returns the common logarithm (base 10) of the specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    LOG10(n) of the value in p1
//////
// Example:
//    ? LOG10(2)		&& Display 0.30
//////
    SVariable* function_log10(SThisCode* thisCode, SVariable* varNumber)
    {
        // Return log10
		return ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_LOG10, _VAR_TYPE_F64, false);
	}




//////////
//
// Function: LOWER()
// Converts every character in the string to lowercase.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to lower
//
//////
// Returns:
//    Character		-- The string with all lowercase characters converted to lowercase
//////
	SVariable* function_lower(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnI;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Copy the source string
		//////
	        iDatum_duplicate(&result->value, &varString->value);


		//////////
		// Lower every character
		//////
			for (lnI = 0; lnI < result->value.length; lnI++)
			{
				if (result->value.data[lnI] >= 'A' && result->value.data[lnI] <= 'Z')
					result->value.data[lnI] += 0x20;
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: LTRIM()
// Trims spaces off the start of the string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//
//////
// Returns:
//    Character		-- The string with any leading spaces removed
//////
	SVariable* function_ltrim(SThisCode* thisCode, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2)
	{
		return(ifunction_trim_common(thisCode, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, true, false));
	}




//////////
//
// Function: MALP()
// Returns the 1.0 - ((255 - ALP()) / 255) calculation.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Color to extract alpha channel from
//
//////
// Returns:
//    Integer in the range 0..255, or floating point in the range 0.0 to 1.0
//
//////
// Usage:
//   ? malp(lnColor)          && Returns floating point
//   ? malp(lnColor, .t.)     && Returns integer
//   ? malp(lnColor, .f.)     && Returns floating point
//////
	SVariable* function_malp(SThisCode* thisCode, SVariable* varColor, SVariable* varAsInteger)
	{
		u32			lnColor;
		f32			lfMalp;
		bool		llAsInteger;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varColor), false);
				return(NULL);
			}


		//////////
		// If varAsInteger exists, it must be logical
		//////
			if (varAsInteger)
			{
				if (!iVariable_isFundamentalTypeLogical(varAsInteger))
				{
					iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varColor), false);
					return(NULL);
				}

				// Grab the value
				llAsInteger = iiVariable_getAs_bool(thisCode, varAsInteger, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varColor), false);	return(NULL);	}

			} else {
				// Set it to false
				llAsInteger = false;
			}


		//////////
		// Grab the value
		//////
			lnColor = iiVariable_getAs_u32(thisCode, varColor, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varColor), false);	return(NULL);	}


		//////////
		// Apply the mask and shift
		//////
			lnColor &= 0xff0000000;
			lnColor >>= 24;
			if (llAsInteger)
			{
				// Unsigned 32-bit integer
				lnColor	= 255 - lnColor;
				result	= iVariable_create(thisCode, _VAR_TYPE_U32, NULL);

			} else {
				// Floating point
				lfMalp	= 1.0f - ((255.0f - (f32)lnColor) / 255.0f);
				result	= iVariable_create(thisCode, _VAR_TYPE_F32, NULL);
			}


		//////////
		// Construct our result
		//////
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Populate and return our result
		//////
			if (llAsInteger)		*result->value.data_u32 = lnColor;
			else					*result->value.data_f32 = lfMalp;
			return(result);
	}




//////////
//
// Function: MAX()
// Returns the maximum value of the two inputs.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pLeft		-- Left-side value, first parameter
//     pRight		-- Right-side value, second parameter
//
//////
// Returns:
//    Either pLeft or pRight copied, depending on which is greater.
//    If they're equal, a copy of pLeft is returned.
//
//////
	SVariable* function_max(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight)
	{
		bool		llLeft;
		s32			lnLeft32, lnRight32;
		s64			lnLeft64, lnRight64;
		f64			lfLeft64, lfRight64;
		bool		error;
		u32			errorNum;
		SDateTime*	dtLeft;
		SDateTime*	dtRight;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varLeft))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varLeft), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varRight))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varRight), false);
				return(NULL);
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_fundamentalType(thisCode, varLeft) != iVariable_fundamentalType(thisCode, varRight))
			{
				// Operand mismatch
				iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_compRelated(thisCode, varRight), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			llLeft = false;
			switch (varLeft->varType)
			{
				case _VAR_TYPE_DATE:			// Note:  Dates are stored internally as YYYYMMDD, so they can be directly compared
				case _VAR_TYPE_CHARACTER:
					if (varLeft->value.length == 0 || varRight->value.length == 0)
					{
						// At least one of them is null, return the left
						llLeft = true;

					} else {
						// They both have a non-zero length
						switch (_memicmp(varLeft->value.data, varRight->value.data, min(varLeft->value.length, varRight->value.length)))
						{
							case -1:
							case 0:
								// Left is less than or equal to right
								llLeft = true;
								break;

							default:
								// Right is less
								break;
						}
					}
					break;

				case _VAR_TYPE_DATETIME:
					dtLeft	= (SDateTime*)varLeft->value.data;
					dtRight	= (SDateTime*)varRight->value.data;
					if (dtLeft->julian < dtRight->julian)
					{
						// Left is less
						llLeft = true;

					} else if (dtLeft->julian > dtRight->julian) {
						// Right is less

					} else {
						// They are equal, compare the time
						if (dtLeft->seconds <= dtRight->seconds)
						{
							// Left is less or equal
							llLeft = true;

						} else {
							// Right is less
						}
					}
					break;

				default:
					if (iVariable_isTypeBig(varLeft) || iVariable_isTypeBig(varRight))
					{
						// It's a character compared to a character
						iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
						return(NULL);

					} else if (iVariable_isTypeFloatingPoint(varLeft) || iVariable_isTypeFloatingPoint(varRight)) {
						// Comparing floating point values
						lfLeft64	= iiVariable_getAs_f64(thisCode, varLeft, false, &error, &errorNum);
						if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

						lfRight64	= iiVariable_getAs_f64(thisCode, varRight, false, &error, &errorNum);
						if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

						// Perform the test
						if (lfLeft64 <= lfRight64)
						{
							// Left is less
							llLeft = true;

						} else {
							// Right is less
						}

					} else if (iVariable_isTypeNumeric(varLeft) || iVariable_isTypeNumeric(varRight)) {
						// Comparing numerics
						if (iVariable_isNumeric64Bit(varLeft) || iVariable_isNumeric64Bit(varRight))
						{
							// It requires a 64-bit signed compare
							lnLeft64	= iiVariable_getAs_s64(thisCode, varLeft, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

							lnRight64	= iiVariable_getAs_s64(thisCode, varRight, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

							// Perform the test
							if (lnLeft64 <= lnRight64)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}

						} else {
							// It can be done in a 32-bit signed compare
							lnLeft32	= iiVariable_getAs_s32(thisCode, varLeft, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

							lnRight32	= iiVariable_getAs_s32(thisCode, varRight, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

							// Perform the test
							if (lnLeft32 <= lnRight32)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}
						}

					} else {
						// We cannot compare these types
						iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_compRelated(thisCode, varLeft), false);
						return(NULL);
					}
			}
			// When we get here, llLeft is populated with our intent
			if (llLeft)
			{
				// Left is less, so duplicate right
				result = iVariable_create(thisCode, varRight->varType, NULL);
				iDatum_duplicate(&result->value, &varRight->value);

			} else {
				// Right is less, so duplicate left
				result = iVariable_create(thisCode, varLeft->varType, NULL);
				iDatum_duplicate(&result->value, &varLeft->value);
			}

			// Indicate our result
			return(result);
	}




//////////
//
// Function: MIN()
// Returns the minimum value of the two inputs.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pLeft		-- Left-side value, first parameter
//     pRight		-- Right-side value, second parameter
//
//////
// Returns:
//    Either pLeft or pRight copied, depending on which is less.
//    If they're equal, a copy of pLeft is returned.
//
//////
	SVariable* function_min(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight)
	{
		bool		llLeft;
		s32			lnLeft32, lnRight32;
		s64			lnLeft64, lnRight64;
		f64			lfLeft64, lfRight64;
		bool		error;
		u32			errorNum;
		SDateTime*	dtLeft;
		SDateTime*	dtRight;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varLeft))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varLeft), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varRight))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varRight), false);
				return(NULL);
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_fundamentalType(thisCode, varLeft) != iVariable_fundamentalType(thisCode, varRight))
			{
				// Operand mismatch
				iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_compRelated(thisCode, varRight), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			llLeft = false;
			switch (varLeft->varType)
			{
				case _VAR_TYPE_DATE:			// Note:  Dates are stored internally as YYYYMMDD, so they can be directly compared
				case _VAR_TYPE_CHARACTER:
					if (varLeft->value.length == 0 || varRight->value.length == 0)
					{
						// At least one of them is null, return the left
						llLeft = true;

					} else {
						// They both have a non-zero length
						switch (_memicmp(varLeft->value.data, varRight->value.data, min(varLeft->value.length, varRight->value.length)))
						{
							case -1:
							case 0:
								// Left is less than or equal to right
								llLeft = true;
								break;

							default:
								// Right is less
								break;
						}
					}
					break;

				case _VAR_TYPE_DATETIME:
					dtLeft	= (SDateTime*)varLeft->value.data;
					dtRight	= (SDateTime*)varRight->value.data;
					if (dtLeft->julian < dtRight->julian)
					{
						// Left is less
						llLeft = true;

					} else if (dtLeft->julian > dtRight->julian) {
						// Right is less

					} else {
						// They are equal, compare the time
						if (dtLeft->seconds <= dtRight->seconds)
						{
							// Left is less or equal
							llLeft = true;

						} else {
							// Right is less
						}
					}
					break;

				default:
					if (iVariable_isTypeBig(varLeft) || iVariable_isTypeBig(varRight))
					{
						// It's a character compared to a character
						iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
						return(NULL);

					} else if (iVariable_isTypeFloatingPoint(varLeft) || iVariable_isTypeFloatingPoint(varRight)) {
						// Comparing floating point values
						lfLeft64	= iiVariable_getAs_f64(thisCode, varLeft, false, &error, &errorNum);
						if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

						lfRight64	= iiVariable_getAs_f64(thisCode, varRight, false, &error, &errorNum);
						if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

						// Perform the test
						if (lfLeft64 <= lfRight64)
						{
							// Left is less
							llLeft = true;

						} else {
							// Right is less
						}

					} else if (iVariable_isTypeNumeric(varLeft)) {
						// Comparing numerics
						if (iVariable_isNumeric64Bit(varLeft) || iVariable_isNumeric64Bit(varRight))
						{
							// It requires a 64-bit signed compare
							lnLeft64	= iiVariable_getAs_s64(thisCode, varLeft, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

							lnRight64	= iiVariable_getAs_s64(thisCode, varRight, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

							// Perform the test
							if (lnLeft64 <= lnRight64)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}

						} else {
							// It can be done in a 32-bit signed compare
							lnLeft32	= iiVariable_getAs_s32(thisCode, varLeft, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varLeft), false);	return(NULL);	}

							lnRight32	= iiVariable_getAs_s32(thisCode, varRight, false, &error, &errorNum);
							if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRight), false);	return(NULL);	}

							// Perform the test
							if (lnLeft32 <= lnRight32)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}
						}

					} else {
						// We cannot compare these types
						iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_compRelated(thisCode, varLeft), false);
						return(NULL);
					}
			}
			// When we get here, llLeft is populated with our intent
			if (llLeft)
			{
				// Left is less, so copy left
				result = iVariable_create(thisCode, varLeft->varType, NULL);
				iDatum_duplicate(&result->value, &varLeft->value);

			} else {
				// Right is less, so copy right
				result = iVariable_create(thisCode, varRight->varType, NULL);
				iDatum_duplicate(&result->value, &varRight->value);
			}

			// Indicate our result
			return(result);
	}





//////////
//
// Function: MOD()
// Divides one numeric expression by another numeric expression and returns the remainder.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.08.2015
//////
// Change log:
//     Mar.14.2015 - Fix bug when lfMod = 0 by Stefano D'Amico			// https://github.com/RickCHodgin/libsf/issues/2
//     Mar.08.2015 - Merge into main by Rick C. Hodgin, reformatting
//     Feb.28.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    nDividend		-- Specifies the dividend
//    nDivisor		-- Specifies the divisor
//
//////
// Returns:
//    Numeric		-- Returns the remainder
//////
// Example:
//    ? MOD(5, 2)      && 1
//    ? MOD(5, -2)     && -1
//    ? MOD(5.3, 2)    && 1.3
//    ? MOD(5.3, -2)   && -0.7
//////
	SVariable* function_mod(SThisCode* thisCode, SVariable* varDividend, SVariable* varDivisor)
	{
		f64			lfDividend, lfDivisor, lfMod;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varDividend) || !iVariable_isTypeNumeric(varDividend))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varDividend), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varDivisor) || !iVariable_isTypeNumeric(varDivisor))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varDivisor), false);
				return(NULL);
			}


		//////////
		// Grab the dividend
		//////
			if (iVariable_isTypeFloatingPoint(varDividend))
			{
				lfDividend = iiVariable_getAs_f64(thisCode, varDividend, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDividend), false);	return(NULL);	}

			} else {
				if (iVariable_isNumeric64Bit(varDividend))
				{
					lfDividend = (f64)iiVariable_getAs_s64(thisCode, varDividend, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDividend), false);	return(NULL);	}

				} else {
					lfDividend = (f64)iiVariable_getAs_s32(thisCode, varDividend, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDividend), false);	return(NULL);	}
				}
			}


		//////////
		// Grab the divisor
		//////
			if (iVariable_isTypeFloatingPoint(varDivisor))
			{
				lfDivisor = iiVariable_getAs_f64(thisCode, varDivisor, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDivisor), false);	return(NULL);	}

			} else {
				if (iVariable_isNumeric64Bit(varDivisor))
				{
					lfDivisor = (f64)iiVariable_getAs_s64(thisCode, varDivisor, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDivisor), false);	return(NULL);	}

				} else {
					lfDivisor = (f64)iiVariable_getAs_s32(thisCode, varDivisor, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDivisor), false);	return(NULL);	}
				}
			}


		//////////
		// Verify divisor not 0
		//////
			if (lfDivisor == 0.0)
			{
				// Oops!
				iError_reportByNumber(thisCode, _ERROR_DIVISION_BY_ZERO, iVariable_compRelated(thisCode, varDivisor), false);
				return(NULL);
			}


		//////////
		// Compute
		//////
			lfMod = fmod(lfDividend, abs(lfDivisor));
			if (lfDivisor < 0 && lfMod != 0.0)			// Mar.14.2015
				lfMod += lfDivisor;


		//////////
        // Create the return result
		//////
	        result = iVariable_create(thisCode, varDividend->varType, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}

		//////////
        // Populate the return value
		//////
			if (!iVariable_set_f64_toExistingType(thisCode, result, lfMod))
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
        // Return our result
		//////
	        return result;
	}




//////////
//
// Function: NCSET()
// Nuance compatibility settings. Used to enable or disable enhancements
// in VXB which may not be present in other xbase languages.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 -- Initial creation
//////
// Parameters:
//    varIndex		-- The index to set
//    varP1..varP6	-- Various, depends on the indexed function's requirements
//
//////
// Returns:
//    s32			-- The number of times
//////
	SVariable* function_ncset(SThisCode* thisCode, SVariable* varIndex, SVariable* varP1, SVariable* varP2, SVariable* varP3, SVariable* varP4, SVariable* varP5, SVariable* varP6)
	{
		s32			lnIndex;
		bool		llEnabled, llNewValue;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// nIndex must be numeric
		//////
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);
			}
			lnIndex = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);	return(NULL);	}


		//////////
		// Create the return variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_LOGICAL, NULL);
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);
			}


		//////////
		// What function are they requesting?
		//////
			// Based on the index, set the value
			switch (lnIndex)
			{
				//////////
				// SIGN(), SIGN2()
				//////
					case _NCSET_SIGN_SIGN2:
						// Get the value
						llEnabled = propGet_settings_ncset_signSign2(_settings);
						if (varP1)
						{
							// They are setting the value
							if (iVariable_isFundamentalTypeLogical(varP1))
							{
								// Obtain its value as a logical
								llNewValue = iiVariable_getAs_bool(thisCode, varP1, false, &error, &errorNum);
								if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);	return(NULL);	}

								// Set the new value
								propSet_settings_ncset_signSign2_fromBool(_settings, llNewValue);

							} else {
								// The variable is not a type that can be processed as logical
								iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varP1), false);
								return(NULL);
							}
						}
						break;


				//////////
				// CEILING(), FLOOR()
				//////
					case _NCSET_CEILING_FLOOR:
						// Get the value
						llEnabled = propGet_settings_ncset_ceilingFloor(_settings);
						if (varP1)
						{
							// They are setting the value
							if (iVariable_isFundamentalTypeLogical(varP1))
							{
								// Obtain its value as a logical
								llNewValue = iiVariable_getAs_bool(thisCode, varP1, false, &error, &errorNum);
								if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);	return(NULL);	}

								// Set the new value
								propSet_settings_ncset_ceilingFloor_fromBool(_settings, llNewValue);

							} else {
								// The variable is not a type that can be processed as logical
								iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varP1), false);
								return(NULL);
							}
						}
						break;


				//////////
				// Alpha channel is opaque in RGB() and BGR() colors
				//////
					case _NCSET_RGBA_ALPHA_IS_OPAQUE:
						// Get the value
						llEnabled = propGet_settings_ncset_alphaIsOpaque(_settings);
						if (varP1)
						{
							// They are setting the value
							if (iVariable_isFundamentalTypeLogical(varP1))
							{
								// Obtain its value as a logical
								llNewValue = iiVariable_getAs_bool(thisCode, varP1, false, &error, &errorNum);
								if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);	return(NULL);	}

								// Set the new value
								propSet_settings_ncset_alphaIsOpaque_fromBool(_settings, llNewValue);

							} else {
								// The variable is not a type that can be processed as logical
								iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varP1), false);
								return(NULL);
							}
						}
						break;

				default:
					// Unrecognized option
					iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_compRelated(thisCode, varIndex), false);
					return(NULL);
			}


		//////////
		// Set the result based on the value, and return it
		//////
			*result->value.data_s8 = ((llEnabled) ? _LOGICAL_TRUE : _LOGICAL_FALSE);
			return(result);
	}




//////////
//
// Function: OCCURS(), and OCCURSC()
// Counts the number of times the first parameter is found in the second, and
// optionally with regards to case.
//
//////
// Version 0.56
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//    pNeedle		-- The string they're looking for
//    pHaystack		-- The string being searched
//
//////
// Returns:
//    s32			-- The number of times
//////
	SVariable* function_occurs(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack)
	{
		u32			lnFoundCount;
		SVariable*	result;


		// Compute the found count
		result = ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, NULL, true, false, &lnFoundCount);
		if (result)
		{
			// Update the return variable
			*(s32*)result->value.data_s32 = lnFoundCount;
		}

		// Return our result
		return(result);
	}

	SVariable* function_occursc(SThisCode* thisCode, SVariable* varNeedle, SVariable* varHaystack)
	{
		u32			lnFoundCount;
		SVariable*	result;


		// Compute the found count
		result = ifunction_at_occurs_common(thisCode, varNeedle, varHaystack, NULL, false, false, &lnFoundCount);
		if (result)
		{
			// Update the return variable
			*(s32*)result->value.data_s32 = lnFoundCount;
		}

		// Return our result
		return(result);
	}




//////////
//
// Function: PADC(), PADL(), and PADR()
//
// and lowercases everything else.
//
//////
// Version 0.56
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pExpression		-- The input, converted to character, and then aligned
//     pResultSize		-- The size of the result
//     pPadCharacter	-- Optional, the character to use, if unspecified then uses SPACE(1)
//
//////
// Returns:
//    Character         -- The string is converted from whatever it was to character, and
//                         then padded to its destination size. If the string is larger than
//                         the destination, then it remains as it is.
//////
	SVariable* function_padc(SThisCode* thisCode, SVariable* varExpression, SVariable* varResultSize, SVariable* varPadCharacter)
	{
		return(ifunction_pad_common(thisCode, varExpression, varResultSize, varPadCharacter, true, true));
	}

	SVariable* function_padl(SThisCode* thisCode, SVariable* varExpression, SVariable* varResultSize, SVariable* varPadCharacter)
	{
		return(ifunction_pad_common(thisCode, varExpression, varResultSize, varPadCharacter, true, false));
	}

	SVariable* function_padr(SThisCode* thisCode, SVariable* varExpression, SVariable* varResultSize, SVariable* varPadCharacter)
	{
		return(ifunction_pad_common(thisCode, varExpression, varResultSize, varPadCharacter, false, true));
	}

	SVariable* ifunction_pad_common(SThisCode* thisCode, SVariable* varExpression, SVariable* varResultSize, SVariable* varPadCharacter, bool tlPadLeft, bool tlPadRight)
	{
		u32			errorNum;
		s32			lnI, lnResultSize, lnCopyStart, lnPadLeftStopper, lnPadRightStart, lnPadRightStopper;
		bool		error;
		SVariable*	tempVar;
		SVariable*	result;


		//////////
        // Make sure our parameters are correct
		//////
			if (!tlPadLeft && !tlPadRight)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Parameter 1 must be valid
		//////
			if (!iVariable_isValid(varExpression))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, NULL, false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varResultSize) || !iVariable_isTypeNumeric(varResultSize))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varResultSize), false);
				return(NULL);
			}
			lnResultSize = iiVariable_getAs_s32(thisCode, varResultSize, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varResultSize), false);	return(NULL);	}


		//////////
		// Parameter 3 is optional, but if present...
		//////
			if (iVariable_isValid(varPadCharacter))
			{
				// ...it must be character
				if (!iVariable_isTypeCharacter(varPadCharacter))
				{
					iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varPadCharacter), false);
					return(NULL);
				}

				// Validate the pad character is at least one character long
				if (varPadCharacter->value.length == 0)
				{
					iError_report((cu8*)"Parameter 3 must be at least one character", false);
					return(NULL);
				}

			} else {
				// The first occurrence is what we're after
				varPadCharacter = varConstant_space;
			}


		//////////
		// Create the return variable
		//////
			tempVar = iVariable_convertForDisplay(thisCode, varExpression);

			// If it wasn't created, or it's already as long or longer than its target, return it
			if (!tempVar || tempVar->value.length >= lnResultSize)
				return(tempVar);

			// If we get here, the result will be needed
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			iDatum_allocateSpace(&result->value, lnResultSize);


		//////////
		// Determine where the string should go
		//////
			if (tlPadLeft && tlPadRight)
			{
				// Pad both
				lnCopyStart			= (lnResultSize - tempVar->value.length) / 2;
				lnPadLeftStopper	= lnCopyStart;
				lnPadRightStart		= lnCopyStart + tempVar->value.length;
				lnPadRightStopper	= lnResultSize;

			} else if (tlPadLeft) {
				// Pad left
				lnCopyStart			= lnResultSize - tempVar->value.length;
				lnPadLeftStopper	= lnCopyStart;
				lnPadRightStart		= -1;
				lnPadRightStopper	= -1;

			} else {
				// Pad right
				lnCopyStart			= 0;
				lnPadLeftStopper	= -1;
				lnPadRightStart		= tempVar->value.length;
				lnPadRightStopper	= lnResultSize;
			}


		//////////
		// Pad left
		//////
			if (lnPadLeftStopper >= 1)
			{
				// Iterate through every cycle required to populate the left side
				for (lnI = 0; lnI < lnPadLeftStopper; lnI += varPadCharacter->value.length)
				{
					// Copy this string, or as much of it will fit
					memcpy(result->value.data + lnI, varPadCharacter->value.data, min(lnPadLeftStopper - lnI, varPadCharacter->value.length));
				}
			}


		//////////
		// Pad right
		//////
			if (lnPadRightStopper >= 1)
			{
				// Iterate through every cycle required to populate the right side
				for (lnI = lnPadRightStart; lnI < lnPadRightStopper; lnI += varPadCharacter->value.length)
				{
					// Copy this string, or as much of it will fit
					memcpy(result->value.data + lnI, varPadCharacter->value.data, min(lnPadRightStopper - lnI, varPadCharacter->value.length));
				}
			}


		//////////
		// Copy the source string and delete the source string variable
		//////
			// Copy the string
			memcpy(result->value.data + lnCopyStart, tempVar->value.data, tempVar->value.length);

			// Delete our temporary variable
			iVariable_delete(thisCode, tempVar, true);


		//////////
		// Indicate our status
		//////
			return(result);
	}




//////////
//
// Function: PI()
// Returns the numeric constant pi.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     none
//////
// Returns:
//    Numeric		-- Returns the numeric constant pi
//////
// Example:
//    ? pi()				&& Displays 3.14
//////
	SVariable* function_pi(SThisCode* thisCode)
	{
		// Return pi
		return ifunction_numbers_common(thisCode, NULL, _FP_COMMON_PI, _VAR_TYPE_F64, false);
	}




//////////
//
// Function: PROPER()
// Converts the first character after every space to upper-case,
// and lowercases everything else.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to proper
//
//////
// Returns:
//    Character		-- The string with all words proper'd (if I can use that as a verb)
//////
	SVariable* function_proper(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnI;
		bool		llUpperNext;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Copy the source string
		//////
	        iDatum_duplicate(&result->value, &varString->value);


		//////////
		// Upper every first character after a space, and lower every character
		//////
			llUpperNext = true;
			for (lnI = 0; lnI < result->value.length; lnI++)
			{
				// Spaces are treated differently
				if (result->value.data[lnI] == 32)
				{
					// We've found a space, the next one will be upper-case
					llUpperNext = true;

				} else {
					// We're on data
					if (llUpperNext)
					{
						// Make this one uppercase if it's lower
						llUpperNext = false;
						if (result->value.data[lnI] >= 'a' && result->value.data[lnI] <= 'z')
							result->value.data[lnI] -= 0x20;

					} else {
						// Make this one lowercase if it's upper
						if (result->value.data[lnI] >= 'A' && result->value.data[lnI] <= 'Z')
							result->value.data[lnI] += 0x20;
					}
				}
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: RANGER()
// Force Into Range.  The function is the equivalent of xResult = MIN(MAX(xVar, xMin), xMax)).
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.14.2015
//////
// Change log:
//     Mar.14.2015 - GitHub commit by Rick C. Hodgin, refactoring into varExpression type
//     Mar.13.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    varExpression	-- Specifies the expression to valuate
//    varMin		-- Specifies the min range
//    varMin		-- Specifies the max range
//
//////
// Returns:
//   Returns the value forced into the range xMin..xMax
//////
// Example:
//  x = 10
//	? x                            && Displays 10
//	? RANGER(x, 20, 80)            && Displays 20
//	x = RANGER(x, 20, 80)          && Can be used as assignment
//	? x							   && Displays 20
//////
	SVariable* function_ranger(SThisCode* thisCode, SVariable* varExpression, SVariable* varMin, SVariable* varMax)
	{
		SVariable*	tempMin;
		SVariable*	tempMax;
		SVariable*	tempResult1;
		SVariable*	tempResult2;
		SVariable*	result;


		//////////
		// Test Parameter 1
		//////
			if (!iVariable_isValid(varExpression))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varExpression), false);
				return(NULL);
			}


		//////////
		// Test Parameter 2
		//////
			if (!iVariable_isValid(varMin))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varMin), false);
				return(NULL);
			}


		//////////
		// Test Parameter 3 
		//////
			if (!iVariable_isValid(varMax))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varMax), false);
				return(NULL);
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_fundamentalType(thisCode, varExpression) != iVariable_fundamentalType(thisCode, varMin))
			{
				// Operand mismatch
				iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_compRelated(thisCode, varMin), false);
				return(NULL);
			}	
			if (iVariable_fundamentalType(thisCode, varExpression) != iVariable_fundamentalType(thisCode, varMax))
			{
				// Operand mismatch
				iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_compRelated(thisCode, varMax), false);
				return(NULL);
			}

		
		//////////
		// Initialize
		//////
			tempMin		= NULL;
			tempMax		= NULL;
			tempResult1	= NULL;
			tempResult2		= NULL;


		//////////
		// Verify we are working with properly ordered min/max
		//////
			do {
				// Loop entered for structured programming
				if ((tempMin = function_min(thisCode, varMin, varMax)) == NULL)
				{
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varMax), false);
					return(NULL);
				}

				if ((tempMax = function_max(thisCode, varMin, varMax)) == NULL)
				{
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varMax), false);
					break;
				}


			//////////
			// RANGER() executed as "result = MIN(MAX(xVar, xMin), xMax))"
			//////
				// Compute first part of result
				if ((tempResult1 = function_max(thisCode, varExpression, tempMin)) == NULL)
				{
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varMax), false);
					break;
				}

				// Compute the final result
				if ((tempResult2 = function_min(thisCode, tempResult1, tempMax)) == NULL)
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varMax), false);

				// Force the result into the same form as varExpression originally was
				if (tempResult2)
				{
					// Create one of the same type, and populate
					result = iVariable_create(thisCode, varExpression->varType, NULL);
					if (result)
					{
						// Convert to the target type for propagation through the expression
						if (!iVariable_setNumeric_toDestinationType(thisCode, result, tempResult2))
							iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_compRelated(thisCode, varExpression), false);
					}
				}

				// All done
				break;

			} while (1);


		//////////
		// Delete our temporary variables
		/////
			if (tempMin)		iVariable_delete(thisCode, tempMin,		true);
			if (tempMax)		iVariable_delete(thisCode, tempMax,		true);
			if (tempResult1)	iVariable_delete(thisCode, tempResult1,	true);
			if (tempResult2)	iVariable_delete(thisCode, tempResult2,	true);


		//////////
		// Indicate our true result
		//////
			return(result);
	}




//////////
//
// Function: REPLICATE()
// Returns the indicated string replicated N times.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to replicate
//     pCount		-- Numeric, the number of copies to generate
//
//////
// Returns:
//    Character		-- The string of the input replicated N times
//////
	SVariable* function_replicate(SThisCode* thisCode, SVariable* varString, SVariable* varCount)
	{
		s32			lnI, lnCopies;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be nmumeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnCopies = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}

			if (lnCopies > 0 && varString->value.length > 0)
			{
				// Repeat the string as many as are indicated
				iDatum_allocateSpace(&result->value, lnCopies * varString->value.length);
				for (lnI = 0; lnI < lnCopies; lnI++)
					memcpy(result->value.data + (lnI * varString->value.length), varString->value.data, varString->value.length);
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: RGB()
// Returns the RGB() of the three input values.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed RGB() integer
//
//////
	SVariable* function_rgb(SThisCode* thisCode, SVariable* varRed, SVariable* varGrn, SVariable* varBlu)
	{
		return(ifunction_rgba_common(thisCode, varRed, varGrn, varBlu, NULL));
	}

	SVariable* ifunction_rgba_common(SThisCode* thisCode, SVariable* varRed, SVariable* varGrn, SVariable* varBlu, SVariable* varAlp)
	{
		f32			lfRed, lfGrn, lfBlu, lfAlp;
		s32			lnRed, lnGrn, lnBlu, lnAlp;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varRed) || !iVariable_isTypeNumeric(varRed))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varRed), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varGrn) || !iVariable_isTypeNumeric(varGrn))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varGrn), false);
				return(NULL);
			}


		//////////
		// Parameter 3 must be numeric
		//////
			if (!iVariable_isValid(varBlu) || !iVariable_isTypeNumeric(varBlu))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varBlu), false);
				return(NULL);
			}


		//////////
		// Parameter 4 must be numeric
		//////
			if (varAlp)
			{
				if (!iVariable_isValid(varAlp) || !iVariable_isTypeNumeric(varAlp))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varAlp), false);
					return(NULL);
				}

			} else {
				// Default to fully transparent or fully opaque based on its ncset()
				if (propGet_settings_ncset_alphaIsOpaque(_settings))	varAlp = varTwoFiftyFive;
				else													varAlp = varZero;
			}


		//////////
		// Red
		//////
			if (iVariable_isTypeFloatingPoint(varRed))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfRed = iiVariable_getAs_f32(thisCode, varRed, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRed), false);	return(NULL);	}
				lnRed = (s32)(255.0f * min(max(lfRed, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnRed = iiVariable_getAs_s32(thisCode, varRed, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRed), false);	return(NULL);	}
			}
			if (lnRed < 0 || lnRed > 255)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varRed), false);
				return(NULL);
			}


		//////////
		// Green
		//////
			if (iVariable_isTypeFloatingPoint(varGrn))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfGrn = iiVariable_getAs_f32(thisCode, varGrn, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varGrn), false);	return(NULL);	}
				lnGrn = (s32)(255.0f * min(max(lfGrn, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnGrn = iiVariable_getAs_s32(thisCode, varGrn, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varGrn), false);	return(NULL);	}
			}
			if (lnGrn < 0 || lnGrn > 255)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varGrn), false);
				return(NULL);
			}


		//////////
		// Blue
		//////
			if (iVariable_isTypeFloatingPoint(varBlu))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfBlu = iiVariable_getAs_f32(thisCode, varBlu, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varBlu), false);	return(NULL);	}
				lnBlu = (s32)(255.0f * min(max(lfBlu, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnBlu	= iiVariable_getAs_s32(thisCode, varBlu, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varBlu), false);	return(NULL);	}
			}
			if (lnBlu < 0 || lnBlu > 255)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varBlu), false);
				return(NULL);
			}


		//////////
		// Alpha
		//////
			if (iVariable_isTypeFloatingPoint(varAlp))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfAlp = iiVariable_getAs_f32(thisCode, varAlp, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varAlp), false);	return(NULL);	}
				lnAlp = (s32)(255.0f * min(max(lfAlp, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnAlp	= iiVariable_getAs_s32(thisCode, varAlp, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varAlp), false);	return(NULL);	}
			}
			if (lnAlp < 0 || lnAlp > 255)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varAlp), false);
				return(NULL);
			}


		//////////
        // Create the return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_U32, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Populate the return value
		//////
			*(u32*)result->value.data = bgra((u32)lnBlu, (u32)lnGrn, (u32)lnRed, (u32)lnAlp);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: RGBA()
// Returns the RGBA() of the four input values.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pAlp			-- Blue, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed RGBA() integer
//
//////
	SVariable* function_rgba(SThisCode* thisCode, SVariable* varRed, SVariable* varGrn, SVariable* varBlu, SVariable* varAlp)
	{
		return(ifunction_rgba_common(thisCode, varRed, varGrn, varBlu, varAlp));
	}




//////////
//
// Function: RED()
// Retrieves the red channel from an RGBA or BGRA color.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Numeric, a color (0..(2^32)-1)
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
	SVariable* function_red(SThisCode* thisCode, SVariable* varColor)
	{
		return(ifunction_color_common(thisCode, varColor, 0x000000ff, 0));
	}

	SVariable* ifunction_color_common(SThisCode* thisCode, SVariable* varColor, u32 tnMask, u32 tnShift)
	{
		u32			lnColor;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varColor), false);
				return(NULL);
			}


		//////////
		// Grab the value
		//////
			lnColor = iiVariable_getAs_u32(thisCode, varColor, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varColor), false);	return(NULL);	}


		//////////
		// Apply the mask and shift
		//////
			lnColor &= tnMask;
			if (tnShift != 0)
				lnColor >>= tnShift;


		//////////
		// Construct our result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_U32, NULL);
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Populate and return our result
		//////
			*result->value.data_u32 = lnColor;
			return(result);
	}




//////////
//
// Function: RIGHT()
// Returns the right N characters of a string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//     pCount		-- Numeric, the number of characters to copy
//
//////
// Returns:
//    Character		-- The string of the right N characters
//////
	SVariable* function_right(SThisCode* thisCode, SVariable* varString, SVariable* varCount)
	{
		s32			lnStart, lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be nmumeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Copy as much of the source string as will fit
		//////
			if (lnLength >= varString->value.length)
			{
				// Copy only the length of the current string
				iDatum_duplicate(&result->value, &varString->value);

			} else if (lnLength > 0) {
				// We can do an extraction
				lnStart = varString->value.length - lnLength;
				iDatum_duplicate(&result->value, varString->value.data_u8 + lnStart, lnLength);
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: ROUND()
// Returns a numeric expression rounded to a specified number of decimal places.
//  
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.17.2015
//////
// Change log:
//     Mar.17.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    varNumber			-- Specifies the numeric expression whose value is to be rounded.
//    varDecimalPlaces	-- Specifies the number of decimal places nExpression is rounded to.
//
//////
// Returns:
//    Numeric		-- ROUND( ) returns a value rounded to the nearest decimal position as specified by nDecimalPlaces.
//////
// Example:
//    ? ROUND(53.213, 2)   && 53.21
//    ? ROUND(532, -2)     && 500
//////
	SVariable* function_round(SThisCode* thisCode, SVariable* varNumber, SVariable* varDecimalPlaces)
	{
		f64			lfValue, lfRounded;
		s32			lnDecimalPlaces;
		bool		error;
		u32			errorNum;

		SVariable*	result;

//TODO: more speed by type checking :-)

		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varDecimalPlaces) || !iVariable_isTypeNumeric(varDecimalPlaces))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varDecimalPlaces), false);
				return(NULL);
			}


		//////////
		// Grab the p1, convert to f64
		//////
			lfValue = iiVariable_getAs_f64(thisCode, varNumber, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Grab the p2, convert to s32
		//////
			lnDecimalPlaces = iiVariable_getAs_s32(thisCode, varDecimalPlaces, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varDecimalPlaces), false);
				return(NULL);
			}


		//////////
		// Check -18<=lnDecimalPlaces<=16,  max 16 :-(
		//////
			if (lnDecimalPlaces < -18 || lnDecimalPlaces > 16)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_compRelated(thisCode, varDecimalPlaces), false);
				return(NULL);
			}

		//////////
		// Compute round
		//////
			lfRounded = ((s64)(lfValue * pow(10.0, lnDecimalPlaces) + .5) / pow(10.0, lnDecimalPlaces));


		//////////
        // Create the return result
		//////
	        result = iVariable_create(thisCode, varNumber->varType, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Populate the return value
		//////
			if (!iVariable_setNumeric_toNumericType(thisCode, result, NULL, &lfRounded, NULL, NULL, NULL, NULL))
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);


		//////////
        // Return our result
		//////
	        return result;
	}





//////////
//
// Function: RTOD()
// Converts radians to its equivalent in degrees.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    RTOD(n) of the value in p1
//////
// Example:
//    ? RTOD(PI())		&& Display 180.00
//////
    SVariable* function_rtod(SThisCode* thisCode, SVariable* varNumber)
    {
        // Return rtod
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_RTOD, _VAR_TYPE_F64, false));
	}




//////////
//
// Function: RTRIM()
// Trims spaces off the end of the string.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//
//////
// Returns:
//    Character		-- The string with any trailing spaces removed
//////
	SVariable* function_rtrim(SThisCode* thisCode, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2)
	{
		return(ifunction_trim_common(thisCode, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, false, true));
	}




//////////
//
// Function: SIGN()
// Returns a numeric value of 1, -1, or 0 if varNumber is positive,
// negative, or 0 value.
//
//////
//
// Function: SIGN2()
// Returns a numeric value of 1 if varNumber >= 0, and -1 otherwise.
//
//////
// Version 0.56
// Last update:
//     Mar.14.2015
//////
// Change log:
//     Mar.15.2015 - Added common() and sign2() functions
//     Mar.14.2015 - Merge into main by Rick C. Hodgin, refactor result to match varNumber varType
//     Mar.14.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    SIGN(n) of the value in p1
//////
// Example:
//    ? sign(2)				&& Displays 1
//    ? sign(-2)			&& Displays -1
//    ? sign(0)				&& Displays 0
//    ? sign(-0.0)			&& Displays 0
//    ? sign(-0.3333)		&& Displays -1
//    ? sign(2.65656)		&& Displays 1
//    ? sign(-2.65656)		&& Displays -1
//////
    SVariable* function_sign(SThisCode* thisCode, SVariable* varNumber)
    {
		// SIGN() returns -1, 0, or 1
		return(ifunction_sign_common(thisCode, varNumber, false));
	}

	SVariable* function_sign2(SThisCode* thisCode, SVariable* varNumber)
	{
		// SIGN2() returns -1 if non-zero negative, 1 otherwise
		return(ifunction_sign_common(thisCode, varNumber, true));
	}

	SVariable* ifunction_sign_common(SThisCode* thisCode, SVariable* varNumber, bool tlIncrementZero)
	{
		f64			lfValue;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Parameter 1, Convert to f64
		//////
			lfValue = iiVariable_getAs_f64(thisCode, varNumber, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Create output variable
		//////
			if (propGet_settings_ncset_signSign2(_settings))
			{
				// They want it to be the input type if possible
				result = iVariable_create(thisCode, varNumber->varType, NULL);

			} else {
				// Always an integer return value
				result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);
			}
			if (!result)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
		// Compute sign
		//////
			if (lfValue != 0.0)
			{
				// Converting of lfValue to 1 or -1
				lfValue = lfValue / abs(lfValue);	

			} else if (tlIncrementZero) {
				// Should we increment a 0 value (so it will be returned as 1 instead of 0)?
				++lfValue;
			}


		//////////
		// Set the value
		//////
			if (!iVariable_setNumeric_toNumericType(thisCode, result, NULL, &lfValue, NULL, NULL, NULL, NULL))
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNumber), false);


		//////////
        // Return sign
		//////
	        return result;
    }

	

//////////
//
// Function: SIN()
// Returns the sine of an angle.
//
//////
// Version 0.56
// Last update:
//     Mar.17.2015
//////
// Change log:
//     Mar.17.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    SIN(n) of the value in p1
//////
// Example:
//    ? SIN(0)		&& Display 0.00
//////
    SVariable* function_sin(SThisCode* thisCode, SVariable* varNumber)
    {
		// Return exp
		return(ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_SIN, _VAR_TYPE_F64, false));
	}



//////////
//
// Function: SPACE()
// Creates a character variable initialized with spaces.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pCount		-- The number of spaces to populate
//
//////
// Returns:
//    Character		-- The string with any leading and trailing spaces removed
//////
	SVariable* function_space(SThisCode* thisCode, SVariable* varCount)
	{
		s32			lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varCount), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Create the source string and initialize to spaces
		//////
	        iDatum_allocateSpace(&result->value, lnLength);
			memset(result->value.data, 32, lnLength);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: SQRT()
// Returns the square root of the specified numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varNumber	-- Numeric or floating point
//
//////
// Returns:
//    SQRT(n) of the value in p1
//////
// Example:
//    ? SQRT(2)		&& Display 1.41
//    ? SQRT(2.0)	&& Display 1.41
//    ? SQRT(-2)	&& Error: argument cannot be negative
//////
    SVariable* function_sqrt(SThisCode* thisCode, SVariable* varNumber)
	{
		// Return sqrt
		return ifunction_numbers_common(thisCode, varNumber, _FP_COMMON_SQRT, _VAR_TYPE_F64, false);
	}




//////////
//
// Function: STRTRAN()
// Converts the matching portions of the string from one form to another.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Aug.21.2014
//////
// Change log:
//     Aug.21.2014 - Initial creation
//////
// Parameters:
//     pString			-- Original string
//     pSearch			-- Search string to replace
//     pReplace			-- String to replace with
//     pRecursiveCount	-- How many times should we recursively parse this string?
//
//////
// Returns:
//    Character		-- The original string with all components replaced
//
//////
	SVariable* function_strtran(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace, SVariable* varRecursiveCount)
	{
		return(ifunction_strtran_common(thisCode, varString, varSearch, varReplace, varRecursiveCount, true));
	}

	SVariable* function_strtranc(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace, SVariable* varRecursiveCount)
	{
		return(ifunction_strtran_common(thisCode, varString, varSearch, varReplace, varRecursiveCount, false));
	}

	SVariable* ifunction_strtran_common(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace, SVariable* varRecursiveCount, bool tlCaseSensitive)
	{
		s32			lnI, lnIteration, lnSrc, lnDst, lnLength, lnRecursiveCount, lnFoundCount;
		bool		error;
		u32			errorNum;
        SVariable*	result;
		SVariable*	resultNew;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varSearch) || !iVariable_isTypeCharacter(varSearch))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varSearch), false);
				return(NULL);
			}


		//////////
		// Parameter 3 is optional, but must be character if present
		//////
			if (!iVariable_isValid(varReplace))
			{
				// They didn't provide a 3rd parameter, so we'll use a pseudo placeholder which is an empty string
				varReplace = varEmptyString;

			} else if (!iVariable_isTypeCharacter(varReplace)) {
				// It is invalid
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varReplace), false);
				return(NULL);
			}


		//////////
		// Parameter 4 is optional, but must be numeric if present
		//////
			if (!iVariable_isValid(varRecursiveCount))
			{
				// They didn't provide a 3rd parameter, so we'll use a pseudo placeholder which is an empty string
				lnRecursiveCount = 1;

			} else if (!iVariable_isTypeNumeric(varRecursiveCount)) {
				// It is invalid
				iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_compRelated(thisCode, varRecursiveCount), false);
				return(NULL);

			} else {
				// Grab the actual value
				lnRecursiveCount = iiVariable_getAs_s32(thisCode, varRecursiveCount, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varRecursiveCount), false);	return(NULL);	}
				if (lnRecursiveCount < 0)
				{
					// It is invalid
					iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_compRelated(thisCode, varRecursiveCount), false);
					return(NULL);
				}
			}


		//////////
		// If we aren't searching for anything, we don't need to go through the rigmarole
		//////
			// If the original string is empty, or the characters to search for are empty, then we don't need to do anything
			if (varSearch->value.length == 0 || varSearch->value.length > varString->value.length)
			{
				// Allocate a full copy of the original string
				result = iVariable_createAndPopulate(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length);
				return(result);
			}


		//////////
		// Iterate through the string twice, the first to determine how long the destination will be, the second to copy
		//////
			for (lnIteration = 1, result = varString; lnRecursiveCount == 0 || lnIteration <= lnRecursiveCount; lnIteration++)
			{
				// Search for any matches, and determine the overall length
				for (lnI = 0, lnFoundCount = 0; lnI < result->value.length - varSearch->value.length; )
				{
					// See if this matches the source string
					if (tlCaseSensitive)
					{
						// Case-sensitive compare
						if (memcmp(result->value.data + lnI, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							++lnFoundCount;
							lnI += varSearch->value.length;

						} else {
							// Skip to the next character
							++lnI;
						}

					} else {
						// Case-insensitive compare
						if (_memicmp(result->value.data + lnI, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							++lnFoundCount;
							lnI += varSearch->value.length;

						} else {
							// Skip to the next character
							++lnI;
						}
					}
				}

				// If we didn't find any, we're done
				if (lnFoundCount == 0)
				{
					// If we haven't made an official copy yet, we need to do so now
					if (result == varString)
						result = iVariable_createAndPopulate(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length);

					// Return our result
					return(result);
				}

				// When we get here, we have a new length for our copy
				lnLength = result->value.length - (lnFoundCount * varSearch->value.length) + (lnFoundCount * varReplace->value.length);

				// Allocate a new string of that length
				resultNew = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
				iDatum_allocateSpace(&resultNew->value, lnLength);

				// Copy the content
				for (lnSrc = 0, lnDst = 0; lnSrc < result->value.length; )
				{
					// See if this matches the source string
					if (tlCaseSensitive)
					{
						// Case-sensitive compare
						if (memcmp(result->value.data + lnSrc, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							memcpy(resultNew->value.data + lnDst, varReplace->value.data, varReplace->value.length);
							lnSrc += varSearch->value.length;
							lnDst += varReplace->value.length;

						} else {
							// Skip to the next character
							resultNew->value.data[lnDst] = result->value.data[lnSrc];
							++lnDst;
							++lnSrc;
						}

					} else {
						// Case-insensitive compare
						if (_memicmp(result->value.data + lnSrc, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							memcpy(resultNew->value.data + lnDst, varReplace->value.data, varReplace->value.length);
							lnSrc += varSearch->value.length;
							lnDst += varReplace->value.length;

						} else {
							// Skip to the next character
							resultNew->value.data[lnDst] = result->value.data[lnSrc];
							++lnDst;
							++lnSrc;
						}
					}
				}

				// Delete our original (if it wasn't pointing to our source string)
				if (result != varString)
					iVariable_delete(thisCode, result, true);

				// Set the new to our result
				result = resultNew;
				// Continue on for the next iteration
			}


		//////////
		// Return our final string
		/////
			return(result);
	}




//////////
//
// Function: STUFF()
// Returns a string which has been modified, having optionally some characters optionally removed, some optionally inserted.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pOriginalString		-- Input string
//     pStartPos			-- Starting position
//     pNumToRemove			-- Number of characters to remove
//     pStuffString			-- String to insert there
//
//////
// Returns:
//    Character		-- String has been modified as per the STUFF() function.
//
//////
	SVariable* function_stuff(SThisCode* thisCode, SVariable* varOriginalString, SVariable* varStartPos, SVariable* varNumToRemove, SVariable* varStuffString)
	{
		s32			lnStartPosition, lnRemoveCount, lnBufferLength;
		bool		error;
		u32			errorNum;
		u8*			lcBuffer;
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varOriginalString) || !iVariable_isTypeCharacter(varOriginalString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varOriginalString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varStartPos) || !iVariable_isTypeNumeric(varStartPos))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varStartPos), false);
				return(NULL);
			}


		//////////
		// Parameter 3 must be numeric
		//////
			if (!iVariable_isValid(varNumToRemove) || !iVariable_isTypeNumeric(varNumToRemove))
			{
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_compRelated(thisCode, varNumToRemove), false);
				return(NULL);
			}


		//////////
		// Parameter 4 must be character
		//////
			if (!iVariable_isValid(varStuffString) || !iVariable_isTypeCharacter(varStuffString))
			{
				iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_compRelated(thisCode, varStuffString), false);
				return(NULL);
			}


		//////////
		// Grab the parameters as usable values
		//////
			// Your algorithm code goes here
			lnStartPosition	= iiVariable_getAs_s32(thisCode, varStartPos, false, &error, &errorNum);
			lnRemoveCount	= iiVariable_getAs_s32(thisCode, varNumToRemove, false, &error, &errorNum);


		//////////
		// If they are trying to do negative things, report it
		//////
			if (lnStartPosition < 1)		lnStartPosition		= 1;
			if (lnRemoveCount   < 0)		lnRemoveCount		= 0;


		//////////
		// Adjust them based on real-world observations from the string
		//////
			// Are they trying to start beyond the end of the string?  If so, reduce to the end.
			if (lnStartPosition > varOriginalString->value.length)
				lnStartPosition = varOriginalString->value.length + 1;

			// Are they trying to remove more than can be extracted?
			if (lnStartPosition - 1 + lnRemoveCount > varOriginalString->value.length)
				lnRemoveCount = varOriginalString->value.length - lnStartPosition + 1;


		//////////
		// Construct our destination
		//////
			lnBufferLength	= varOriginalString->value.length - lnRemoveCount + varStuffString->value.length;
			lcBuffer = (u8*)malloc(lnBufferLength);
			if (!lcBuffer)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_MEMORY, NULL, false);
				return(NULL);
			}

			// Copy the first part of the original string, plus the stuffed in part, plus the end of the last part of the original string
			--lnStartPosition;

			// We only copy the first part if there is something to copy
			if (lnStartPosition > 0)
				memcpy((s8*)lcBuffer, varOriginalString->value.data, lnStartPosition);

			// We only insert our stuff string if there is something to put there
			if (varStuffString->value.length > 0)
				memcpy((s8*)lcBuffer + lnStartPosition, varStuffString->value.data, varStuffString->value.length);

			// We only copy over the last part if there's something there
			if (varOriginalString->value.length - lnStartPosition - lnRemoveCount > 0)
				memcpy((s8*)lcBuffer + lnStartPosition + varStuffString->value.length, varOriginalString->value.data + lnStartPosition + lnRemoveCount, varOriginalString->value.length - lnStartPosition - lnRemoveCount);


		//////////
        // Create the return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report((u8*)"Internal error.", false);
				return(NULL);
			}


		//////////
        // Populate the return value
		//////
			iDatum_duplicate(&result->value, lcBuffer, lnBufferLength);


		//////////
		// Release the temporary buffer
		//////
			free(lcBuffer);


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: SYS()
// SYS function support (Dec.27.2014 incomplete)
//
///////
// Version 0.56
// Last update:
//     Dec.27.2014
//////
// Change log:
//     Dec.27.2014 - Initial creation
//////
// Parameters:
//		2015			-- none
//////
// Returns:
//		2015			-- Character, unique procedure name
//////
	SVariable* function_sys(SThisCode* thisCode, SVariable* varIndex, SVariable* varP1, SVariable* varP2, SVariable* varP3, SVariable* varP4, SVariable* varP5, SVariable* varP6)
	{
		s32			lnIndex;
		u32			lnExtraPrefixWidth, lnExtraPostfixWidth;
		s64			ln2015;
		u32			errorNum;
        bool		error;
		SYSTEMTIME	lst;
		SVariable*	result;


// TODO:  Untested function, breakpoint and examine
debug_break;
		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);
			}

			// Grab the index
			lnIndex = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
			if (error)
			{
				// An error extracting the value (should never happen)
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);
			}


		//////////
		// Based on the function...
		//////
			switch (lnIndex)
			{
				case 2015:
					// Unique procedure names take on the form YYYYMMDDHHMMSSmmm converted to base-36, prefixed with an underscore
					GetLocalTime(&lst);
					ln2015 =	(lst.wYear		* 10000000000000) +
								(lst.wMonth		* 100000000000) +
								(lst.wDay		* 1000000000) +
								(lst.wHour		* 10000000) +
								(lst.wMinute	* 100000) +
								(lst.wSecond	* 1000) +
								lst.wMilliseconds;

					// Optional 2nd and 3rd parameter indicate how many extra prefix and postfix characters to insert
					if (iVariable_isValid(varP1))
					{
						//////////
						// Since P1 was provided, it must be numeric
						//////
							if (!iVariable_isTypeNumeric(varP1))
							{
								iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varP1), false);
								goto clean_exit;
							}


						//////////
						// Get the prefix width
						//////
							lnExtraPrefixWidth = iiVariable_getAs_s32(thisCode, varP1, false, &error, &errorNum);
							if (error)
							{
								iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varP1), false);
								goto clean_exit;
							}
							// Right now, we have lnExtraPrefixWidth


						/////////
						// Did they also provide a 3rd parameter?
						//////
							if (iVariable_isValid(varP2))
							{
								//////////
								// Since P2 was provided, it must be numeric
								//////
									if (!iVariable_isTypeNumeric(varP2))
									{
										iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varP2), false);
										goto clean_exit;
									}


								//////////
								// Get the postfix width
								//////
									lnExtraPostfixWidth = iiVariable_getAs_s32(thisCode, varP2, false, &error, &errorNum);
									if (error)
									{
										iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varP2), false);
										goto clean_exit;
									}
									// Right now, we have lnExtraPostfixWidth

							} else {
								// Nope, just assign it to 0
								lnExtraPostfixWidth = 0;
							}

					} else {
						lnExtraPrefixWidth	= 0;
						lnExtraPostfixWidth	= 0;
					}

					// Create a variable in base-36 (uses 0..9, A..Z)
					result = iVariable_createByRadix(thisCode, ln2015, 36, 1 + lnExtraPrefixWidth, lnExtraPostfixWidth);

					// Prefix with an underscore
					if (result)
						result->value.data_u8[lnExtraPrefixWidth] = '_';

					// Right now, the variable looks something like:  _19B2L483
					break;

				default:
					// Not currently supported
					iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_compRelated(thisCode, varIndex), false);
					result = iVariable_create(thisCode, _VAR_TYPE_LOGICAL, varFalse);
					break;
			}

clean_exit:
		//////////
		// Clean house
		//////
			// Currently nothing to clean


		//////////
		// Indicate our result
		//////
			return(result);
	}

	// Note:  Helper function.  iFunction_sys2015() is a shortcut function for accessing the oft-used get-unique-procedure-name feature
	SVariable* iFunction_sys2015(SThisCode* thisCode, u32 tnPrefixWidth, u32 tnPostfixWidth)
	{
// TODO:  Untested function, breakpoint and examine
debug_break;
		s32			ln2015		= 2015;
		SVariable*	var2015		= iVariable_createAndPopulate(thisCode, _VAR_TYPE_S32,	(cu8*)&ln2015,			sizeof(ln2015));
		SVariable*	varPrefix	= iVariable_createAndPopulate(thisCode, _VAR_TYPE_S32,	(cu8*)&tnPrefixWidth,	sizeof(tnPrefixWidth));
		SVariable*	varPostfix	= iVariable_createAndPopulate(thisCode, _VAR_TYPE_S32,	(cu8*)&tnPostfixWidth,	sizeof(tnPostfixWidth));
		SVariable*	varSys2015	= function_sys(thisCode, var2015, varPrefix, varPostfix, NULL, NULL, NULL, NULL);


		//////////
		// Clean house
		//////
			iVariable_delete(thisCode, var2015,		true);
			iVariable_delete(thisCode, varPrefix,	true);
			iVariable_delete(thisCode, varPostfix,	true);


		//////////
		// Return our value
		//////
			return(varSys2015);
	}




//////////
//
// Function: SYSMETRIC()
// Based on the index, returns a wide array of information.
//
//////
// Version 0.56
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pIndex		-- Numeric, in the range 1..34
//
//////
// Returns:
//    Numeric		-- Depending on index, various value ranges are returned
//////
    SVariable* function_sysmetric(SThisCode* thisCode, SVariable* varIndex)
    {
        s32			index;
		RECT		lrc;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);
			}


		//////////
        // It must be in the range 1..34
		//////
			index = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);

			} else if (index > 34 || index < 1) {
				// We report our own error
				iError_report((cu8*)"Parameter must be in the range 1..34", false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Populate the result with its sysmetric()
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			switch (index)
			{
				case 1:
					// Screen width
					*(s32*)result->value.data = (lrc.right - lrc.left);
					break;
				case 2:
					// Screen height
					*(s32*)result->value.data = (lrc.bottom - lrc.top);
					break;
				case 3:
					// Width of a sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;
				case 4:
					// Height of a sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;
				case 5:
					// Width of scroll arrows on a vertical scroll bar
					*(s32*)result->value.data = 0;
					break;
				case 6:
					// Height of scroll arrows on a vertical scroll bar
					*(s32*)result->value.data = 0;
					break;
				case 7:
					// Width of scroll arrows on a horizontal scroll bar
					*(s32*)result->value.data = 0;
					break;
				case 8:
					// Height of scroll arrows on a horizontal scroll bar
					*(s32*)result->value.data = 0;
					break;
				case 9:
					// Height of form caption
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;
				case 10:
					// Width of non-sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;
				case 11:
					// Height of a non-sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;
				case 12:
					// Width of a double or panel window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;
				case 13:
					// Height of a double or panel window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;
				case 14:
					// Scroll box width on horizontal scroll bars in text editing windows
					*(s32*)result->value.data = 0;
					break;
				case 15:
					// Scroll box height on horizontal scroll bars in text editing windows
					*(s32*)result->value.data = 0;
					break;
				case 16:
					// Minimized window icon width
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;
				case 17:
					// Minimized window icon height
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;
				case 18:
					// Maximum insertion point width
					*(s32*)result->value.data = 0;
					break;
				case 19:
					// Maximum insertion point height
					*(s32*)result->value.data = 0;
					break;
				case 20:
					// Single-line menu bar height
					*(s32*)result->value.data = _MENU_BAR_HEIGHT;
					break;
				case 21:
					// Maximized window width
					*(s32*)result->value.data = (lrc.right - lrc.left);
					break;
				case 22:
					// Maximized window height
					*(s32*)result->value.data = (lrc.bottom - lrc.top);
					break;
				case 23:
					// Kanji window height
					*(s32*)result->value.data = ((GetSystemMetrics(SM_CYKANJIWINDOW) != 0) ? 1 : 0);
					break;
				case 24:
					// Minimum sizable window width
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biWidth;
					break;
				case 25:
					// Minimum sizable window height
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biHeight;
					break;
				case 26:
					// Minimum window width
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biWidth;
					break;
				case 27:
					// Minimum window height
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biHeight;
					break;
				case 28:
					// Window controls width
					*(s32*)result->value.data = 2 * bmpClose->bi.biWidth;
					break;
				case 29:
					// Window controls height
					*(s32*)result->value.data = 2 * bmpClose->bi.biHeight;
					break;
				case 30:
					// 1 if mouse hardware present, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_MOUSEPRESENT) != 0) ? 1 : 0);
					break;
				case 31:
					// 1 for Microsoft Windows debugging version, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_DEBUG) != 0) ? 1 : 0);
					break;
				case 32:
					// 1 if mouse buttons are swapped, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_SWAPBUTTON) != 0) ? 1 : 0);
					break;
				case 33:
					// width of a button in a half-height title bar
					*(s32*)result->value.data = bmpClose->bi.biWidth;
					break;
				case 34:
					// Height of half-height caption area
					*(s32*)result->value.data = bmpClose->bi.biHeight;
					break;
			}


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Function: TRANSFORM()
// Converts any variable input to a character form, and applies formatting based on codes.
//
//////
// Version 0.56
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the variable to transform
//     pformat		-- Character, the format codes
//
//////
// Returns:
//    Character		-- The string after the variable was converted and formatted
//////
	SVariable* function_transform(SThisCode* thisCode, SVariable* varVariable, SVariable* varFormat)
	{
		SVariable* result;


		//////////
		// Parameter 1 must be valid
		//////
			if (!iVariable_isValid(varVariable))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varVariable), false);
				return(NULL);
			}


		//////////
		// Parameter 2 is optional, but if present...
		//////
			if (iVariable_isValid(varFormat))
			{
				// ...it must be character
				if (!iVariable_isTypeCharacter(varFormat))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varFormat), false);
					return(NULL);
				}
			}


		//////////
		// Create the return variable
		//////
			result = iVariable_convertForDisplay(thisCode, varVariable);


		//////////
		// Formatters:
		//		@D		date,		convert using SET DATE
		//		@E		date,		convert using BRITISH
		//		@YL		date,		convert using LONG
		//		@YS		date,		convert using SHORT
		//		Y		logical,	use Y and N
		//		@T		character,	ALLTRIM() input before conversion
		//		@!		character,	UPPER() input
		//		!		character,	UPPER() on the character in this position
		//		.		Use decimal point
		//		,		Use 1000s separator
		//		X		Specifies output width by character count
		//
		// Output formats:
		//		@B		numeric,	left-justify
		//		@$		numeric,	append based on SET CURRENCY symbol
		//		@C		numeric,	append "CR" after if zero or positive
		//		@X		numeric,	appends "DB" after if negative
		//		@L		numeric,	prefix with leading 0s
		//		@Z		numeric,	if zero display CHR(32) instead of "0"
		//		@(		numeric,	surround with () if negative
		//		@^		numeric,	scientific notation
		//		@0		numeric,	convert to hexadecimal equivalent
		//		@R		format around other characters encountered using 9,#,! for source data
		//////


		//////////
		// Indicate our status
		//////
			return(result);
	}




//////////
//
// Function: UPPER()
// Converts every character in the string to uppercase.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to upper
//
//////
// Returns:
//    Character		-- The string with all lowercase characters converted to uppercase
//////
	SVariable* function_upper(SThisCode* thisCode, SVariable* varString)
	{
		s32			lnI;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString), false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Copy the source string
		//////
	        iDatum_duplicate(&result->value, &varString->value);


		//////////
		// Lower every character
		//////
			for (lnI = 0; lnI < result->value.length; lnI++)
			{
				if (result->value.data[lnI] >= 'a' && result->value.data[lnI] <= 'z')
					result->value.data[lnI] -= 0x20;
			}


		//////////
        // Return our converted result
		//////
	        return result;
	}




//////////
//
// Function: VERSION()
// Based on input, retrieves various version information.
//
//////
// Version 0.56
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pIndex		-- (Optional) If present, Numeric, in the range 1..5
//
//////
// Returns:
//    Numeric or Character	-- Depending on index, various values are returned
//////
    SVariable* function_version(SThisCode* thisCode, SVariable* varIndex)
    {
        s32			index;
		u32			errorNum;
        bool		error;
		u8*			lptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			lptr = NULL;
			if (!iVariable_isValid(varIndex))
			{
				// They are requesting the default information
				lptr = (u8*)cgcVersionText;

			} else if (!iVariable_isTypeNumeric(varIndex)) {
				// The parameter is not numeric
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varIndex), false);
				return(NULL);

			} else {
				// It must be in the range 1..5
				index = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varIndex), false);
					return(NULL);

				} else if (index < 1 || index > 5) {
					// We report our own error
					iError_report((cu8*)"Parameter must be in the range 1..5", false);
					return(NULL);
				}
			}


		//////////
        // Create our return result
		//////
			if (lptr || index == 1 || index == 4)
			{
				// Character return
				result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
				if (lptr)
				{
					// Copy the version info
					iDatum_duplicate(&result->value, lptr, -1);

				} else if (index == 1) {
					// Copy the version1 info
					iDatum_duplicate(&result->value, cgcVersion1Text, -1);

				} else {
					// Copy the version4 info
					iDatum_duplicate(&result->value, cgcVersion4Text, -1);
				}

			} else {
				result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL);
				if (index == 2)
				{
					// 0=runtime, 1=standard, 2=professional
					*(s32*)result->value.data = gnVersion2;	// Oh yeah!

				} else if (index == 3) {
					// Localized version
					*(s32*)result->value.data = gnVersion3;	// English

				} else {
					// Version in a form like Major.Minor as M.mm, or 123 for version 1.23
					*(s32*)result->value.data = gnVersion5;
				}
			}
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return(NULL);
			}


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Function: CONCATENATE()
// Note:  This is a temporary function until the main compiler engine is coded.
// Concatenates two strings together.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- String1
//     p2		-- String2
//
//////
// Returns:
//    The sum of p1 + p2
//
//////
	SVariable* function_concatenate(SThisCode* thisCode, SVariable* varString1, SVariable* varString2)
	{
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString1) || !iVariable_isTypeCharacter(varString1))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varString1), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varString2) || !iVariable_isTypeCharacter(varString2))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varString2), false);
				return(NULL);
			}


		//////////
		// Allocate enough space for the assemblage
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL);
			iDatum_allocateSpace(&result->value, varString1->value.length + varString2->value.length);
			// Create the concatenated string
			memcpy(result->value.data,						varString1->value.data,		varString1->value.length);
			memcpy(result->value.data + varString1->value.length,	varString2->value.data,		varString2->value.length);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Function: ADD()
// Note:  This is a temporary function until the main compiler engine is coded.
// Adds two values and returns the result.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to add
//     p2		-- Value2 to add
//
//////
// Returns:
//    The sum of p1 + p2
//
//////
	SVariable* function_add(SThisCode* thisCode, SVariable* varNum1, SVariable* varNum2)
	{
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNum1), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varNum2), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Create our floating point result
				result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 + lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 + (f64)lnValue2;
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

					// Store the result
					*(f64*)result->value.data = (f64)lnValue1 + lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_S64, NULL);

					// Store the result
					*(s64*)result->value.data = lnValue1 + lnValue2;
				}
			}


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Function: SUB()
// Note:  This is a temporary function until the main compiler engine is coded.
// Subtracts two values and returns the result.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to subtract value2 from
//     p2		-- Value2
//
//////
// Returns:
//    The sum of p1 - p2
//
//////
	SVariable* function_sub(SThisCode* thisCode, SVariable* varSub1, SVariable* varSub2)
	{
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varSub1) || !iVariable_isTypeNumeric(varSub1))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varSub1), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varSub2) || !iVariable_isTypeNumeric(varSub2))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varSub2), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varSub1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(thisCode, varSub1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub1), false);	return(NULL);	}

				// Create our floating point result
				result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varSub2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varSub2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 - lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varSub2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 - (f64)lnValue2;
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(thisCode, varSub1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub1), false);	return(NULL);	}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varSub2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varSub2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

					// Store the result
					*(f64*)result->value.data = (f64)lnValue1 - lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varSub2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varSub2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_S64, NULL);

					// Store the result
					*(s64*)result->value.data = lnValue1 - lnValue2;
				}
			}


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Function: MUL()
// Note:  This is a temporary function until the main compiler engine is coded.
// Multiplies two values and returns the result.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to multiply
//     p2		-- Value2 to multiply
//
//////
// Returns:
//    The sum of p1 * p2
//
//////
	SVariable* function_mul(SThisCode* thisCode, SVariable* varNum1, SVariable* varNum2)
	{
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNum1), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varNum2), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Create our floating point result
				result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 * lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 * (f64)lnValue2;
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

					// Store the result
					*(f64*)result->value.data = (f64)lnValue1 * lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Create our floating point result
					result = iVariable_create(thisCode, _VAR_TYPE_S64, NULL);

					// Store the result
					*(s64*)result->value.data = lnValue1 * lnValue2;
				}
			}


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Function: DIV()
// Note:  This is a temporary function until the main compiler engine is coded.
// Divides two values and returns the result.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to divide by value2
//     p2		-- Value2
//
//////
// Returns:
//    The sum of p1 / p2
//
//////
	SVariable* function_div(SThisCode* thisCode, SVariable* varNum1, SVariable* varNum2)
	{
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_compRelated(thisCode, varNum1), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_compRelated(thisCode, varNum2), false);
				return(NULL);
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Create our floating point result
				result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 / lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = lfValue1 / (f64)lnValue2;
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(thisCode, varNum1, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum1), false);	return(NULL);	}

				// Create our floating point result
				result = iVariable_create(thisCode, _VAR_TYPE_F64, NULL);

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = (f64)lnValue1 / lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(thisCode, varNum2, false, &error, &errorNum);
					if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_compRelated(thisCode, varNum2), false);	return(NULL);	}

					// Store the result
					*(f64*)result->value.data = (f64)lnValue1 / (f64)lnValue2;
				}
			}


		//////////
		// Indicate our result
		//////
			return(result);
	}

 


//////////
//
// Command:  CLEAR
// Clears various things.
//
//////
// Version 0.56
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015
//////
// Parameters:
//		compClear -- The [CLEAR] component
//////
// Returns:
//		Nothing, but whatever it is that's being modified may be open for modifying.
//////
	void command_clear(SThisCode* thisCode, SComp* compClear)
	{
		s32				lnSaveLines;
		bool			llManufactured;
		SEM_callback	ecb;
		SVariable*		var;
		bool			error;
		u32				errorNum;


// 		SComp*	compAll				= iComps_findNextBy_iCode(compModify, _ICODE_ALL,		NULL);
// 		SComp*	compClass			= iComps_findNextBy_iCode(compModify, _ICODE_CLASS,		NULL);
// 		SComp*	compClassName		= iComps_getNth(compClass, 1);
// 		SComp*	compClassLib		= iComps_findNextBy_iCode(compModify, _ICODE_CLASSLIB,	NULL);
// 		SComp*	compClassLibName	= iComps_getNth(compClassLib, 1);
		SComp*	compKeep			= iComps_findNextBy_iCode(compClear, _ICODE_KEEP,	NULL);;
		SComp*	compKeepCount		= iComps_getNth(compKeep, 1);
// 		SComp*	compDebug			= iComps_findNextBy_iCode(compModify, _ICODE_DEBUG,		NULL);
// 		SComp*	compDlls			= iComps_findNextBy_iCode(compModify, _ICODE_DLLS,		NULL);
// 		SComp*	compDllAlias		= iComps_getNth(compDlls, 1);
// 		SComp*	compEvents			= iComps_findNextBy_iCode(compModify, _ICODE_EVENTS,	NULL);
// 		SComp*	compError			= iComps_findNextBy_iCode(compModify, _ICODE_ERROR,		NULL);
// 		SComp*	compFields			= iComps_findNextBy_iCode(compModify, _ICODE_FIELDS,	NULL);
// 		SComp*	compGets			= iComps_findNextBy_iCode(compModify, _ICODE_GETS,		NULL);
// 		SComp*	compMacros			= iComps_findNextBy_iCode(compModify, _ICODE_MACROS,	NULL);
// 		SComp*	compMemory			= iComps_findNextBy_iCode(compModify, _ICODE_MEMORY,	NULL);
// 		SComp*	compMenus			= iComps_findNextBy_iCode(compModify, _ICODE_MENUS,		NULL);
// 		SComp*	compPopups			= iComps_findNextBy_iCode(compModify, _ICODE_POPUPS,	NULL);
// 		SComp*	compProgram			= iComps_findNextBy_iCode(compModify, _ICODE_PROGRAM,	NULL);
// 		SComp*	compPrompt			= iComps_findNextBy_iCode(compModify, _ICODE_PROMPT,	NULL);
// 		SComp*	compRead			= iComps_findNextBy_iCode(compModify, _ICODE_READ,		NULL);
// 		SComp*	compResources		= iComps_findNextBy_iCode(compModify, _ICODE_RESOURCES,	NULL);
// 		SComp*	compTypeahead		= iComps_findNextBy_iCode(compModify, _ICODE_TYPEAHEAD,	NULL);
// 		SComp*	compWindows			= iComps_findNextBy_iCode(compModify, _ICODE_WINDOWS,	NULL);
// 		SComp*	compFilename		= iComps_getNth(compWindows, 1);

		if (compKeep)
		{
			// CLEAR KEEP -- Keeps a certain number of lines at the end of the buffer, and clears the rest
			if (compKeepCount)
			{
				//////////
				// CLEAR KEEP nCount
				//////
					var = iEngine_get_variableName_fromComponent(thisCode, compKeepCount, &llManufactured);
					if (!var)
					{
						// Unknown parameter
						iError_reportByNumber(thisCode, _ERROR_UNRECOGNIZED_PARAMETER, compKeepCount, false);
						return;
					}


				//////////
				// Find out how many lines
				//////
					lnSaveLines = iiVariable_getAs_s32(thisCode, var, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, compKeepCount, false);
						return;
					}


				//////////
				// Clean house
				//////
					if (llManufactured)
						iVariable_delete(thisCode, var, true);


				//////////
				// Validate the number is in range
				//////
					if (lnSaveLines < 0)
					{
						iError_reportByNumber(thisCode, _ERROR_CANNOT_BE_NEGATIVE, compKeepCount, false);
						return;
					}

			} else {
				// Clear them all
				lnSaveLines = 0;
			}

		} else {
			// Clear them all
			lnSaveLines = 0;
		}


		//////////
		// Prepare for the clear
		//////
			memset(&ecb, 0, sizeof(ecb));
			ecb._callback = (uptr)&iiCommand_clear_keep_callback;
			ecb.extra1 = (uptr)lnSaveLines;
			ecb.extra2 = (uptr)iSEM_renumber(screenData, 1);


		//////////
		// Clear
		//////
			iSEM_deleteChainWithCallback(&screenData, false, &ecb);


		//////////
		// Count what remains, and set _tally
		//////
			iEngine_update_tally(thisCode, iSEM_renumber(screenData, 1));


		//////////
		// Redraw what remains
		//////
			iSEM_navigateToEndLine(screenData, _screen);
			screen_editbox->isDirtyRender = true;
			iWindow_render(NULL, gWinJDebi, false);
			// All done
	}

	// Tests the line number, only saves the tail
	bool iiCommand_clear_keep_callback(SEM_callback* ecb)
	{
		// If (endNum - saveCount) > lineNum ... delete it
		return(ecb->sem->lastLine->lineNumber - ecb->extra1 >= ecb->line->lineNumber);
	}
	
 


//////////
//
// Command:  MODIFY
// Modifies various things.
//
//////
// Version 0.56
// Last update:
//     Jan.09.2015
//////
// Change log:
//     Jan.09.2015
//////
// Parameters:
//		compModify	-- The [MODIFY] component
//////
// Returns:
//		Nothing, but whatever it is that's being modified may be open for modifying.
//////
	void command_modify(SThisCode* thisCode, SComp* compModify)
	{
		SComp*	compType;
//		SComp*	compTarget;


		//////////
		// Make sure there's something after the modify command
		//////
			if (!(compType = iComps_getNth(compModify, 1)))
			{
				// There was nothing after, which means syntax error
				iError_reportByNumber(thisCode, _ERROR_MISSING_PARAMETER, compModify, false);
				return;
			}


		//////////
		// Based on what's after, validate the syntaxes
		//////
// TODO:  Working on here ... the thing after MODIFY should be a fully qualified thing as per the compiler engine
//			compTarget = iComps_getNth(compType, 1);
			switch (compType->iCode)
			{
				case _ICODE_CLASS:
					// MODIFY CLASS
					break;

				case _ICODE_COMMAND:
					// MODIFY COMMAND
					break;

				case _ICODE_CONNECTION:
					// MODIFY CONNECTION
					break;

				case _ICODE_DATABASE:
					// MODIFY DATABASE
					break;

				case _ICODE_FILE:
					// MODIFY FILE
					break;

				case _ICODE_FORM:
					// MODIFY FORM
					break;

				case _ICODE_GENERAL:
					// MODIFY GENERAL
					break;

				case _ICODE_LABEL:
					// MODIFY LABEL
					break;

				case _ICODE_MEMO:
					// MODIFY MEMO
					break;

				case _ICODE_MENU:
					// MODIFY MENU
					break;

				case _ICODE_PROCEDURE:
					// MODIFY PROCEDURE
					break;

				case _ICODE_PROJECT:
					// MODIFY PROJECT
					break;

				case _ICODE_QUERY:
					// MODIFY QUERY
					break;

				case _ICODE_REPORT:
					// MODIFY REPORT
					break;

				case _ICODE_STRUCTURE:
					// MODIFY STRUCTURE
					break;

				case _ICODE_VIEW:
					// MODIFY VIEW
					break;

				case _ICODE_WINDOW:
					// MODIFY WINDOW
					break;
			}


		//////////
		// If we get here, syntax error
		//////
			iError_reportByNumber(thisCode, _ERROR_SYNTAX, compType, false);
	}




//////////
//
// Command:  OPEN
// Multiple forms.  Opens a database container.
//
//////
// Version 0.56
// Last update:
//     Jan.06.2015
//////
// Change log:
//     Jan.06.2015 - Initial creation
//////
// Parameters:
//		compOpen		-- The [OPEN] component
//////
// Returns:
//		Nothing, but the environment may be changed.
//////
	void command_open(SThisCode* thisCode, SComp* compOpen)
	{
		s32		lnLength;
		sptr	lnDbcArea;
		bool	llIsExclusive;
		SComp*	compPathname;
		SComp*	compDatabase;
		SComp*	compExclusive;
		SComp*	compShared;
		SComp*	compValidate;
		SComp*	compRecover;
		s8		dbcNameBuffer[_MAX_PATH];


		//////////
		// Access the options which are available for this command
		//////
			compDatabase	= iComps_findNextBy_iCode(compOpen, _ICODE_DATABASE,	NULL);
			compExclusive	= iComps_findNextBy_iCode(compOpen, _ICODE_EXCLUSIVE,	NULL);
			compShared		= iComps_findNextBy_iCode(compOpen, _ICODE_SHARED,		NULL);
			compValidate	= iComps_findNextBy_iCode(compOpen, _ICODE_VALIDATE,	NULL);
			compRecover		= iComps_findNextBy_iCode(compOpen, _ICODE_RECOVER,		NULL);


		//////////
		// Make sure the syntax was OPEN DATABASE
		//////
			if (!compDatabase)
			{
				// Syntax error
				iError_reportByNumber(thisCode, _ERROR_SYNTAX, compOpen, false);
				return;
			}
			if (!compDatabase->ll.next)
			{
				// Syntax error
				iError_reportByNumber(thisCode, _ERROR_SYNTAX, compDatabase, false);
				return;
			}
			// Grab the component after [database]
			compPathname = iComps_getNth(compDatabase, 1);


		//////////
		// Extract the DBC name
		//////
			lnLength = iComps_getContiguousLength(compPathname, NULL, 0, NULL);
			if (lnLength >= (s32)sizeof(dbcNameBuffer))
			{
				// Parameter is too long
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_TOO_LONG, compPathname, false);
				return;
			}
			memset(dbcNameBuffer, 0, sizeof(dbcNameBuffer));
			memcpy(dbcNameBuffer, compPathname->line->sourceCode->data + compPathname->start, lnLength);


		//////////
		// Cannot have both SHARED and EXCLUSIVE
		//////
			if (compShared && compExclusive)
			{
				iError_reportByNumber(thisCode, _ERROR_CONFLICTING_PARAMETERS, ((compShared->ll.uniqueId < compExclusive->ll.uniqueId) ? compExclusive : compShared), false);
				return;
			}

			// Determine shared or exclusive status
			if (compShared)
			{
				// Explicitly shared
				llIsExclusive	= false;

			} else if (compExclusive) {
				// Explicitly exclusive
				llIsExclusive	= true;

			} else {
				// Use the current SET default
				llIsExclusive	= propGet_settings_Exclusive(_settings);
			}


		//////////
		// Try to open it
		//////
			lnDbcArea = iDbf_open(thisCode, (cs8*)dbcNameBuffer, (cs8*)cgcDbcKeyName, llIsExclusive, false, false);
			if (lnDbcArea < 0)
			{
				// Unable to open
				iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_OPEN_DBC, compPathname, false);
				return;
			}


		//////////
		// If we need to validate, do so
		//////
			// Pass it our output screen
			if (compValidate)
				iDbc_validate(thisCode, &gsDbcArea[lnDbcArea], (compRecover != NULL), ((propGet_settings_Talk(_settings)) ? screen_editbox->p.sem : NULL), gWinJDebi);
	}




//////////
//
// Command: SET
// Sets various components within the current _settings object.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation
//////
// Parameters:
//     comp		-- The [SET] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//////
	void command_set(SThisCode* thisCode, SComp* compSet)
	{
		s32				lnIndex;
		bool			llManufactured;
		SComp*			compSetTarget;
		SComp*			compSetValue;
		SObjPropMap*	objProp;
		SBasePropMap*	baseProp;
		SVariable*		varSet;
		SVariable*		varSetNewValue;

// iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, compSet, false);
// return;

		//////////
		// Get the next component
		//////
			compSetTarget = iComps_getNth(compSet, 1);
			if (compSetTarget)
			{
				// SET SOMETHING


				//////////
				// The thing after should be the value, or the keyword TO
				//////
					compSetValue = iComps_getNth(compSetTarget, 1);

					// TO is superfluous, so if it exists, skip it
					if (compSetValue && compSetValue->iCode == _ICODE_TO)
						compSetValue = iComps_getNth(compSetValue, 1);


				//////////
				// Is there anything there?
				//////
					if (!compSetValue)
					{
						// Syntax error
						iError_reportByNumber(thisCode, _ERROR_SYNTAX, compSetTarget, false);
						return;
					}


				//////////
				// Translate the xyz part of the SET xyz TO abcc into the actual _INDEX_SET_* value
				/////
					lnIndex = iObjProp_settingsTranslate(thisCode, compSetTarget->iCode);
					if (lnIndex <= 0)
					{
						iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, compSetTarget, false);
						return;
					}


				//////////
				// Find out what the xyz is for SET xyz TO ...
				//////
					varSet = iObjProp_get_variable_byIndex(thisCode, _settings, lnIndex, &baseProp, &objProp);
					if (varSet && objProp && baseProp)
					{
						// We found the setting and the default variable type
						varSetNewValue = iEngine_get_variableName_fromComponent(thisCode, compSetValue, &llManufactured);
//////////
// Note:
//		Settings are handled a little differently compared to other objects.
//		They are only ever referenced as a settings object, so their values are
//		only ever set through the setter settings, which use the setterObject_set()
//		function instead of the standard setterObject() function.
//////////

						// Try to set the value using our special set values
						if (objProp->_setterObject_set)
						{
							// We have our own value, use it
							if (objProp->setterObject_set(thisCode, varSet, compSetValue, varSetNewValue, llManufactured))
								return;		// If we get here, we're good

							// If we get here, it couldn't be set
							iError_reportByNumber(thisCode, _ERROR_SYNTAX, compSetValue, false);
							return;
						}

						// If we get here, try the standard method
						if (!iObjProp_set(thisCode, _settings, compSetTarget->iCode, varSetNewValue))
						{
							iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, compSetTarget, false);
							return;
						}
					}
					// If we get here, invalid setting
					// Fall through
			}


		//////////
		// If we get here, syntax error
		//////
			iError_reportByNumber(thisCode, _ERROR_SYNTAX, compSet, false);
	}




//////////
//
// Command: USE
// Multiple forms.  Opens or close a table or view in the current or another area.
//
//////
// Version 0.56   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
//////
// Parameters:
//     comp		-- The [USE] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//////
	void command_use(SThisCode* thisCode, SComp* compUse)
	{
		sptr		lnWorkArea, lnWorkAreaAlias;
		bool		llIsInUse, llIsValidWorkArea, llManufacturedTableName, llManufacturedAliasName, llIsExclusive;
		SComp*		comp2;
		SComp*		comp3;
		SComp*		comp4;
		SVariable*	varInXyz;
		SVariable*	varTableName;
		SVariable*	varAliasName;
		u32			errorNum;
		bool		error;


		//////////
		// Initialize
		//////
			varInXyz					= NULL;
			varTableName				= 0;
			varAliasName				= 0;
			llManufacturedTableName		= false;
			llManufacturedAliasName		= false;
			llIsExclusive				= false;


		//////////
		// Access the options which are available for this command
		//////
			SComp*	compAgain				= iComps_findNextBy_iCode(compUse, _ICODE_AGAIN,				NULL);
//			SComp*	compNoRequery			= iComps_findNextBy_iCode(compUse, _ICODE_NOREQUERY,			NULL);
//			SComp*	compNoData				= iComps_findNextBy_iCode(compUse, _ICODE_NODATA,				NULL);
//			SComp*	compNoUpdate			= iComps_findNextBy_iCode(compUse, _ICODE_NOUPDATE,				NULL);
//			SComp*	compExclamationPoint	= iComps_findNextBy_iCode(compUse, _ICODE_EXCLAMATION_POINT,	NULL);
			SComp*	compIn					= iComps_findNextBy_iCode(compUse, _ICODE_IN,					NULL);
//			SComp*	compIndex				= iComps_findNextBy_iCode(compUse, _ICODE_INDEX,				NULL);
//			SComp*	compOrder				= iComps_findNextBy_iCode(compUse, _ICODE_ORDER,				NULL);
//			SComp*	compTag					= iComps_findNextBy_iCode(compUse, _ICODE_TAG,					NULL);
			SComp*	compAscending			= iComps_findNextBy_iCode(compUse, _ICODE_ASCENDING,			NULL);
			SComp*	compDescending			= iComps_findNextBy_iCode(compUse, _ICODE_DESCENDING,			NULL);
			SComp*	compAlias				= iComps_findNextBy_iCode(compUse, _ICODE_ALIAS,				NULL);
			SComp*	compExclusive			= iComps_findNextBy_iCode(compUse, _ICODE_EXCLUSIVE,			NULL);
			SComp*	compShared				= iComps_findNextBy_iCode(compUse, _ICODE_SHARED,				NULL);
//			SComp*	compConnString			= iComps_findNextBy_iCode(compUse, _ICODE_CONNSTRING,			NULL);
			SComp*	compValidate			= iComps_findNextBy_iCode(compUse, _ICODE_VALIDATE,				NULL);


		//////////
		// Report any conflicts
		//////
			//////////
			// Cannot have both ASCENDING and DESCENDING
			//////
				if (compAscending && compDescending)
				{
					iError_reportByNumber(thisCode, _ERROR_CONFLICTING_PARAMETERS, ((compAscending->ll.uniqueId < compDescending->ll.uniqueId) ? compDescending : compAscending), false);
					goto clean_exit;
				}


			//////////
			// Cannot have both SHARED and EXCLUSIVE
			//////
				if (compShared && compExclusive)
				{
					iError_reportByNumber(thisCode, _ERROR_CONFLICTING_PARAMETERS, ((compShared->ll.uniqueId < compExclusive->ll.uniqueId) ? compExclusive : compShared), false);
					goto clean_exit;
				}

				// Determine shared or exclusive status
				if (compShared)
				{
					// Explicitly shared
					llIsExclusive	= false;

				} else if (compExclusive) {
					// Explicitly exclusive
					llIsExclusive	= true;

				} else {
					// Use the current SET default
					llIsExclusive	= propGet_settings_Exclusive(_settings);
				}


			//////////
			// If they specify IN, they must specify something after it
			//////
// TODO:  Untested function, breakpoint and examine
// debug_break;
				if (compIn && !compIn->ll.next)
				{
					iError_reportByNumber(thisCode, _ERROR_SYNTAX, compIn, false);
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				if (compIn)
					compIn = compIn->ll.nextComp;


			//////////
			// If they specified an alias, they must specify something after it
			//////
				if (compAlias && !compAlias->ll.next)
				{
					iError_reportByNumber(thisCode, _ERROR_SYNTAX, compAlias, false);
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				if (compAlias)
					compAlias = compAlias->ll.nextComp;


			//////////
			// What type of USE are we pursuing?
			//////
				if (compUse && !compUse->ll.next)
				{
					// USE ... They have specified USE by itself, closing the current work area
					if ((lnWorkArea = iDbf_get_workArea_current(thisCode, null)))
					{
						// Close it
						iDbf_close(thisCode, &gsWorkArea[lnWorkArea]);

					} else {
						// The current work area is invalid
						// Hmmm... this shouldn't ever happen. Ever. :-)
						iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, compUse, false);
					}

					// We're good
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				compUse = compUse->ll.nextComp;


		//////////
		// Find out if they specified a workarea
		//////
			// Note:  Right now, compIn is already pointing to the thing after "IN"
			if (compIn)
			{
				// Get what comes after the IN
				comp3 = NULL;
				comp4 = NULL;
				if ((comp2 = iComps_getNth(compIn, 1)) && (comp3 = iComps_getNth(comp2, 1)) && (comp4 = iComps_getNth(comp3, 1)))
				{
					// Placeholder to allow engagement through the if expression as far as it will go
				}

				// Find out what they're selecting
				if (compIn->iCode == _ICODE_SELECT)
				{
					// They've specified USE IN SELECT something
					// Perform tests on what comes after SELECT()
					if (!comp2) {
						// Syntax error
						iError_reportByNumber(thisCode, _ERROR_SYNTAX, compIn, false);
						goto clean_exit;

					} else if (comp2->iCode != _ICODE_PARENTHESIS_LEFT) {
						// Syntax error missing parenthesis
						iError_reportByNumber(thisCode, _ERROR_SYNTAX, comp2, false);
						goto clean_exit;

					} else if (!comp3) {
						// Syntax error missing parameter
						iError_reportByNumber(thisCode, _ERROR_MISSING_PARAMETER, comp2, false);
						goto clean_exit;

					} else if (!(comp4 = iComps_getNth(comp3, 1))) {
						// Syntax error
						iError_reportByNumber(thisCode, _ERROR_SYNTAX, comp3, false);
						goto clean_exit;

					} else if (comp4->iCode != _ICODE_PARENTHESIS_RIGHT) {
						// Syntax error parenthesis expected
						iError_reportByNumber(thisCode, _ERROR_PARENTHESIS_EXPECTED, comp4, false);
						goto clean_exit;
					}
					// Once we get here, we know we have SELECT(...something

					// They've specified USE IN SELECT(something)
					varInXyz = iEngine_get_variableName_fromComponent(thisCode, comp3, &llManufacturedAliasName);

				} else {
					// They must've specified a number or alias name
					varInXyz = iEngine_get_variableName_fromComponent(thisCode, compIn, &llManufacturedAliasName);
				}
			}


		//////////
		// See if they specified an integer or character for the SELECT()
		//////
			if (varInXyz)
			{
				//////////
				// See what they specified
				//////
					if (iVariable_isTypeNumeric(varInXyz))
					{
						// They're are specifying a number
						lnWorkArea = iiVariable_getAs_s32(thisCode, varInXyz, false, &error, &errorNum);
						if (error)	{ iError_reportByNumber(thisCode, errorNum, compIn, false); return; }

					} else if (iVariable_isTypeCharacter(varInXyz)) {
						// They specified something character (could be a work area letter, or alias)
						if (iDbf_isWorkAreaLetter(thisCode, varInXyz))
						{
							// Work area letter
							lnWorkArea = (s32)iUpperCase(varInXyz->value.data_s8[0]) - (s32)'A' + 1;

						} else {
							// Alias name
							lnWorkArea = (s32)iDbf_get_workArea_byAlias(thisCode, varInXyz, null);
						}

						// Did we get a valid work area?
						if (lnWorkArea < 0)
						{
							iError_reportByNumber(thisCode, _ERROR_ALIAS_NOT_FOUND, iVariable_compRelated(thisCode, varInXyz), false);
							goto clean_exit;
						}
						// If we get here, we have our work area number

					} else {
						// Unrecognized syntax
						iError_reportByNumber(thisCode, _ERROR_SYNTAX, compIn->ll.nextComp, false);
						goto clean_exit;
					}

			} else {
				// Just grab the current work area
				lnWorkArea = (s32)iDbf_get_workArea_current(thisCode, null);
			}


		//////////
		// Was "USE IN..." specified?
		//////
			// Note:  Right now, compUse is already pointing to the thing after "USE"
			if (compUse->iCode == _ICODE_IN)
			{
				// Yes, close that work area and we're done
				iDbf_close(thisCode, &gsWorkArea[lnWorkArea]);
				goto clean_exit;
			}


		//////////
		// Get the table name
		//////
			// Note:  compUse is actually pointing to whatever was after USE by this point
			if ((varTableName = iEngine_get_variableName_fromComponent(thisCode, compUse, &llManufacturedTableName))) {
				// Placeholder, we were able to obtain a variable name
				// Note:  The variable is checked for sanity below

			} else if ((varTableName = iEngine_get_contiguousComponents(thisCode, compUse, &llManufacturedTableName, NULL, 0))) {
					// Placeholder, we were able to obtain a contiguous stream of characters
//////////
// TODO:	Enhancement consideration.  May not ever be needed.
//
//			For the contiguous components grab, it may be desirable to pass an array through to obtain only
//			those components that are known to be part of a valid pathname for the target OS.  This could
//			also be setup to be specified by a SET VALID_PATHNAME_CHARS TO cString to allow that string to
//			be parsed out and the components derived obtained therein.  Such a creature would generally look
//			like this:
//
// 				#define _VALID_PATHNAME_ICODE_ARRAY_COUNT 7
// 				s32 gnValidPathname_iCodeArray[_VALID_PATHNAME_ICODE_ARRAY_COUNT];
//
// 				gnValidPathname_iCodeArray[0] = _ICODE_ALPHA;
// 				gnValidPathname_iCodeArray[1] = _ICODE_NUMERIC;
// 				gnValidPathname_iCodeArray[2] = _ICODE_ALPHANUMERIC;
// 				gnValidPathname_iCodeArray[3] = _ICODE_COLON;
// 				gnValidPathname_iCodeArray[4] = _ICODE_BACKSLASH;
// 				gnValidPathname_iCodeArray[5] = _ICODE_DOT;
// 				gnValidPathname_iCodeArray[6] = _ICODE_UNDERSCORE;
// 				// Plus any other characters to add
//
//			And in use:
//				iEngine_get_contiguousComponents(compUse, &llManufacturedTableName, &gnValidPathname_iCodeArray[0], _VALID_PATHNAME_ICODE_ARRAY_COUNT)
//////
			}

			// Is it valid?
			if (!varTableName || !iVariable_isTypeCharacter(varTableName))
			{
				// We didn't get what we needed
				iError_reportByNumber(thisCode, _ERROR_UNRECOGNIZED_PARAMETER, compUse, false);
				goto clean_exit;
			}
			// Note:	The parameter, while character, may still be incorrect.
			//			It may be an invalid filename.  That will be sorted out on the open.


		//////////
		// If they didn't specify AGAIN, make sure it's not already open
		//////
			if (!compAgain)
			{
				// No AGAIN clause was specified, so make sure it isn't already found as being in use
				if (iDbf_get_workArea_byTablePathname(thisCode, varTableName, null) >= 0)
				{
					// It was found, which means it's already in use
					iError_reportByNumber(thisCode, _ERROR_TABLE_ALREADY_IN_USE, compUse, false);
					goto clean_exit;
				}
			}


		//////////
		// Get the alias name, making sure it's unique amongst the other alias name
		//////
			if (compAlias)
			{
				// They've specified an alias
				varAliasName	= iEngine_get_variableName_fromComponent(thisCode, compAlias->ll.nextComp, &llManufacturedTableName);
				lnWorkAreaAlias	= iDbf_get_workArea_byAlias(thisCode, varAliasName, null);
				if (lnWorkAreaAlias > 0)
				{
					// They've specified an alias name
					// If it's the current work area, or the one they specified with the "IN xyz" clause, then we're okay
					if (lnWorkArea != lnWorkAreaAlias)
					{
						// Nope, they're trying to re-use an alias already in use
						iError_reportByNumber(thisCode, _ERROR_ALIAS_ALREADY_IN_USE, compAlias, false);
						goto clean_exit;
					}
					// If we get here, the work area is okay

				} else {
					// Unknown alias
					iError_reportByNumber(thisCode, _ERROR_ALIAS_NOT_FOUND, compAlias, false);
					goto clean_exit;
				}

			} else {
				// We need to construct the alias from the table name
				varAliasName = iDbf_get_alias_fromPathname(thisCode, varTableName, null);
			}
			if (!varAliasName)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, compUse, false);
				goto clean_exit;
			}


		//////////
		// See if the current work area already has a table open
		//////
			llIsInUse = iDbf_isWorkAreaUsed(thisCode, &gsWorkArea[lnWorkArea], &llIsValidWorkArea);
			if (!llIsValidWorkArea)
			{
				// They specified an invalid work area number
				iError_reportByNumber(thisCode, _ERROR_INVALID_WORK_AREA, compIn, false);
				goto clean_exit;

			} else if (llIsInUse) {
				// If it's already open, close it
				iDbf_close(thisCode, &gsWorkArea[lnWorkArea]);
			}


		//////////
		// Get the alias
		//////
			iDbf_set_workArea_current(thisCode, (u32)lnWorkArea, null);
			lnWorkArea = iDbf_open(thisCode, varTableName, varAliasName, llIsExclusive, (compAgain != NULL), (compValidate != NULL));
			if (lnWorkArea < 0)
			{
				// The negative work area number indicates the error
				switch (lnWorkArea)
				{
					case -1:
						// General error
						iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_OPEN_TABLE, compUse, false);
						break;

					case -2:
						// Work area is not free
						iError_reportByNumber(thisCode, _ERROR_WORK_AREA_ALREADY_IN_USE, compUse, false);
						break;

					case -3:
						// Error in DBC
						iError_reportByNumber(thisCode, _ERROR_ERROR_OPENING_DBC, compUse, false);
						break;

					default:
						// Unexpected error (shouldn't happen)
						iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, compUse, false);
						break;
				}

			} else {
				// Set any meta data about the table
//				SComp*	compAgain				= iComps_findNextBy_iCode(compUse, _ICODE_AGAIN,				NULL);
//				SComp*	compNoRequery			= iComps_findNextBy_iCode(compUse, _ICODE_NOREQUERY,			NULL);
//				SComp*	compNoData				= iComps_findNextBy_iCode(compUse, _ICODE_NODATA,				NULL);
//				SComp*	compNoUpdate			= iComps_findNextBy_iCode(compUse, _ICODE_NOUPDATE,				NULL);
//				SComp*	compExclamationPoint	= iComps_findNextBy_iCode(compUse, _ICODE_EXCLAMATION_POINT,	NULL);
//				SComp*	compIn					= iComps_findNextBy_iCode(compUse, _ICODE_IN,					NULL);
//				SComp*	compIndex				= iComps_findNextBy_iCode(compUse, _ICODE_INDEX,				NULL);
//				SComp*	compOrder				= iComps_findNextBy_iCode(compUse, _ICODE_ORDER,				NULL);
//				SComp*	compTag					= iComps_findNextBy_iCode(compUse, _ICODE_TAG,					NULL);
//				SComp*	compAscending			= iComps_findNextBy_iCode(compUse, _ICODE_ASCENDING,			NULL);
//				SComp*	compDescending			= iComps_findNextBy_iCode(compUse, _ICODE_DESCENDING,			NULL);
//				SComp*	compAlias				= iComps_findNextBy_iCode(compUse, _ICODE_ALIAS,				NULL);
//				SComp*	compExclusive			= iComps_findNextBy_iCode(compUse, _ICODE_EXCLUSIVE,			NULL);
//				SComp*	compShared				= iComps_findNextBy_iCode(compUse, _ICODE_SHARED,				NULL);
//				SComp*	compConnString			= iComps_findNextBy_iCode(compUse, _ICODE_CONNSTRING,			NULL);
			}

clean_exit:
			// Release variables
			if (varInXyz)			iVariable_delete(thisCode, varInXyz,		true);
			if (varTableName)		iVariable_delete(thisCode, varTableName,	true);
			if (varAliasName)		iVariable_delete(thisCode, varAliasName,	true);
	}
