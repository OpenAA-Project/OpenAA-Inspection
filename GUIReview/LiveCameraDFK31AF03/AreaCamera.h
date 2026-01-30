/*
 * Copyright (C) 2022
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

#include <QWidget>
#include <QLabel>
#include <QThread>

#include <tisudshl.h>

//#include "listener.h"

// �\���X�V�X���b�h
class ThreadView : public QThread
{
	Q_OBJECT

public:
	ThreadView():m_flg_updateEnable(true),m_flg_stop(false),m_intervalTime(50){};
	ThreadView(int IntervalTime):m_flg_stop(false),m_intervalTime(IntervalTime){};

public:
	void setStopFlag(bool flg){ m_flg_stop = flg; };
	void setUpdateEnable(bool flg){ m_flg_updateEnable = flg; }
	void stop(){ m_flg_stop = true; };
	void setIntervalTime(int time){ m_intervalTime = time; };

protected:
	void run();

private:
	volatile bool m_flg_updateEnable;
	volatile bool m_flg_stop;
	int m_intervalTime;

signals:
	void update();
};

class AreaCamera : public QLabel
{
	Q_OBJECT

public:
	AreaCamera(QWidget *parent);
	~AreaCamera();

	bool StartLive(void);
	bool StopLive(void);
	bool SingleShot(void);
	bool GetCameraImage(void);
	bool GetCameraImage(QImage &image);
	bool Close(void);
	bool Open(void);
	bool ShowSettingDialog(void);
	void Resize(void);

protected:
	virtual	void mousePressEvent(QMouseEvent *)	override;
	virtual	void showEvent(QShowEvent *)		override;
	virtual	void hideEvent(QHideEvent *)		override;

public:
	void grapWindow(WId id);

public slots:
	bool init(void);
	void resetWindow();
	bool changePaintLabel(QLabel *label);
	void Update();
	void uninit(void);

signals:
	void clicked(QPointF pos);

private:
	DShowLib::Grabber m_cGrabber;
	DShowLib::FrameHandlerSink::tFHSPtr m_pSink;
	//DShowLib::CListener m_cListener;

public:
	void setEditMode(bool editMode){ m_isEditMode = editMode; };
	bool isInitialized() const { return m_isInitialized;};
	bool isEditMode() const { return m_isEditMode; };

private:
	void setInitialized(bool inited){ m_isInitialized = inited; };

private:
	QSize m_oldWindowSize;
	QSize m_outputImageSize;
	QLabel *m_paintWidget;
	ThreadView *m_thread;
	bool m_isEditMode;
	bool m_isInitialized;
};