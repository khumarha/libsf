//////////
//
// /libsf/source/vjr/vjr.cpp
//
//////
// Version 0.54
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




#include "vjr.h"




int CALLBACK WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR		lpCmdLine,
						int			nCmdShow	)
{
	MSG		msg;
	HACCEL	hAccelTable;


	//////////
	// Initialize
	//////
		ghInstance = hInstance;
		iVjr_init(&hAccelTable);
		iVjr_appendSystemLog("Initialization complete");


	//////////
	// Read events
	//////
		iVjr_appendSystemLog("Engage main loop");
		while (!glShuttingDown && GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// When the WM_QUIT message is received, we exit


	//////////
	// Do allocated resource shutdown
	//////
		if (!glShuttingDown)
			iVjr_shutdown();


	//////////
	// Return our exit code
	//////
		return((int)msg.wParam);
}




//////////
//
// Startup initialization, called from WinMain() only.
//
//////
	void iVjr_init(HACCEL* hAccelTable)
	{
		RECT		lrc;
		s8			logBuffer[256];
		SBitmap*	bmp;


		// Get startup time
		systemStartedTickCount	= GetTickCount();
		systemStartedMs			= iTime_getLocalMs();

		// Default value for spinners
		gsProps_master[_INDEX_INCREMENT]._f64	= 1.0;		// Default to 1.0 for incrementing
		gsProps_master[_INDEX_ROUND_TO]._f64	= 0.01;		// Default to 2 decimal places

		// Create a 1x1 no image bitmap placeholder
		bmpNoImage = iBmp_allocate();
		iBmp_createBySize(bmpNoImage, 1, 1, 24);

		// Initialize primitive variables
		iSettings_push();
		iVariable_createDefaultValues();
		iVariable_createPropsMaster();
		varConstant_space		= iVariable_createAndPopulate(_VAR_TYPE_CHARACTER, cgc_spaceText, 1);
		varEmptyString			= iVariable_createAndPopulate(_VAR_TYPE_CHARACTER, (s8*)NULL, 0);
		var2000Spaces			= iVariable_create(_VAR_TYPE_CHARACTER, NULL);
		varTrue					= iVariable_createAndPopulate(_VAR_TYPE_LOGICAL, (s8*)NULL, 0);
		varFalse				= iVariable_createAndPopulate(_VAR_TYPE_LOGICAL, (s8*)NULL, 0);

		// 2000 blank spaces
		iDatum_allocateSpace(&var2000Spaces->value, 2000);
		memset(var2000Spaces->value.data, 32, 2000);

		// Constant logical
		*varTrue->value.data_s8		= (s8)_LOGICAL_TRUE;
		*varFalse->value.data_s8	= (s8)_LOGICAL_FALSE;

		// Keyboard shortcuts
		*hAccelTable = LoadAccelerators(ghInstance, MAKEINTRESOURCE(IDC_VJR));

		// Initialize our critical sections
		InitializeCriticalSection(&cs_uniqueIdAccess);
		InitializeCriticalSection(&cs_logData);

		// These arrows are used as a standard throughout the system for the size of an icon.
		// They must be loaded first.
		bmpArrowUl		= iBmp_rawLoad(cgc_arrowUlBmp);
		bmpArrowUr		= iBmp_rawLoad(cgc_arrowUrBmp);
		bmpArrowLl		= iBmp_rawLoad(cgc_arrowLlBmp);
		bmpArrowLr		= iBmp_rawLoad(cgc_arrowLrBmp);

		// Initialize our builders
		iBuilder_createAndInitialize(&gWindows,	-1);
		iBuilder_createAndInitialize(&gFonts,	-1);

		// Default font
		gsFontDefault				= iFont_create(cgcFontName_default,			10,	FW_NORMAL,	0, 0);
		gsFontDefault9				= iFont_create(cgcFontName_default,			9,	FW_NORMAL,	0, 0);
		gsFontDefaultBold			= iFont_create(cgcFontName_default,			10,	FW_BOLD,	0, 0);
		gsFontDefaultItalic8		= iFont_create(cgcFontName_default,			8,	FW_NORMAL,	1, 0);
		gsFontDefaultFixedPoint		= iFont_create(cgcFontName_defaultFixed,	10,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFont		= iFont_create(cgcFontName_windowTitleBar,	12,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFontSubform	= iFont_create(cgcFontName_windowTitleBar,	10,	FW_NORMAL,	0, 0);
		gsFontDefaultTooltip		= iFont_create(cgcFontName_defaultTooltip,	9,	FW_BOLD,	0, 0);
		gsFontCask					= iFont_create(cgcFontName_cask,			20, FW_BOLD,	0, 0);

		// Initialize the sound system
		isound_initialize();
		memset(&gseRootSounds, 0, sizeof(gseRootSounds));	// Initialize our root sounds array

//////////
// Jul.29.2014
// Removed due to limitations in the Shobjidl.h in MinGW.  Can be manually re-added with copy-and-paste... enjoy doing that! :-)
//		// Taskbar interface
//		HRESULT		hRes;
//		hRes = OleInitialize(NULL);
//		CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);
//////////


		//////////
		// Allocate a sourceLight area
		//////
			bmpSourceLight = iBmp_allocate();
			iBmp_createBySize(bmpSourceLight, 800, 1024, 24);
			iSourceLight_reset();


		//////////
		// Load our icons and images
		//////
			bmpVjrIcon						= iBmp_rawLoad(cgc_appIconBmp);
			bmpJDebiIcon					= iBmp_rawLoad(cgc_jdebiAppIconBmp);
			bmpSourceCodeIcon				= iBmp_rawLoad(cgc_sourcecodeIconBmp);
			bmpLocalsIcon					= iBmp_rawLoad(cgc_localsIconBmp);
			bmpWatchIcon					= iBmp_rawLoad(cgc_watchIconBmp);
			bmpCommandIcon					= iBmp_rawLoad(cgc_commandIconBmp);
			bmpDebugIcon					= iBmp_rawLoad(cgc_debugIconBmp);
			bmpOutputIcon					= iBmp_rawLoad(cgc_outputIconBmp);
			bmpSourceLightIcon				= iBmp_rawLoad(cgc_sourcelightIconBmp);

			// Carousels
			bmpCarouselCarouselIcon			= iBmp_rawLoad(cgc_carouselCarouselBmp);
			bmpCarouselTabsIcon				= iBmp_rawLoad(cgc_carouselTabsBmp);
			bmpCarouselPad					= iBmp_rawLoad(cgc_carouselPadBmp);
			bmpCarouselIcon					= iBmp_rawLoad(cgc_carouselIconBmp);

			bmpClose						= iBmp_rawLoad(cgc_closeBmp);
			bmpMaximize						= iBmp_rawLoad(cgc_maximizeBmp);
			bmpMinimize						= iBmp_rawLoad(cgc_minimizeBmp);
			bmpMove							= iBmp_rawLoad(cgc_moveBmp);

			bmpCheckboxOn					= iBmp_rawLoad(cgc_checkboxOnBmp);
			bmpCheckboxOff					= iBmp_rawLoad(cgc_checkboxOffBmp);

			bmpButton						= iBmp_rawLoad(cgc_buttonBmp);
			bmpTextbox						= iBmp_rawLoad(cgc_textboxBmp);

			bmpStoplightRed					= iBmp_rawLoad(cgc_stoplightRedBmp);
			bmpStoplightAmber				= iBmp_rawLoad(cgc_stoplightAmberBmp);
			bmpStoplightGreen				= iBmp_rawLoad(cgc_stoplightGreenBmp);
			bmpStoplightBlue				= iBmp_rawLoad(cgc_stoplightBlueBmp);

			bmpBreakpointAlways				= iBmp_rawLoad(cgc_breakpointAlways);
			bmpBreakpointAlwaysCountdown	= iBmp_rawLoad(cgc_breakpointAlwaysCountdown);
			bmpConditionalTrue				= iBmp_rawLoad(cgc_breakpointConditionalTrue);
			bmpConditionalFalse				= iBmp_rawLoad(cgc_breakpointConditionalFalse);
			bmpConditionalTrueCountdown		= iBmp_rawLoad(cgc_breakpointConditionalTrueCountdown);
			bmpConditionalFalseCountdown	= iBmp_rawLoad(cgc_breakpointConditionalFalseCountdown);

			bmpDapple1						= iBmp_rawLoad(cgc_dappleBmp);
			bmpDapple2						= iBmp_rawLoad(cgc_dapple2Bmp);

			//////////
			// Casks
			//////
				iVjr_init_loadCaskIcons();


			//////////
			// The radio image has a 44x44 dot in the upper-left.
			//////
				bmpRadio	= iBmp_rawLoad(cgc_radioBmp);											// Load the raw bmpRadio
				bmpRadioDot = iBmp_createAndExtractRect(bmpRadio, 0, 0, 44, 44);					// Extract the 44x44 rectangle
				SetRect(&lrc, 0, 0, 44, 44);
				iBmp_fillRect(bmpRadio, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);		// And cover it up with white


		if (glShowSplash)
		{
			// Load the splash screen
			bmpVjrSplash = iBmp_rawLoad(cgc_splashBmp);
			bmp = iiVjr_buildSplashScreen(bmpVjrSplash);
			CreateThread(0, 0, &iSplash_show, bmp, 0, 0);
		}

		// Play the startup music if any
		sprintf(logBuffer, "VJr launched %u milliseconds after system boot\0", systemStartedTickCount);
		iVjr_appendSystemLog(logBuffer);
		if (glShowSplash)
			CreateThread(0, 0, &iPlay_ariaSplash, (LPVOID)cgcSoundStartupWav, 0, 0);

		// Focus window accumulator
		iVjr_appendSystemLog("Create focus highlight buffer");
		iBuilder_createAndInitialize(&gFocusHighlights, -1);

		// Create the default reference datetimes
		iVjr_appendSystemLog("Create default datetime variables");
		iInit_createDefaultDatetimes();

		// Create our message window
		iVjr_appendSystemLog("Create message window");
		iInit_createMessageWindow();

		// Create our global variables
		iVjr_appendSystemLog("Create global variables");
		varGlobals = function_datetime(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		iDatum_duplicate(&varGlobals->name, cgcName_startupTime, -1);

		// Create our default objects
		iVjr_appendSystemLog("Create default objects");
		iInit_createDefaultObjects();

		// Create our main screen window
		iVjr_appendSystemLog("TEMPORARY:  Manually create _jdebi");
		iInit_create_jdebi();

		// Initially render each one
		iVjr_appendSystemLog("Render _jdebi");
		iObj_render(_jdebi, true);

		// Attach them to physical windows
		iVjr_appendSystemLog("Allocate OS Window for _jdebi");
		gWinJDebi = iWindow_allocate();
		iObj_createWindowForForm(_jdebi, gWinJDebi, IDI_JDEBI);

		// Initially populate _screen
		// Load in the history if it exists
		if (!iSEM_loadFromDisk(screenData, (s8*)cgcScreenDataFilename, false, true))
		{
			// Indicate success
			sprintf(logBuffer, "Loaded: %s\0", cgcScreenDataFilename);
			iSEM_appendLine(output_editbox->p.sem, logBuffer, strlen(logBuffer), false);
			iVjr_appendSystemLog("Populate _screen with default data");
			iSEM_appendLine(screenData, (s8*)cgcScreenTitle, -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
			iSEM_appendLine(screenData, (s8*)"Please report any bugs:  http://www.visual-freepro.org/vjr", -1, false);
			iSEM_appendLine(screenData, (s8*)"Thank you, and may the Lord Jesus Christ bless you richly. :-)", -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
			iSEM_appendLine(screenData, (s8*)"              _____", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (s8*)"     ________|     |________     In God's sight we've come together.", -1, false);
			iSEM_appendLine(screenData, (s8*)"    |                       |    We've come together to help each other.", -1, false);
			iSEM_appendLine(screenData, (s8*)"    |________       ________|    Let's grow this project up ... together!", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |             In service and love to The Lord, forever!", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |             Sponsored by:", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |                LibSF -- Liberty Software Foundation", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |             We need more coders. Please consider helping out.", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |             Your contribution would make a difference.", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (s8*)"             |_____|", -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
		}
		// Navigate to the end of the content
		iSEM_navigateToEndLine(screenData, _screen);

		// Initially populate _jdebi
		// Load in the history if it exists
		if (!iSEM_loadFromDisk(command_editbox->p.sem, (s8*)cgcCommandHistoryFilename, true, true))
		{
			// Indicate success
			sprintf(logBuffer, "Loaded: %s\0", cgcCommandHistoryFilename);
			iSEM_appendLine(output_editbox->p.sem, logBuffer, strlen(logBuffer), false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** Welcome to Visual FreePro, Junior! :-)", -1, false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** For now, this can be thought of as a command window ... with a twist.", -1, false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** It works like an editor window.  You can insert new lines, edit old ones, etc.", -1, false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** To execute a command, press F6 or Enter if you're on the last line, or use F6 on any line.", -1, false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** You can use clear, quit, ? 999, ? \"sample\" (literals), and ? _startupTime (global variable) in this daily build.", -1, false);
			iSEM_appendLine(command_editbox->p.sem, (s8*)"*** Remember this always:  Love makes you smile. It keeps an inward peace unlike any other. :-)", -1, false);
		}

		// Navigate to the last line
		iSEM_navigateToEndLine(command_editbox->p.sem, command_editbox);

		// Make sure there's a blank line at the end
		if (command_editbox->p.sem->line_cursor->sourceCode_populatedLength != 0)
		{
			iSEM_appendLine(command_editbox->p.sem, NULL, 0, false);
			iSEM_navigateToEndLine(command_editbox->p.sem, command_editbox);
		}

		// Load some source code
		if (iSEM_loadFromDisk(sourceCode_editbox->p.sem, (s8*)cgcStartupPrgFilename, true, true))
		{
			// Indicate success
			sprintf(logBuffer, "Loaded: %s\0", cgcStartupPrgFilename);
			iSEM_appendLine(output_editbox->p.sem, logBuffer, strlen(logBuffer), false);
		}

		// Redraw
		iVjr_appendSystemLog("Final render _jdebi");
		iWindow_render(gWinJDebi, true);

		// Remove the splash screen 1/2 second later
		CreateThread(0, 0, &iSplash_delete, (LPVOID)500, 0, 0);

		// Create a thread to display the content in 3D
		CreateThread(0, 0, &iGrace, 0, 0, 0);
	}
