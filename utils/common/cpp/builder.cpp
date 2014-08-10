//////////
//
// /libsf/utils/common/cpp/builder.cpp
//
//////
//
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
//
//////////
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
//////




//////////
// The SBuilder structure.
// Initialize with iBuilder_createAndInitialize().
// Populate with iBuilder_append*().
// Release with iBuilder_freeAndRelease().
//////
	struct SBuilder
	{
		union {
			s8*		data;												// Pointer to a buffer allocated in blocks
			u32		_data;
		};
		u32			allocatedLength;									// How much of space has been allocated for the buffer
		u32			populatedLength;									// How much of the allocated buffer is actually populated with data
		u32			allocateBlockSize;									// Typically 16KB, the larger the size the fewer reallocs() are required
	};




//////////
// Some constant declarations used for appending
//////
	#ifndef cgcCr
		const s8 cgcCr[2]	= { 13, 0 };
	#endif
	#ifndef cgcLf
		const s8 cgcLf[2]	= { 10, 0 };
	#endif
	#ifndef cgcCrLf
		const s8 cgcCrLf[]	= "\n";
	#endif




//////////
//
// Called to ensure the indicated number of bytes can be appended onto the buffer without
// issue.  If not, reallocates the buffer.
//
//////
	void iBuilder_verifySizeForNewBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (buffRoot->data)
			{
				// Are we there yet?
				if (buffRoot->populatedLength + tnDataLength < buffRoot->allocatedLength)
				{
					// We're good, update our populated size
					buffRoot->populatedLength += tnDataLength;
					return;
				}
				// If we get here, we need to allocate more space

				// Reallocate and continue
				buffRoot->data				= (s8*)realloc(buffRoot->data, buffRoot->allocatedLength + buffRoot->allocateBlockSize);
				buffRoot->allocatedLength	+= buffRoot->allocateBlockSize;
			}
		}
		// If we get here, there's been an error
	}




//////////
//
// Initializes a new buffer to the default allocation size.
// No content is changed.
//
// Returns:  
//		Pointer to the point in the buffer where the
//////
	void iBuilder_createAndInitialize(SBuilder** buffRoot, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// See if they want to use the default size
		if (tnAllocationBlockSize == (u32)-1)
			tnAllocationBlockSize = 16384;		// Default to a 16KB allocation size

		// Make sure our environment is sane
		if (buffRoot && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)malloc(sizeof(SBuilder));
			if (buffNew)
			{
				// Initialize
				memset(buffNew, 0, sizeof(SBuilder));

				// Store the pointer
				*buffRoot = buffNew;

				// Make sure our allocation block size is at least 4KB
				tnAllocationBlockSize		= max(4096, tnAllocationBlockSize);

				// Allocate the data space
				buffNew->data				= (s8*)malloc(tnAllocationBlockSize);

				// If we allocated, we're good
				if (buffNew->data)
				{
					buffNew->allocatedLength = tnAllocationBlockSize;
					memset(buffNew->data, 0, tnAllocationBlockSize);

				} else {
					buffNew->allocatedLength = 0;
				}

				// Update the allocation size
				buffNew->allocateBlockSize	= tnAllocationBlockSize;
			}
		}
	}




//////////
//
// Appends the indicated text to the end of the buffer.
//
// Returns:  
//		Pointer to the point in the buffer where the text was inserted, can be used
//		for a furthering or continuance of this function embedded in a higher call.
//////
	s8* iBuilder_appendData(SBuilder* buffRoot, s8* tcData, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// If they want us to populate the length, do so
			if (tnDataLength == (u32)-1)
				tnDataLength = (u32)strlen(tcData);

			// If there's anything to do, do it
			if (tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);

				// If we're still valid, proceed with the copy
				if (buffRoot->data && tcData)
					memcpy(buffRoot->data + buffRoot->populatedLength - tnDataLength, tcData, tnDataLength);
			}
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Appends the indicated 32-bit value.
//
//////
	s8* iBuilder_append_u32(SBuilder* buffRoot, u32 tnValue)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			iBuilder_verifySizeForNewBytes(buffRoot, 4);

			// Copy the data
			if (buffRoot->data)
				*(u32*)(buffRoot->data + buffRoot->populatedLength - 4) = tnValue;
			
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - 4);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to append a CR to the builder
//
//////
	s8* iBuilder_appendCr(SBuilder* buffRoot)
	{
		return(iBuilder_appendData(buffRoot, (s8*)cgcCr, sizeof(cgcCr) - 1));
	}




//////////
//
// Called to append a CR+LF to the builder
//
//////
	s8* iBuilder_appendCrLf(SBuilder* buffRoot)
	{
		return(iBuilder_appendData(buffRoot, (s8*)cgcCrLf, sizeof(cgcCrLf) - 1));
	}




//////////
//
// Called to allocate bytes in the builder, but not yet populate them with anything
//
//////
	s8* iBuilder_allocateBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			if (tnDataLength != 0)
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);
			
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Specifies the size the buffer should be.  Either allocates up or down. No content
// is changed, however the buffer pointer value could be changed from oss_realloc().
// In addition, this function should not be used for resizing in general.  Simply call
// the builder_AppendData() function and it will automatically resize if needed, as
// per the allocated block size.
//
//////
	void iBuilder_setSize(SBuilder* buffRoot, u32 tnBufferLength)
	{
		s8* lcNew;


		// Make sure our environment is sane
		if (buffRoot)
		{
			//////////
			// See if they want to make it whatever the populated size is
			//////
				if (tnBufferLength == (u32)-1)
					tnBufferLength = buffRoot->populatedLength;


			//////////
			// See if they're releasing everything
			//////
				if (tnBufferLength == 0)
				{
					//////////
					// They are freeing everything
					//////
						free(buffRoot->data);
						buffRoot->data				= NULL;
						buffRoot->populatedLength	= 0;
						buffRoot->allocatedLength	= 0;


				} else if (tnBufferLength != buffRoot->allocatedLength) {
					//////////
					// They are resizing
					//////
						lcNew = (s8*)realloc(buffRoot->data, tnBufferLength);
						if (lcNew)
						{
							//////////
							// Set the allocated length
							//////
								buffRoot->data				= lcNew;
								buffRoot->allocatedLength	= tnBufferLength;


							//////////
							// If our populated length no longer fits into the new allocated space, then adjust it down
							//////
								if (buffRoot->populatedLength > buffRoot->allocatedLength)
									buffRoot->populatedLength = buffRoot->allocatedLength;		// Bring the populated area down to the new size

						} else {
							// Failure on resize -- should not happen
							debug_break;
						}
				}
		}
	}




//////////
//
// Releases the buffer allocated for the SBuilder structure
//
//////
	void iBuilder_freeAndRelease(SBuilder** buffRoot)
	{
		SBuilder* buffDelete;


		// Make sure our environment is sane
		if (buffRoot && *buffRoot)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *buffRoot;
			*buffRoot	= NULL;

			// Release the data buffer
			if (buffDelete->data)
			{
				// Trim our sizes down to 0
				buffDelete->allocatedLength = 0;
				buffDelete->populatedLength = 0;

				// Release our buffer
				free(buffDelete->data);

				// Mark it as no longer valid
				buffDelete->data = NULL;
			}

			// Release the SBuilder structure
			free(buffDelete);
		}
	}




//////////
//
// Called to write out the indicated builder file as an 8-bit ASCII file
//
//////
	u32 iBuilder_asciiWriteOutFile(SBuilder* buffRoot, s8* tcPathname)
	{
		FILE* lfh;


		// Make sure there's something to write
		if (buffRoot && tcPathname)	
		{
			// Try to create the file
			lfh = fopen(tcPathname, "wb+");
			if (lfh)
			{
				// Write out the data if need be
				if (buffRoot->data && buffRoot->populatedLength != 0)
				{
					fwrite(buffRoot->data, 1, buffRoot->populatedLength, lfh);
					fclose(lfh);
					return(buffRoot->populatedLength);
				}
				// If we get here, nothing to write
				fclose(lfh);
				return(0);
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to load a file into the indicated buffer.
//
//////
	bool iBuilder_asciiReadFromFile(SBuilder** buffRoot, s8* tcPathname)
	{
		u32		lnSize, lnNumread, lnStart;
		FILE*	lfh;


		// Make sure our environment is sane
		if (buffRoot && tcPathname)
		{
			//////////
			// If we don't have a buffer, create one
			//////
				if (!*buffRoot)
					iBuilder_createAndInitialize(buffRoot, -1);


			// Try to open the indicated file
			lfh = fopen(tcPathname, "rb");
			if (lfh)
			{
				//////////
				// Find out how big the file is
				//////
					fseek(lfh, 0, SEEK_END);
					lnSize = ftell(lfh);
					fseek(lfh, 0, SEEK_SET);

				
				//////////
				// Allocate that buffer
				//////
					lnStart = (*buffRoot)->populatedLength;
					iBuilder_verifySizeForNewBytes(*buffRoot, lnSize);


				//////////
				// Read in the content
				//////
					lnNumread						= fread((*buffRoot)->data + lnStart, 1, lnSize, lfh);
					(*buffRoot)->populatedLength	= lnStart + min(lnNumread, lnSize);


				//////////
				// Close the file
				//////
					fclose(lfh);


				//////////
				// Were we successful?
				//////
					if (lnNumread == lnSize)
					{
						// We're good
						return(true);
					}

			} else {
				// We could not open the file
				// We don't do anything here, but just trap the condition and note it here in the comments
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to compact data
//
//////
	void iBuilder_compactData(SBuilder* buffRoot, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction)
	{
		u32 lnI, lnCopyTo;
		union
		{
			// This 
			u32		_compactCallbackFunction;
			bool	(*compactCallbackFunction)	(void* ptr);
		};


		// Make sure our environment is sane
		if (buffRoot && buffRoot->data && buffRoot->populatedLength >= tnStart)
		{
			// Setup our callback function
			_compactCallbackFunction = tnCompactCallbackFunction;

			// Iterate through each pointer
			lnCopyTo = tnStart;
			for (lnI = tnStart; lnI < buffRoot->populatedLength; lnI += tnStride)
			{
				if (!compactCallbackFunction(buffRoot->data + lnI))
				{
					// We are keeping this one
					if (lnCopyTo != lnI)
						memcpy(buffRoot->data + lnCopyTo, buffRoot->data + lnI, tnStride);

					// Move to next one
					lnCopyTo += tnStride;
				}
			}
			// When we get here, everything's been compacted
			if (lnCopyTo < buffRoot->populatedLength)
				iBuilder_setSize(buffRoot, lnCopyTo);
		}
	}




//////////
//
// Called to insert bytes at the indicated location.
//
//////
	s8* iBuilder_insertBytes(SBuilder* buffRoot, u32 tnStart, u32 tnLength)
	{
		u32		lnI, lnStop;
		s8*		buffNew;
		s8*		lcSrc;
		s8*		lcDst;


		//////////
		// Make sure our environment is sane
		//////
			buffNew = NULL;
			if (buffRoot && buffRoot->data)
			{
				//////////
				// Are we adding to the end?
				//////
					if (buffRoot->populatedLength == tnStart)
						return(iBuilder_allocateBytes(buffRoot, tnLength));		// We're appending to the end


				//////////
				// If we get here, we're inserting in the middle
				// We go ahead and allocate the new bytes
				//////
					buffNew = iBuilder_allocateBytes(buffRoot, tnLength);
					if (buffNew)
					{
						//////////
						// Now, we have to copy everything backwards so we don't propagate a portion repeatedly
						//////
							lcSrc	= buffRoot->data + buffRoot->populatedLength - tnLength - 1;
							lcDst	= buffRoot->data + buffRoot->populatedLength - 1;
							lnStop	= buffRoot->populatedLength - tnStart - tnLength;


						//////////
						// Copy until we're done
						//////
							for (lnI = 0; lnI < lnStop; lnI++, lcDst--, lcSrc--)
								*lcDst = *lcSrc;


						//////////
						// Indicate where our new record is
						//////
							buffNew = buffRoot->data + tnStart;
					}
			}
			// Indicate our status
			return(buffNew);
	}



//////////
//
// Searching for a needle in a haystack.
// Called to perform a binary search on the data in a builder.  This is typically used for a fixed
// structure that is repeatedly stored.  The optional parameter allows the item to be inserted
// where it should go if it was not found.
//
//////
// TODO:  A speedup for this algorithm would be to test tnDataLength and if it's 32-bit or 64-bit, then do integer searches rather than string compare searches
	u32 iBuilder_binarySearch(SBuilder* haystack, s8* tcNeedle, u32 tnNeedleLength, bool* tlFound, bool tlInsertIfNotFound)
	{
		s32		lnResult;
		s32		lnTop, lnMid, lnBot;
		s8*		buffNew;


// TODO:  untested, breakpoint and examine
		debug_break;
		//////////
		// Make sure our environment is sane
		//////
			if (haystack && haystack->data && haystack->populatedLength % tnNeedleLength == 0)
			{
				//////////
				// Perform a binary search
				//////
					lnTop = 0;
					lnBot = (haystack->populatedLength / tnNeedleLength) - 1;
					lnMid = max((lnTop + lnBot) / 2, lnTop);
					while (lnTop <= lnBot)
					{
						// Position our search pointer
						lnMid = (lnTop + lnBot) / 2;

						// See if it's above or below this position
						lnResult = memcmp(haystack->data + (lnMid * tnNeedleLength), tcNeedle, tnNeedleLength);
						if (lnResult == 0)
						{
							// Found, but this may not be the first one, we need to creep backwards to find the first
							if (lnMid == lnBot)
							{
								// Success!
								if (tlFound)
									*tlFound = true;

								// Indicate our entry
								return(lnMid * tnNeedleLength);
							}
							// Continue looking in the top half
							lnBot = lnMid;

						} else if (lnResult < 0) {
							// Our haystack entry is less than our needle, it's after this in the list
							lnTop = lnMid + 1;

						} else {
							// Our haystack entry is greater than our need, it's before this in the list
							lnBot = lnMid - 1;
						}
					}
					// When we get here, it was not found
					if (tlFound)
						*tlFound = false;


				//////////
				// See if they want us to add it
				//////
					if (tlInsertIfNotFound)
					{
						// We will insert it where lnMid is
						buffNew = iBuilder_insertBytes(haystack, lnMid * tnNeedleLength, tnNeedleLength);
						if (buffNew)
						{
							// We can copy over and insert it
							memcpy(buffNew, tcNeedle, tnNeedleLength);

							// Indicate where it exists in the list
							return(lnMid * tnNeedleLength);

						} else {
							// Failure adding
							return(-3);
						}

					} else {
						// Indicate no find
						return(-1);
					}
			}


		//////////
		// Was not found, is invalid configuration
		//////
			if (tlFound)	*tlFound = false;
			return(-2);		// Is invalid configuration
	}
