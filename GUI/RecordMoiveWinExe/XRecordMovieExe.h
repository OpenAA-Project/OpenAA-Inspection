/*
 * Copyright (C) 2026
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

#pragma once

#include <QString>
#include <QImage>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include <QLocalSocket>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QProcess> // Added for Linux/Raspberry Pi

#ifdef Q_OS_WIN
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <codecapi.h>
#include <d3d11.h>
#include <d3d11_4.h>
#include <atomic>
#endif

#include "XServiceForLayers.h"
#include "XMovieCommon.h"

class AddImageForMovie;
class RecordMovie;
class DataInPage;

#ifdef Q_OS_WIN
class BmpClass
{
	friend	class	AddImageForMovie;
public:
    IMFMediaBuffer *pBuffer;
    DWORD           cbBufferSize;
	IMFSample		*pSample;

	AddImageForMovie	*Parent;
	RecordMovie			*RecordParent;
	DWORD				AddedMiliSec;
	HRESULT				Result;

	BmpClass(AddImageForMovie *p,RecordMovie	*RP);
	virtual	~BmpClass(void);

	bool	AddImage(void);
	void	AllocateBuff(void);

private:
	void	AddImageRGB(DataInPage* P);
};

// User's custom media buffer class
// (Does not release memory internally)
class UnownedMediaBuffer : public IMFMediaBuffer
{
public:
    UnownedMediaBuffer(BYTE* pData, DWORD length) 
        : m_refCount(1), m_pData(pData), m_length(length) {}

    // --- IUnknown Implementation ---
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IMFMediaBuffer) {
            *ppv = static_cast<IMFMediaBuffer*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef() override {
        return ++m_refCount;
    }

    STDMETHODIMP_(ULONG) Release() override {
        ULONG count = --m_refCount;
        if (count == 0) {
            delete this;
        }
        return count;
    }
    
    // --- IMFMediaBuffer Implementation ---
    
    // Lock: Return the internal pointer
    STDMETHODIMP Lock(BYTE** ppbBuffer, DWORD* pcbMaxLength, DWORD* pcbCurrentLength) override {
        if (!ppbBuffer) return E_POINTER;
        *ppbBuffer = m_pData; // Pass the pointer without copying
        if (pcbMaxLength) *pcbMaxLength = m_length;
        if (pcbCurrentLength) *pcbCurrentLength = m_length;
        return S_OK;
    }

    // Unlock: Do nothing
    STDMETHODIMP Unlock() override { return S_OK; }
    
    STDMETHODIMP GetCurrentLength(DWORD* pcbCurrentLength) override {
        if (!pcbCurrentLength) return E_POINTER;
        *pcbCurrentLength = m_length;
        return S_OK;
    }

    STDMETHODIMP SetCurrentLength(DWORD cbCurrentLength) override {
        // Since it's an external buffer, size cannot be changed; return OK just in case
        if (cbCurrentLength > m_length) return E_INVALIDARG;
        return S_OK;
    }

    STDMETHODIMP GetMaxLength(DWORD* pcbMaxLength) override {
        if (!pcbMaxLength) return E_POINTER;
        *pcbMaxLength = m_length;
        return S_OK;
    }

private:
    std::atomic<ULONG> m_refCount;
    BYTE    * m_pData;   // User's raw pointer
    DWORD   m_length;
    virtual ~UnownedMediaBuffer() = default;
};

// Macro for smart pointers, etc.
template <class T> void SafeRelease(T **ppT) {
    if (*ppT) { (*ppT)->Release(); *ppT = NULL; }
}
#endif // Q_OS_WIN

class MovieSocket : public QLocalSocket
{
	Q_OBJECT
public:
	MovieSocket(QObject *obj): QLocalSocket(obj) {}
};

class AddImageForMovie : public QThread
{
	Q_OBJECT
	friend	class	WriteFileForMovieThread;
#ifdef Q_OS_WIN
	friend	class BmpClass;
#endif

#ifdef Q_OS_WIN
	IMFSinkWriter           *pSinkWriter = nullptr;
    IMFDXGIDeviceManager    *m_pDXGIManager = nullptr;
    ID3D11Device            *m_pD3D11Device = nullptr;
	IMFMediaBuffer		    *pBuffer = nullptr;
	IMFSample			    *pSample = nullptr;
#else
    QProcess                *m_ffmpegProcess = nullptr; // Process for Linux
#endif

    DWORD			streamIndex = 0;
    long long		frameDuration = 0; // 100 nanoseconds unit
    long long		currentSampleTime = 0;
    int				videoWidth = 0;
    int				videoHeight = 0;
    bool			isOpened = false;

	int				FPS;
	int				BitRate;
	int				image_width;
	int				image_height;
	double			ZoomRate;

	MovieSocket			*Socket;
	QSharedMemory		*SharedMemForMovie;
	QSystemSemaphore	*Semaphore;

    QTimer          TM;

	volatile	bool	InitialOpened;
public:
	volatile	bool	Terminated;
	volatile	bool	Running;
	int			Error;
    int         FrameCount;
    int         LoopCount;

	QString		MovieFileName;
	int			UsePage;

public:
	AddImageForMovie(int page ,QObject *obj);
	virtual	~AddImageForMovie(void);

	void	Close(void);

	bool	StartRecording(wchar_t	*filename, int width, int height, int fps, int bitrate);
	bool	RestartRecording(void);
	bool	HaltRecording(void);
	bool	EndRecording(void);

	virtual	void	run();

private slots:
	void	SlotReadyRead();
    void    SlotTimeout();
private:
#ifdef Q_OS_WIN
    HRESULT createD3DManager();
	bool	InitializeSinkWriter(wchar_t *filename, int fps, int bitrate);
#endif
	bool	WriteFrame(void);
};