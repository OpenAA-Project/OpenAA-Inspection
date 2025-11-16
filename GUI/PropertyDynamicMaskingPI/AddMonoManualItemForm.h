/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\AddMonoManualItemForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef ADDMONOMANUALITEMFORM_H
#define ADDMONOMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddMonoManualItemForm.h"
#include "XTypeDef.h"
#include "XDynamicMaskingPI.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include <QToolButton>

class AddMonoManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddMonoManualItemForm(LayersBase *base ,QWidget *parent);
	~AddMonoManualItemForm();

	int32		AbsLR, AbsHR;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	int32		AbsLR2, AbsHR2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	int32		MinSize;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;

	void	SetInitial(void);
	QList<QToolButton *>	LayerPickupButtons;
	IntList		AdaptedPickupLayers;

private:
	Ui::AddMonoManualItemFormClass ui;

private slots:
	void on_pushButtonOKDrawMask_2_clicked();
	void on_pushButtonCancelDrawMask_2_clicked();
	void on_radioButtonDrawMask_2_toggled(bool);
	void on_pushButtonCancelDrawMask_clicked();
	void on_pushButtonOKDrawMask_clicked();
	void on_radioButtonDrawMask_toggled(bool);
	void on_radioButtonPickupMask_toggled(bool);
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
    void on_toolButtonLayer_clicked();
};

#endif // ADDMONOMANUALITEMFORM_H
