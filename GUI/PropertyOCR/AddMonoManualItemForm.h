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
#include "XServiceForLayers.h"
#include "XIntClass.h"

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

	int32		MinSize;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;

	void	SetInitial(void);

private:
	Ui::AddMonoManualItemFormClass ui;

private slots:

	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
    void on_pushButtonOK_2_clicked();
    void on_pushButtonCancel_2_clicked();
};

#endif // ADDMONOMANUALITEMFORM_H
