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

#include "playvideowidget_global.h"
#include <QToolButton>
#include <QThread>

#include <QAction>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

#include <QVideoWidget>
#include <QMediaPlayer>

class PlayVideoWidget;
class MMFVideoWidget;
class QMediaPlayer;
class MediaVideoWidget;

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

signals:
	void	SignalBlaybackFinished();

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
	void	SlotPlaybackFinished();

private:
protected:
	//bool event(QEvent *e);
};