/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayStatus\DisplayStatusForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DISPLAYSTATUSFORM_H
#define DISPLAYSTATUSFORM_H

#include "XGUIFormBase.h"
#include "ui_DisplayStatusForm.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XStatusController.h"

class DisplayStatusForm : public GUIFormBase
{
	Q_OBJECT

public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DisplayStatusForm(LayersBase *Base ,QWidget *parent = 0);
	~DisplayStatusForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowComment(bool HTMLMode ,const QString &comment);
private:
	Ui::DisplayStatusFormClass ui;
private slots:
	void	SlotShowComment(bool HTMLMode ,const QStringList &comment);
	void	ResizeAction();
};


#endif // DISPLAYSTATUSFORM_H
