/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\InputNamingNameForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTNAMINGNAMEFORM_H
#define INPUTNAMINGNAMEFORM_H

#include <QWidget>
#include "ui_InputNamingNameForm.h"
#include "XServiceForLayers.h"

class	NamingListForPacket;

class InputNamingNameForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

	NamingListForPacket *NamingItem;
public:
	InputNamingNameForm(LayersBase *base, QWidget *parent = 0);
	~InputNamingNameForm();
	bool	RetOK;

	void	SetNamingItem(NamingListForPacket *item);
	QString		InputedName;
	int			Row;
	int			Column;
signals:
	void	SignalClose();
private:
	Ui::InputNamingNameFormClass ui;

private slots:
	void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
};

#endif // INPUTNAMINGNAMEFORM_H
