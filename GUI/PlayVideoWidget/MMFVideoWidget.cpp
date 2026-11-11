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

#include <QLabel>
#include <QImage>
#include <QThread>
#include <QFileDialog>
#include <QDebug>
#include <QElapsedTimer>

#ifdef Q_OS_WIN
// Windows / Media Foundation Headers
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>       
#include <mfreadwrite.h> 
#include <d3d11.h>
#include <d3d11_4.h>
#include <propvarutil.h> // For PROPVARIANT operations

// Linker settings
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "opengl32.lib")

template <class T> void SafeRelease(T **ppT) {
    if (*ppT) { (*ppT)->Release(); *ppT = NULL; }
}
#else
// Linux / Raspberry Pi: FFmpeg Headers
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
}
#endif

#include "PlayVideoWidget.h"
#include "XVideoWidget.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"


MMFVideoWidget::MMFVideoWidget(PlayVideoWidget* player, QWidget *parent)
    : QOpenGLWidget(parent), Parent(player), Player(this)
{
    connect(&Player, &MFDecoderThread::durationChanged, this, [&](qint64 totalMs){
        totalDuration = totalMs;
    });
    connect(&Player, SIGNAL(positionChanged(qint64)), this, SLOT(SlotPositionChanged(qint64)), Qt::QueuedConnection);
    connect(&Player, SIGNAL(playbackFinished()), this, SLOT(SlotBlaybackFinished()), Qt::QueuedConnection);
}

MMFVideoWidget::~MMFVideoWidget()
{
    Player.stop();
    Player.wait(1000);

    makeCurrent();
    if (m_texture) m_texture->destroy();
    delete m_texture;
    delete m_program;
    doneCurrent();
}

void MMFVideoWidget::SlotPositionChanged(qint64 currentMs)
{
    CurrentMs = currentMs;
    emit SignalPositionChanged(currentMs);
}

void MMFVideoWidget::SlotBlaybackFinished()
{
    emit SignalBlaybackFinished();
}

bool MMFVideoWidget::IsPlaying()
{
    return (Player.m_playing.load() && !Player.m_stop.load() && !Player.m_pause.load());
}

bool MMFVideoWidget::IsPausing()
{
    return (Player.m_playing.load() && !Player.m_stop.load() && Player.m_pause.load());
}

qint64 MMFVideoWidget::duration()
{
    return totalDuration;
}

qint64 MMFVideoWidget::position()
{
    return CurrentMs;
}

// Seek to the specified position in milliseconds
void MMFVideoWidget::seek(qint64 ms)
{
    // Clamp to valid range (0 to totalDuration)
    if (ms < 0) ms = 0;
    if (totalDuration > 0 && ms > totalDuration) ms = totalDuration;

    // Update current position immediately for UI responsiveness
    CurrentMs = ms;
    emit SignalPositionChanged(CurrentMs);

    // Send seek request to the decoder thread
    Player.seekTo(ms);
}

void MMFVideoWidget::rewind(qint64 /*ms*/)
{
    seek(0);
}

void MMFVideoWidget::setPlaybackRate(double rate)
{
    // Notify the decoder thread
    Player.setPlaybackRate(rate);
}

double MMFVideoWidget::playbackRate() const
{
    return Player.m_requestedRate.load();
}

// For fast-forward button: toggles between 1.0x and 2.0x speed
void MMFVideoWidget::forward()
{
    if (Player.m_requestedRate.load() == 2.0) {
        setPlaybackRate(1.0);
    } else {
        setPlaybackRate(2.0);
    }
}

// Called from the decoder thread: copies frame data to the back buffer
void MMFVideoWidget::updateFrame(const uchar* data, int width, int height, int stride, bool isBGRA)
{
    QMutexLocker locker(&m_mutex);
    
    // Resize buffer if dimensions changed
    if (m_buffer.size() != static_cast<size_t>(width * height * 4)) {
        m_buffer.resize(width * height * 4);
    }
    
    m_videoWidth = width;
    m_videoHeight = height;
    
    // Copy row by row considering stride.
    // Top-to-bottom order is preserved since UV coordinates handle orientation.
    const uchar* src = data;
    uchar* dst = m_buffer.data();
    int lineBytes = width * 4; // RGBA 32bit
    
    if (!isBGRA) {
        // Already in RGBA order (Linux / FFmpeg)
        if (stride == lineBytes) {
            memcpy(dst, src, m_buffer.size());
        } else {
            for (int y = 0; y < height; ++y) {
                memcpy(dst, src, lineBytes);
                src += stride;
                dst += lineBytes;
            }
        }
    } else {
        // Convert BGRA to RGBA (for Windows Media Foundation RGB32)
        for (int y = 0; y < height; ++y) {
            const uchar* sLine = src;
            uchar* dLine = dst;
            for (int x = 0; x < width; ++x) {
                dLine[0] = sLine[2]; // R
                dLine[1] = sLine[1]; // G
                dLine[2] = sLine[0]; // B
                dLine[3] = sLine[3]; // A
                sLine += 4;
                dLine += 4;
            }
            src += stride;
            dst += lineBytes;
        }
    }
    
    m_newFrameAvailable = true;
    // Request update() on the UI thread
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}

void MMFVideoWidget::setSource(const QString &path)
{
    Player.setSource(path);
    totalDuration = static_cast<qint64>(GetVideoDuration(path) * 1000.0);
}

double MMFVideoWidget::GetVideoDuration(const QString& filename)
{
    if (filename.isEmpty()) return 0.0;

#ifdef Q_OS_WIN
    IMFSourceReader* pReader = nullptr;
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) return 0.0;

    // 1. Create Source Reader
    std::wstring wfilename = filename.toStdWString();
    hr = MFCreateSourceReaderFromURL(wfilename.c_str(), nullptr, &pReader);
    if (FAILED(hr)) {
        MFShutdown();
        return 0.0;
    }

    // 2. Retrieve presentation duration attribute (in 100-nanosecond units)
    double durationSec = 0.0;
    PROPVARIANT var;
    PropVariantInit(&var);
    if (SUCCEEDED(pReader->GetPresentationAttribute(MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &var))) {
        durationSec = (double)var.uhVal.QuadPart / 10000000.0;
    }
    PropVariantClear(&var);
    pReader->Release();
    MFShutdown();
    return durationSec;
#else
    AVFormatContext* fmtCtx = nullptr;
    QByteArray utf8Path = filename.toUtf8();
    if (avformat_open_input(&fmtCtx, utf8Path.constData(), nullptr, nullptr) != 0) {
        return 0.0;
    }
    double durationSec = 0.0;
    if (avformat_find_stream_info(fmtCtx, nullptr) >= 0) {
        if (fmtCtx->duration != AV_NOPTS_VALUE) {
            durationSec = static_cast<double>(fmtCtx->duration) / AV_TIME_BASE;
        }
    }
    avformat_close_input(&fmtCtx);
    return durationSec;
#endif
}

void MMFVideoWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Create shader program
    m_program = new QOpenGLShaderProgram();
    
    // Vertex shader: simple full-screen quad
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, R"(
        attribute vec4 position;
        attribute vec2 texCoord;
        varying vec2 vTexCoord;
        void main() {
            gl_Position = position;
            vTexCoord = texCoord;
        }
    )");
    
    // Fragment shader: texture sampling (includes precision qualifier for OpenGL ES)
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, R"(
        #ifdef GL_ES
        precision mediump float;
        #endif
        uniform sampler2D texture;
        varying vec2 vTexCoord;
        void main() {
            gl_FragColor = texture2D(texture, vTexCoord);
        }
    )");
    
    m_program->link();
}

void MMFVideoWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MMFVideoWidget::paintGL()
{
    // Clear background to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Do not render if video dimensions or widget height are zero
    if (m_videoWidth == 0 || m_videoHeight == 0 || height() == 0) return;
    
    QMutexLocker locker(&m_mutex);
    
    if (!m_program) return;
    m_program->bind();
    
    // Initialize or recreate texture if dimensions changed
    if (!m_texture || m_texture->width() != m_videoWidth || m_texture->height() != m_videoHeight) {
        if (m_texture) {
            m_texture->destroy();
            delete m_texture;
        }
        m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        m_texture->setSize(m_videoWidth, m_videoHeight);
        m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
        m_texture->allocateStorage();
        m_texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    }
    
    // Upload new frame to GPU if available (unified as RGBA for OpenGL / OpenGL ES)
    if (m_newFrameAvailable) {
        m_texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, m_buffer.data());
        m_newFrameAvailable = false;
    }
    
    m_texture->bind();
    
    // ---------------------------------------------------------
    // Aspect ratio calculation (letterboxing / pillarboxing)
    // ---------------------------------------------------------
    float windowRatio = (float)width() / (float)height();
    float videoRatio = (float)m_videoWidth / (float)m_videoHeight;
    
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    
    if (windowRatio > videoRatio) {
        // Window is wider than video -> add black bars on left and right
        scaleX = videoRatio / windowRatio;
    } else {
        // Window is taller than video -> add black bars on top and bottom
        scaleY = windowRatio / videoRatio;
    }

    // Apply calculated scale to vertex coordinates (-1.0 to 1.0)
    float vertices[] = {
        -scaleX, -scaleY,  0.0f, 1.0f, // Bottom-left
         scaleX, -scaleY,  1.0f, 1.0f, // Bottom-right
        -scaleX,  scaleY,  0.0f, 0.0f, // Top-left
         scaleX,  scaleY,  1.0f, 0.0f  // Top-right
    };
    // ---------------------------------------------------------
    
    int posLoc = m_program->attributeLocation("position");
    int texLoc = m_program->attributeLocation("texCoord");
    
    m_program->enableAttributeArray(posLoc);
    m_program->enableAttributeArray(texLoc);
    
    m_program->setAttributeArray(posLoc, GL_FLOAT, vertices, 2, 4 * sizeof(float));
    m_program->setAttributeArray(texLoc, GL_FLOAT, vertices + 2, 2, 4 * sizeof(float));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    m_program->disableAttributeArray(posLoc);
    m_program->disableAttributeArray(texLoc);
    
    m_texture->release();
    m_program->release();
}

void MMFVideoWidget::play()
{
    if (IsPlaying()) {
        Player.stop();
        Player.wait(2000);
    }
    if (Player.PreparePlay()) {
        Player.start();
    }
}

void MMFVideoWidget::stop()
{
    Player.stop();
}

void MMFVideoWidget::pause()
{
    Player.pause();
}

void MMFVideoWidget::restart()
{
    Player.restart();
}

//======================================================================
// ---------------------------------------------------------
// MFDecoderThread: Decodes video and passes raw pixel data to the widget
// ---------------------------------------------------------

MFDecoderThread::MFDecoderThread(MMFVideoWidget* widget, QObject *parent) 
    : QThread(parent), m_glWidget(widget)
{
    m_pause = false;
    m_playing = false;
    m_stop = false;
    m_seekRequest = false;
    m_seekTargetMs = 0;
    m_requestedRate = 1.0;
}

MFDecoderThread::~MFDecoderThread()
{
    stop();
    cleanupDecoder();
}
    
void MFDecoderThread::setSource(const QString &path) { m_filePath = path; }
void MFDecoderThread::stop()    { m_stop = true; wait(); }
void MFDecoderThread::pause()   { m_pause = true; }
void MFDecoderThread::restart() { m_pause = false; }

void MFDecoderThread::seekTo(qint64 ms)
{
    m_seekTargetMs = ms;
    m_seekRequest = true;
}

void MFDecoderThread::setPlaybackRate(double rate)
{
    if (rate > 0.0) {
        m_requestedRate = rate;
    }
}

void MFDecoderThread::cleanupDecoder()
{
#ifdef Q_OS_WIN
    SafeRelease(&pReader);
    SafeRelease(&pAttributes);
    SafeRelease(&pDXGIManager);
    SafeRelease(&pContext);
    SafeRelease(&pD3D11Device);
#else
    if (m_swsCtx) {
        sws_freeContext(m_swsCtx);
        m_swsCtx = nullptr;
    }
    if (m_codecCtx) {
        avcodec_free_context(&m_codecCtx);
        m_codecCtx = nullptr;
    }
    if (m_formatCtx) {
        avformat_close_input(&m_formatCtx);
        m_formatCtx = nullptr;
    }
    m_videoStreamIdx = -1;
#endif
}

bool MFDecoderThread::PreparePlay()
{
    if (m_filePath.isEmpty()) {
        return false;
    }
    stop();
    cleanupDecoder();

    m_stop = false;
    m_pause = false;
    m_seekRequest = false;
    m_requestedRate = 1.0; // Default 1.0x speed

#ifdef Q_OS_WIN
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        return false;
    }
    
    // D3D11 Init
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, 0, D3D11_SDK_VERSION, &pD3D11Device, NULL, &pContext);
    
    if (pD3D11Device) {
        ID3D11Multithread *pMultithread = nullptr;
        pD3D11Device->QueryInterface(__uuidof(ID3D11Multithread), (void**)&pMultithread);
        if (pMultithread) { pMultithread->SetMultithreadProtected(TRUE); pMultithread->Release(); }
    }
    
    UINT token = 0;
    MFCreateDXGIDeviceManager(&token, &pDXGIManager);
    if (pDXGIManager && pD3D11Device) pDXGIManager->ResetDevice(pD3D11Device, token);
    
    MFCreateAttributes(&pAttributes, 0);
    if (pDXGIManager) pAttributes->SetUnknown(MF_SOURCE_READER_D3D_MANAGER, pDXGIManager);
    pAttributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE);
    pAttributes->SetUINT32(MF_SOURCE_READER_ENABLE_ADVANCED_VIDEO_PROCESSING, TRUE);
    
    hr = MFCreateSourceReaderFromURL(reinterpret_cast<LPCWSTR>(m_filePath.utf16()), pAttributes, &pReader);
    SafeRelease(&pAttributes);
    
    if (FAILED(hr)) {
        cleanupDecoder();
        MFShutdown();
        return false;
    }
    
    // Get Duration
    PROPVARIANT var; PropVariantInit(&var);
    if (SUCCEEDED(pReader->GetPresentationAttribute(MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &var))) {
        emit durationChanged(var.uhVal.QuadPart / 10000);
    }
    PropVariantClear(&var);
    
    // Set Format RGB32
    IMFMediaType *pType = nullptr;
    MFCreateMediaType(&pType);
    pType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    pType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32);
    pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, NULL, pType);
    SafeRelease(&pType);
    
    m_playing = true;
    return true;

#else
    QByteArray utf8Path = m_filePath.toUtf8();
    if (avformat_open_input(&m_formatCtx, utf8Path.constData(), nullptr, nullptr) != 0) {
        return false;
    }
    if (avformat_find_stream_info(m_formatCtx, nullptr) < 0) {
        cleanupDecoder();
        return false;
    }

    if (m_formatCtx->duration != AV_NOPTS_VALUE) {
        emit durationChanged((m_formatCtx->duration * 1000) / AV_TIME_BASE);
    }

    const AVCodec* codec = nullptr;
    m_videoStreamIdx = av_find_best_stream(m_formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (m_videoStreamIdx < 0 || !codec) {
        cleanupDecoder();
        return false;
    }

    AVStream* videoStream = m_formatCtx->streams[m_videoStreamIdx];
    m_codecCtx = avcodec_alloc_context3(codec);
    if (!m_codecCtx) {
        cleanupDecoder();
        return false;
    }

    if (avcodec_parameters_to_context(m_codecCtx, videoStream->codecpar) < 0) {
        cleanupDecoder();
        return false;
    }

    // Automatically select thread count for multi-core CPUs (e.g., Raspberry Pi)
    m_codecCtx->thread_count = 0;

    if (avcodec_open2(m_codecCtx, codec, nullptr) < 0) {
        cleanupDecoder();
        return false;
    }

    m_playing = true;
    return true;
#endif
}

void MFDecoderThread::run()
{
    QElapsedTimer clock;
    bool isFirstFrame = true;

    // Pause duration tracking
    QElapsedTimer pauseClock;     // Timer to measure pause duration
    qint64 totalPausedTime = 0;   // Cumulative paused time in milliseconds
    bool wasPaused = false;       // Whether the thread was paused in the previous iteration
    
    // Playback rate control: anchor point management
    double currentRate = 1.0;
    qint64 anchorPts = 0;         // Video PTS at the moment of rate change
    qint64 anchorRealTime = 0;    // Real elapsed time at the moment of rate change

#ifdef Q_OS_WIN
    HRESULT hr;

    while (!m_stop) {
        // --- 1. Seek handling ---
        if (m_seekRequest) {
            PROPVARIANT posVar;
            PropVariantInit(&posVar);
            posVar.vt = VT_I8;
            posVar.hVal.QuadPart = m_seekTargetMs.load() * 10000; // Convert ms to 100ns units
            
            hr = pReader->SetCurrentPosition(GUID_NULL, posVar);
            PropVariantClear(&posVar);
            
            if (SUCCEEDED(hr)) {
                // Reset synchronization variables on successful seek.
                // Setting isFirstFrame = true ensures one frame is rendered even while paused.
                isFirstFrame = true;
                totalPausedTime = 0;
                wasPaused = false;
            }
            m_seekRequest = false;
        }

        // --- 2. Pause handling ---
        if (m_pause) {
            // Wait if paused, except for the first frame right after a seek
            if (!isFirstFrame) {
                if (!wasPaused) {
                    pauseClock.start();
                    wasPaused = true;
                }
                msleep(50);
                continue;
            }
        } else {
            // Resumed from pause
            if (wasPaused) {
                totalPausedTime += pauseClock.elapsed();
                pauseClock.invalidate();
                wasPaused = false;
            }
        }
 
        // --- 3. Read frame ---
        IMFSample *pSample = nullptr;
        DWORD flags = 0;
        LONGLONG llSampleTime = 0;
        
        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, &llSampleTime, &pSample);
        if (FAILED(hr)) {
            break; // Exit on error
        }

        // --- End of stream ---
        if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
            emit playbackFinished(); 
            break;
        }

        if (pSample) {
            qint64 currentPtsMs = llSampleTime / 10000;
            emit positionChanged(currentPtsMs);
            
            // --- 4. Synchronization logic (variable playback rate support) ---
            if (isFirstFrame) {
                clock.start();
                currentRate = m_requestedRate.load();
                anchorPts = currentPtsMs;
                anchorRealTime = 0;
                isFirstFrame = false;
            } else if (!m_pause) {
                qint64 currentRealTime = clock.elapsed() - totalPausedTime;
                double reqRate = m_requestedRate.load();
                
                // Detect playback rate change and update anchor
                if (reqRate != currentRate) {
                    currentRate = reqRate;
                    anchorPts = currentPtsMs;
                    anchorRealTime = currentRealTime;
                }

                // Synchronize based on elapsed time from anchor point
                qint64 timeSinceAnchor = currentRealTime - anchorRealTime;
                qint64 expectedPts = anchorPts + (qint64)(timeSinceAnchor * currentRate);
                
                qint64 diffPts = currentPtsMs - expectedPts;
                if (diffPts > 0) {
                    qint64 waitMs = (qint64)(diffPts / currentRate);
                    if (waitMs > 0)
                        msleep(waitMs);
                }
            }
            
            // --- 5. Transfer frame for rendering ---
            IMFMediaBuffer *pBuffer = nullptr;
            pSample->ConvertToContiguousBuffer(&pBuffer);
            
            if (pBuffer) {
                BYTE *pData = nullptr;
                DWORD currentLength = 0;
                pBuffer->Lock(&pData, NULL, &currentLength); // GPU -> CPU readback

                IMFMediaType *pCurrentType = nullptr;
                pReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, &pCurrentType);
                UINT32 width = 0, height = 0;
                MFGetAttributeSize(pCurrentType, MF_MT_FRAME_SIZE, &width, &height);
                UINT32 stride = 0;
                pCurrentType->GetUINT32(MF_MT_DEFAULT_STRIDE, &stride);
                SafeRelease(&pCurrentType);
                
                if (width > 0 && height > 0) {
                    if (stride == 0) stride = width * 4;
                    long lStride = (long)stride;
                    if (lStride < 0) lStride = -lStride;

                    if (m_glWidget) {
                        m_glWidget->updateFrame(pData, width, height, lStride, true);
                    }
                }
                pBuffer->Unlock();
                pBuffer->Release();
            }
            pSample->Release();
        }
    }
    
    cleanupDecoder();
    m_playing = false;
    emit positionChanged(0);
    MFShutdown();

#else
    // Linux / Raspberry Pi (FFmpeg decoding loop)
    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();
    AVStream* videoStream = m_formatCtx->streams[m_videoStreamIdx];
    double timeBaseMs = av_q2d(videoStream->time_base) * 1000.0;

    std::vector<uint8_t> rgbaBuffer;
    int lastWidth = 0;
    int lastHeight = 0;

    while (!m_stop) {
        // --- 1. Seek handling ---
        if (m_seekRequest) {
            qint64 targetMs = m_seekTargetMs.load();
            int64_t seekTarget = static_cast<int64_t>(targetMs / timeBaseMs);
            if (av_seek_frame(m_formatCtx, m_videoStreamIdx, seekTarget, AVSEEK_FLAG_BACKWARD) >= 0) {
                avcodec_flush_buffers(m_codecCtx);
                isFirstFrame = true;
                totalPausedTime = 0;
                wasPaused = false;
            }
            m_seekRequest = false;
        }

        // --- 2. Pause handling ---
        if (m_pause) {
            if (!isFirstFrame) {
                if (!wasPaused) {
                    pauseClock.start();
                    wasPaused = true;
                }
                msleep(50);
                continue;
            }
        } else {
            if (wasPaused) {
                totalPausedTime += pauseClock.elapsed();
                pauseClock.invalidate();
                wasPaused = false;
            }
        }

        // --- 3. Read packet & decode frame ---
        int ret = av_read_frame(m_formatCtx, packet);
        if (ret < 0) {
            if (ret == AVERROR_EOF) {
                emit playbackFinished();
            }
            break;
        }

        if (packet->stream_index == m_videoStreamIdx) {
            if (avcodec_send_packet(m_codecCtx, packet) == 0) {
                while (avcodec_receive_frame(m_codecCtx, frame) == 0) {
                    int64_t pts = (frame->best_effort_timestamp != AV_NOPTS_VALUE)
                                  ? frame->best_effort_timestamp : frame->pts;
                    qint64 currentPtsMs = (pts != AV_NOPTS_VALUE)
                                          ? static_cast<qint64>(pts * timeBaseMs) : 0;

                    emit positionChanged(currentPtsMs);

                    // --- 4. Synchronization logic ---
                    if (isFirstFrame) {
                        clock.start();
                        currentRate = m_requestedRate.load();
                        anchorPts = currentPtsMs;
                        anchorRealTime = 0;
                        isFirstFrame = false;
                    } else if (!m_pause) {
                        qint64 currentRealTime = clock.elapsed() - totalPausedTime;
                        double reqRate = m_requestedRate.load();
                        if (reqRate != currentRate) {
                            currentRate = reqRate;
                            anchorPts = currentPtsMs;
                            anchorRealTime = currentRealTime;
                        }

                        qint64 timeSinceAnchor = currentRealTime - anchorRealTime;
                        qint64 expectedPts = anchorPts + static_cast<qint64>(timeSinceAnchor * currentRate);

                        qint64 diffPts = currentPtsMs - expectedPts;
                        if (diffPts > 0) {
                            qint64 waitMs = static_cast<qint64>(diffPts / currentRate);
                            if (waitMs > 0)
                                msleep(waitMs);
                        }
                    }

                    // --- 5. Convert to RGBA & transfer frame for rendering ---
                    int width = frame->width;
                    int height = frame->height;
                    if (width > 0 && height > 0) {
                        if (!m_swsCtx || width != lastWidth || height != lastHeight) {
                            if (m_swsCtx) sws_freeContext(m_swsCtx);
                            m_swsCtx = sws_getContext(
                                width, height, static_cast<AVPixelFormat>(frame->format),
                                width, height, AV_PIX_FMT_RGBA,
                                SWS_BILINEAR, nullptr, nullptr, nullptr
                            );
                            rgbaBuffer.resize(width * height * 4);
                            lastWidth = width;
                            lastHeight = height;
                        }

                        if (m_swsCtx) {
                            uint8_t* dest[4] = { rgbaBuffer.data(), nullptr, nullptr, nullptr };
                            int destLinesize[4] = { width * 4, 0, 0, 0 };
                            sws_scale(m_swsCtx, frame->data, frame->linesize, 0, height, dest, destLinesize);

                            if (m_glWidget) {
                                m_glWidget->updateFrame(rgbaBuffer.data(), width, height, width * 4, false);
                            }
                        }
                    }

                    if (m_stop || m_seekRequest) break;
                }
            }
        }
        av_packet_unref(packet);
    }

    av_frame_free(&frame);
    av_packet_free(&packet);
    cleanupDecoder();

    m_playing = false;
    emit positionChanged(0);
#endif
}
