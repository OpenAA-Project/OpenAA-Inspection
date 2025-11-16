/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorChangeShiftForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef TRUECOLORCHANGESHIFTFORM_H
#define TRUECOLORCHANGESHIFTFORM_H

#include <QWidget>
#include "ui_TrueColorChangeShiftForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class TrueColorChangeShiftForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT
	QWidget *ImageParent;
public:
	TrueColorChangeShiftForm(LayersBase *Base,QWidget *parent = 0);
	~TrueColorChangeShiftForm();
	void	Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::TrueColorChangeShiftFormClass ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButton_clicked();
};

#endif // TRUECOLORCHANGESHIFTFORM_H
