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

#ifndef LIVECAMERAARTCAM035IMXWOM_H
#define LIVECAMERAARTCAM035IMXWOM_H

#include "LiveCameraArtCam_035IMX_WOM_global.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"

#include "CArtCamSdk.hpp"

#include "ui_LiveCameraArtCam_035IMX_WOMForm.h"

//#include "AreaCameraLib.h"


// �\���X�V�X���b�h
class ThreadView : public QThread
{
	Q_OBJECT

public:
	ThreadView():m_flg_updateEnable(true),m_flg_stop(false),m_intervalTime(50){};
	ThreadView(int IntervalTime, int StartIntervalTime=10000):m_flg_stop(false),m_intervalTime(IntervalTime),m_startIntervalTime(StartIntervalTime){};

public:
	void setStopFlag(bool flg){ m_flg_stop = flg; };
	void setUpdateEnable(bool flg){ m_flg_updateEnable = flg; }
	void stop(){ m_flg_stop = true; };
	void setIntervalTime(int time){ m_intervalTime = time; };

protected:
	void run(){
		bool oldUpdateEnable = m_flg_updateEnable;

		msleep(m_startIntervalTime);
		while(!m_flg_stop){
			if(m_flg_updateEnable){
				if(oldUpdateEnable==false){
					msleep(150);
				}
				emit update();
			}
			oldUpdateEnable = m_flg_updateEnable;
			msleep(m_intervalTime);
		}
	};

private:
	volatile bool m_flg_updateEnable;
	volatile bool m_flg_stop;
	int m_intervalTime;
	int m_startIntervalTime;

signals:
	void update();
};

// �e���v���[�gGUIReview
class LIVECAMERAARTCAM035IMXWOM_EXPORT LiveCameraArtCam_035IMX_WOM : public GUIFormBase
{
	Q_OBJECT

public:
	LiveCameraArtCam_035IMX_WOM(LayersBase *Base,QWidget *parent);
	~LiveCameraArtCam_035IMX_WOM();

public:
	// �X�V�v�����󂯎����Am_map���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void mousePressEvent(QMouseEvent *)		override;
	virtual	bool eventFilter(QObject *, QEvent *)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����

public slots:
	void ResizeAction(void);
	void Update();

private:
	void setUpdateEnable(bool enable){ updateEnableLocal; };
	bool isUpdateEnable() const { return updateEnableLocal; };

private:
	CArtCamSdk camSdk;
	QLabel *previewLabel;
	ThreadView *threadView;
	BYTE *cameraImageBuff;
	int cameraImageBuffSize;
	bool updateEnableLocal;

private:
	Ui::LiveCameraArtCam_035IMX_WOMClass ui;
};


#endif // LIVECAMERAARTCAM035IMXWOM_H