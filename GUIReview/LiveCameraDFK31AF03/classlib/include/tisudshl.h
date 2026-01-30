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

#ifndef TISUDSHL_H
#define TISUDSHL_H

#pragma warning( push )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4100 ) // warning C4100: unreferenced formal parameter

#include <string>
#include <cassert>
#include <vector>
#include <shlwapi.h>

// DLL public interface 
#include "libbasedefs.h"
#include "udshl_defs.h"

#include "dshow_header.h"

// linker helper, to bind to the UDSHL
#include "udshl_lnk.h"

#include "smart_ptr.h"
#include "smart_com.h"

#include "simplectypes.h"

#include "int_interface_pre.h"

#include "VideoFormatItem.h"
#include "VideoFormatDesc.h"
#include "VideoNormItem.h"
#include "VideoCaptureDeviceItem.h"
#include "AnalogChannelItem.h"

#include "Error.h"
#include "Grabber.h"
#include "MemBufferCollection.h"
#include "MemBuffer.h"
#include "Framegrabbersink.h"
#include "AviSink.h"
#include "OverlayBitmap.h"
#include "GrabberListener.h"

#include "FrameHandlerSink.h"
#include "MediaStreamSink.h"

#include "IVCDProperty.h"
#include "IVCDPropertyInterfaces.h"
#include "VCDPropertyDef.h"

#include "VCDPropertyID.h"
#include "VCDPropertyIDTIS.h"

#include "FilterLoader.h"
#include "FrameFilter.h"
#include "FrameFilterImpl.h"

#pragma warning( pop )

#endif /* TISUDSHL_H */