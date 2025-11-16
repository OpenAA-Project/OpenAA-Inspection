/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XSequenceRepairLocal.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XSequenceRepairLocalH
#define XSequenceRepairLocalH
//---------------------------------------------------------------------------
#include <QtGui>
#include <time.h>
#include "ThreadSequence.h"

void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl);

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d);
int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID);

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID, bool d);
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID);

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID);
void	_SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d);

void	_SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d);
double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID);

class   SeqControlParam : public QObject,public SeqLocalParam
{
    Q_OBJECT

  public:
    SeqControlParam(LayersBase *Base,QWidget *Form=0);

	volatile    int		MoveMode;
	volatile    int		ReviewResult;
	volatile    int		NGPieceNumbers;
	volatile    int		ErrorCount;
	volatile    int		ErrorIndex;
	volatile    int		ErrorCode;
	volatile    int		MacErrorCode;
	volatile    int		InspectionNumb;
	volatile    int		InspectionID;
	volatile    int		MasterID;		//Front side
	volatile    int		LotAutoCount;	
	volatile    int		Side;			//1 :Top side	2:Back side
	volatile    bool	PCStandBy;
	volatile    bool	ErrNextBS;
	volatile    bool	NGBS;
	volatile    bool	BackBS;
	volatile    bool	ReviewFinished;
	volatile    bool	UnloadDone;
	volatile    bool	UnloadCloseDone;
	volatile    bool	MaxOver;
	volatile    bool	MacEmergency;
	volatile    bool	SoftEmergency;
	volatile    bool	MacIDMismatch;
//	volatile    int		WaitTime;
	QString				LotName;

	volatile    bool    FoundForm;

	volatile int XPosition;
	volatile int YPosition;
	volatile int ZPosition;

	volatile int MoterRequire;

	// モーターステータス設定
	// 1の時設定可能と判断する
	volatile bool XMoterStatus;
	volatile bool YMoterStatus;
	volatile bool ZMoterStatus;

	// 読み込み専用のミリあたりのパルス数
	// 微動に関して使用する
	volatile int XMoterPulsePerMM;
	volatile int YMoterPulsePerMM;
	volatile int ZMoterPulsePerMM;

	virtual	void	SetDataSpecialOperand(int ID, int d);
	virtual	int		GetDataSpecialOperand(int ID);
	virtual	void	SetDataSpecialBitOperand(int ID, bool d);
	virtual	bool	GetDataSpecialBitOperand(int ID);
	virtual	void	SetDataSpecialStringOperand(int ID, QString d);
	virtual	QString GetDataSpecialStringOperand(int ID);

	volatile	bool	DoneControlGUI;

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
	void	SignalTableItemSearchSelect(QString formname ,QString controlname,int col,QString	searchstr);

	void	SignalFinishMode(int mode);

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
	void	SlotTableItemSearchSelect(QString formname ,QString controlname,int col,QString serachstr);

	void	SlotFinishMode(int mode);

private:
	QWidget	*RepairMainForm;
};

//extern  SeqControlParam *SeqControlParamData;

#endif
