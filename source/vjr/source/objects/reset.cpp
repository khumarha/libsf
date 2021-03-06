//////////
//
// /libsf/source/vjr/source/objects/reset.cpp
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
//     Dec.18.2014
//////
// Change log:
//     Dec.18.2014 - Initial creation
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
//









//////////
//
// Called to reset the object to its hard defaults.
//
//////
	void iiSubobj_resetToDefaultEmpty(SThisCode* thisCode, SObject* empty, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (empty)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, empty, true, true, propList, tnPropCount);
		}

		// No object-specific initialization because empty objects do nothing except exist as placeholders
	}

	void iiSubobj_resetToDefaultForm(SThisCode* thisCode, SObject* form, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		SObject*	objChild;
		SBitmap*	bmp;
		RECT		lrc;


		logfunc(__FUNCTION__);
		if (form)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, form, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&form->rc, 0, 0, 375, 250);
				SetRect(&form->rco, 0, 0, 375, 250);
				SetRect(&form->rcp, 0, 0, 375, 250);

				// Set the size of the child components
				iObj_setSize(thisCode, form, 0, 0, 375, 250);

				// Font
				iFont_delete(&form->p.font, true);
				form->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set default anchor to fixed in all positions, no resize
			//////
				propSetAnchor(form, _ANCHOR_FIXED_NORESIZE);
				propSetBackColor(form, whiteColor);
				propSetForeColor(form, blackColor);
				propSetIcon(form, bmpVjrIcon);
				propSetCaption(form, cgcName_form);
				propSetPictureBmp(form, bmpNoImage);


			//////////
			// Reset our min/max
			//////
				SetRect(&form->p.rcMax, -1, -1, -1, -1);
				SetRect(&form->p.rcMin, -1, -1, -1, -1);


			//////////
			// Default child settings
			//////
				SetRect(&lrc, 0, 0, bmpArrowUl->bi.biWidth, bmpArrowUl->bi.biHeight);
				objChild = form->firstChild;
				while (objChild)
				{
					// See which object this is
					if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
					{
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Form icon
						propSetPictureBmp(objChild, bmpVjrIcon);
						propSetPictureBmpDown(objChild, bmpVjrIcon);
						propSetPictureBmpOver(objChild, bmpVjrIcon);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
						// Caption
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left + bmpVjrIcon->bi.biWidth + 2, objChild->rc.top, objChild->rc.right - objChild->rc.left, bmpVjrIcon->bi.biHeight);

						propSetCaption(objChild, cgcName_formCaption);
						iObjProp_set_s32_direct(thisCode, objChild, _INDEX_BACKSTYLE, _BACK_STYLE_TRANSPARENT);
						iFont_delete(&objChild->p.font, true);
						objChild->p.font		= iFont_create(cgcFontName_windowTitleBar, 11, FW_NORMAL, false, false);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMove)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Move icon
						propSetPictureBmp(objChild, bmpMove);
						propSetPictureBmpDown(objChild, bmpMove);
						propSetPictureBmpOver(objChild, bmpMove);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMinimize)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Minimize icon
						propSetPictureBmp(objChild, bmpMinimize);
						propSetPictureBmpDown(objChild, bmpMinimize);
						propSetPictureBmpOver(objChild, bmpMinimize);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);
						iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);
						iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMaximize)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Maximize icon
						propSetPictureBmp(objChild, bmpMaximize);
						propSetPictureBmpDown(objChild, bmpMaximize);
						propSetPictureBmpOver(objChild, bmpMaximize);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconClose)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Close icon
						propSetPictureBmp(objChild, bmpClose);
						propSetPictureBmpDown(objChild, bmpClose);
						propSetPictureBmpOver(objChild, bmpClose);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleUl)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Arrow icon
						propSetPictureBmp(objChild, bmpArrowUl);
						propSetPictureBmpDown(objChild, bmpArrowUl);
						propSetPictureBmpOver(objChild, bmpArrowUl);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleUr)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Arrow icon
						propSetPictureBmp(objChild, bmpArrowUr);
						propSetPictureBmpDown(objChild, bmpArrowUr);
						propSetPictureBmpOver(objChild, bmpArrowUr);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleLr)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Arrow icon
						propSetPictureBmp(objChild, bmpArrowLr);
						propSetPictureBmpDown(objChild, bmpArrowLr);
						propSetPictureBmpOver(objChild, bmpArrowLr);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleLl)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Arrow icon
						propSetPictureBmp(objChild, bmpArrowLl);
						propSetPictureBmpDown(objChild, bmpArrowLl);
						propSetPictureBmpOver(objChild, bmpArrowLl);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);
					}

					// Move to next object
					objChild = objChild->ll.nextObj;
				}
		}
	}

	void iiSubobj_resetToDefaultSubform(SThisCode* thisCode, SObject* subform, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		SObject*	objChild;
		SBitmap*	bmp;
		RECT		lrc;


		logfunc(__FUNCTION__);
		if (subform)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, subform, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&subform->rc, 0, 0, 200, 100);
				SetRect(&subform->rco, 0, 0, 200, 100);
				SetRect(&subform->rcp, 0, 0, 200, 100);

				// Set the size of the child components
				iObj_setSize(thisCode, subform, 0, 0, 200, 100);

				// Font
				iFont_delete(&subform->p.font, true);
				subform->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set the defaults
			//////
				propSetAnchor(subform, _ANCHOR_FIXED_NORESIZE);
				propSetBackColor(subform, whiteColor);
				propSetBackStyle(subform, _BACK_STYLE_TRANSPARENT);
				propSetForeColor(subform, blackColor);
				propSetIcon(subform, bmpVjrIcon);
				propSetCaption(subform, cgcName_subform);


			//////////
			// Default child settings
			//////
				SetRect(&lrc, 0, 0, bmpArrowUl->bi.biWidth, bmpArrowUl->bi.biHeight);
				objChild = subform->firstChild;
				while (objChild)
				{
					// See which object this is
					if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
					{
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, bmpVjrIcon->bi.biWidth, bmpVjrIcon->bi.biHeight);

						// Form icon
						propSetPictureBmp(objChild, bmpVjrIcon);
						propSetPictureBmpDown(objChild, bmpVjrIcon);
						propSetPictureBmpOver(objChild, bmpVjrIcon);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.5f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.5f);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
						// Caption
						iObjProp_set_character_direct(thisCode, objChild, _INDEX_CAPTION, cgcName_formCaption, -1);
						iObjProp_set_s32_direct(thisCode, objChild, _INDEX_BACKSTYLE, _BACK_STYLE_TRANSPARENT);
						iFont_delete(&objChild->p.font, true);
						objChild->p.font = iFont_create(cgcFontName_windowTitleBar, 10, FW_NORMAL, false, false);
						propSetVisible(objChild, _LOGICAL_TRUE);
					}

					// Move to next object
					objChild = objChild->ll.nextObj;
				}
		}
	}

	void iiSubobj_resetToDefaultCarousel(SThisCode* thisCode, SObject* carousel, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		bool		llVisible;
		RECT		lrc;
		SBitmap*	bmp;
		SObject*	objChild;


		logfunc(__FUNCTION__);
		if (carousel)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, carousel, true, true, propList, tnPropCount);


			//////////
			// Standard default settings
			//////
				propSetAlignment(carousel, _ALIGNMENT_BOTTOM);
				propSetTitlebar(carousel, _LOGICAL_FALSE);
				propSetBorderStyle(carousel, _BORDER_STYLE_FIXED);
				iFont_delete(&carousel->p.font, true);
				carousel->p.font = iFont_create(cgcFontName_windowTitleBar, 10, FW_NORMAL, false, false);


			//////////
			// Set default size and position
			//////
				SetRect(&carousel->rc, 0, 0, 320, 480);
				SetRect(&carousel->rco, 0, 0, 320, 480);
				SetRect(&carousel->rcp, 0, 0, 320, 480);

				// Set the size
				iObj_setSize(thisCode, carousel, 0, 0, 320, 480);


			//////////
			// Default child settings
			//////
				SetRect(&lrc, 0, 0, bmpArrowUl->bi.biWidth, bmpArrowUl->bi.biHeight);
				llVisible	= propTitleBar(carousel);
				objChild	= carousel->firstChild;
				while (objChild)
				{
					// See which object this is
					if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
					{
						// Carousel icon
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP,		bmpCarouselIcon);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_DOWN,	bmpCarouselIcon);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_OVER,	bmpCarouselIcon);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetVisible_fromBool(objChild, llVisible);


					} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
						// Caption
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						propSetAlignment(objChild, _ALIGNMENT_MIDDLE_LEFT);
						propSetVisible_fromBool(objChild, llVisible);

						// Titlebar font
						iFont_delete(&objChild->p.font, true);
						objChild->p.font = iFont_create(cgcFontName_windowTitleBar, 10, FW_NORMAL, false, false);
						propSetCaption(carousel, cgcName_carouselCaption);


					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconCarousel)) {
						// Carousel tabs icon
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP,		bmpCarouselTabsIcon);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_DOWN,	bmpCarouselTabsIcon);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_OVER,	bmpCarouselTabsIcon);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetVisible_fromBool(objChild, llVisible);


					} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconClose)) {
						// Close icon
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP,		bmpClose);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_DOWN,	bmpClose);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_OVER,	bmpClose);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f);
						propSetVisible_fromBool(objChild, llVisible);
					}

					// Move to next object
					objChild = objChild->ll.nextObj;
				}

		}
	}

	void iiSubobj_resetToDefaultRider(SThisCode* thisCode, SObject* rider, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (rider)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, rider, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&rider->rc, 0, 0, 320, 480);
				SetRect(&rider->rco, 0, 0, 320, 480);
				SetRect(&rider->rcp, 0, 0, 320, 480);

				// Set the size
				iObj_setSize(thisCode, rider, 0, 0, 320, 480);
		}
	}

	void iiSubobj_resetToDefaultLabel(SThisCode* thisCode, SObject* label, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (label)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, label, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&label->rc, 0, 0, 40, 17);
				SetRect(&label->rco, 0, 0, 40, 17);
				SetRect(&label->rcp, 0, 0, 40, 17);

				// Set the size
				iObj_setSize(thisCode, label, 0, 0, 40, 17);

				// Font
				iFont_delete(&label->p.font, true);
				label->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set the default colors
			//////
				propSetBackColor(label, whiteColor);
				propSetForeColor(label, blackColor);


			//////////
			// Set the characteristics
			//////
				propSetAlignment(label, _ALIGNMENT_LEFT);
				propSetCaption(label, cgcName_label);
				propSetBackStyle(label, _BACK_STYLE_TRANSPARENT);
				propSetBorderStyle(label, _BORDER_STYLE_NONE);
				propSetBorderColor(label, blackColor);
				propSetDisabledBackColor(label, disabledBackColor);
				propSetDisabledForeColor(label, disabledForeColor);
		}
	}

	void iiSubobj_resetToDefaultTextbox(SThisCode* thisCode, SObject* textbox, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (textbox)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, textbox, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&textbox->rc, 0, 0, 100, 23);
				SetRect(&textbox->rco, 0, 0, 100, 23);
				SetRect(&textbox->rcp, 0, 0, 100, 23);

				// Set the size
				iObj_setSize(thisCode, textbox, 0, 0, 100, 23);

				// Font
				iFont_delete(&textbox->p.font, true);
				textbox->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set the defaults
			//////
				propSetAnchor(textbox, _ANCHOR_FIXED_NORESIZE);
				propSetBackColor(textbox, whiteColor);
				propSetForeColor(textbox, blackColor);
				propSetStyle(textbox, _STYLE_3D);
				propSetAlignment(textbox, _ALIGNMENT_LEFT);
				propSetBackStyle(textbox, _BACK_STYLE_OPAQUE);
				propSetBorderStyle(textbox, _BORDER_STYLE_NONE);
				propSetBorderColor(textbox, blackColor);
				propSetSelectedBackColor(textbox, selectedBackColor);
				propSetSelectedForeColor(textbox, selectedForeColor);
				propSetDisabledBackColor(textbox, disabledBackColor);
				propSetDisabledForeColor(textbox, disabledForeColor);

		}
	}

	void iiSubobj_resetToDefaultButton(SThisCode* thisCode, SObject* button, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (button)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, button, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&button->rc, 0, 0, 84, 27);
				SetRect(&button->rco, 0, 0, 84, 27);
				SetRect(&button->rcp, 0, 0, 84, 27);

				// Set the size
				iObj_setSize(thisCode, button, 0, 0, 84, 27);

				// Font
				button->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set the default properties
			//////
				propSetBackColor(button, grayColor);
				propSetForeColor(button, blackColor);
				propSetStyle(button, _STYLE_3D);
				propSetAlignment(button, _ALIGNMENT_CENTER);
				propSetBackStyle(button, _BACK_STYLE_TRANSPARENT);
				propSetCaption(button, cgcName_button);
				propSetDisabledBackColor(button, disabledBackColor);
				propSetDisabledForeColor(button, disabledForeColor);

		}
	}

	void iiSubobj_resetToDefaultEditbox(SThisCode* thisCode, SObject* editbox, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (editbox)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, editbox, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&editbox->rc, 0, 0, 100, 53);
				SetRect(&editbox->rco, 0, 0, 100, 53);
				SetRect(&editbox->rcp, 0, 0, 100, 53);

				// Set the size
				iObj_setSize(thisCode, editbox, 0, 0, 100, 53);

				// Font
				editbox->p.font = iFont_duplicate(gsFontDefault);


			//////////
			// Set the defaults
			//////
				propSetBackColor(editbox, whiteColor);
				propSetForeColor(editbox, blackColor);
				propSetStyle(editbox, _STYLE_3D);
				propSetAlignment(editbox, _ALIGNMENT_LEFT);
				propSetBackStyle(editbox, _BACK_STYLE_OPAQUE);
				propSetBorderStyle(editbox, _BORDER_STYLE_NONE);
				propSetBorderColor(editbox, blackColor);
				propSetSelectedBackColor(editbox, selectedBackColor);
				propSetSelectedBackColor(editbox, selectedForeColor);
				propSetDisabledBackColor(editbox, disabledBackColor);
				propSetDisabledForeColor(editbox, disabledForeColor);

				iSEM_deleteChain(thisCode, &editbox->p.sem, true);
				editbox->p.sem = iSEM_allocate(thisCode, false);

		}
	}

	void iiSubobj_resetToDefaultImage(SThisCode* thisCode, SObject* image, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (image)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, image, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&image->rc, 0, 0, 100, 36);
				SetRect(&image->rco, 0, 0, 100, 36);
				SetRect(&image->rcp, 0, 0, 100, 36);

				// Set the size
				iObj_setSize(thisCode, image, 0, 0, 100, 36);


			//////////
			// Set the default values
			//////
				propSetStyle(image, _IMAGE_STYLE_OPAQUE);
				propSetPictureBmp(image, bmpNoImage);

		}
	}

	void iiSubobj_resetToDefaultCheckbox(SThisCode* thisCode, SObject* checkbox, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		SObject*	objChild;
		SBitmap*	bmp;
		RECT		lrc;


		logfunc(__FUNCTION__);
		if (checkbox)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, checkbox, true, true, propList, tnPropCount);


			//////////
			// Set default size, position, font
			//////
				SetRect(&checkbox->rc, 0, 0, 60, 17);
				SetRect(&checkbox->rco, 0, 0, 60, 17);
				SetRect(&checkbox->rcp, 0, 0, 60, 17);

				// Set the size
				iObj_setSize(thisCode, checkbox, 0, 0, 60, 17);

				// Font
				checkbox->p.font = iFont_duplicate(gsFontDefault9);


			//////////
			// Set the default values
			//////
				propSetValue_s32(checkbox, 0);

				propSetBackColor(checkbox, whiteColor);
				propSetForeColor(checkbox, blackColor);
				propSetAlignment(checkbox, _ALIGNMENT_LEFT);
				propSetStyle(checkbox, _STYLE_3D);
				propSetCaption(checkbox, cgcName_checkbox);
				propSetBackStyle(checkbox, _BACK_STYLE_TRANSPARENT);
				propSetBorderStyle(checkbox, _BORDER_STYLE_NONE);
				propSetBorderColor(checkbox, blackColor);
				propSetDisabledBackColor(checkbox, disabledBackColor);
				propSetDisabledForeColor(checkbox, disabledForeColor);


			//////////
			// Default child settings
			//////
				SetRect(&lrc, 0, 0, bmpArrowUl->bi.biWidth, bmpArrowUl->bi.biHeight);
				objChild = checkbox->firstChild;
				while (objChild)
				{
					// See which object this is
					if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_checkboxImage))
					{
						// Adjust the size
						iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, 17, objChild->rc.bottom);

						// Checkbox image
						bmp = iBmp_allocate();
						iBmp_createBySize(bmp, 17, 17, 24);

						// Based on type, populate the image
						if (iObjProp_get_s32_direct(thisCode, checkbox, _INDEX_VALUE) == 0)
						{
							// Off
							iBmp_scale(bmp, bmpCheckboxOff);	// Set the new

						} else {
							// On
							iBmp_scale(bmp, bmpCheckboxOn);		// Set the new
						}

						// Replicate that image for the over and down images
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP,			bmp);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_DOWN,	bmp);
						iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP_OVER,	bmp);

						// Delete the temporary image
						iBmp_delete(&bmp, true, true);

						// Add highlighting for the over and down
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.5f);
						bmp = iObjProp_get_bitmap(thisCode, objChild, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.5f);

						// Mark it for re-rendering
						objChild->isDirtyRender	= true;
						propSetVisible(objChild, _LOGICAL_TRUE);

					} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_checkboxLabel)) {
						// Adjust the size
						iObj_setSize(thisCode, objChild, 17, 0, 60, objChild->rc.bottom);

						// Checkbox label
						propSetCaption(objChild, cgcName_checkbox);
						propSetBackStyle(objChild, _BACK_STYLE_TRANSPARENT);
						iFont_delete(&objChild->p.font, true);
						objChild->p.font = iFont_duplicate(checkbox->p.font);

						// Mark it for re-rendering
						objChild->isDirtyRender	= true;
						propSetVisible(objChild, _LOGICAL_TRUE);
					}

					// Move to next object
					objChild = objChild->ll.nextObj;
				}
		}
	}

	void iiSubobj_resetToDefaultOption(SThisCode* thisCode, SObject* option, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (option)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, option, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&option->rc, 0, 0, 60, 40);
				SetRect(&option->rco, 0, 0, 60, 40);
				SetRect(&option->rcp, 0, 0, 60, 40);

				// Set the size
				iObj_setSize(thisCode, option, 0, 0, 60, 40);

				// Font
				option->p.font = iFont_duplicate(gsFontDefault9);


			//////////
			// Set the default values
			//////
				propSetBackColor(option, whiteColor);
				propSetForeColor(option, blackColor);
				propSetAlignment(option, _ALIGNMENT_LEFT);
				propSetStyle(option, _STYLE_3D);
				propSetCount(option, 0);
				propSetMultiSelect(option, _LOGICAL_FALSE);

		}
	}

	void iiSubobj_resetToDefaultRadio(SThisCode* thisCode, SObject* radio, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (radio)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, radio, true, true, propList, tnPropCount);


			//////////
			// Set default size and position
			//////
				SetRect(&radio->rc, 0, 0, 72, 72);
				SetRect(&radio->rco, 0, 0, 72, 72);
				SetRect(&radio->rcp, 0, 0, 72, 72);

				// Set the size
				iObj_setSize(thisCode, radio, 0, 0, 72, 72);

				// Font
				radio->p.font  = iFont_duplicate(gsFontDefault);


			//////////
			// Set the default properties
			//////
				propSetBackColor(radio, whiteColor);
				propSetForeColor(radio, blackColor);
				propSetAlignment(radio, _ALIGNMENT_LEFT);
				propSetStyle(radio, _STYLE_3D);

				propSetValue_f64(radio, 1.0);
				propSetValueMinimum(radio, 1.0);
				propSetValueMaximum(radio, 100.0);
				propSetValueRoundTo(radio, 1.0f);

				propSetBackStyle(radio, _BACK_STYLE_OPAQUE);
				propSetBorderStyle(radio, _BORDER_STYLE_NONE);
				propSetBorderColor(radio, blackColor);
				propSetDisabledBackColor(radio, disabledBackColor);
				propSetDisabledForeColor(radio, disabledForeColor);

		}
	}




	void iiSubobj_resetToDefaultCmdGroup(SThisCode* thisCode, SObject* cmdGroup, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (cmdGroup)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, cmdGroup, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultOptGroup(SThisCode* thisCode, SObject* optGroup, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (optGroup)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, optGroup, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultListbox(SThisCode* thisCode, SObject* listbox, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (listbox)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, listbox, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultCombobox(SThisCode* thisCode, SObject* combobox, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (combobox)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, combobox, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultFormset(SThisCode* thisCode, SObject* formset, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (formset)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, formset, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultToolbar(SThisCode* thisCode, SObject* toolbar, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (toolbar)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, toolbar, true, true, propList, tnPropCount);

				propSetBackColor(toolbar, toolbarBackColor);
				propSetBackStyle(toolbar, _BACK_STYLE_TRANSPARENT);
		}
	}

	void iiSubobj_resetToDefaultSeparator(SThisCode* thisCode, SObject* separator, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (separator)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, separator, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultLine(SThisCode* thisCode, SObject* line, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (line)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, line, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultShape(SThisCode* thisCode, SObject* shape, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (shape)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, shape, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultContainer(SThisCode* thisCode, SObject* container, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (container)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, container, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultControl(SThisCode* thisCode, SObject* control, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (control)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, control, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultGrid(SThisCode* thisCode, SObject* grid, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (grid)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, grid, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultColumn(SThisCode* thisCode, SObject* column, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (column)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, column, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultHeader(SThisCode* thisCode, SObject* header, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (header)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, header, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultOleBound(SThisCode* thisCode, SObject* oleBound, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (oleBound)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, oleBound, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultOleContain(SThisCode* thisCode, SObject* oleContain, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (oleContain)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, oleContain, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultSpinner(SThisCode* thisCode, SObject* spinner, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (spinner)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, spinner, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultTimer(SThisCode* thisCode, SObject* timer, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (timer)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, timer, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultHyperlink(SThisCode* thisCode, SObject* hyperlink, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (hyperlink)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, hyperlink, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultCollection(SThisCode* thisCode, SObject* collection, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (collection)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, collection, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultPage(SThisCode* thisCode, SObject* page, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (page)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, page, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultPageframe(SThisCode* thisCode, SObject* pageframe, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (pageframe)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, pageframe, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultSession(SThisCode* thisCode, SObject* session, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (session)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, session, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultCustom(SThisCode* thisCode, SObject* custom, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (custom)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, custom, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultException(SThisCode* thisCode, SObject* exception, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (exception)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, exception, true, true, propList, tnPropCount);
		}
	}

	void iiSubobj_resetToDefaultSettings(SThisCode* thisCode, SObject* settings, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount)
	{
		logfunc(__FUNCTION__);
		if (settings)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(thisCode, settings, true, true, propList, tnPropCount);
		}
	}
