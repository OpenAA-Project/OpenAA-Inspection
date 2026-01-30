/*
 * Copyright (C) 2025
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

#include <mfapi.h>
#include "XLibWMF.h"
#include "LibWMFCamera.h"

VideoBufferLock::VideoBufferLock(IMFMediaBuffer *aBuffer) 
	: m2DBuffer(NULL), mLocked(false)
{
	mBuffer = aBuffer;
	mBuffer->AddRef();

	// Query for the 2-D buffer interface. OK if this fails.
	(void)mBuffer->QueryInterface(IID_PPV_ARGS(&m2DBuffer));
}

VideoBufferLock::~VideoBufferLock()
{
	UnlockBuffer();
	if (mBuffer)
		mBuffer->Release();
	if (m2DBuffer)
		m2DBuffer->Release();
}

HRESULT VideoBufferLock::LockBuffer(
	LONG  aDefaultStride,    // Minimum stride (with no padding).
	DWORD aHeightInPixels,  // Height of the image, in pixels.
	BYTE  **aScanLine0,    // Receives a pointer to the start of scan line 0.
	LONG  *aStride          // Receives the actual stride.
	)
{
	HRESULT hr = S_OK;

	// Use the 2-D version if available.
	if (m2DBuffer)
	{
		hr = m2DBuffer->Lock2D(aScanLine0, aStride);
	}
	else
	{
		// Use non-2D version.
		BYTE *data = NULL;

		hr = mBuffer->Lock(&data, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			*aStride = aDefaultStride;
			if (aDefaultStride < 0)
			{
				// Bottom-up orientation. Return a pointer to the start of the
				// last row *in memory* which is the top row of the image.
				*aScanLine0 = data + abs(aDefaultStride) * (aHeightInPixels - 1);
			}
			else
			{
				// Top-down orientation. Return a pointer to the start of the
				// buffer.
				*aScanLine0 = data;
			}
		}
	}

	mLocked = (SUCCEEDED(hr));

	return hr;
}


void VideoBufferLock::UnlockBuffer()
{
	if (mLocked)
	{
		if (m2DBuffer)
		{
			(void)m2DBuffer->Unlock2D();
		}
		else
		{
			(void)mBuffer->Unlock();
		}
		mLocked = false;
	}
}