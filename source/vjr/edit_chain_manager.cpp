//////////
//
// /libsf/source/vjr/edit_chain_manager.cpp
//
//////
// Version 0.48
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.06.2014
//////
// Change log:
//     Jul.06.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
//
// Called to create a new EM (Edit Manager)
//
//////
	SEM* iSEM_allocate(bool tlIsSourceCode)
	{
		SEM* em;


		// Allocate a new structure
		em = (SEM*)malloc(sizeof(SEM));

		// Initialize
		if (em)
		{
			// Reset all
			memset(em, 0, sizeof(SEM));

			// Store defaults
			em->isSourceCode		= tlIsSourceCode;
			if (tlIsSourceCode)
				em->showLineNumbers	= true;

			// Default to 4-character tab width
			em->tabWidth			= 4;
			em->tabsEnforced		= true;
		}

		// Indicate our status
		return(em);
	}




//////////
//
// Called to accumulate the indicated line range into a builder buffer.
//
//////
	SBuilder* iSEM_accumulateBuilder(SEM* em, SEdit* ecHintStart, SEdit* ecHintEnd)
	{
		SBuilder*	b;
		SEdit*		line;


		// Make sure our environment is sane
		b = NULL;
		if (em)
		{
			//////////
			// Create our builder
			//////
				iBuilder_createAndInitialize(&b, -1);


			//////////
			// Make sure the parameters are set.  They can pass the start or end if
			// they only want a partial file.
			//////
				if (!ecHintStart)		ecHintStart = em->ecFirst;
				if (!ecHintEnd)			ecHintEnd	= em->ecLast;


			//////////
			// Repeat until we're at the end
			//////
				if (ecHintStart && ecHintEnd)
				{
					//////////
					// Build repeatedly
					//////
						line = ecHintStart;
						while (line)
						{
							//////////
							// If populated, append its content
							//////
								if (line->sourceCode && line->sourceCodePopulated > 0)
									iBuilder_appendData(b, line->sourceCode->data, line->sourceCodePopulated);


							//////////
							// Append a carriage return + line feed
							//////
								iBuilder_appendCrLf(b);


							//////////
							// Was this the last line?
							//////
								if (line == ecHintEnd)
									break;		// Yes, sir, it was


							//////////
							// Move to next line
							//////
								line = (SEdit*)line->ll.next;
						}
						// When we get here, the block is copied out
				}
		}

		// Indicate our status
		return(b);
	}




//////////
//
// Called to save the indicated EM to disk.  Saved as a raw text file.
//
//////
	bool iSEM_saveToDisk(SEM* em, s8* tcPathname)
	{
		SBuilder* content;


		// Make sure our environment is sane
		if (em && tcPathname)
		{
			// Grab the content
			content = iSEM_accumulateBuilder(em, NULL, NULL);
			if (content)
			{
				// Write it out
				iBuilder_asciiWriteOutFile(content, tcPathname);

				// Release it
				iBuilder_freeAndRelease(&content);

				// Indicate success
				return(true);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Loads in a text file into an EM beginning optionally near ecHint.
//
//////
	bool iSEM_loadFromDisk(SEM* em, s8* tcPathname, bool isSourceCode)
	{
		s32			lnI, lnJ, lnLast;
		bool		llOtherCharacters;
		SBuilder*	content;
		SEdit*		start;
		SEdit*		end;
		s8			buffer[_MAX_PATH + 64];


		// Make sure our environment is sane
		if (em && tcPathname)
		{
			// Read it in
			content = NULL;
			if (iBuilder_asciiReadFromFile(&content, tcPathname))
			{
				// Read in the file
				start	= NULL;
				end		= NULL;

				// Copy through lines into the ecm
				llOtherCharacters = false;
				for (lnI = 0, lnLast = 0; (u32)lnI < content->populatedLength; )
				{
					// Are we on a CR/LF combination?
					for (lnJ = 0; (content->data[lnI] == 13 || content->data[lnI] == 10) && lnJ < 2 && (u32)lnI < content->populatedLength; lnJ++)
						++lnI;	// Increase also past this CR/LF character

					// If we found a CR/LF combination
					if (lnJ != 0 || (u32)lnI >= content->populatedLength)
					{
						// We've entered into a CR/LF block, append a new line
						if (!llOtherCharacters)
						{
							// We only had CR+LF characters, no data
							end = iSEM_appendLine(em, content->data + lnLast, 0);

						} else {
							// We had at least some data
							end = iSEM_appendLine(em, content->data + lnLast, lnI - lnJ - lnLast);
						}
						if (!start)
							start = end;

						// Indicate where we are now
						llOtherCharacters	= false;
						lnLast				= lnI;

					} else {
						llOtherCharacters = true;
						++lnI;
					}
					// Continue on processing the next line if we have room
				}

				// Release it
				iBuilder_freeAndRelease(&content);

				// Renumber everything
				iSEM_renumber(em, 1);

				// Parse the content if it's source code
				if (isSourceCode)
				{
					// Iterate from start to end and parse each source code line
					while (start && (SEdit*)start->ll.prev != end)
					{
						// Parse it
						iEngine_parseSourceCodeLine(start);

						// Move to next line
						start = (SEdit*)start->ll.next;
					}
				}

				// Log it
				sprintf(buffer, "Load %s\0", tcPathname);
				iVjr_appendSystemLog(buffer);

				// Indicate success
				sprintf(buffer, "Loaded: %s\0", tcPathname);
				iSEM_appendLine(output_editbox->pa.em, buffer, strlen(buffer));
				return(true);

			} else {
				// Log it
				sprintf(buffer, "Load inquiry %s\0", tcPathname);
				iVjr_appendSystemLog(buffer);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Duplicate the entire ECM
//
//////
	bool iSEM_duplicate(SEM** root, SEM* emSource, bool tlIncludeUndoHistory)
	{
// 		SEM*	ecmNew;
// 		SEditChain*			ecSource;
// 		SEditChain*			ecNew;
// 		SEditChain*			ecLast;
// 		SEditChain**		ecPrev;
// 		SExtraInfo*			eiSource;
// 		SExtraInfo*			eiNew;
// 		SExtraInfo**		eiPrev;
// 		SBuilder*			xlatRoot;
// 		STranslate*			xlat;


		// Create the master record
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
debug_break;
// 		ecmNew = (SEM*)malloc(sizeof(SEM));
// 		if (ecmNew)
// 		{
// 			//////////
// 			// Initialize
// 			//////
// 				memcpy(ecmNew, ecmSource, sizeof(SEM));
// 
// 
// 			//////////
// 			// Remove the connection to any undo history
// 			// Note:  The undo history will be copied and translated separately if need be
// 			//////
// 				ecmNew->undoHistory = NULL;
// 				iBuilder_createAndInitialize(&xlatRoot, -1);
// 				// Note:  We create the translation regardless so we can update the ecmNew-> members which relate to cursor line, highlighted, etc.
// 
// 
// 			//////////
// 			// Update caller
// 			//////
// 				*root = ecmNew;
// 				// Right now:
// 				//		ecmNew		-- our new SEC
// 				//		ecmSource	-- SEC to duplicate
// 
// 
// 			//////////
// 			// Indicate where we'll be updating
// 			//////
// 				ecPrev	= &ecmNew->ecFirst;
// 				ecLast	= NULL;
// 
// 
// 			//////////
// 			// Duplicate the chain
// 			//////
// 				ecSource = ecmSource->ecFirst;
// 				while (ecSource)
// 				{
// 					//////////
// 					// Create a new entry for this one
// 					//////
// 						ecNew = (SEditChain*)malloc(sizeof(SEditChain));
// 						if (ecNew)
// 						{
// 							// Create a translation for original pointers to new pointers
// 							if (tlIncludeUndoHistory)
// 							{
// 								// Create the translation for this ecSource <--> ecNew
// 								xlat = (STranslate*)iBuilder_allocateBytes(xlatRoot, sizeof(STranslate));
// 								if (xlat)
// 								{
// 									// Create the translation
// 									xlat->p1	= ecSource;									// The old pointer in the undoHistory will point to
// 									xlat->p2	= ecNew;									// the new pointer
// 								}
// 							}
// 
// 						} else {
// 							// Should not happen.
// 							return(false);
// 						}
// 
// 
// 					//////////
// 					// Copy source information to new
// 					//////
// 						memcpy(ecNew, ecSource, sizeof(SEditChain));
// 						*ecPrev		= ecNew;												// Update the prior record to point here
// 						ecNew->prev	= ecLast;												// Point backward to the previous entry
// 						ecNew->next	= NULL;													// Currently points forward to nothing
// 
// 
// 					//////////
// 					// Duplicate its data
// 					//////
// 						ecNew->sourceCode = NULL;
// 						iDatum_duplicate(ecNew->sourceCode, ecSource->sourceCode);
// 
// 
// 					//////////
// 					// General purpose extra data
// 					//////
// 						if (ecSource->extra_info)
// 						{
// 							// Copy any extra_info that's relevant
// 							eiPrev		= &ecNew->extra_info;
// 							eiSource	= ecSource->extra_info;
// 							while (eiSource)
// 							{
// 								//////////
// 								// Duplicate this entry
// 								//////
// 									// Are we duplicating by a function call?  Or manually?
// 									if (*(u32*)&eiSource->extra_info_duplicate != 0)
// 									{
// 										// Function call
// 										eiNew = eiSource->extra_info_duplicate(ecmSource, ecSource, ecSource->extra_info);
// 										// Right now, eiNew has either been updated or not depending on the decision making process in extra_info_duplicate().
// 
// 									} else {
// 										// Manual duplication
// 										eiNew = (SExtraInfo*)malloc(sizeof(SExtraInfo));
// 										if (eiNew)
// 										{
// 											// Copy everything
// 											memcpy(eiNew, eiSource, sizeof(SExtraInfo));
// 
// 											// Clear, and then duplicate the info datum
// 											memset(&eiNew->info, 0, sizeof(eiNew->info));
// 											iDatum_duplicate(&eiNew->info, &eiSource->info);
// 
// 										} else {
// 											// Should not happen
// 											return(false);
// 										}
// 									}
// 
// 
// 								//////////
// 								// Update the back-link if need be
// 								//////
// 									if (eiNew)
// 									{
// 										*eiPrev	= eiNew;
// 										eiPrev	= &eiNew->next;
// 									}
// 
// 
// 								//////////
// 								// Move to next extra_info
// 								//////
// 									eiSource = eiSource->next;
// 							}
// 						}
// 
// 
// 					//////////
// 					// Move to next entry to duplicate
// 					//////
// 						ecLast		= ecNew;
// 						ecPrev		= &ecNew->next;
// 						ecSource	= ecSource->next;
// 				}
// 
// 
// 			//////////
// 			// Translate each of the ecmSource pointers for ecmNew
// 			// Note:  The rest of them use uid lookups
// 			//////
// 				ecmNew->ecFirst				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecFirst);
// 				ecmNew->ecLast				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecLast);
// 				ecmNew->ecTopLine				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecTopLine);
// 				ecmNew->ecCursorLine		= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLine);
// 				ecmNew->ecCursorLineLast	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLineLast);
// 				ecmNew->ecSelectedLineStart	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineStart);
// 				ecmNew->ecSelectedLineEnd	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineEnd);
// 
// 
// 			//////////
// 			// Free the pointers
// 			//////
// 				iBuilder_freeAndRelease(&xlatRoot);
// 
// 
// 			//////////
// 			// Indicate success
// 			//////
// 				return(true);
// 		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to free the EM content, and optionally itself
//
//////
	void iSEM_delete(SEM** root, bool tlDeleteSelf)
	{
		SEM* em;


		// Make sure our environment is sane
		if (root && *root)
		{
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
debug_break;
			em = *root;
			//////////
			// Are we really the thing?  Or just an indirect reference to the thing?
			//////
				if (!em->indirect)
				{
					//////////
					// We are the thing
					// Free undo history
					//////
						if ((*root)->undoHistory)
							iSEM_delete(&(*root)->undoHistory, true);


					//////////
					// Free content
					//////
						iEditChain_free(&(*root)->ecFirst, true);
				}


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
				{
					free(*root);
					*root = NULL;
				}
		}
	}




//////////
//
// Called to delete the entire chain explicitly
//
//////
	void iSEM_deleteChain(SEM** root, bool tlDeleteSelf)
	{
		// Delete with no callback
		iSEM_deleteChainWithCallback(root, tlDeleteSelf, NULL);
	}

	void iSEM_deleteChainWithCallback(SEM** root, bool tlDeleteSelf, SEM_callback* ecb)
	{
		SLL* nodeNext;
		SEM_callback	lecb;


		// Make sure our environment is sane
		if (root && *root)
		{
			//////////
			// If we don't have an ecb, make a local one
			//////
				if (!ecb)
				{
					// Initialize and setup the pointer
					memset(&lecb, 0, sizeof(lecb));
					ecb = &lecb;
				}


			//////////
			// Delete from the beginning
			//////
				ecb->em		= *root;
				ecb->ec		= ecb->em->ecFirst;


			// Iterate through deleting each entry after turning off the display
			ecb->em->isHeavyProcessing = true;
			while (ecb->ec)
			{
				//////////
				// Grab the next node
				//////
					nodeNext = ecb->ec->ll.next;


				//////////
				// Perform the callback
				//////
					if (ecb && ecb->_callback)
						ecb->callback(ecb);


				//////////
				// Delete the node itself
				//////
					ecb->em->ecCursorLine = ecb->ec;
					iSEM_deleteLine(ecb->em);


				//////////
				// Move to next node
				//////
					ecb->ec = (SEdit*)nodeNext;
			}
		}
	}




//////////
//
// Renumber the source code lines
//
//////
	void iSEM_renumber(SEM* em, u32 tnStartingLineNumber)
	{
		SEdit* ec;


		// Make sure our environment is sane
		if (em && em->ecFirst && em->ecLast)
		{
			// Begin at the beginning
			ec = em->ecFirst;
			while (ec)
			{
				// Set the line number
				ec->line = tnStartingLineNumber++;

				// Are we done
				if (ec == em->ecLast)
					break;

				// Move to next line
				ec = (SEdit*)ec->ll.next;
			}
		}
	}




//////////
//
// Called to append a line of text to the indicated ECM.
//
//////
	SEdit* iSEM_appendLine(SEM* em, s8* tcText, s32 tnTextLength)
	{
		s32		lnI, lnJ, lnPass, lnTextLength, lnCount;
		SEdit*	ec;


		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		ec = NULL;
		if (em && !em->isReadOnly)
		{
			// Allocate our new structure
			if (em->ecLast)
			{
				// Append after the last line
				ec = (SEdit*)iLl_appendNewNodeAtEnd((SLL**)&em->ecLast, sizeof(SEdit));

			} else {
				// This is the first line, add it and set the last line to the same
				ec = (SEdit*)iLl_appendNewNodeAtEnd((SLL**)&em->ecFirst, sizeof(SEdit));
				if (ec)
				{
					// Update defaults
					em->ecCursorLine			= ec;
					em->ecCursorLineLast		= ec;
					em->ecTopLine				= ec;
					em->ecSelectedLineStart		= NULL;
					em->ecSelectedLineEnd		= NULL;
				}
			}

			// Update and populate if added
			if (ec)
			{
				// We've added it to the end
				em->ecLast = ec;

				// Make sure the length is valid
				if (tnTextLength == -1)
				{
					if (tcText)		tnTextLength = strlen(tcText);
					else			tnTextLength = 0;
				}

				// Run two passes over the line.
				// Pass 1 -- Determine how long the line should be with tabs expanded to spaces
				// Pass 2 -- Populate the source into the destination padding tabs with spaces
				for (lnPass = 0; lnPass < 2; lnPass++)
				{
					// Determine how long the text is (expanding tabs)
					for (lnI = 0, lnTextLength = 0; lnI < tnTextLength; lnI++)
					{
						// If it's a tab, expand up to the nearest tabWidth characters
						if (tcText[lnI] == 9)
						{
							// Expand up to the next tabstop
							if (lnTextLength % em->tabWidth == 0)	lnCount = em->tabWidth;
							else									lnCount = em->tabWidth - (lnTextLength % em->tabWidth);

							// Copy if on pass 1
							if (lnPass == 1)
							{
								// Expand the difference with spaces
								for (lnJ = 0; lnJ < lnCount; lnJ++)
									ec->sourceCode->data[lnTextLength + lnJ] = 32;		// Fill with spaces
							}

							// Skip past our added space
							lnTextLength += lnCount;

						} else {
							// Copy one character on pass 1
							if (lnPass == 1)
								ec->sourceCode->data[lnTextLength] = tcText[lnI];

							// Increase by one
							++lnTextLength;
						}
					}

					// If we're on pass 0, allocate space, on the second pass we copy
					if (lnPass == 0)
					{
						// Allocate the datum
						ec->sourceCode = iDatum_allocate(NULL, 0);

						// Allocate space for the copy if there's any data
						if (lnTextLength != 0)
							iDatum_allocateSpace(ec->sourceCode, lnTextLength);

						// Set the populated length
						ec->sourceCodePopulated	= lnTextLength;
					}
				}

				// Renumber if need be
				if (em->showLineNumbers)
					iSEM_renumber(em, 1);
			}
		}

		// Indicate our status
		return(ec);
	}




//////////
//
// Called to insert a line before or after the indicated line
//
//////
	SEdit* iSEM_insertLine(SEM* em, s8* tcText, s32 tnTextLength, SEdit* line, bool tlInsertAfter)
	{
		SEdit* lineNew;


		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		lineNew = NULL;
		if (em && line)
		{
			// Create a new entry
			lineNew = (SEdit*)malloc(sizeof(SEdit));
			if (lineNew)
			{
				// Initialize
				memset(lineNew, 0, sizeof(SEdit));

				// Append a blank line
				lineNew->sourceCode = iDatum_allocate(tcText, tnTextLength);

				// Insert before or after the indicated line
				if (tlInsertAfter)
				{
					// Have we added one at the end?
					if (em->ecLast == line)
						em->ecLast = lineNew;

					//////////
					// [line->] [<-after]
					// becomes:
					// [line->] [<-lineNew->] [<after]
					//////
						lineNew->ll.next	= line->ll.next;
						lineNew->ll.prev	= (SLL*)line;
						line->ll.next		= (SLL*)lineNew;


					//////////
					// If there's one after this, have it point back
					//////
						if (lineNew->ll.next)
						{
							// Insert it after
							lineNew->ll.prev		= lineNew->ll.next->prev;
							lineNew->ll.next->prev	= (SLL*)lineNew;

						} else {
							// None after, so we update ecLast
							em->ecLast = lineNew;
						}

				} else {
					// Have we added one before the beginning?
					if (em->ecFirst == line)
						em->ecFirst = lineNew;

					//////////
					// [before->] [<-line]
					// becomes:
					// [before->] [<-lineNew->] [<-line]
					//////
						lineNew->ll.prev	= line->ll.prev;
						lineNew->ll.next	= (SLL*)line;
						line->ll.prev		= (SLL*)lineNew;


					//////////
					// If there's one before this, have it point forward
					//////
						if (lineNew->ll.next)
						{
							// Insert it before
							lineNew->ll.next		= lineNew->ll.prev->next;
							lineNew->ll.prev->next	= (SLL*)lineNew;

						} else {
							// None after, so we update ecLast
							em->ecFirst = lineNew;
						}
				}

				// Renumber if need be
				if (em->showLineNumbers)
					iSEM_renumber(em, 1);
			}
		}

		// Indicate our status
		return(lineNew);
	}




//////////
//
// Delete the indicated line
//
//////
	void iSEM_deleteLine(SEM* em)
	{
		SEdit* lineDeleted;
		SEdit* lineNewCursorLine;


		// Make sure the environment is sane
		if (em && !em->isReadOnly && em->ecCursorLine)
		{
			// Delete any content on this line
			if (em->ecCursorLine->sourceCode)
				iDatum_delete(em->ecCursorLine->sourceCode, true);

// TODO:  delete compiler info, and extra info

			// Delete the line itself, and determine which one would be the new line
			lineDeleted			= em->ecCursorLine;
			lineNewCursorLine	= (SEdit*)iLl_deleteNode((SLL*)em->ecCursorLine, true);

			// Update anything that may have changed as a result
			if (em->ecLast == lineDeleted)
				em->ecLast = lineNewCursorLine;

			if (em->ecFirst == lineDeleted)
				em->ecFirst = lineNewCursorLine;

			if (em->ecTopLine == lineDeleted)
				em->ecTopLine = lineNewCursorLine;

			em->ecCursorLine = lineNewCursorLine;

			// Renumber if need be
			if (em->showLineNumbers)
				iSEM_renumber(em, 1);
		}
	}




//////////
//
// Called to get the colors
//
//////
	void iSEM_getColors(SEM* em, SObject* obj, SBgra& backColor, SBgra& foreColor)
	{
		// Make sure our environment is sane
		if (em && obj)
		{
			// What is the object?
			backColor	= obj->p.backColor;
			foreColor	= obj->p.foreColor;

		} else {
			// It's insane, so we set our colors to default
			backColor	= whiteColor;
			foreColor	= blackColor;
		}
	}




//////////
//
// Obtains the rectangle we have to operate in.  If the object we relate back to is a
// form or subform, then we use the rcClient parameters created by the last render,
// otherwise we use the object's rc.
//
//////
	SFont* iSEM_getRectAndFont(SEM* em, SObject* obj, RECT* rc)
	{
		SFont* font;


		// Make sure our environment is sane
		font = gsFontDefault;
		if (em && obj)
		{
			// Get the client rect
			SetRect(rc, 0, 0, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top);
			if (em->font)		font = em->font;
			else				font = obj->pa.font;

		} else {
			// It's insane, so we set our rc to something that will prevent processing
			SetRect(rc, 0, 0, 0, 0);
			font = gsFontDefault;
		}

		// Return the font
		return(font);
	}




//////////
//
// Called when a keypress is made in a source code window, or when a prior keypress
// is now signaling repated keystrokes.
//
//////
	bool iSEM_onKeyDown_sourceCode(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, s16 tnAsciiChar, u16 tnVKey, bool tlIsCAS, bool tlIsAscii)
	{
		SEM*			em;
		SObject*		subform;


		// Make sure our environment is sane
		if (obj && obj->objType == _OBJ_TYPE_EDITBOX)
		{
			// Grab the EM for this
			em = obj->pa.em;

			// Send it its key
			if (!tlCtrl && !tlShift && !tlAlt)
			{
				// Regular key without special flags
				switch (tnVKey)
				{
					case VK_F9:
						// Breakpoint toggle
						if (em && em->ecCursorLine)
						{
							// Toggle it
							iEditChain_toggleBreakpoint(em);

							// Force the redraw
							iObj_setDirtyRender(obj, true);

							// Re-render the window
							iWindow_render(win, false);
						}
						break;

					case VK_F6:
					case VK_F8:
					case VK_F10:
					case VK_F11:
						// Execute this line of code
						if (em && em->ecCursorLine && em->ecCursorLine->sourceCodePopulated > 0)
						{
							iEngine_executeStandaloneCommand(em->ecCursorLine);

							// Move to next line and redraw
							iSEM_navigate(em, obj, 1, 0);
							iWindow_render(win, false);
							return(true);
						}
						break;

					case VK_RETURN:
						// Are we on the last line in the command window?
						if (em && em->ecCursorLine && !em->ecCursorLine->ll.next && em->ecCursorLine->sourceCodePopulated > 0)
						{
							subform = iObj_find_thisSubform(obj);
							if (subform && iObj_isCommandWindow(subform))
							{
								// Execute the command
								iEngine_executeStandaloneCommand(em->ecCursorLine);

								// Draw it like normal
								iSEM_returnKey(em, obj);
								iWindow_render(win, false);
								return(true);
							}
							// If we get here, we pass the return key through for editing
						}
						break;
				}

			} else if (tlCtrl && !tlShift && !tlAlt) {
				// CTRL+

			} else if (!tlCtrl && tlShift && !tlAlt) {
				// SHIFT+

			} else if (!tlCtrl && !tlShift && tlAlt) {
				// ALT+

			} else if (tlCtrl && tlShift && !tlAlt) {
				// CTRL+SHIFT+

			} else if (tlCtrl && !tlShift && tlAlt) {
				// CTRL+ALT+

			} else if (!tlCtrl && tlShift && tlAlt) {
				// SHIFT+ALT

			} else if (tlCtrl && tlShift && tlAlt) {
				// CTRL+ALT+SHIFT+
			}
		}

		// If they are holding down Ctrl+Alt+Shift, we need to re-render because this highlights information related to wherever the cursor is
		if (tlCtrl && tlShift && tlAlt)
		{
			iObj_setDirtyRender(obj, true);
			iWindow_render(win, false);
		}

		// Indicate additional events should be processed
		return(iSEM_onKeyDown(win, obj, tlCtrl, tlAlt, tlShift, tlCaps, tnAsciiChar, tnVKey, tlIsCAS, tlIsAscii));
	}




//////////
//
// Called when a keypress is made, or when a prior keypress is now signaling repated keystrokes.
//
//////
	bool iSEM_onKeyDown(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, s16 tnAsciiChar, u16 tnVKey, bool tlIsCAS, bool tlIsAscii)
	{
		bool	llProcessed;
		SEM*	em;


		// Make sure our environment is sane
		llProcessed = false;
		if (obj && obj->objType == _OBJ_TYPE_EDITBOX && obj->pa.em)
		{
			// Grab the EM for this
			em = obj->pa.em;

			// Send it its key
			if (!tlCtrl && !tlShift && !tlAlt)
			{
				// Regular key without special flags
				switch (tnVKey)
				{
					case VK_UP:
						iSEM_navigate(em, obj, -1, 0);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:
						iSEM_navigate(em, obj, 1, 0);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_PRIOR:		// Page up
						iSEM_navigatePages(em, obj, -1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_NEXT:		// Page down
						iSEM_navigatePages(em, obj, 1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_ESCAPE:		// They hit escape, and are cancelling the input
						iSEM_clearLine(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_TAB:
						iSEM_tabIn(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RETURN:
						// Draw it like normal
						iSEM_returnKey(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_LEFT:
						iSEM_navigate(em, obj, 0, -1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:
						iSEM_navigate(em, obj, 0, 1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:
						iSEM_navigate(em, obj, 0, -(em->column));

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:
						if (em->column != em->ecCursorLine->sourceCodePopulated)
							iSEM_navigate(em, obj, 0, em->ecCursorLine->sourceCodePopulated - em->column);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_INSERT:
						iSEM_toggleInsert(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_BACK:
						iSEM_deleteLeft(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DELETE:
						iSEM_deleteRight(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (tlCtrl && !tlShift && !tlAlt) {
				// CTRL+
				switch (tnVKey)
				{
					case VK_ADD:
						if (em->font)			em->font = iFont_bigger(em->font,		true);
						else					em->font = iFont_bigger(obj->pa.font,	false);
						iSEM_verifyCursorIsVisible(em, obj);
						iObj_setDirtyRender(obj, true);
						llProcessed = true;
						break;

					case VK_SUBTRACT:
						if (em->font)			em->font = iFont_smaller(em->font,		true);
						else					em->font = iFont_smaller(obj->pa.font,	false);
						iSEM_verifyCursorIsVisible(em, obj);
						iObj_setDirtyRender(obj, true);
						llProcessed = true;
						break;

					case 'A':		// Select all
						iSEM_selectAll(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'X':		// Cut
						iSEM_cut(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'C':		// Copy
						iSEM_copy(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'V':		// Paste
						iSEM_paste(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'W':		// Save and close
						break;

					case 'Q':		// Quit
						break;

					case VK_LEFT:	// Word left
						iSEM_navigateWordLeft(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Word right
						iSEM_navigateWordRight(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:	// Home (go to top of content)
						iSEM_navigateTop(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:	// Page down (go to end of content)
						iSEM_navigateEnd(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_BACK:
						iSEM_deleteWordLeft(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DELETE:
						iSEM_deleteWordRight(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (!tlCtrl && tlShift && !tlAlt) {
				// SHIFT+
				switch (tnVKey)
				{
					case VK_UP:		// Select line up
						iSEM_selectLineUp(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:	// Select line down
						iSEM_selectLineDown(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_LEFT:	// Select left
						iSEM_selectLeft(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Select right
						iSEM_selectRight(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:	// Select to end
						iSEM_selectToEndOfLine(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:	// Select to start
						iSEM_selectToBeginOfLine(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_TAB:	// Shift tab
						iSEM_tabOut(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (!tlCtrl && !tlShift && tlAlt) {
				// ALT+
				switch (tnVKey)
				{
					case 'K':		// Select column mode
						iSEM_selectColumnToggle(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'L':		// Select full line mode
						iSEM_selectLineToggle(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (tlCtrl && tlShift && !tlAlt) {
				// CTRL+SHIFT+
				switch (tnVKey)
				{
					case VK_LEFT:	// Select word left
						iSEM_selectWordLeft(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Select word right
						iSEM_selectWordRight(em, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (tlCtrl && !tlShift && tlAlt) {
				// CTRL+ALT+

			} else if (!tlCtrl && tlShift && tlAlt) {
				// SHIFT+ALT

			} else if (tlCtrl && tlShift && tlAlt) {
				// CTRL+ALT+SHIFT+

			}

			// If we get here, it wasn't processed above.  Try to stick it in the buffer
			if (!llProcessed && tlIsAscii)
				iSEM_keystroke(em, obj, (u8)tnAsciiChar);		// It's a regular input key
		}

		// Re-render the window if need be
		iWindow_render(win, false);

		// Indicate additional events should be processed
		return(true);
	}




//////////
//
// Called to render the ECM in the indicated rectangle on the object's bitmap
//
//////
	u32 iSEM_render(SEM* em, SObject* obj, bool tlRenderCursorline)
	{
		u32			lnPixelsRendered;
		s32			lnTop, lnSkip, lnDeltaX, lnLevel;
		bool		llIsValid, llCtrl, llAlt, llShift, llLeft, llMiddle, llRight, llCaps;
		SFont*		font;
		SEdit*		line;
		SBitmap*	bmp;
		SBitmap*	bmpCask;
		SBitmap*	bmpBreakpoint;
		SBitmap*	bmpBreakpointScaled;
		SComp*		comp;
		SComp*		comp2;
		SComp*		compPBBLeft;
		SComp*		compPBBRight;
		HGDIOBJ		hfontOld;
		SBgra		foreColor, backColor, fillColor, backColorLast, foreColorLast, compColor;
		RECT		rc, lrc, lrc2, lrc3, lrcComp;
		// Added to work around the font->tm.* width and height values not being accurate
		RECT		lrcCompCalcStart, lrcCompCalcDwell;
		s8			bigBuffer[2048];


		// Make sure our environment is sane
		lnPixelsRendered = 1;
		if (em && obj)
		{
			// Get the top line and continue down as far as we can
			line	= em->ecTopLine;
			bmp		= obj->bmp;
			lnTop	= 0;


			//////////
			// Grab font, coordinates, and colors
			//////
				font = iSEM_getRectAndFont(em, obj, &rc);
				iSEM_getColors(em, obj, backColor, foreColor);
				backColorLast.color			= backColor.color;
				foreColorLast.color			= foreColor.color;
				iMisc_adjustColorBrightness(backColorLast, -5.0f);
				iMisc_adjustColorBrightness(foreColorLast, 5.0f);
				hfontOld = SelectObject(bmp->hdc, font->hfont);		// Save the original font, and set our current font


			//////////
			// Prepare for rendering
			//////
				CopyRect(&lrc, &rc);
				if (em->showLineNumbers)
				{
					// Adjust lrc over for room for line numbers
					CopyRect(&em->rcLineNumberLastRender, &rc);
					DrawText(bmp->hdc, "  9999 ", 7, &em->rcLineNumberLastRender, DT_SINGLELINE | DT_LEFT | DT_NOPREFIX | DT_CALCRECT);
					SetRect(&em->rcLineNumberLastRender, rc.left, rc.top, rc.left + (em->rcLineNumberLastRender.right - em->rcLineNumberLastRender.left), rc.bottom);
					lrc.left	= em->rcLineNumberLastRender.right;
					rc.left		= em->rcLineNumberLastRender.right;
				}


			// Iterate for every visible line
			while (line && lrc.top + font->tm.tmHeight < rc.bottom)
			{
				if (line->compilerInfo && line->compilerInfo->firstComp)
				{
					//////////
					// Clear off any former highlights, and highlight the current
					//////
						comp = line->compilerInfo->firstComp;
						while (comp)
						{
							// Clear this entry
							comp->overrideMatchingBackColor = NULL;
							comp->overrideMatchingForeColor = NULL;

							// Move to next component
							comp = (SComp*)comp->ll.next;
						}


					//////////
					// Highlight the closest parenthesis, bracket, or brace
					//////
						if (line == em->ecCursorLine)
						{
							//////////
							// Locate the closest match
							//////
								comp = line->compilerInfo->firstComp;
								while (comp)
								{
									// Are they on this component?
									if (em->column >= comp->start && em->column <= comp->start + comp->length)
									{
										// This is the current component we're highlighting
										if (iComps_findClosest_parensBracketsBraces(comp, comp, &compPBBLeft, &compPBBRight))
										{
											// We found something
											if (iComps_isParensBracketsBraces(comp))
											{
												// Mark all commas between as highlighted
												comp2	= (SComp*)compPBBLeft->ll.next;
												lnLevel	= 0;
												while (comp2 != compPBBRight)
												{
													if (lnLevel == 0 && comp2->iCode == _ICODE_COMMA)
													{
														// Mark this component
														comp2->overrideMatchingBackColor	= &overrideMatchingBackColorMultiple;
														comp2->overrideMatchingForeColor	= &overrideMatchingForeColorMultiple;

														comp2->overrideMatchingBackColor	= &overrideMatchingBackColorMultiple;
														comp2->overrideMatchingForeColor	= &overrideMatchingForeColorMultiple;

													} else if (iComps_isMateOf(comp2, compPBBLeft->iCode)) {
														// If the left-most is (, then this is a ), going shallow
														++lnLevel;

													} else if (comp2->iCode == compPBBLeft->iCode) {
														// We're going deep
														--lnLevel;
													}

													// Move to next component
													comp2 = (SComp*)comp2->ll.next;
												}

											}
											// Mark the two
											compPBBLeft->overrideMatchingBackColor	= &overrideMatchingBackColor;
											compPBBLeft->overrideMatchingForeColor	= &overrideMatchingForeColor;

											compPBBRight->overrideMatchingBackColor	= &overrideMatchingBackColor;
											compPBBRight->overrideMatchingForeColor	= &overrideMatchingForeColor;
										}
										break;
									}

									// Move to next component
									comp = (SComp*)comp->ll.next;
								}
						}
				}


				//////////
				// Determine the position
				//////
					SetRect(&lrc2, rc.left, rc.top + lnTop, rc.right, rc.top + lnTop + (font->tm.tmHeight * 2));
					DrawText(bmp->hdc, bigBuffer, 1, &lrc2, DT_CALCRECT);
					SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.top + lnTop + (lrc2.bottom - lrc2.top));
					if (lrc.bottom > rc.bottom)
						lrc.bottom = rc.bottom;


				//////////
				// Determine the color
				//////
					SetBkMode(bmp->hdc, OPAQUE);
					if (em->ecCursorLine == line && em->showCursorLine && tlRenderCursorline)
					{
						// Display in the cursor color line
						SetBkColor(bmp->hdc, RGB(currentStatementBackColor.red, currentStatementBackColor.grn, currentStatementBackColor.blu));
						SetTextColor(bmp->hdc, RGB(currentStatementForeColor.red, currentStatementForeColor.grn, currentStatementForeColor.blu));
						fillColor.color	= currentStatementBackColor.color;

					} else if (line->ll.next || ((!em->showCursorLine || !tlRenderCursorline) && !em->showEndLine)) {
						// Display in normal background color
						SetBkColor(bmp->hdc, RGB(backColor.red, backColor.grn, backColor.blu));
						SetTextColor(bmp->hdc, RGB(foreColor.red, foreColor.grn, foreColor.blu));
						hfontOld		= SelectObject(bmp->hdc, font->hfont);
						fillColor.color	= backColor.color;

					} else {
						// This is the last line, display in the last line color
						SetBkColor(bmp->hdc, RGB(backColorLast.red, backColorLast.grn, backColorLast.blu));
						SetTextColor(bmp->hdc, RGB(foreColorLast.red, foreColorLast.grn, foreColorLast.blu));
						hfontOld		= SelectObject(bmp->hdc, font->hfont);
						fillColor.color	= backColorLast.color;
					}


				//////////
				// Determine the render rectangles (populated area on left, area to clear on right)
				//////
					CopyRect(&lrc2, &lrc);

					// Will we fit?
					if (line->sourceCode->data && line->sourceCodePopulated > 0 && em->leftColumn < line->sourceCodePopulated)
					{
						// Draw the portion that will fit
						DrawText(bmp->hdc, line->sourceCode->data + em->leftColumn, line->sourceCodePopulated - em->leftColumn, &lrc2, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
						lrc2.right	= min(rc.right,  lrc2.right);
						lrc2.bottom	= min(rc.bottom, lrc2.bottom);
						// Set the clear border
						SetRect(&lrc3, lrc2.right, lrc2.top, rc.right, lrc2.bottom);

					} else {
						// We're scrolled past this line, so the entire area must be filled in
						// Set the clear border
						CopyRect(&lrc3, &lrc);
					}


				//////////
				// Fill the line with the appropriate background color
				//////
					iBmp_fillRect(bmp, &lrc3, fillColor, fillColor, fillColor, fillColor, false, NULL, false);


					// Do we need to draw anything?
					if (!line->sourceCode->data || line->sourceCodePopulated == 0 || line->sourceCodePopulated < em->leftColumn)
					{
						// Nope, nothing to draw on this line

					} else {
					//////////
					// Draw the text
					//////
						DrawText(bmp->hdc, line->sourceCode->data + em->leftColumn, line->sourceCodePopulated - em->leftColumn, &lrc2, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						if (em->isSourceCode && line->compilerInfo && line->compilerInfo->firstComp && em->leftColumn < line->sourceCodePopulated)
						{
							// Source code, syntax highlight
							if (em->isSourceCode && line->compilerInfo && line->compilerInfo->firstComp)
							{
								// Redraw items that are to be colorized in their color
								comp = line->compilerInfo->firstComp;
								while (comp)
								{
									// Fore color
									     if (comp->overrideMatchingForeColor)		compColor.color	= comp->overrideMatchingForeColor->color;
									else if (comp->color)							compColor.color = comp->color->color;
									else											compColor.color = foreColor.color;

									// Find out where it starts
									SetRect(&lrcCompCalcStart, 0, 0, 200000, lrc.bottom);
									if (comp->start != 0)		DrawText(bmp->hdc, comp->line->sourceCode->data, comp->start, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
									else						SetRect(&lrcCompCalcStart, 0, 0, 0, lrc.bottom);

									// Find out how long it dwells
									SetRect(&lrcCompCalcDwell, lrcCompCalcStart.right, 0, 200000, lrc.bottom);
									DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start, comp->length, &lrcCompCalcDwell, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
									SetRect(&lrcComp, rc.left + lrcCompCalcDwell.left, lrc2.top, rc.left + lrcCompCalcDwell.right, lrc2.bottom);

									// Do we need to adjust it back for scrolling?
									if (em->leftColumn != 0)
									{
										// Adjust it for the em->leftColumn
										lnDeltaX		= em->leftColumn * ((lrcComp.right - lrcComp.left) / comp->length);
										lrcComp.left	-= lnDeltaX;
										lrcComp.right	-= lnDeltaX;
									}

									// Is it a cask or text?
									if (comp->iCode >= _ICODE_CASK_MINIMUM && comp->iCode <= _ICODE_CASK_MAXIMUM)
									{
										// It's a cask, build it
										bmpCask = iBmp_cask_createAndPopulate(comp->iCode,
																				lrcComp.right  - lrcComp.left,
																				lrcComp.bottom - lrcComp.top,
																				&lnSkip,
																				comp->length,
																				backColor,
																				foreColor,
																				fillColor);

										// Publish it
										if (line == em->ecCursorLine && em->column >= comp->start && em->column <= comp->start + comp->length)
										{
// For now, just don't render it when we're on it
// 											// The cursor is currently on this item, draw with a 15% transparency
//											iBmp_bitBltAlpha(bmp, &lrcComp, bmpCask, 0.15f);

										} else {
											// Draw completely opaque
											iBmp_bitBlt(bmp, &lrcComp, bmpCask);

// If we decide to display it with an alpha, this also may need to be brought outside of the if block
											// Overlay the text
											SetBkMode(bmp->hdc, TRANSPARENT);
											SetTextColor(bmp->hdc, RGB(blackColor.red, blackColor.grn, blackColor.blu));
											--lrcComp.top;
											DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start + lnSkip, comp->length - (2 * lnSkip), &lrcComp, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
											++lrcComp.top;
											SetBkMode(bmp->hdc, OPAQUE);
										}

										// Delete it
										iBmp_delete(&bmpCask, true, true);

									} else {
										// Draw the text
										// Set the color
										SetTextColor(bmp->hdc, RGB(compColor.red, compColor.grn, compColor.blu));

										// An explicit background color?
										if (comp->overrideMatchingBackColor)		SetBkColor(bmp->hdc, RGB(comp->overrideMatchingBackColor->red, comp->overrideMatchingBackColor->grn, comp->overrideMatchingBackColor->blu));
										else										SetBkColor(bmp->hdc, RGB(fillColor.red, fillColor.grn, fillColor.blu));

										// Draw this component
										SetBkMode(bmp->hdc, OPAQUE);
										DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start, comp->length, &lrcComp, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

										// If we should bold, bold it
										if (comp->useBoldFont)
										{
											// Set transparent mode
											SetBkMode(bmp->hdc, TRANSPARENT);

											// Adjust right one pixel, redraw
//											++lrcComp.left;
//	 										++lrcComp.right;
											DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start, comp->length, &lrcComp, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

											// Set back to opaque
											SetBkMode(bmp->hdc, OPAQUE);
										}

										// If they're ont he cursor line, on a flow control directive, and holding down Ctrl+Alt+Shift, then we want to show that directive's mate on the line above
										if (line == em->ecCursorLine && comp->iCat == _ICAT_FLOW && em->column >= comp->start && em->column <= comp->start + comp->length)
										{
											// Grab the keyboard and mouse flags
											iiMouse_getFlags_async(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps);
											if (llCtrl && llAlt && llShift)
											{
												// Based on the directive, search up or down to find the mate
// TODO:  Working here
											}
										}
									}


									//////////
									// Check errors and warnings
									//////
										if (line != em->ecCursorLine && (comp->isError || comp->isWarning))
										{
											// Adjust the top down to the lower 1/4th
											lrcComp.top += ((lrcComp.bottom - lrcComp.top) * 3) / 4;

											// Is it a warning?
											if (comp->isWarning && !comp->isError)
											{
												iBmp_wavyLine(bmp, &lrcComp, orangeColor);		// Overlay an amber wavy line on the lower 1/3rd of the component
// 												iBmp_colorize(bmp, &lrcComp, pastelOrangeColor, false, 0.0f);
											}

											// Is it an error? (if there is an error and a warning, errors take precedence)
											if (comp->isError)
											{
												iBmp_wavyLine(bmp, &lrcComp, redColor);			// Overlay a red wavy line on the lower 1/3rd of the component
// 												iBmp_colorize(bmp, &lrcComp, pastelRedColor, false, 0.0f);
											}
										}


									// Move to next component
									comp = (SComp*)comp->ll.next;
								}
							}
						}
					}


				//////////
				// Draw the cursor if on the cursor line
				//////
					if (em->ecCursorLine == line && em->showCursorLine && tlRenderCursorline)
					{
						SetRect(&lrcCompCalcStart, 0, 0, lrc.right, lrc.bottom);
						if (em->column != 0)
						{
							// It's somewhere on the line
							DrawText(bmp->hdc, bigBuffer, em->column - em->leftColumn, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcCompCalcDwell, lrcCompCalcStart.right, 0, lrc.right, lrc.bottom);
							DrawText(bmp->hdc, bigBuffer, 1, &lrcCompCalcDwell, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcComp, rc.left + lrcCompCalcDwell.left, lrc2.top, rc.left + lrcCompCalcDwell.right, lrc2.bottom);

						} else {
							// It's all the way to the left
							DrawText(bmp->hdc, bigBuffer, 1, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcComp, rc.left + ((em->isOverwrite) ? 0 : 1), lrc.top, rc.left + lrcCompCalcStart.right, lrc.bottom);
						}

						iBmp_invert(bmp, lrcComp.left - ((em->isOverwrite) ? 0 : 1), ((em->isOverwrite) ? lrc.bottom - 2 : lrc.top), ((em->isOverwrite) ? lrcComp.right : lrcComp.left + ((em->isOverwrite) ? 0 : 1)), lrc.bottom);
					}


				//////////
				// Overlay the line number
				//////
					if (em->showLineNumbers)
					{
						// Left-side overlay
						SetRect(&lrc3, em->rcLineNumberLastRender.left, lrc2.top, em->rcLineNumberLastRender.right, lrc2.bottom);
						iBmp_fillRect(bmp, &lrc3, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, false, NULL, false);
						iBmp_drawVerticalLine(bmp, lrc3.top, lrc3.bottom, lrc3.right - 1, lineNumberBackColor);

						// Get our line number
						sprintf(bigBuffer, "%u\0", line->line);

						// Back off one character, and render the line number right-justified
						lrc3.right -= (em->rcLineNumberLastRender.right - em->rcLineNumberLastRender.left) / 7;
						SetBkMode(bmp->hdc, TRANSPARENT);
						SetTextColor(bmp->hdc, RGB(lineNumberForeColor.red, lineNumberForeColor.grn, lineNumberForeColor.blu));
						DrawText(bmp->hdc, bigBuffer, strlen(bigBuffer), &lrc3, DT_SINGLELINE | DT_RIGHT | DT_NOPREFIX);


						//////////
						// If we're on the cursor line, extend its color influence to the left line number area
						//////
							if (line == em->ecCursorLine && !line->breakpoint && tlRenderCursorline)
							{
								SetRect(&lrc3, em->rcLineNumberLastRender.left, lrc2.top, em->rcLineNumberLastRender.right, lrc2.bottom);
								iBmp_colorize(bmp, &lrc3, currentStatementBackColor, false, 0.0f);
							}


						//////////
						// Show the breakpoint
						//////
							if (line->breakpoint && line->breakpoint->isUsed)
							{
								// Determine the breakpoint parameters
								llIsValid = true;
								switch (line->breakpoint->type)
								{
									case _BREAKPOINT_ALWAYS:
										if (line->breakpoint->countdownResetValue == 0)			bmpBreakpoint = bmpBreakpointAlways;
										else													bmpBreakpoint = bmpBreakpointAlwaysCountdown;
										break;

									case _BREAKPOINT_CONDITIONAL_TRUE:
										bmpBreakpoint = bmpConditionalTrue;
										break;

									case _BREAKPOINT_CONDITIONAL_FALSE:
										bmpBreakpoint = bmpConditionalFalse;
										break;

									case _BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN:
										bmpBreakpoint = bmpConditionalTrueCountdown;
										break;

									case _BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN:
										bmpBreakpoint = bmpConditionalFalseCountdown;
										break;

									default:
										// Unknown type, ignore it
										llIsValid = false;
										break;
								}

								// Render the breakpoint if it's valid
								if (llIsValid)
								{
									//////////
									// Draw the icon
									//////
										bmpBreakpointScaled = iBmp_allocate();
										iBmp_createBySize(bmpBreakpointScaled, (lrc3.bottom - lrc3.top), (lrc3.bottom - lrc3.top), bmpBreakpoint->bi.biBitCount);
										iBmp_scale(bmpBreakpointScaled, bmpBreakpoint);
										iBmp_bitBlt(bmp, &lrc3, bmpBreakpointScaled);
										iBmp_delete(&bmpBreakpointScaled, true, true);


									//////////
									// Give the source code line some breakpoing color love :-)
									//////
										if (line == em->ecCursorLine)
										{
											// Just do the em->rcLineNumberLastRender portion
											SetRect(&lrc3, em->rcLineNumberLastRender.left, lrc2.top, em->rcLineNumberLastRender.right, lrc2.bottom);

										} else {
											// Do the entire line
											SetRect(&lrc3, 0, lrc.top, rc.right, lrc.bottom);
										}

										// Colorize it
										iBmp_alphaColorizeMask(bmp, &lrc3, breakpointBackColor, 0.25f);
								}
						}


					//////////
					// Show any breakcrumbs
					//////
						
					}


				//////////
				// Move down to the next row
				//////
					lnTop	+= (lrc.bottom - lrc.top);
					line	= (SEdit*)line->ll.next;
			}

			// Fill in the remainder of the display
			SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.bottom);
			iBmp_fillRect(bmp, &lrc, backColor, backColor, backColor, backColor, false, NULL, false);

			// Line number portion
			SetRect(&lrc3, em->rcLineNumberLastRender.left, rc.top + lnTop, em->rcLineNumberLastRender.right, rc.bottom);
			iBmp_fillRect(bmp, &lrc3, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, false, NULL, false);
			iBmp_drawVerticalLine(bmp, lrc3.top, lrc3.bottom, lrc3.right - 1, lineNumberBackColor);

// s8 buffer[256];
// if (obj->parent && obj->parent->objType == _OBJ_TYPE_SUBFORM && iDatum_compare(&obj->parent->pa.caption, cgcSourceCodeTitle, sizeof(cgcSourceCodeTitle) - 1) == 0)
// {
// 	sprintf(buffer, "c:\\temp\\ems\\%u.bmp\0", (u32)em);
// 	iBmp_saveToDisk(bmp, buffer);
// 	iBmp_saveToDisk(bmp, "c:\\temp\\em.bmp");
// }

			// Reset the font
			SelectObject(bmp->hdc, hfontOld);
		}

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}




//////////
//
// Called to verify the cursor is visible by adjusting em->leftColumn
//
//////
	bool iSEM_verifyCursorIsVisible(SEM* em, SObject* obj)
	{
		s32		lnI, lnUp, lnDn, lnNewLeftColumn, lnCols, lnRows, lnWidth, lnHeight, lnExtra;
		bool	llChanged;
		SEdit*	lineUp;
		SEdit*	lineDn;
		SFont*	font;
		RECT	lrc;


		llChanged = false;
		if (!em->isHeavyProcessing)
		{
			//////////
			// Indicate initially that no changes were made that require a re-render
			//////
				font = iSEM_getRectAndFont(em, obj, &lrc);


			//////////
			// Make sure our environment is sane
			//////
				llChanged = false;
				if (em)
				{
					//////////
					// Compute our maximum rows and cols based on visible display area
					//////
// TODO:  There must be a more elegant way to do this.
						lnWidth		= (lrc.right - lrc.left);
						lnHeight	= (lrc.bottom - lrc.top);
						lnExtra		= font->tm.tmMaxCharWidth - (font->tm.tmAveCharWidth * 2);			// Added to fix the bug mentioned below
						if (lnExtra < 0)
							lnExtra = 0;
						lnCols		= max((lnWidth  / (font->tm.tmAveCharWidth + lnExtra)),	2);			// There is some kind of bug in the font->tm.tmAveCharWidth which prevents this from always being able to be an exact calculation, so we back off 10 characters
						lnRows		= max((lnHeight / font->tm.tmHeight),					2);			// And for the height, we back off one

						// Adjust to 90% of extents
						lnCols		= lnCols - (lnCols / 10);
						lnRows		= lnRows - (lnRows / 10);


					//////////
					// Make sure we're not before it to the left
					//////
						if (em->column < em->leftColumn)
						{
							em->leftColumn	= em->column;
							llChanged		= true;
						}


					//////////
					// Make sure we're not beyond it to the right
					//////
						lnNewLeftColumn = em->column - lnCols;
						if (em->leftColumn - lnNewLeftColumn < 0)
						{
							em->leftColumn	= lnNewLeftColumn;
							llChanged		= true;
						}


					//////////
					// Make sure we're on-screen vertically
					//////
						if (!em->ecCursorLine)
						{
							// No cursor line has been set
							if (!em->ecTopLine)
							{
								// Set the top line
								em->ecTopLine		= em->ecFirst;
								em->ecCursorLine	= em->ecFirst;

							} else {
								// Position it at the top line
								em->ecCursorLine = em->ecTopLine;
							}
							llChanged = true;

						} else {
							// Find out how many rows away the cursor line is from the top line by scanning up and down
							lineUp	= em->ecTopLine;
							lineDn	= em->ecTopLine;
							for (lnUp = 0, lnDn = 0; (lineUp || lineDn) && lineUp != em->ecCursorLine && lineDn != em->ecCursorLine; )
							{
								//////////
								// Can we go up?
								//////
									if (lineUp)
									{
										lineUp = (SEdit*)lineUp->ll.prev;
										++lnUp;
									}


								//////////
								// Can we go down?
								//////
									if (lineDn)
									{
										lineDn = (SEdit*)lineDn->ll.next;
										++lnDn;
									}
							}
							// When we get here, either lineUp or lineDn found the cursor line

							if (lineUp == em->ecCursorLine)
							{
								// We went up, so set the top line to this location
								em->ecTopLine = em->ecCursorLine;
								llChanged = true;

							} else if (lineDn == em->ecCursorLine) {
								// We went down to find it
								if (lnDn >= lnRows)
								{
									// And the position is too far down
									for (lnI = 0; lnI <= lnDn - lnRows; lnI++)
										em->ecTopLine = (SEdit*)em->ecTopLine->ll.next;

									// Indicate the change
									llChanged = true;
								}

							} else {
								// If we get here, it wasn't found
								em->ecTopLine = em->ecCursorLine;
								llChanged = true;
							}
						}
				}
		}

		// If something has changed, we need to re-render
		iObj_setDirtyRender(obj, true);

		// Indicate our status
		return(llChanged);
	}




//////////
//
// Called to process the ASCII character into the input buffer.
//
//////
	bool iSEM_keystroke(SEM* em, SObject* obj, u8 asciiChar)
	{
		bool	llChanged;
//		SFont*	font;
//		RECT	lrc;


		//////////
		// Indicate initially that no changes were made that require a re-render
		//////
			llChanged = false;
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// Make sure our environment is sane
// TODO:  Added the extra test on ecm->column because of a bug when scrolling... will fix. :-)
		if (em && !em->isReadOnly)
		{
			//////////
			// Are we on a line?
			//////
				if (!em->ecFirst)
					iSEM_appendLine(em, NULL, 0);		// Append a blank line to receive this keystroke


			//////////
			// Is a line currently selected?
			//////
				if (!em->ecCursorLine)
					iSEM_navigateTop(em, obj);


			//////////
			// Are we in insert mode?
			//////
				if (!em->isOverwrite)
				{
					// We are inserting
					if (em->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llChanged = iEditChain_characterInsert(em, asciiChar);
					}

				} else {
					// We are overwriting
					if (em->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llChanged = iEditChain_characterOverwrite(em, asciiChar);
					}
				}
		}

		// If we updated something, mark the object dirty
		if (llChanged)
		{
			// Indicate the object needs re-rendered
			obj->isDirtyRender = true;

			// Reprocess the source code on the line
			iEngine_parseSourceCodeLine(em->ecCursorLine);

			// Verify our cursor is visible
			iSEM_verifyCursorIsVisible(em, obj);
		}

		// Indicate our status
		return(llChanged);
	}
;




//////////
//
// Called to scroll rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iSEM_scroll(SEM* em, SObject* obj, s32 deltaY, s32 deltaX)
	{
		s32			lnI;
//		SFont*		font;
//		RECT		lrc;
//
//
//		//////////
//		// Grab the rectangle we're working in
//		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine && em->ecCursorLine->sourceCode)
			{
				//////////
				// Scroll by count
				//////
					if (deltaY != 0)
					{
						if (deltaY > 0)
						{
							// Going forward
							for (lnI = 0; em->ecCursorLine->ll.next && lnI != deltaY; lnI++)
							{
								em->ecTopLine		= (SEdit*)em->ecTopLine->ll.next;
								em->ecCursorLine	= (SEdit*)em->ecCursorLine->ll.next;
							}

						} else {
							// Going backward
							for (lnI = 0; em->ecTopLine->ll.prev && lnI != deltaY; lnI--)
							{
								em->ecTopLine		= (SEdit*)em->ecTopLine->ll.prev;
								em->ecCursorLine	= (SEdit*)em->ecCursorLine->ll.prev;
							}
						}
				}


				//////////
				// Move columns
				//////
					if (deltaX != 0)
					{
						if (deltaX < 0)
						{
							// Moving left
							em->column		= max(em->column     + deltaX, 0);
							em->leftColumn	= max(em->leftColumn + deltaX, 0);

						} else {
							// Moving right
							em->column		+= deltaX;
							em->leftColumn	+= deltaX;
						}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iSEM_navigate(SEM* em, SObject* obj, s32 deltaY, s32 deltaX)
	{
		s32			lnI, lnTop, lnBottom;
		bool		llResetTopLine;
		SFont*		font;
		SEdit*		line;
		SEdit*		lineRunner;
		RECT		lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine && em->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = em->ecCursorLine;


				//////////
				// Navigate by lines
				//////
					if (deltaY != 0)
					{
						if (deltaY > 0)
						{
							// Going forward
							for (lnI = 0; line->ll.next && lnI != deltaY; lnI++)
								line = (SEdit*)line->ll.next;

							// We need to scan forward from ecTopLine to see if we'd be off screen.
							// If so, we drag ecTopLine forward until we reach the visible portion
							lnTop		= lrc.top;
							lnBottom	= lrc.bottom - font->tm.tmHeight;
							lineRunner	= em->ecTopLine;
							while (em->ecTopLine->ll.next && lineRunner != line)
							{
								//////////
								// Are we still on screen?
								//////
									if (lnTop > lnBottom)
									{
										// We're off screen, so we're dragging the top forward
										em->ecTopLine = (SEdit*)em->ecTopLine->ll.next;

									} else {
										// Still on the same page
										lnTop += font->tm.tmHeight;
									}


								//////////
								// Move to next line
								//////
									lineRunner = (SEdit*)lineRunner->ll.next;
							}

						} else {
							// Going backward
							llResetTopLine = false;
							for (lnI = 0; line->ll.prev && lnI != deltaY; lnI--)
							{
								// Are we dragging the top line with us yet?
								if (em->ecTopLine == line)
									llResetTopLine = true;

								// Move back one line
								line = (SEdit*)line->ll.prev;
							}

							if (llResetTopLine)
								em->ecTopLine = line;
						}

					//////////
					// Update the pointers
					//////
						em->ecCursorLine = line;
				}


				//////////
				// Move columns
				//////
					if (deltaX != 0)
					{
						if (deltaX < 0)
						{
							// Moving left
							em->column = max(em->column + deltaX, 0);

						} else {
							// Moving right
							em->column += deltaX;
						}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate pages (deltaY) forward or backward)
//
//////
	bool iSEM_navigatePages(SEM* em, SObject* obj, s32 deltaY)
	{
		s32		lnI;
		bool	llMoveForward;
		SFont*	font;
		RECT	lrc;
		SEdit*	line;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine && em->ecCursorLine->sourceCode && deltaY != 0)
			{
				//////////
				// Determine how many visible lines there are and move that far
				//////
					deltaY = deltaY * ((lrc.bottom - lrc.top) / font->tm.tmHeight);
					if (deltaY > 0)
					{
						// See how many lines there are left on the page
						llMoveForward = true;
						if (em->ecCursorLine != em->ecLast)
						{
							// We're not on the last line, so we first see if we can navigate a partial page down without moving the top line
							// before we reach the end of the file
							line = em->ecCursorLine;
							for (lnI = 0; line->ll.next && lnI != deltaY; lnI++)
							{
								// Move the cursor line to the next line
								line = (SEdit*)line->ll.next;
							}

							// If we've reached the end before reaching our delta...then...
							if (lnI != deltaY)
							{
								// We can do the partial page
								em->ecCursorLine	= line;
								llMoveForward		= false;
							}
						}

						// Going forward
						if (llMoveForward)
						{
							if (!em->ecCursorLine->ll.next && em->ecCursorLine != em->ecTopLine)
							{
								// We're already at the bottom, so just move down a line
								em->ecTopLine = (SEdit*)em->ecTopLine->ll.next;

							} else {
								// Scroll the whole page
								for (lnI = 0; em->ecCursorLine->ll.next && lnI != deltaY; lnI++)
								{
									// Move the top line to the next line
									em->ecTopLine		= (SEdit*)em->ecTopLine->ll.next;
									em->ecCursorLine	= (SEdit*)em->ecCursorLine->ll.next;
								}
							}
						}

					} else {
						// Going backward
						for (lnI = 0; em->ecCursorLine->ll.prev && lnI != deltaY; lnI--)
						{
							// Move the top line up (if we can)
							if (em->ecTopLine->ll.prev)
								em->ecTopLine	= (SEdit*)em->ecTopLine->ll.prev;

							// Move the cursor line up
							em->ecCursorLine	= (SEdit*)em->ecCursorLine->ll.prev;
						}

					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear the entire line.
//
//////
	bool iSEM_clearLine(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear from where we are to the end of the line
//
//////
	bool iSEM_clearToEndOfLine(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear from one character left of where we are to the beginning of the line
//
//////
	bool iSEM_clearToBeginningOfLine(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle insert mode
//
//////
	bool iSEM_toggleInsert(SEM* em, SObject* obj)
	{
		if (em)
		{
			// Toggle the flag
			em->isOverwrite = !em->isOverwrite;

			// Something has changed, we need to re-render
			iObj_setDirtyRender(obj, true);

			// Toggling insert changes the shape of the cursor, so we always redraw
			return(true);
		}

		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called when the users press TAB
//
//////
	bool iSEM_tabIn(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called when the users presses SHIFT+TAB
//
//////
	bool iSEM_tabOut(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// 
//
//////
	bool iSEM_returnKey(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// Make sure the environment is sane
		if (em && !em->isReadOnly && em->ecCursorLine && obj)
		{
			// If we're in insert mode, we split the line
			if (!em->isOverwrite)
			{
				// Insert mode
				iSEM_insertLine(em, NULL, 0, em->ecCursorLine, true);	// Append a new line after the cursor line

			} else {
				// Overwrite mode
				if (!em->ecCursorLine->ll.next)
					iSEM_appendLine(em, NULL, 0);		// Append a new line at the end
			}

			// Move to the new line, and to the start of that line
			iSEM_navigate(em, obj, 1, -em->column);

			// Indicate success
			return(true);
		}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select everything
//
//////
	bool iSEM_selectAll(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to cut to the clipboard
//
//////
	bool iSEM_cut(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to copy to the clipboard
//
//////
	bool iSEM_copy(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to paste from the clipboard
//
//////
	bool iSEM_paste(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate one word left
//
//////
	bool iSEM_navigateWordLeft(SEM* em, SObject* obj)
	{
//		SFont*		font;
		SEdit*		line;
//		RECT		lrc;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine && em->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = em->ecCursorLine;


				//////////
				// Iterate until we find a space
				//////
					if (em->column == 0 || line->sourceCodePopulated == 0)
					{
						// We have to go to the previous line (if we can)
						if (em->ecFirst != line)
						{
							// Go up one line
							iSEM_navigate(em, obj, -1, 0);

							// Go to the end of this line
							iSEM_navigate(em, obj, 0, em->ecCursorLine->sourceCodePopulated);

							// Continue looking word left on this line
							return(iSEM_navigateWordLeft(em, obj));
						}

					} else if (line->sourceCodePopulated < em->column) {
						// We're beyond end of line, move to the end of line
						iSEM_navigate(em, obj, 0, em->ecCursorLine->sourceCodePopulated - em->column);

						// Then continue looking word left on this line
						return(iSEM_navigateWordLeft(em, obj));

					} else {
						//////////
						// We're somewhere on the line, move one column left first
						//////
							--em->column;


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							// When we get to the first non-whitespace, we break
							for ( ; em->column > 0 && (line->sourceCode->data[em->column] == 32 || line->sourceCode->data[em->column] == 9); )
								--em->column;


						//////////
						// If we're not at the beginning of the line, then we look for the first whitespace character
						//////
							if (em->column != 0)
							{
								// Search left for the first whitespace or comma
								for ( ; em->column > 0; em->column--)
								{
									// Did we find a whitespace to our left?
									if (line->sourceCode->data[em->column - 1] == 32 || line->sourceCode->data[em->column - 1] == 9 || line->sourceCode->data[em->column - 1] == ',')
										break;	// Yes
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate one word right
//
//////
	bool iSEM_navigateWordRight(SEM* em, SObject* obj)
	{
//		SFont*		font;
		SEdit*		line;
//		RECT		lrc;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine && em->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = em->ecCursorLine;


				//////////
				// Iterate until we find a space
				//////
					if (em->column >= line->sourceCodePopulated)
					{
						// We have to go to the next line (if we can)
						if (em->ecLast != line)
						{
							// Go down one line
							iSEM_navigate(em, obj, 1, 0);

							// Go to the start of the line
							if (em->column > 0)
								iSEM_navigate(em, obj, 0, -em->column);

							// Continue looking word left on this line
							return(iSEM_navigateWordRight(em, obj));
						}

					} else {
						//////////
						// We're somewhere on the line, move one column right first
						//////
							++em->column;
							if (em->column == 1 && line->sourceCodePopulated == 1)
								return(true);


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							// When we get to the first non-whitespace, we break
							for ( ; em->column < line->sourceCodePopulated && (line->sourceCode->data[em->column] == 32 || line->sourceCode->data[em->column] == 9); )
								++em->column;


						//////////
						// If we're not at the end of the line, then we look for the first whitespace character
						//////
							if (em->column < line->sourceCodePopulated)
							{
								// Search right for the first whitespace or comma
								for ( ; em->column < line->sourceCodePopulated; em->column++)
								{
									// Did we find a whitespace to our left?
									if (line->sourceCode->data[em->column + 1] == 32 || line->sourceCode->data[em->column + 1] == 9 || line->sourceCode->data[em->column + 1] == ',')
										break;	// Yes
								}

							} else {
								// We have to go to the next line (if we can)
								if (em->ecLast != line)
								{
									// Go down one line
									iSEM_navigate(em, obj, 1, 0);

									// Go to the start of the line
									if (em->column > 0)
										iSEM_navigate(em, obj, 0, -em->column);

									// Continue looking word left on this line
									return(iSEM_navigateWordLeft(em, obj));
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the top of the chain
//
//////
	bool iSEM_navigateTop(SEM* em, SObject* obj)
	{
		// Make sure the environment is sane
		if (em && em->ecFirst)
		{
			//////////
			// Save previous position
			//////
				em->ecCursorLineLast	= em->ecCursorLine;

			
			//////////
			// Move to top of the document
			//////
				em->ecTopLine			= em->ecFirst;
				em->ecCursorLine		= em->ecFirst;


			//////////
			// Verify we're visible
			//////
				iSEM_verifyCursorIsVisible(em, obj);


			// Indicate we did something
			return(true);
		}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the end of the chain
//
//////
	bool iSEM_navigateEnd(SEM* em, SObject* obj)
	{
		s32			lnTop, lnBottom;
		SFont*		font;
		SEdit*		line;
		RECT		lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && em->ecCursorLine)
			{
				//////////
				// Grab the line and form
				//////
					line = em->ecCursorLine;


				//////////
				// Navigate to the end
				//////
					// We need to scan forward from ecTopLine to see if we'd be off screen.
					// If so, we drag ecTopLine forward until we reach the visible portion
					lnTop		= lrc.top;
					lnBottom	= lrc.bottom - font->tm.tmHeight;
					while (em->ecTopLine->ll.next && line->ll.next)
					{
						//////////
						// Are we still on screen?
						//////
							if (lnTop > lnBottom)
							{
								// We're off screen, so we're dragging the top forward
								em->ecTopLine = (SEdit*)em->ecTopLine->ll.next;

							} else {
								// Still on the same page
								lnTop += font->tm.tmHeight;
							}


						//////////
						// Move to next line
						//////
							line = (SEdit*)line->ll.next;
					}


				//////////
				// Update the cursor line
				//////
					em->ecCursorLine = line;


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are up one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iSEM_selectLineUp(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are down one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iSEM_selectLineDown(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select left one character.
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line.
//
//////
	bool iSEM_selectLeft(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select right one character.
//
//////
	bool iSEM_selectRight(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are to the end of line
//
//////
	bool iSEM_selectToEndOfLine(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to left one character of where we are to the beginning of line
//
//////
	bool iSEM_selectToBeginOfLine(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle selection by column mode
//
//////
	bool iSEM_selectColumnToggle(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle selection by line mode
//
//////
	bool iSEM_selectLineToggle(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one word left
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the beginning of the line, at which time we will navigate to the previous line
//        and all of the previous line will be selected.
//
//////
	bool iSEM_selectWordLeft(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one word right
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line and all
//        of the next line will be selected.
//
//////
	bool iSEM_selectWordRight(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one character left (backspace)
//
//////
	bool iSEM_deleteLeft(SEM* em, SObject* obj)
	{
		SEdit*	line;
		SEdit*	lineLast;
//		SFont*	font;
//		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && !em->isReadOnly && em->ecCursorLine)
			{
				// Grab the line
				line		= em->ecCursorLine;
				lineLast	= em->ecLast;

				// If there's nothing on this line, delete it
				if (em->ecCursorLine->sourceCodePopulated == 0)
				{
					if (em->ecFirst != em->ecLast)
					{
						// Delete the current line
						iSEM_deleteLine(em);

						if (lineLast != line)
						{
							// Navigate up one line
							iSEM_navigate(em, obj, -1, 0);
						}

						// Navigate to the end of the current line
						iSEM_navigate(em, obj, 0, em->ecCursorLine->sourceCodePopulated - em->column);
					}

				} else {
					// Do we need to do anything?
					if (em->column == 0)
					{
						if (em->ecFirst != em->ecLast)
						{
							// Delete the current line
							iSEM_deleteLine(em);

							if (lineLast != line)
							{
								// Navigate up one line
								iSEM_navigate(em, obj, -1, 0);
							}

							// Navigate to the end of the current line
							iSEM_navigate(em, obj, 0, em->ecCursorLine->sourceCodePopulated - em->column);
						}

					} else if (em->column > 0 && em->column <= line->sourceCodePopulated) {
						// Reduce our column position
						--em->column;

						// Based on insert, handle it different
						if (!em->isOverwrite)
						{
							// We're in insert mode, so we drag everything with us
							iEditChain_characterDelete(em);

						} else {
							// We're in overwrite mode, so we just insert a space
							iEditChain_characterOverwrite(em, ' ');

							// The overwrite moves us back right again, so we reduce our column position
							--em->column;
						}
					}
				}

				// Reprocess the source code on the line
				iEngine_parseSourceCodeLine(em->ecCursorLine);


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one character right (delete key)
//
//////
	bool iSEM_deleteRight(SEM* em, SObject* obj)
	{
//		SFont*	font;
//		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (em && !em->isReadOnly && em->ecCursorLine)
			{
				if (em->ecCursorLine->sourceCodePopulated == 0)
				{
					// There's no data on this line, if we're in insert mode delete the line
					if (!em->isOverwrite)
						iSEM_deleteLine(em);

				} else {
					// Delete everything to the right
					iEditChain_characterDelete(em);
				}

				// Reprocess the source code on the line
				iEngine_parseSourceCodeLine(em->ecCursorLine);


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(em, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word left (ctrl+backspace)
//
//////
	bool iSEM_deleteWordLeft(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word right (ctrl+delete)
//
//////
	bool iSEM_deleteWordRight(SEM* em, SObject* obj)
	{
//		RECT	lrc;
//		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
//			font = iEditManager_getRectAndFont(em, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the indicated position on the screen
//
//////
	bool iSEM_navigateTo_pixelXY(SEM* em, SObject* obj, s32 x, s32 y)
	{
		s32			lnI, lnRow, lnExtra;
		bool		llResult;
		RECT		lrc;
		SEdit*		edit;
		SFont*		font;


		// Make sure our environment is sane
		llResult = false;
		if (em && em->ecTopLine && obj)
		{
			//////////
			// Grab the rectangle we're working in
			//////
				font = iSEM_getRectAndFont(em, obj, &lrc);


			//////////
			// Back off if we're showing line numbers
			//////
				if (em->showLineNumbers)
					x -= em->rcLineNumberLastRender.right;


			//////////
			// See which row and column the click would be on
			//////
				lnRow		= y / font->tm.tmHeight;
				lnExtra		= font->tm.tmMaxCharWidth - (font->tm.tmAveCharWidth * 2);			// Added to fix the bug mentioned below
				if (lnExtra < 0)
					lnExtra = 0;
				em->column	= em->leftColumn + (x / (font->tm.tmAveCharWidth + lnExtra));


			//////////
			// Move to that location
			//////`
				edit = em->ecTopLine;
				for (lnI = 0, edit = em->ecTopLine; edit && edit->ll.next && lnI < lnRow; lnI++)
					edit = (SEdit*)edit->ll.next;


			///////////
			// At this point, edit is what should be the cursor line
			//////
				em->ecCursorLineLast	= em->ecCursorLine;
				em->ecCursorLine		= edit;


			//////////
			// Verify we're visible
			//////
				iSEM_verifyCursorIsVisible(em, obj);


			// Indicate success
			llResult = true;
		}

		// Indicate our status
		return(llResult);
	}
