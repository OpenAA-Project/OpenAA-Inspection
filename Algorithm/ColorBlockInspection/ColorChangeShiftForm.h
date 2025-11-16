/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorChangeShiftForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COLORCHANGESHIFTFORM_H
#define COLORCHANGESHIFTFORM_H

#include <QWidget>
#include "ui_ColorChangeShiftForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class ColorChangeShiftForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT
	QWidget *ImageParent;
public:
	ColorChangeShiftForm(LayersBase *Base,QWidget *parent = 0);
	~ColorChangeShiftForm();

	void	Initial(QWidget *parent ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::ColorChangeShiftFormClass ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButton_clicked();
};

#endif // COLORCHANGESHIFTFORM_H
