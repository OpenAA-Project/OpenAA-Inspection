/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Naming\SetNamingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SETNAMINGFORM_H
#define SETNAMINGFORM_H

#include <QWidget>
#include "ui_SetNamingForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class SetNamingForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	SetNamingForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent = 0);
	~SetNamingForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::SetNamingFormClass ui;

	AlgorithmItemIndependentPack	*IData;
	QString		AreaName;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // SETNAMINGFORM_H
