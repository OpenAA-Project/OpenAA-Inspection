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

#ifndef LIVECAMERAALGONTSC_H
#define LIVECAMERAALGONTSC_H

#include "livecameraalgontsc_global.h"

#include <QPushButton>
#include <QThread>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"

#include "CameraSettingForm.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class LiveCameraAlgoNTSC;

template<>
class PropertyBase<LiveCameraAlgoNTSC>;

typedef PropertyBase<LiveCameraAlgoNTSC> LiveCameraAlgoNTSCProperty;

namespace Ui{
class LiveCameraAlgoNTSCPropertyClass;
}
// �v���p�e�B�錾�I��


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

// �\������
// �J�����f�����\������
// todo signal
//  clicked(QPoint)    -> ����
//  setParameter(RGB)  -> RGB�o�C�A�X
class CameraView : public QLabel
{
	Q_OBJECT

public:
	CameraView(QWidget *parent, bool EditMode=false, int refleshTime=50);
	~CameraView();

public:
	void Resize(int width, int height);
	bool Open();
	bool Close();
	bool StartLive();
	bool StopLive();
	bool SingleShot();
	void Restart();
	void SetBrightness(int BArray[]);
	bool CreateImageBuffer(int width, int height);
	int *GetPlusRedPtr();
	int *GetPlusGreenPtr();
	int *GetPlusBluePtr();
	int GetPlusRed();
	int GetPlusGreen();
	int GetPlusBlue();
	void ShowSettingForm();
	bool GetCameraImage(QImage *image);

public slots:
	void GetCameraImageFast();
	void GetCameraImageModify();
	void Update();
	void StartUpdate();
	void StopUpdate();
	void SetRGB(int r, int g, int b);
	void SetWindow(QLabel *target);

private:
	QVector<QVector<unsigned char*> >	m_iData;
	QImage m_Image;
	ThreadView *m_Thread;
	int m_CapXLen, m_CapYLen;
	int m_BrightArray[256];
	int m_PlusRed, m_PlusGreen, m_PlusBlue;
	CameraSettingForm *m_SettingForm;

	bool m_EditMode;
	QLabel *m_paintWidget;
};


// GUI�{��
class LIVECAMERAALGONTSC_EXPORT LiveCameraAlgoNTSC : public GUIFormBase
{
	Q_OBJECT

public:
	LiveCameraAlgoNTSC(LayersBase *Base ,QWidget *parent);
	~LiveCameraAlgoNTSC(void);
	
	virtual void	Prepare(void)	override;

	bool	StartLive();//�Đ�
	bool	StopLive();//���~
	bool	SingleShot();//�X�i�b�v�V���b�g�B�e
	bool	Close();//�f�o�C�X���N���[�Y
	bool	Open();//�f�o�C�X���I�[�v��
	bool	Init();//������

	void	SetBrightness(int BArray[]);//�P�x�A���C���ݒ� 255
	void	SetPlusRGB(int Red,int Green,int Blue);//�eRGB�̃o�C�A�X�l�ݒ�

	int		GetWidth()	{	return(640);	}//�������T�C�Y
	int		GetHeight()	{	return(480);	}//�c�����T�C�Y

public slots:
	void	ResizeAction();//�E�B���h�E�T�C�Y�ύX���̓���
	void	SettingAction();
	void	RestartAction();//�J�����f�o�C�X�̍ăI�[�v��
	void	SnapAction();
	bool	Save();
	bool	Load();
	
public:
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void	contextMenuEvent(QContextMenuEvent * event )	override;
	virtual	void	mousePressEvent(QMouseEvent *)	override;

private:
	CameraView	m_CameraView;	//�J�����f���\���E�B�W�F�b�g(GUI�̃��C���E�B�W�F�b�g)
	int m_PlusRed,m_PlusGreen,m_PlusBlue;
	int m_BrightArray[256];
	//ThreadView *m_ThreadView;
	QWidget	*m_parent;
	QMenu	*m_ContextMenu;
	QAction	*m_SettingAction;
	QAction	*m_ResetAction;
	QAction *m_SnapAction;

/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	LiveCameraAlgoNTSCProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::LiveCameraAlgoNTSCPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const LiveCameraAlgoNTSCProperty &getProperty() const { return *m_property; };
	LiveCameraAlgoNTSCProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline LiveCameraAlgoNTSCProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(LiveCameraAlgoNTSCProperty *property){ m_property = property; };
	void setPropertyUi(Ui::LiveCameraAlgoNTSCPropertyClass *ui){ m_propertyUi = ui; };
	Ui::LiveCameraAlgoNTSCPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const LiveCameraAlgoNTSCProperty &property);
private:
	void setPropertyToUi(const LiveCameraAlgoNTSCProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(LiveCameraAlgoNTSCProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �I��-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // LIVECAMERAALGONTSC_H