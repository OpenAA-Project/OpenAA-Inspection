/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// FrameGrabberSink.h: interface for the FrameGrabberSink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEGRABBERSINK_H__DE7BC1B6_25F9_4F33_919B_710A99EA015A__INCLUDED_)
#define AFX_FRAMEGRABBERSINK_H__DE7BC1B6_25F9_4F33_919B_710A99EA015A__INCLUDED_

#pragma once

#include "GrabberSinkType.h"
#include "MemBufferCollection.h"

class ISampleTransformHandler;

namespace _DSHOWLIB_NAMESPACE
{
	class Grabber;
	class GrabberPImpl;

	class CFGSinkType;

	/** This class is deprecated. Use the FrameHandlerSink object.
	 * 
	 * Sink type for a framegrabber
	 */
	class _UDSHL_EXP_API FrameGrabberSink : public GrabberSinkType  
	{
		friend Grabber;
		friend GrabberPImpl;
	public:
		enum tFrameGrabberMode
		{
			eSNAP,		///< mode where you have to call snapImage to get a frame copied into the ring buffer
			eGRAB,		///< continuous grabbing mode, where every frame is copied into the ring buffer
		};

		typedef smart_ptr<MemBufferCollection> tMemBufferCollectionPtr;
	public:
		/** ctor
		 * @param grabber if true then a continuous grab operation is started with startLive(), 
		 * if false, then you are able to snap particular frames into the ring buffer
		 * @param type is the type of the sink
		 */
		FrameGrabberSink( tFrameGrabberMode mode, tColorformatEnum type = eRGB24, tSinkModes AutoStart = eRUN );
		
		/** copy ctor*/
		FrameGrabberSink( const FrameGrabberSink& op2 );
		/** dtor */
		virtual ~FrameGrabberSink();

		/** assignment operator */
		FrameGrabberSink&				operator=( const FrameGrabberSink& op2 );

		/** return the type of the sink. pure virtual function from the base
		 * @return always eFrameGrabberSink
		 */
		tSinkType						getSinkType() const;

		/** returns the set Colorformat */
		tColorformatEnum				getColorformat() const;
		/** returns the set mode */
		tFrameGrabberMode				getMode() const;
	protected:
		/** Creates a new MemBufferCollection which fits for this sink.
		 * @param buffer_count	The count of buffers in the collection.
		 * @return 0 on error
		 *			Otherwise a valid collection as needed.
		 */
		tMemBufferCollectionPtr			newMemBufferCollection( DWORD buffer_count ) const;
		/** Creates a new MemBufferCollection which fits for this sink.
		 * @param buffersize	The size of an individual Buffer you passed.
		 * @param buffers		An array of pointer which contains buffer_count pointer to buffers, to which
		 *							the Grabber will write. (If one entry is 0, then 0 is returned).
		 * @param buffer_count	The count of buffers in the collection.
		 * @return 0 on error
		 *			Otherwise a valid collection as needed.
		 */
		tMemBufferCollectionPtr			newMemBufferCollection( DWORD buffersize, BYTE* buffers[], DWORD buffer_count ) const;

	protected:
		smart_com<icbase::IDShowFilter>			getBaseSinkFilter() const;

		Error							setMemBufferCollection( const tMemBufferCollectionPtr& pCol );
		smart_ptr<MemBufferCollection>	getMemBufferCollection() const;

		smart_ptr<MemBuffer>			getActiveMemBuffer() const;
		DWORD							getFrameCount() const;
		
		Error							snapImages( DWORD count, DWORD timeout );
		void							setSinkDim( const SIZE& r );

		bool							isValid() const;

		unsigned long					getFrameDataSize();

#pragma _DLL_EXPORT_WARNING_DISABLE
		smart_ptr<CFGSinkType>	m_pFGFilter;
#pragma _DLL_EXPORT_WARNING_ENABLE
	};
};

#endif // !defined(AFX_FRAMEGRABBERSINK_H__DE7BC1B6_25F9_4F33_919B_710A99EA015A__INCLUDED_)