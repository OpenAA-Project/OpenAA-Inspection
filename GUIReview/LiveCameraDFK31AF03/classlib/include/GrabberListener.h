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


#ifndef GRABBERLISTENER_H_INC
#define GRABBERLISTENER_H_INC

#include "udshl_defs.h"
#include "smart_ptr.h"

#include "simplectypes.h"
#include "OverlayBitmap.h"
#include "MemBuffer.h"

namespace _DSHOWLIB_NAMESPACE
{
	class Grabber;
	class MemBuffer;
	class OverlayBitmap;
	class VideoCaptureDeviceItem;

	///< base class for listener which can be registered to receive events from the grabber object.
	class GrabberListener
	{
	public:
		///< the type of the Callbacks the listener receives
		enum tListenerType
		{
			eDEVICELOST = 0x1,
			eFRAMEREADY = 0x2,
			eOVERLAYCALLBACK = 0x4,

			eALL = eDEVICELOST | eFRAMEREADY | eOVERLAYCALLBACK,
		};
	public:
		///< dtor
		virtual ~GrabberListener()	{}

		/** called when the current device gets lost (e.g. is unplugged).
		 * @param caller	reference to the calling object.
		 */
		virtual void	deviceLost( Grabber& caller )	{}
		/** called when after the frame in pBuffer is copied.
		 * @param caller	reference to the calling object.
		 * @param pBuffer	reference to the buffer in which the frame was copied, for which the callback is called.
		 * @param FrameNumber
		 */
		virtual void	frameReady( Grabber& caller, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber ){}
		/** called when before the overlay gets updated.
		 * @param caller	reference to the calling object.
		 * @param pBitmap	reference to the OverlayBitmap object which you can use to directly draw onto the overlay.
		 * @param desc		reference to a data structure which contains the sample times and a description of the sample.
		 *				You should not use the contents of the structure after the CB returned
		 *				(the pointer of desc.pData is either invalid or may point to some other sample).
		 */
		virtual void	overlayCallback( Grabber& caller, smart_ptr<OverlayBitmap> pBitmap, const tsMediaSampleDesc& desc )	{}
	};
};

#endif // GRABBERLISTENER_H_INC