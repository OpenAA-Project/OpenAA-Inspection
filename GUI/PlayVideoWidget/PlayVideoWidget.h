#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "playvideowidget_global.h"
#include <QToolButton>
#include <QThread>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QAction>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class PlayVideoWidget;
class MMFVideoWidget;

class IMFAttributes			;
class IMFSourceReader			;
class IMFDXGIDeviceManager	;
class ID3D11Device			;
class ID3D11DeviceContext		;

class MediaVideoWidget : public QVideoWidget
{
	Q_OBJECT

	friend	class PlayVideoWidget;

public:
	MediaVideoWidget(PlayVideoWidget* player, QWidget* parent = 0);


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
	PlayVideoWidget		* m_player;
	QBasicTimer			m_timer;
	QAction				m_action;
};


// ---------------------------------------------------------
// MFDecoderThread: 動画デコードを行いウィジェットに生データを渡す
// ---------------------------------------------------------
class MFDecoderThread : public QThread
{
    Q_OBJECT

	friend	class MMFVideoWidget;

public:
    MFDecoderThread(MMFVideoWidget* widget, QObject *parent = nullptr);
    void setSource(const QString &path);
    void	stop();
	void	pause();
	void	restart();

	void	PreparePlay();

	void	seekTo(qint64 ms);
	void	setPlaybackRate(double rate);
signals:
    void durationChanged(qint64 totalMs);
    void positionChanged(qint64 currentMs);

protected:
    void run() override;

private:
    QString			m_filePath;
	bool			m_playing;
    bool			m_stop;
	bool			m_pause;
    MMFVideoWidget	*m_glWidget;

	bool	m_seekRequest = false;
    qint64	m_seekTargetMs = 0;
	double	m_requestedRate = 1.0;

	IMFAttributes			*pAttributes	;
	IMFSourceReader			*pReader		;
	IMFDXGIDeviceManager	*pDXGIManager	;
    ID3D11Device			*pD3D11Device	;
    ID3D11DeviceContext		*pContext		;
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

    // デコーダースレッドから呼ばれる: データをバックバッファにコピー
    void updateFrame(const uchar* data, int width, int height, int stride);

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

	qint64	duration();
	qint64	position();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
	void	SignalPositionChanged(qint64 currentMs);
private slots:
	void SlotPositionChanged(qint64 currentMs);

private:
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLTexture *m_texture = nullptr;
    
    QMutex m_mutex;
    std::vector<uchar> m_buffer; // Raw Pixel Data
    int m_videoWidth = 0;
    int m_videoHeight = 0;
    bool m_newFrameAvailable = false;

	qint64 totalDuration;
	qint64 CurrentMs;
};

class PlayVideoWidget : public GUIFormBase
{
	Q_OBJECT

	friend	class MediaVideoWidget;

	QMediaPlayer		*Player		;
	MediaVideoWidget	*VideoWidget;
	MMFVideoWidget		*glWidget	;
	QMediaPlayer::PlaybackState		LastState;
	qint64				LastDuration;
	qint64				LastPosition;
public:

	PlayVideoWidget(LayersBase* Base, QWidget* parent);
	~PlayVideoWidget();

	virtual	void	Prepare(void) 		override;
	virtual void	ReadyParam(void)	override;

	void setFile(const QString& text);
	virtual	void dragEnterEvent(QDragEnterEvent* e)	override;
	virtual	void dragMoveEvent(QDragMoveEvent* e)	override;
	virtual	void dropEvent(QDropEvent* e)			override;
	void handleDrop(QDropEvent* e);
	bool playPauseForDialog();
	qint64 openFile(QString& fileNames)	;

	virtual void	TransmitDirectly(GUIDirectMessage* packet)	override;

public slots:
	void rewind();
	void forward();
	void updateInfo();
	void updateTime();
	void finished();
	void playPause();
	void pause();
private slots:
	void	ResizeAction();
	void stateChanged(QMediaPlayer::PlaybackState);
private:
protected:
	//bool event(QEvent *e);
};
