/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\ChangeShiftForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CHANGESHIFTFORM_H
#define CHANGESHIFTFORM_H

#include <QWidget>
#include "ui_ChangeShiftForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class ChangeShiftForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT
	QWidget *ImageParent;
public:
	ChangeShiftForm(LayersBase *Base,QWidget *parent = 0);
	~ChangeShiftForm();

	void	Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::ChangeShiftFormClass ui;

	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButton_clicked();
};

#endif // CHANGESHIFTFORM_H
