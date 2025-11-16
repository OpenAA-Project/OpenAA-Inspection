/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\XSequenceLocalExecuter.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XSequenceLocalH
#define XSequenceLocalH
//---------------------------------------------------------------------------
#include <QtGui>
#include <time.h>
#include "ThreadSequence.h"
class IntegrationPlayer;

//グローバル関数の定義
void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl);

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d);
int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID);

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID, bool d);
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID);

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID);
void	_SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d);

void	_SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d);
double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID);

//システムレジスタクラスの定義
class   SeqControlParam : public QObject,public SeqLocalParam
{
    Q_OBJECT

	IntegrationPlayer	*Parent;
public:
    SeqControlParam(IntegrationPlayer *p,LayersBase *Base);
	virtual	~SeqControlParam(void);

	volatile    bool	ReadyForScan;
	volatile    bool	PermitCapture;
	volatile    bool    DoneCapture;

	virtual	void	SetDataSpecialOperand(int ID, int d)			override;
	virtual	int		GetDataSpecialOperand(int ID)			const	override;
	virtual	void	SetDataSpecialBitOperand(int ID, bool d)		override;
	virtual	bool	GetDataSpecialBitOperand(int ID)		const	override;
	virtual	void	SetDataSpecialStringOperand(int ID, QString d)	override;
	virtual	QString GetDataSpecialStringOperand(int ID)		const	override;

signals:
	void	SignalLightOn();
	void	SignalLightOff();
	void	SignalMoveChildWindow(int n);
private slots:
	void	SlotLightOn();
	void	SlotLightOff();
	void	SlotMoveChildWindow(int n);
};



#endif
