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

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QAction>
#include <QBasicTimer>
#include <QThread>
#include <QMutex>
#include <vector>
#include <atomic>

#ifdef Q_OS_WIN
class IMFAttributes;
class IMFSourceReader;
class IMFDXGIDeviceManager;
class ID3D11Device;
class ID3D11DeviceContext;
#else
struct AVFormatContext;
struct AVCodecContext;
struct SwsContext;
#endif

class PlayVideoWidget;

class MediaVideoWidget : public QVideoWidget
{
	Q_OBJECT

	friend	class PlayVideoWidget;

public:
	MediaVideoWidget(PlayVideoWidget* player, QWidget* parent = nullptr);

public slots:
	// Over-riding non-virtual Phonon::VideoWidget slot
	void setFullScreen(bool);

signals:
	void fullScreenChanged(bool);

protected:
	virtual	void mouseDoubleClickEvent(QMouseEvent* e)	override;
	virtual	void keyPressEvent(QKeyEvent* e)			override;
	virtual	bool event(QEvent* e)						override;
	virtual	void timerEvent(QTimerEvent* e)				override;
	virtual	void dropEvent(QDropEvent* e)				override;
	virtual	void dragEnterEvent(QDragEnterEvent* e)		override;

private:
	PlayVideoWidget		*m_player;
	QBasicTimer			m_timer;
	QAction				m_action;
};


// ---------------------------------------------------------
// MFDecoderThread: Decodes video and passes raw pixel data to the widget
// (Windows: Media Foundation / Linux & Raspberry Pi: FFmpeg)
// ---------------------------------------------------------
class MFDecoderThread : public QThread
{
    Q_OBJECT

	friend	class MMFVideoWidget;

public:
    MFDecoderThread(MMFVideoWidget* widget, QObject *parent = nullptr);
    ~MFDecoderThread();

    void	setSource(const QString &path);
    void	stop();
	void	pause();
	void	restart();

	bool	PreparePlay();

	void	seekTo(qint64 ms);
	void	setPlaybackRate(double rate);

signals:
    void	durationChanged(qint64 totalMs);
    void	positionChanged(qint64 currentMs);
	void	playbackFinished();

protected:
    void run() override;

private:
    void cleanupDecoder();

    QString			m_filePath;
	std::atomic<bool>	m_playing;
    std::atomic<bool>	m_stop;
	std::atomic<bool>	m_pause;
    MMFVideoWidget	*m_glWidget;

	std::atomic<bool>	m_seekRequest;
    std::atomic<qint64>	m_seekTargetMs;
	std::atomic<double>	m_requestedRate;

#ifdef Q_OS_WIN
	IMFAttributes			*pAttributes	= nullptr;
	IMFSourceReader			*pReader		= nullptr;
	IMFDXGIDeviceManager	*pDXGIManager	= nullptr;
    ID3D11Device			*pD3D11Device	= nullptr;
    ID3D11DeviceContext		*pContext		= nullptr;
#else
	AVFormatContext			*m_formatCtx	= nullptr;
	AVCodecContext			*m_codecCtx		= nullptr;
	SwsContext				*m_swsCtx		= nullptr;
	int						m_videoStreamIdx = -1;
#endif
};

class MMFVideoWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

	friend	class MFDecoderThread;

	PlayVideoWidget	*Parent;
	MFDecoderThread Player;
public:
    MMFVideoWidget(PlayVideoWidget* player, QWidget *parent = nullptr);
    ~MMFVideoWidget();

    // Called from the decoder thread: copies frame data to the back buffer.
    // If isBGRA is true, channels are swizzled to RGBA during copy for OpenGL ES compatibility.
    void updateFrame(const uchar* data, int width, int height, int stride, bool isBGRA = false);

	void setSource(const QString &path);

	void	play();
	void	stop();
	void	pause();
	void	restart();

	bool	IsPlaying();
	bool	IsPausing();

	void	seek(qint64 ms);
    void	forward();
    void	rewind(qint64 ms = 5000);
	void	setPlaybackRate(double rate);
	double	playbackRate() const;

	qint64	duration();
	qint64	position();

protected:
	double GetVideoDuration(const QString& filename);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
	void	SignalPositionChanged(qint64 currentMs);
	void	SignalBlaybackFinished();

private slots:
	void	SlotPositionChanged(qint64 currentMs);
	void	SlotBlaybackFinished();

private:
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLTexture *m_texture = nullptr;
    
    QMutex m_mutex;
    std::vector<uchar> m_buffer; // Raw Pixel Data (RGBA 32bit)
    int m_videoWidth = 0;
    int m_videoHeight = 0;
    bool m_newFrameAvailable = false;

	qint64 totalDuration = 0;
	qint64 CurrentMs = 0;
};
