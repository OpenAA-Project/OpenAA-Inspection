/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentGroupForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTALIGNMENTGROUPFORM_H
#define INPUTALIGNMENTGROUPFORM_H

#include <QDialog>
#include "ui_InputAlignmentGroupForm.h"
#include "XServiceForLayers.h"

class InputAlignmentGroupForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentGroupForm(LayersBase *Base,QWidget *parent);
	~InputAlignmentGroupForm();
	
	int	Group;
private:
	Ui::InputAlignmentGroupFormClass ui;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // INPUTALIGNMENTGROUPFORM_H
