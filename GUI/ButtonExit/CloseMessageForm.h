/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\CloseMessageForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef CLOSEMESSAGEFORM_H
#define CLOSEMESSAGEFORM_H

#include <QDialog>
#include "ui_CloseMessageForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"

class CloseMessageForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	GUIFormBase	*ParentGUI;
public:
	CloseMessageForm(LayersBase *Base ,GUIFormBase *parentGUI,QWidget *parent);
	~CloseMessageForm();

private:
	Ui::CloseMessageFormClass ui;

private slots:
	void on_pushButtonCalcen_clicked();
	void on_pushButtonCloseOne_clicked();
	void on_pushButtonCloseAll_clicked();
};

#endif // CLOSEMESSAGEFORM_H
