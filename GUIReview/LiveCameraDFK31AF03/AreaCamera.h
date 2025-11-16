#pragma once

#include <QWidget>
#include <QLabel>
#include <QThread>

#include <tisudshl.h>

//#include "listener.h"

// 表示更新スレッド
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
