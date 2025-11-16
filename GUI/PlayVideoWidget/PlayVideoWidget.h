#pragma once

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
class PlayVideoWidget : public GUIFormBase
{
	Q_OBJECT

	friend	class MediaVideoWidget;

	QMediaPlayer		*Player;
	MediaVideoWidget	*VideoWidget;
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
private slots:
	void	ResizeAction();
	void stateChanged(QMediaPlayer::PlaybackState);
private:
protected:
	//bool event(QEvent *e);
};

class	CmdVideo_Rewind : public GUIDirectMessage
{
public:
	CmdVideo_Rewind(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_Forward : public GUIDirectMessage
{
public:
	CmdVideo_Forward(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_Play : public GUIDirectMessage
{
public:
	CmdVideo_Play(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_LoadFile : public GUIDirectMessage
{
public:
	QString	FileName;
	qint64	TotalTime;

	CmdVideo_LoadFile(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_SetPlaybackRate : public GUIDirectMessage
{
public:
	double	PlaybackRate;

	CmdVideo_SetPlaybackRate(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_GetPlaybackRate : public GUIDirectMessage
{
public:
	double	PlaybackRate;

	CmdVideo_GetPlaybackRate(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_GetCurrentTime : public GUIDirectMessage
{
public:
	bool	IsPlaying;
	qint64	MaxTime;
	qint64	CurrentTime;

	CmdVideo_GetCurrentTime(LayersBase* base) :GUIDirectMessage(base) {}
};
