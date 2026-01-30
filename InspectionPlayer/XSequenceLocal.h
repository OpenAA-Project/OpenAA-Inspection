/*
 * Copyright (C) 2023
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



//---------------------------------------------------------------------------

#ifndef XSequenceLocalH
#define XSequenceLocalH
//---------------------------------------------------------------------------
#include <QtGui>
#include <time.h>
#include "ThreadSequence.h"

//�O���[�o���֐��̒��`
void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl);

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d);
int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID);

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID, bool d);
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID);

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID);
void	_SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d);

void	_SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d);
double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID);

//�V�X�e�����W�X�^�N���X�̒��`
class   SeqControlParam : public QObject,public SeqLocalParam
{
    Q_OBJECT

	bool	*CaptureBeginFlag;
public:
    SeqControlParam(LayersBase *Base);
	virtual	~SeqControlParam(void);

	volatile    bool    RepeatMode;
	volatile    bool    StartInspection;
	volatile    bool    StartScanOnly;
	volatile    bool    ExecuteInspection;
	volatile    bool    ExecuteScanMaster;
	volatile    int		InspectionStrategy;
	volatile    bool	ReadyForScan;
	volatile    int		InspectionResult;		//1:OK 2:NG
	volatile    int		InspectionResultSub;	//1:OK 2:NG	3:TimeOver	4:MaxError	5:Halt
	volatile    int		InspectionFinalResult;	//1:OK 2:NG
	volatile    int		InspectionRemark;
	volatile    bool	PermitCapture;
	volatile    int		TactTimeMilisec;
	volatile    int		InspectionID;
	volatile    int		CaptureStartCounter;

	volatile    int		StageCode;
	volatile    int		CaptureMode;
	volatile    int		WorkLeft;
	volatile    int		WorkTop;
	volatile    int		WorkRight;
	volatile    int		WorkBottom;
	volatile    int		SystemStrategyNumb;

	volatile    int		ResultIndex;

    volatile    int		InspectStartTime;
    volatile    int		DoneInspectTime;
	volatile    int		CancelCapturing;
	volatile    int		InspactionStatus;
	volatile    int		RailWidth;			//0.1mm�P��
	volatile    int		ZHeight;			//1�ʂ��P��
	volatile    int		ErrorIndex;
	volatile    bool    FoundForm;
	volatile    int		CapturedFlag;
	volatile    bool    LoadedMasterData;
	volatile    bool    NowProcessing;
	volatile    bool    AllFinishInProcess;
	volatile    bool    DoneCapture;

	volatile    int		GeneralInfo0;
	volatile    int		GeneralInfo1;
	volatile    int		GeneralInfo2;
	volatile    int		GeneralInfo3;
	volatile    int		GeneralInfo4;
	volatile    int		GeneralInfo5;
	volatile    int		GeneralInfo6;
	volatile    int		GeneralInfo7;
	volatile    int		GeneralInfo8;
	volatile    int		GeneralInfo9;

	volatile	int		VRSReqMoterMove;
	volatile	int		VRSPosX;
	volatile	int		VRSPosY;
	volatile	int		VRSPosZ;

	volatile	int		VRSMoterPalusX;
	volatile	int		VRSMoterPalusY;
	volatile	int		VRSMoterPalusZ;

	volatile	bool	VRSMoterEnableX;
	volatile	bool	VRSMoterEnableY;
	volatile	bool	VRSMoterEnableZ;

	virtual	void	SetDataSpecialOperand(int ID, int d)	;
	virtual	int		GetDataSpecialOperand(int ID)			const;
	virtual	void	SetDataSpecialBitOperand(int ID, bool d);
	virtual	bool	GetDataSpecialBitOperand(int ID)		const;
	virtual	void	SetDataSpecialStringOperand(int ID, QString d);
	virtual	QString GetDataSpecialStringOperand(int ID)		const;

	volatile	bool	DoneControlGUI;
	volatile	bool	NotOutputResult;

	void	Captured(int Page);
	void	SetCaptureBegins(int page);
	bool	DoesCaptureBegin(void)	const;
	void	ClearCaptureBeginFlag(void);

signals:
	void	SignalButtonClick(QString formname ,QString controlname);
	void	SignalTableWidgetSelect(QString formname ,QString controlname,int row ,int col);
	void	SignalInputEdit(QString formname ,QString controlname,QString data);
	void	SignalInputValue(QString formname ,QString controlname,int data);
	void	SignalCheckDown(QString formname ,QString controlname);
	void	SignalCheckUp(QString formname ,QString controlname);
	void	SignalCheckToggle(QString formname ,QString controlname);
	void	SignalSearchForm(QString formname);
	void	SignalVisilize(QString formname ,QString controlname);
	void	SignalInvisilize(QString formname ,QString controlname);
	void	SignalEnable(QString formname ,QString controlname);
	void	SignalDisable(QString formname ,QString controlname);
	void	SignalButtonDown(QString formname ,QString controlname);

	void	SignalFinishMode(int mode);
	void	SignalInspectionNumber(int Number);
	void	SignalSetCurrentPhaseScanNumber(int d);
	void	SignalForceStrategicNumber(int d);
	void	SignalForceToChangeCurrentStrategicNumber(int n);
	void	SignalLightOn();
	void	SignalLightOff();
private slots:
	void	SlotButtonClick(QString formname ,QString controlname);
	void	SlotTableWidgetSelect(QString formname ,QString controlname,int row ,int col);
	void	SlotInputEdit(QString formname ,QString controlname,QString data);
	void	SlotInputValue(QString formname ,QString controlname,int data);
	void	SlotCheckDown(QString formname ,QString controlname);
	void	SlotCheckUp(QString formname ,QString controlname);
	void	SlotCheckToggle(QString formname ,QString controlname);
	void	SlotSearchForm(QString formname);
	void	SlotVisilize(QString formname ,QString controlname);
	void	SlotInvisilize(QString formname ,QString controlname);
	void	SlotEnable(QString formname ,QString controlname);
	void	SlotDisable(QString formname ,QString controlname);
	void	SlotInspectionNumber(int Number);
	void	SlotForceToChangeCurrentStrategicNumber(int n);
	void	SlotButtonDown(QString formname ,QString controlname);

	void	SlotFinishMode(int mode);
	void	SlotSetCurrentPhaseScanNumber(int d);
	void	SlotForceStrategicNumber(int d);
	void	SlotLightOn();
	void	SlotLightOff();
};

#endif