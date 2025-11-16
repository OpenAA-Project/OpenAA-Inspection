/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CameraSettingButton\SelectCameraDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTCAMERADIALOG_H
#define SELECTCAMERADIALOG_H

#include <QDialog>
#include "ui_SelectCameraDialog.h"
#include <QButtonGroup>
#include "XIntClass.h"
#include "XServiceForLayers.h"

class SelectCameraDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	QWidget			ScrollBack;
	QButtonGroup	CamButtons;

public:
	SelectCameraDialog(LayersBase *base ,QWidget *parent);
	~SelectCameraDialog();

	IntList			CamList;
	int	CamNo;

private:
	Ui::SelectCameraDialogClass ui;
private slots:
	void SlotButtonClicked ( int id );
};

#endif // SELECTCAMERADIALOG_H
