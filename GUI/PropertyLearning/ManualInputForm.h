/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\ManualInputForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MANUALINPUTFORM_H
#define MANUALINPUTFORM_H

#include <QDialog>
#include "ui_ManualInputForm.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"

class ManualInputForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ManualInputForm(LayersBase *base, QWidget *parent);
	~ManualInputForm();

	bool		Ok;			//true:ãïïÒîrèú		false:ÇmÇfî≠ïÒ
    int32		NGLevel;	//0:Most important NG 1,2,3...lighter

private:
	Ui::ManualInputFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // MANUALINPUTFORM_H
