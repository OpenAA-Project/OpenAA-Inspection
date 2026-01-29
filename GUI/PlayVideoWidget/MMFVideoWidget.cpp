#include <QLabel>
#include <QImage>
#include <QThread>
#include <QFileDialog>
#include <QDebug>
#include <QElapsedTimer>

// Windows / Media Foundation Headers
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>       
#include <mfreadwrite.h> 
//#include <mf.h>          
#include <d3d11.h>
#include <d3d11_4.h>
#include <propvarutil.h> // PROPVARIANT操作用

#include "PlayVideoWidget.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

// リンク設定
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "opengl32.lib")


template <class T> void SafeRelease(T **ppT) {
    if (*ppT) { (*ppT)->Release(); *ppT = NULL; }
}

MMFVideoWidget::MMFVideoWidget(PlayVideoWidget* player, QWidget *parent)
    : QOpenGLWidget(parent) ,Parent(player),Player(this)
{
    connect(&Player, &MFDecoderThread::durationChanged, [&](qint64 totalMs){
        totalDuration = totalMs;
    });
    connect(&Player, SIGNAL(positionChanged(qint64)), this, SLOT(SlotPositionChanged(qint64)));
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
    CurrentMs=currentMs;
    emit    SignalPositionChanged(currentMs);
}

bool	MMFVideoWidget::IsPlaying()
{
    if(Player.m_playing==true && Player.m_stop==false && Player.m_pause==false){
        return true;
    }
    return false;
}
bool	MMFVideoWidget::IsPausing()
{
    if(Player.m_playing==true && Player.m_stop==false && Player.m_pause==true){
        return true;
    }
    return false;
}

qint64	MMFVideoWidget::duration()
{
    return totalDuration;
}
qint64	MMFVideoWidget::position()
{
    return CurrentMs;
}
// 指定位置へシーク
void MMFVideoWidget::seek(qint64 ms)
{
    // 範囲チェック (0 ～ 総時間)
    if (ms < 0) ms = 0;
    if (totalDuration > 0 && ms > totalDuration) ms = totalDuration;

    // 現在位置を更新（即座にスライダー等を反応させたい場合）
    CurrentMs = ms;
    emit SignalPositionChanged(CurrentMs);

    // デコードスレッドへ要求
    Player.seekTo(ms);
}

void MMFVideoWidget::rewind(qint64 ms)
{
    //seek(CurrentMs - ms);
    seek(0);
}
void MMFVideoWidget::setPlaybackRate(double rate)
{
    // スレッドへ通知
    Player.setPlaybackRate(rate);
}

// 早送りボタン用: 2倍速に設定する
void MMFVideoWidget::forward()
{
    // 現在の速度を確認してトグル動作にする例
    // 既に2倍速なら1倍に戻す、そうでなければ2倍にする
    if (Player.m_requestedRate == 2.0) {
        setPlaybackRate(1.0);
    } else {
        setPlaybackRate(2.0);
    }
}


// デコーダースレッドから呼ばれる: データをバックバッファにコピー
void MMFVideoWidget::updateFrame(const uchar* data, int width, int height, int stride)
{
    QMutexLocker locker(&m_mutex);
    
    // バッファサイズ調整
    if (m_buffer.size() != width * height * 4) {
        m_buffer.resize(width * height * 4);
    }
    
    m_videoWidth = width;
    m_videoHeight = height;
    
    // 行ごとにコピー (Stride考慮)
    // OpenGLは下から上へ描画する場合があるが、ここではUV座標で調整するため上から下へコピー
    // データが密(packed)なら一括コピー可能だが、安全のため行コピー
    const uchar* src = data;
    uchar* dst = m_buffer.data();
    int lineBytes = width * 4; // RGBA 32bit
    
    if (stride == lineBytes) {
         memcpy(dst, src, m_buffer.size());
    } else {
         for (int y = 0; y < height; ++y) {
             memcpy(dst, src, lineBytes);
             src += stride;
             dst += lineBytes;
         }
    }
    
    m_newFrameAvailable = true;
    // UIスレッドで update() を呼ぶように依頼
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}
void MMFVideoWidget::setSource(const QString &path)
{
    Player.setSource(path);
}
void MMFVideoWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // シェーダーの作成
    m_program = new QOpenGLShaderProgram();
    
    // 頂点シェーダー: 単純な全画面Quad
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, R"(
        attribute vec4 position;
        attribute vec2 texCoord;
        varying vec2 vTexCoord;
        void main() {
            gl_Position = position;
            vTexCoord = texCoord;
        }
    )");
    
    // フラグメントシェーダー: テクスチャサンプリング
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, R"(
        uniform sampler2D texture;
        varying vec2 vTexCoord;
        void main() {
            // BGRA -> RGBA のスウィズルはglTexImage2Dのフォーマット指定で行うため、ここはそのまま
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
    // 背景をクリア (initializeGLで設定した黒色になります)
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 動画サイズが未確定、またはウィンドウの高さが0の場合は描画しない
    if (m_videoWidth == 0 || m_videoHeight == 0 || height() == 0) return;
    
    QMutexLocker locker(&m_mutex);
    
    if (!m_program) return;
    m_program->bind();
    
    // テクスチャの初期化または更新
    if (!m_texture || m_texture->width() != m_videoWidth || m_texture->height() != m_videoHeight) {
        if (m_texture) delete m_texture;
        m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        m_texture->setSize(m_videoWidth, m_videoHeight);
        m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
        m_texture->allocateStorage();
        m_texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    }
    
    // 新しいフレームがあればGPUへアップロード
    if (m_newFrameAvailable) {
        m_texture->setData(QOpenGLTexture::BGRA, QOpenGLTexture::UInt8, m_buffer.data());
        m_newFrameAvailable = false;
    }
    
    m_texture->bind();
    
    // ---------------------------------------------------------
    // アスペクト比計算 (ここが変更点です)
    // ---------------------------------------------------------
    float windowRatio = (float)width() / (float)height();
    float videoRatio = (float)m_videoWidth / (float)m_videoHeight;
    
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    
    if (windowRatio > videoRatio) {
        // ウィンドウの方が横長 -> 左右に黒帯を入れる (幅を縮小)
        scaleX = videoRatio / windowRatio;
    } else {
        // ウィンドウの方が縦長 -> 上下に黒帯を入れる (高さを縮小)
        scaleY = windowRatio / videoRatio;
    }

    // 計算したスケールを頂点座標に適用 (-1.0 ～ 1.0 の範囲を調整)
    float vertices[] = {
        -scaleX, -scaleY,  0.0f, 1.0f, // 左下
         scaleX, -scaleY,  1.0f, 1.0f, // 右下
        -scaleX,  scaleY,  0.0f, 0.0f, // 左上
         scaleX,  scaleY,  1.0f, 0.0f  // 右上
    };
    // ---------------------------------------------------------
    
    int posLoc = m_program->attributeLocation("position");
    int texLoc = m_program->attributeLocation("texCoord");
    
    m_program->enableAttributeArray(posLoc);
    m_program->enableAttributeArray(texLoc);
    
    // データサイズは変更なし (float 4つ * 4頂点)
    m_program->setAttributeArray(posLoc, GL_FLOAT, vertices, 2, 4 * sizeof(float));
    m_program->setAttributeArray(texLoc, GL_FLOAT, vertices + 2, 2, 4 * sizeof(float));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    m_program->disableAttributeArray(posLoc);
    m_program->disableAttributeArray(texLoc);
    
    m_texture->release();
    m_program->release();
}
void	MMFVideoWidget::play()
{
    if(IsPlaying()==true){
        Player.stop();
        Player.wait(2000);
    }
    Player.PreparePlay();
    Player.start();
}
void	MMFVideoWidget::stop()
{
    Player.stop();
}
void	MMFVideoWidget::pause()
{
    Player.pause();
}
void	MMFVideoWidget::restart()
{
    Player.restart();
}

//======================================================================
// ---------------------------------------------------------
// MFDecoderThread: 動画デコードを行いウィジェットに生データを渡す
// ---------------------------------------------------------

MFDecoderThread::MFDecoderThread(MMFVideoWidget* widget, QObject *parent) 
 : QThread(parent), m_glWidget(widget)
{
    m_pause=false;
    m_playing=false;
    m_seekRequest = false;
    m_seekTargetMs = 0;
    m_requestedRate = 1.0;

    pAttributes	=NULL;
    pReader		=NULL;
    pDXGIManager	=NULL;
    pD3D11Device	=NULL;
    pContext		=NULL;
}
    
void    MFDecoderThread::setSource(const QString &path) { m_filePath = path; }
void    MFDecoderThread::stop()     { m_stop = true; wait();    }
void    MFDecoderThread::pause()    {   m_pause=true;           }
void	MFDecoderThread::restart()  {   m_pause=false;          }

void    MFDecoderThread::seekTo(qint64 ms)
{
    m_seekTargetMs = ms;
    m_seekRequest = true;
}
void    MFDecoderThread::setPlaybackRate(double rate)
{
    if (rate > 0.0) {
        m_requestedRate = rate;
    }
}

void	MFDecoderThread::PreparePlay()
{
    if (m_filePath.isEmpty()) return;
    m_stop = false;
    m_pause=false;
    m_seekRequest = false; // 初期化
    m_requestedRate = 1.0; // デフォルト1倍速
   
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) return;
    
    // D3D11 Init
    pD3D11Device = nullptr;
    pContext = nullptr;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, 0, D3D11_SDK_VERSION, &pD3D11Device, NULL, &pContext);
    
    if (pD3D11Device) {
        ID3D11Multithread *pMultithread = nullptr;
        pD3D11Device->QueryInterface(__uuidof(ID3D11Multithread), (void**)&pMultithread);
        if (pMultithread) { pMultithread->SetMultithreadProtected(TRUE); pMultithread->Release(); }
    }
    
    pDXGIManager = nullptr;
    UINT token = 0;
    MFCreateDXGIDeviceManager(&token, &pDXGIManager);
    if(pDXGIManager && pD3D11Device) pDXGIManager->ResetDevice(pD3D11Device, token);
    
    pAttributes = nullptr;
    MFCreateAttributes(&pAttributes, 0);
    if(pDXGIManager) pAttributes->SetUnknown(MF_SOURCE_READER_D3D_MANAGER, pDXGIManager);
    pAttributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE);
    pAttributes->SetUINT32(MF_SOURCE_READER_ENABLE_ADVANCED_VIDEO_PROCESSING, TRUE);
    
    pReader = nullptr;
    hr = MFCreateSourceReaderFromURL(reinterpret_cast<LPCWSTR>(m_filePath.utf16()), pAttributes, &pReader);
    SafeRelease(&pAttributes);
    
    if (FAILED(hr)) {
        SafeRelease(&pDXGIManager); SafeRelease(&pContext); SafeRelease(&pD3D11Device);
        MFShutdown();
        return;
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
    
    m_playing=true;
}
void MFDecoderThread::run()
{
    HRESULT hr;

    QElapsedTimer clock;
    LONGLONG startPts = -1;
    bool    isFirstFrame = true;

    // 一時停止時間の管理用
    QElapsedTimer pauseClock;     // 一時停止中の時間を計るタイマー
    qint64 totalPausedTime = 0;   // 累積の一時停止時間 (ミリ秒)
    bool wasPaused = false;       // 直前までポーズしていたか   
    
    // 速度制御用: 「基準点」管理
    double currentRate = 1.0;
    qint64 anchorPts = 0;       // 速度変更時点の動画内時間 (PTS)
    qint64 anchorRealTime = 0;  // 速度変更時点の実時間 (Real Time)

    while (!m_stop) {
        // --- 1. シーク処理 ---
        if (m_seekRequest) {
            PROPVARIANT posVar;
            PropVariantInit(&posVar);
            posVar.vt = VT_I8;
            posVar.hVal.QuadPart = m_seekTargetMs * 10000; // to 100ns
            
            hr = pReader->SetCurrentPosition(GUID_NULL, posVar);
            PropVariantClear(&posVar);
            
            if (SUCCEEDED(hr)) {
                // シーク成功時は同期変数をリセット
                isFirstFrame = true;
                totalPausedTime = 0;
                wasPaused = false;
                // m_pauseがtrueでも、後続の処理で1フレームだけ描画させるために
                // isFirstFrame = true にしているのが重要
            }
            m_seekRequest = false;
        }

        // --- 2. ポーズ処理 ---
        if (m_pause) {
            // シーク直後などの1フレーム目以外は待機
            if (!isFirstFrame) {
                if (!wasPaused) {
                    pauseClock.start();
                    wasPaused = true;
                }
                msleep(50);
                continue; // 次のループへ
            }
        } else {
            // ポーズ解除
            if (wasPaused) {
                totalPausedTime += pauseClock.elapsed();
                pauseClock.invalidate();
                wasPaused = false;
            }
        }
 
        // --- 3. フレーム読み込み ---
        IMFSample *pSample = nullptr;
        DWORD flags = 0;
        LONGLONG llSampleTime = 0;
        
        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, &llSampleTime, &pSample);
        
        if (FAILED(hr)) {
            break; // エラー時は終了
        }

        // --- 動画の末尾に来た場合 ---
        if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
            // 自動的にポーズ状態に移行する
            //m_pause = true;
            
            // シグナルを出してUI側のボタン表記を「Play」に戻すなどの連携も可能
            // emit playbackFinished(); 
            
            break; // ループの先頭に戻る（先頭のポーズ待機ロジックに入ります）
        }

        if (pSample) {
            qint64 currentPtsMs = llSampleTime / 10000;
            emit positionChanged(currentPtsMs);
            
            // --- 4. 同期ロジック (速度可変対応) ---
            if (isFirstFrame) {
                clock.start();
                currentRate = m_requestedRate;
                anchorPts = currentPtsMs;
                anchorRealTime = 0;
                isFirstFrame = false;
                
                // もしポーズ中のシークなら、このフレームを描画した後に
                // 次回ループからポーズ待機に入る
            } else {
                if (!m_pause) {
                    qint64 currentRealTime = clock.elapsed() - totalPausedTime;
                    
                    // 速度変更検知 -> アンカー更新
                    if (m_requestedRate != currentRate) {
                        currentRate = m_requestedRate;
                        anchorPts = currentPtsMs;
                        anchorRealTime = currentRealTime;
                    }

                    // 基準点からの経過時間で同期
                    qint64 timeSinceAnchor = currentRealTime - anchorRealTime;
                    qint64 expectedPts = anchorPts + (qint64)(timeSinceAnchor * currentRate);
                    
                    qint64 diffPts = currentPtsMs - expectedPts;
                    if (diffPts > 0) {
                        qint64 waitMs = (qint64)(diffPts / currentRate);
                        if (waitMs > 0)
                            msleep(waitMs);
                    }
                }
            }
            
            // --- 5. 描画転送 ---
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
                // ヘルパー関数ではなくメンバ関数を使う(コンパイルエラー対策)
                pCurrentType->GetUINT32(MF_MT_DEFAULT_STRIDE, &stride);
                SafeRelease(&pCurrentType);
                
                if (width > 0 && height > 0) {
                    if (stride == 0) stride = width * 4;
                    long lStride = (long)stride;
                    if (lStride < 0) lStride = -lStride;

                    if (m_glWidget) {
                        m_glWidget->updateFrame(pData, width, height, lStride);
                    }
                }
                pBuffer->Unlock();
                pBuffer->Release();
            }
            pSample->Release();
        }
    }
    
    SafeRelease(&pReader);
    SafeRelease(&pDXGIManager);
    SafeRelease(&pContext);
    SafeRelease(&pD3D11Device);
    
    m_playing=false;
    emit positionChanged(0);

    MFShutdown();
}
