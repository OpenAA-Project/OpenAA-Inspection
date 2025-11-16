/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonWhichImage\WhichImageForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef WHICHIMAGEFORM_H
#define WHICHIMAGEFORM_H

#include "ui_WhichImageForm.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QStringList>

class WhichImageForm : public GUIFormBase
{
	Q_OBJECT

public:
	WhichImageForm(LayersBase *Base ,QWidget *parent = 0);
	~WhichImageForm();
	QStringList	RelatedPanels;

private:
	Ui::WhichImageFormClass ui;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void on_radioButtonLight_toggled(bool);
	void on_radioButtonDark_toggled(bool);
	void on_radioButtonTarget_toggled(bool);
	void on_radioButtonMaster_toggled(bool);
};

#endif // WHICHIMAGEFORM_H
