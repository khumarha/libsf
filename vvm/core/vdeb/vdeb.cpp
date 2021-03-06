//////////
//
// /libsf/vvm/core/vdebug/vdebug.cpp
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
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.07.2012
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.20.2012 - Initial creation
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
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//



#include "windows.h"
#include "stdio.h"
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\oss\oss_class.h"
#include "\libsf\vvm\core\oss\oss_structs.h"
#include "vdeb_const.h"
#include "vdeb_defs.h"
#include "vdeb_glob.h"
#include "vdeb_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "vdeb_screens.h"




//////////
//
// Debugger entry point for Windows
//
//////
	BOOL APIENTRY DllMainW(	HMODULE		hModule,
							DWORD		ul_reason_for_call,
							LPVOID		lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
				break;
		}
		return TRUE;
	}




	// This function is called from the VVM after loading this DLL to give this debugger
	// the address to call for debugger API requests
	u64 CALLTYPE vdeb_firstCallback(u32 tnUniqueId)
	{
		DWORD lnThreadId;


		//////////
		// Load all VVM, VVMOSS and VVMMC functions from the VVM
		//////
			iLoadVvmFunctionsFromDll();
			iLoadOssFunctionsFromDll();
			iLoadMcFunctionsFromDll();


		//////////
		// Tell each DLL to initialize itself
		//////
			vvm_firstCallback(0);
			vvm_bootstrapInitialization();
			oss_firstCallback(0);
			oss_bootstrapInitialization();
			mc_firstCallback(0);
			mc_bootstrapInitialization();


		//////////
		// Load the resource, which contains text and graphics
		//////
			iLoadResource(vvm_getLanguage(NULL));


		//////////
		// Spawn the initial thread which will create and run the debugger instance
		//////
			CreateThread(0, 0, &iDebuggerMain, (void*)tnUniqueId, 0, &lnThreadId);


		// Indicate success
		return(gVvmFunctionCount);
	}




//////////
//
// Loads the indicated resource language for the debugger
//
//////
	bool iLoadResource(s8* tcLanguage)
	{
		s8 buffer[MAX_PATH];


		// Try to load the dll
		sprintf_s(buffer, sizeof(buffer), "vdebug%s.dll\000", tcLanguage);
		ghResourceDll = LoadLibraryA(buffer);
		if (!ghResourceDll)
		{
			// There was an error loading the indicated resource dll
			// Fallback to English
			ghResourceDll = LoadLibraryA(cgcVvmmcEngDll);
			if (!ghResourceDll)
				return(false);		// If we get here, then it's bad, bad, bad news, mister!
		}
		// We're good
		return(true);
	}




//////////
//
// Main debugger entry point after instantiation and connection to vvm
//
//////
	DWORD CALLTYPE iDebuggerMain(LPVOID lpParameter)
	{
		u32		lnDebuggerUid;
		u64		lnNumread, lnError, lnErrorCode;
		SBxml*	bxmlDebuggerSettings;


		//////////
		// Grab the unique id for this instance
		//////
			lnDebuggerUid = (u32)lpParameter;


		//////////
		// Build the debugger screen
		//////
			bxmlDebuggerSettings = vvm_bxmlLoad((s8*)gcVdebSettingsBxml, sizeof(gcVdebSettingsBxml) - 1, &lnNumread, &lnError, &lnErrorCode );
			if (bxmlDebuggerSettings)
				gsBxmlScreens = ivdeb_debuggerScreensCreate(bxmlDebuggerSettings);


		//////////
		// As long as the debugger is running, maintain this thread
		//////
			while (gsBxmlScreens && glDebuggerInstanceRunning)
			{
				// Everything is handled externally, we just check every 1/10th second if it's time to exit
				Sleep(100);
			}


		//////////
		// Delete the indicated screens
		//////
			ivdeb_debuggerScreensDelete(gsBxmlScreens);


		// Indicate success
		ExitThread(0);
	}




// Include support files for VDebug
#include "vdeb_sup.cpp"
