/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\SigmoidGraphForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SIGMOIDGRAPHFORM_H
#define SIGMOIDGRAPHFORM_H

#include <QDialog>
#include "ui_SigmoidGraphForm.h"

class mtLineGraph;
class RepairBase;

/********** シグモイド関数
			  1
	f(x)=━━━━━━	eの値を、1 < e < XXX と変化させてグラフを描く
		  1 + e^(-x)
**********/

class SigmoidGraphForm : public QDialog
{
	Q_OBJECT

public:
	SigmoidGraphForm(RepairBase *ParentClass,QWidget *parent);
	~SigmoidGraphForm();

private slots:
	void dsbVolumeChanged	(double value);
	void sbBrightnessChanged(int value);
	void pbOKClicked		();
	void pbCancelClicked	();

private:
	Ui::SigmoidGraphFormClass ui;

	RepairBase		*PClass;
	mtLineGraph		*SigGraph;
	int				wBrightness[256];
};

#endif // SIGMOIDGRAPHFORM_H
