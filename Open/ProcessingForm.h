/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\ProcessingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROCESSINGFORM_H
#define PROCESSINGFORM_H

#include <QWidget>
#include "ui_ProcessingForm.h"

class ProcessingForm : public QWidget
{
//	Q_OBJECT

public:
	ProcessingForm(QWidget *parent = 0);
	~ProcessingForm();

	void SetUpdate(int value);

private:
	Ui::ProcessingFormClass ui;
};

#endif // PROCESSINGFORM_H
