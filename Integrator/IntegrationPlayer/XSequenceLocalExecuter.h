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
class IntegrationPlayer;

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